import sys
import logging
import pickle
from collections import defaultdict

sys.path.append('..')

import numpy as np
import mpmath
from scipy.stats import norm
import matplotlib.pyplot as plt

from model import *
from model import word_similarity
from model.classifier import Classifier
from model.probability import Distribution
from preprocessing import vocabulary
from algorithm import sw
from model import graph_cycle
from model.graph_cycle import graph_edge


class _Plotter(object):
    def __init__(self, sw_config, ground_truth=None):
        self.iterations = []
        self.energies = []
        self.temperatures = []
        self._sw_config = sw_config
        self.ground_truth = ground_truth
        self._ground_truth_val = None

        plt.ion()
        self.fig = plt.figure(figsize=(16, 10))
        #self.energy_plot = self.fig.add_subplot(211)
        #self.segment_plot = self.fig.add_subplot(212)
        self.energy_plot = self.fig.add_subplot(plt.subplot2grid((1, 3), (0, 0), colspan=2))
        self.temperature_plot = self.fig.add_subplot(plt.subplot2grid((1, 3), (0, 2)))

    def set_ground_truth(self, ground_truth):
        if ground_truth is not None:
            self.ground_truth = ground_truth
            self._ground_truth_val = self._sw_config.energy(self.ground_truth)

    def plot_callback(self, clustering, context):
        for cluster in clustering:
            for v in cluster:
                for doc_id in self._sw_config.vertex_distributions[v].document_ids:
                    print(self._sw_config.documents[doc_id].name)
            print('')

        self.iterations.append(context.iteration_counter)
        logging.debug('>>>')
        self.energies.append(self._sw_config.energy(clustering))
        logging.debug('<<<')
        self.temperatures.append(self._sw_config.cooling_schedule(context.iteration_counter))

        # energy plot
        self.energy_plot.clear()
        self.energy_plot.set_title('Energy')
        self.energy_plot.plot(self.iterations, self.energies)

        if self._ground_truth_val is not None:
            self.energy_plot.hold(True)
            self.energy_plot.plot([1, len(self.iterations)], [self._ground_truth_val]*2, 'r')

        # temperature plot
        self.temperature_plot.clear()
        self.temperature_plot.set_title('Temperature')
        self.temperature_plot.plot(self.iterations, self.temperatures)

        self.fig.canvas.draw()

    def save(self, filename):
        self.fig.savefig(filename, transparent=False, bbox_inches=None, pad_inches=0.1)


class SWConfig(object):
    """One shall inherit this class to give more specific configurations."""
    def __init__(self, graph_size, vertex_distributions, documents, vocabularies, level):
        self.graph_size = graph_size
        self.edges = []
        self.monitor_statistics = self.energy
        self.vertex_distributions = vertex_distributions
        self.level = level
        self.documents = documents
        self.vocabularies = vocabularies

        # cache
        self._likelihood_cache = dict()
        self._kl_cache = dict()

    def setup(self):
        self.edges = self._initialize_edges()
        logging.debug('Selected Edges {0}'.format(self.edges))
        logging.debug('# of vertex: {0}'.format(self.graph_size))
        logging.debug('# of edges: {0} [complete: {1}]'.format(len(self.edges), (self.graph_size*(self.graph_size-1)/2)))

    def _initialize_edges(self):
        """Generate the edges for the graph."""
        edges = []
        distance_all = []
        for i in range(0, self.graph_size-1):
            for j in range(i+1, self.graph_size):
                distance = 0.0
                distance += self._kl_divergence(i, j)
                distance += self._kl_divergence(j, i)
                distance /= 2
                #distance_tv /= NUM_WORD_TYPE
                #distance_all.append(distance)
                distance_all.append((i, j, distance))
        #distance_all_sort = sorted(distance_all, key=float)

        #distance_threshold = distance_all_sort[self.graph_size*2]
        #logging.debug('Distance Threshold {0}'.format(distance_threshold))
        #count = 0
        #for i in range(0, self.graph_size-1):
        #    for j in range(i+1, self.graph_size):
        #        if distance_all[count] < distance_threshold:
        #            edges.append((i, j))
        #        count += 1
        distance_all_sorted = sorted(distance_all, key=lambda graph_edge: graph_edge[2])
        edge_num = self.graph_size*2
        count = 0
        edges_tmp = []
        for e in distance_all_sorted:
            edges_tmp.append((e[0], e[1]))
            if graph_cycle.judge_cycle(edges_tmp):
                edges_tmp = list(edges)
                continue
            edges.append((e[0], e[1]))
            count += 1
            logging.debug('Add edge {0}: ({1}, {2})'.format(count, e[0], e[1]))
            if count >= edge_num:
                break
        return edges

    def _kl_key(self, s, t):
        return '{0}, {1}'.format(s, t)

    def _kl_divergence(self, s, t):
        kl_key = self._kl_key(s, t)
        if kl_key not in self._kl_cache:
            self._kl_cache[kl_key] = self.vertex_distributions[s].kl_divergence(self.vertex_distributions[t])
        return self._kl_cache[kl_key]

    def edge_prob_func(self, s, t, context):
        """Calculate edge probability based on KL divergence."""
        # Cache KL divergence between two vertexes.
        kl_pq = self._kl_divergence(s, t)
        kl_qp = self._kl_divergence(t, s)
        kl_sum = kl_pq + kl_qp

        #temperature = self.cooling_schedule(context.iteration_counter)
        edge_prob = mpmath.exp(-kl_sum/(2*500))
        return edge_prob

    def target_eval_func(self, clustering, context=None):
        temperature = self.cooling_schedule(context.iteration_counter)
        target = mpmath.exp(- self.energy(clustering) / temperature)
        return target

    def energy(self, clustering):
        energy = 0.0
        new_vertex_distribution = _combine_vertex_distributions_given_clustering(
            self.vertex_distributions, clustering)

        energy += -self._log_likelihood(clustering, new_vertex_distribution)

        # prior on time (for level 1 only)
        if self.level == 1:
            for cluster in clustering:
                energy += -mpmath.log(self._time_prior(cluster))

        # prior on cluster size: prefer large clusters
        #for cluster in clustering:
        #    energy += -mpmath.log(mpmath.exp(len(cluster)-len(self.vertex_distributions)))

        # prior on clustering complexity: prefer small number of clusters.
        energy += -30*mpmath.log(mpmath.exp(-len(clustering)))
        return energy

    def _log_likelihood(self, clustering, new_vertex_distribution, weights=[1]*NUM_WORD_TYPE):
        likelihood = 0.0
        for i, cluster in enumerate(clustering):
            # Cache the likelihood of cluster to reduce duplicate computation.
            current_cluster_likelihood = 0.0
            if new_vertex_distribution[i] in self._likelihood_cache:
                current_cluster_likelihood = self._likelihood_cache[new_vertex_distribution[i]]
            else:
                for doc in new_vertex_distribution[i].document_ids:
                    for word_type in WORD_TYPES:
                        for word_id in self.documents[doc].word_ids[word_type]:
                            current_cluster_likelihood += weights[word_type] * mpmath.log(new_vertex_distribution[i][word_type][word_id] + 1e-100)
                self._likelihood_cache[new_vertex_distribution[i]] = current_cluster_likelihood
            likelihood += current_cluster_likelihood
        likelihood /= sum(weights)
        #logging.debug('Likelihood {0}'.format(likelihood))
        return likelihood

    def _time_prior(self, cluster):
        time_series = []
        for doc_id in cluster:
            time_series.append(self.documents[doc_id].timestamp)
        time_series.sort()
        dif = 0.0
        for i in range(0, len(time_series)-1):
            date_dif = time_series[i+1] - time_series[i]
            dif_tmp = date_dif.days
            if dif_tmp > dif:
                dif = dif_tmp
        #dif /= (len(time_series))
        return mpmath.mpf(norm(1, 5).pdf(dif))

    def cooling_schedule(self, iteration_counter):
        starting_temperature = 1000
        period = 5
        step_size = 5

        temperature = starting_temperature - int(iteration_counter/period)*step_size
        if temperature <= 0:
            temperature = 0.1
        return temperature


class SWConfigLevel2(SWConfig):
    """SWConfig for level 2."""
    def __init__(self, graph_size, vertex_distributions, documents, vocabularies, level, classifier):
        super(SWConfigLevel2, self).__init__(graph_size, vertex_distributions, documents, vocabularies, level)
        self._similarity_cache = dict()
        self._within_similarity_cache = dict()
        self._between_similarity_cache = dict()
        self._classification_cache = dict()
        self._classifier = classifier
        self._precalculate_all_similarities()

    def _similarity_key(self, s, t):
        if s > t:
            s, t = t, s
        return '{0}, {1}'.format(s, t)

    def _precalculate_all_similarities(self):
        # try:
        #     # Load pre-calculated result
        #     with open('similarity_cache.dat') as similarity_file:
        #         self._similarity_cache = pickle.load(similarity_file)
        #         logging.debug('Similarity cache loaded.')
        #         return
        # except IOError:
        #     # Calculate and Dump
        #     pass

        types_of_interest = [WORD_TYPE_NP1, WORD_TYPE_NP2]
        words_all_types = []
        for s in range(0, self.graph_size):
            # get top 10 words
            top_words = self._get_top_words(self.vertex_distributions[s], 10, types_of_interest)
            words_all_types.append(top_words)

        for s in range(0, self.graph_size-1):
            for t in range(s+1, self.graph_size):
                key = self._similarity_key(s, t)
                distance_s_t = 0.0
                for word_type in types_of_interest:
                    distance_s_t += word_similarity.word_set_similarity(words_all_types[s][word_type], words_all_types[t][word_type])
                distance_s_t /= len(types_of_interest)
                self._similarity_cache[key] = distance_s_t
                logging.debug('Cache vertex similarity {0}, {1} = {2}'.format(s, t, distance_s_t))

        # Dump result.
        #with open('similarity_cache.dat', 'w') as similarity_file:
        #    pickle.dump(self._similarity_cache, similarity_file)
        #    logging.debug('Similarity cache saved.')

    def _min_similarity_within_cluster(self, cluster_vertex_set, cluster_distribution):
        cluster = list(cluster_vertex_set)
        if len(cluster) == 1:
            min_similarity_within_cluster = 1.0
        else:
            if cluster_distribution in self._within_similarity_cache:
                min_similarity_within_cluster = self._within_similarity_cache[cluster_distribution]
            else:
                # calculate pair wise similarity between vertexes
                min_within_similarity = 1.0
                for i in range(0, len(cluster) - 1):
                    for j in range(i+1, len(cluster)):
                        key = self._similarity_key(cluster[i], cluster[j])
                        assert(key in self._similarity_cache)
                        distance_i_j = self._similarity_cache[key]

                        if distance_i_j < min_within_similarity:
                            min_within_similarity = distance_i_j
                min_similarity_within_cluster = min_within_similarity
                logging.debug('Within min similarity {0} = {1}'.format(cluster_vertex_set, min_similarity_within_cluster))
                self._within_similarity_cache[cluster_distribution] = min_similarity_within_cluster
        return min_similarity_within_cluster

    def _between_similarity_key(self, cluster_i, cluster_j):
        list_i, list_j = list(cluster_i), list(cluster_j)
        list_i.sort()
        list_j.sort()
        if list_j > list_i:
            list_i, list_j = list_j, list_i
        return str(list_i) + str(list_j)

    def _max_similarity_between_clusters(self, cluster_set_i, cluster_set_j):
        cluster_i = list(cluster_set_i)
        cluster_j = list(cluster_set_j)
        between_key = self._between_similarity_key(cluster_set_i, cluster_set_j)
        if between_key in self._between_similarity_cache:
            max_similarity_between_clusters = self._between_similarity_cache[between_key]
        else:
            # Calculate the most similar words between two clusters (cluster_i and cluster_j)
            max_similarity = 0.0
            for v in range(0, len(cluster_i)):
                for u in range(0, len(cluster_j)):
                    key = self._similarity_key(cluster_i[v], cluster_j[u])
                    assert(key in self._similarity_cache)
                    distance_v_u = self._similarity_cache[key]
                    if distance_v_u > max_similarity:
                        max_similarity = distance_v_u
            max_similarity_between_clusters = max_similarity
            logging.debug('Between max similarity {0}, {1} = {2}'.format(cluster_set_i, cluster_set_j, max_similarity_between_clusters))
            self._between_similarity_cache[between_key] = max_similarity_between_clusters
        return max_similarity_between_clusters

    def energy(self, clustering):
        energy = mpmath.mpf(0.0)
        new_vertex_distributions = _combine_vertex_distributions_given_clustering(
            self.vertex_distributions, clustering)

        # likelihood
        likelihood_energy = -self._log_likelihood(clustering, new_vertex_distributions)

        # prior on similarity:
        # We prefer the cluster whose minimum similarity is large.
        # - the similarity of a pair of vertexes is measured by the similarity
        #   of top 10 words in the distribution. (measure each word type
        #   respectively and take average)
        intra_cluster_energy = mpmath.mpf(0.0)
        for cluster_id, cluster_vertex_set in enumerate(clustering):
            min_similarity_within_cluster = self._min_similarity_within_cluster(cluster_vertex_set, new_vertex_distributions[cluster_id])
            intra_cluster_energy += -mpmath.log(mpmath.exp(min_similarity_within_cluster - 1))

        # Between cluster similarity:
        #  - For each pair of clusters, we want to find the pair of words with maximum similarity
        #    and prefer this similarity value to be small.
        inter_cluster_energy = mpmath.mpf(0.0)
        if len(clustering) > 1:
            for i in range(0, len(clustering)-1):
                for j in range(i+1, len(clustering)):
                    max_similarity_between_clusters = self._max_similarity_between_clusters(clustering[i], clustering[j])
                    inter_cluster_energy += -mpmath.log(mpmath.exp(-max_similarity_between_clusters))

        # prior on clustering complexity: prefer small number of clusters.
        length_energy = -mpmath.log(mpmath.exp(-len(clustering)))

        # classification: prefer small number of categories.
        class_energy = 0.0
        if self._classifier is not None:
            num_classes = self._calculate_num_of_categories(clustering, new_vertex_distributions)
            class_energy = -mpmath.log(mpmath.exp(-(abs(num_classes-len(clustering)))))

        # classification confidence: maximize the classification confidence
        confidence_energy = 0.0
        for cluster_id, cluster_vertex_set in enumerate(clustering):
            (category, confidence) = self._predict_label(new_vertex_distributions[cluster_id])
            confidence_energy += -mpmath.log(confidence)

        energy += (0.5)*likelihood_energy + intra_cluster_energy + inter_cluster_energy + 30.0*length_energy + 20.0*class_energy + confidence_energy
        logging.debug('ENERGY: {0:12.6f}\t{1:12.6f}\t{2:12.6f}\t{3:12.6f}\t{4:12.6f}\t{5:12.6f}'.format(
            likelihood_energy.__float__(),
            intra_cluster_energy.__float__(),
            inter_cluster_energy.__float__(),
            length_energy.__float__(),
            class_energy.__float__(),
            confidence_energy.__float__()))
        return energy

    def _get_top_words(self, vertex_distribution, num_words, types_of_interest):
        # Select top 10 word ids
        top_word_ids_all_type = vertex_distribution.get_top_word_ids(10, types_of_interest)

        # Convert word id to words
        words_all_type = dict()
        for word_type in types_of_interest:
            words_all_type[word_type] = [self.vocabularies[word_type].get_word(wid) for wid in top_word_ids_all_type[word_type]]
        return words_all_type

    def _predict_label(self, vertex_distribution):
        if vertex_distribution not in self._classification_cache:
            # Convert document or vertex distribution to word list.
            word_list_all_type = defaultdict(list)
            for doc_id in vertex_distribution.document_ids:
                for word_type in WORD_TYPES:
                    words = [self.vocabularies[word_type].get_word(wid) for wid in self.documents[doc_id].word_ids[word_type]]
                    word_list_all_type[word_type].extend(words)

            # Classify and save result to cache.
            (category, confidence) = self._classifier.predict(word_list_all_type, WORD_TYPES)
            self._classification_cache[vertex_distribution] = (category, confidence)
        return self._classification_cache[vertex_distribution]

    def _calculate_num_of_categories(self, clustering, vertex_distributions):
        category_set = set()
        for i, cluster in enumerate(clustering):
            (category, confidence) = self._predict_label(vertex_distributions[i])
            category_set.add(category)
        return len(category_set)


def _combine_vertex_distributions_given_clustering(current_vertex_distributions, clustering):
    # create new vertex distribution
    new_vertex_distributions = []
    for cluster in clustering:
        vertex_distribution = _VertexDistribution()
        for v in cluster:
            vertex_distribution += current_vertex_distributions[v]
        new_vertex_distributions.append(vertex_distribution)
    return new_vertex_distributions


class TopicModel(object):
    def __init__(self, classifier_model_filename=None):
        self._has_initalized = False
        self.corpus = _Corpus()
        self.topic_tree = _Tree()
        self._classifier_model_file = classifier_model_filename
        pass

    def feed(self, original_documents, need_segmentation=False):
        if not self._has_initalized and need_segmentation:
            raise ValueError(
                'The topic model has to be initialized with segmented data.')

        if need_segmentation:
            # TODO: Do segmentation first if not segmented
            pass

        # Inference and attach to trees
        for original_doc in original_documents:
            document_feature = self.corpus.add_document(original_doc)
            if self._has_initalized:
                self._inference(document_feature)

        # Reform the tree if necessary.
        if (self._need_reform()):
            self._reform_by_multilevel_sw()
        self._has_initalized = True

        # TODO: save the current status of topic model.
        # Consider to use 'pickle' to serialize object.
        pass

    def _inference(self, document):
        """Inference and attach the new document to the current topic tree."""
        # WARINING / FIXME / CRITICAL:
        # (1) here we do not include OCR, because otherwise OCR words
        # will be added to the main word list, which will lead to redundant
        # adding when reform with SW later.
        # (2) the length of vertex distribution we obtained here is the same
        # as new vocabulary size. This may disagree with that of existing nodes
        # in the topic tree. Even more dangerously, the inference is done
        # sequentially, so documents fed in same round may have different
        # distribution length (keep increasing).

        # TENTATIVE SOLUTION:
        # Consider to create a buffer corpus, storing added documents
        # and the vertex distribution shall be created by projecting on the
        # vocabulary of main corpus. When the model is reformed by SW, buffer
        # corpus shall be combined into the main corpus.
        # HOWEVER, this may lead to another problem that every new documents of
        # few shared words with the main corpus may potentially create a new
        # category branch.

        # See also: (Related and affected functions / methods)
        #   _generate_initial_vertex_distributions()
        #   Corpus.get_dococument_distribution()
        #   Corpus.add_document()
        vertex_distribution = self._generate_document_vertex_distribution(
            document_feature, include_ocr=False)
        self.topic_tree.inference(document, vertex_distribution)
        pass

    def _reform_by_multilevel_sw(self):
        """Reform the whole tree by doing multi-level SW-Cuts."""
        need_next_level = True
        level_counter = 0

        # Create label list for printing labels.
        document_labels = [d.name for d in self.corpus.documents]

        # Initially, each document is a vertex.
        current_vertex_distributions = []
        # Initial clustering treat all vertex in the same cluster.
        current_clustering = [set(range(0, len(self.corpus)))]

        while need_next_level:
            level_counter += 1

            config = self._generate_next_sw_config(
                current_vertex_distributions, current_clustering, level_counter)
            plotter = _Plotter(config)

            if len(GROUND_TRUTHS) >= level_counter:
                ground_truth = GROUND_TRUTHS[level_counter - 1]
                plotter.set_ground_truth(ground_truth)

            # Add the very bottom level of tree.
            if (level_counter == 1):
                self._initialize_tree(config.vertex_distributions)
                self.topic_tree.print_hiearchy(labels=document_labels)

            # FIXME: This condition check is keep here temporarily for testing level 2.
            # Remove 'if-condition' and only keep 'else' part before launch.
            #if (level_counter == 1):
            #    current_clustering = ground_truth
            #else:
                # Clustering by SW.
            current_clustering = sw.sample(
                config.graph_size,
                config.edges,
                config.edge_prob_func,
                config.target_eval_func,
                intermediate_callback=plotter.plot_callback,
                initial_clustering=None,
                monitor_statistics=config.monitor_statistics)
            current_vertex_distributions = config.vertex_distributions

            # Save current clustering as a new level to the tree.
            self._add_level_to_tree(current_clustering, _combine_vertex_distributions_given_clustering(current_vertex_distributions, current_clustering))
            self.topic_tree.print_hiearchy(labels=document_labels, synthesize_title=True, vocabularies=self.corpus.vocabularies)
            plotter.save('multilevel_sw_{0}.png'.format(level_counter))

            # To have a classifier out of first level clustering
            #if level_counter == 1:
                #classifier = Classifier()
                #classifier.train_from_corpus(self.corpus, current_clustering)

            if level_counter >= 2:
                need_next_level = False

    def _generate_initial_vertex_distributions(self):
        # WARINING: generating vertex distribution with ocr_included will
        # cause ocr words to be added to main word lists.
        # If the model is further reformed with SW in a later stage,
        # this may lead to redundant ocr words.
        initial_vertex_distributions = []
        for document in self.corpus:
            vertex_distribution = self._generate_document_vertex_distribution(
                document, include_ocr=True)
            initial_vertex_distributions.append(vertex_distribution)
        return initial_vertex_distributions

    def _generate_document_vertex_distribution(self, document, include_ocr):
        vertex_distribution = _VertexDistribution()
        vertex_distribution.document_ids = [document.doc_id]
        for word_type in WORD_TYPES:
            vertex_distribution[word_type] = self.corpus.get_dococument_distribution(document.doc_id, word_type, include_ocr)
        return vertex_distribution

    def _generate_next_sw_config(self, current_vertex_distributions, current_clustering, level_counter):
        """Generate sw configuration for next run base on current clustering result."""
        if level_counter == 1:
            graph_size = len(self.corpus)
            next_vertex_distributions = self._generate_initial_vertex_distributions()
        else:
            graph_size = len(current_clustering)
            # create new vertex distribution
            next_vertex_distributions = _combine_vertex_distributions_given_clustering(
                current_vertex_distributions, current_clustering)

        if level_counter == 1:
            config = SWConfig(graph_size, vertex_distributions=next_vertex_distributions, documents=self.corpus.documents, vocabularies=self.corpus.vocabularies, level=level_counter)
        elif level_counter == 2:
            classifier = None
            if self._classifier_model_file is not None:
                classifier = Classifier(self._classifier_model_file)
            config = SWConfigLevel2(graph_size, vertex_distributions=next_vertex_distributions, documents=self.corpus.documents, vocabularies=self.corpus.vocabularies, level=level_counter, classifier=classifier)
        config.setup()
        return config

    def _need_reform(self):
        """Returns if the current topic_tree needs reforming."""
        # TODO: Add other criterion for judging whether reforming the tree
        #       is needed, like Dunn Index, Davies-Bouldin Index, etc.
        return True

    def _initialize_tree(self, vertex_distributions):
        """Initialize the tree by add the bottom level where each vertex is a document."""
        self.topic_tree.initialize(vertex_distributions)
        pass

    def _add_level_to_tree(self, clustering, vertex_distributions):
        """Add a level to tree."""
        self.topic_tree.add_level_on_top(clustering, vertex_distributions)
        pass


#
# Definitions for Topic Tree.
#
class _TreeNode(object):
    def __init__(self, vertex_distribution=None, children=None):
        if vertex_distribution is not None:
            self._vertex_distribution = vertex_distribution
        else:
            self._vertex_distribution = _VertexDistribution()

        if children is not None:
            self._children = children
        else:
            self._children = []

    #def __iter__(self):
    #    return iter(self._children)

    def children(self):
        return self._children

    def level(self):
        """The level count from bottom. Terminal node has level 0."""
        if len(self._children) == 0:
            return 0
        else:
            return self._children[0].level() + 1

    def log_likelihood(self, document):
        log_likelihood = mpmath.mpf(0.0)
        for word_type in WORD_TYPES:
            for word_id in document.word_ids[word_type]:
                if word_id in self._vertex_distribution[word_type]:
                    log_likelihood += mpmath.log(self._vertex_distribution[word_type][word_id] + 1e-100)
        return log_likelihood

    def add_child(self, node):
        self._children.append(node)
        # FIXME: need to merge distribution after add a child?

    def get_child(self, index):
        return self._children[index]

    def is_terminal(self):
        return (len(self._children) == 0)

    def synthesize_title(self, vocabularies):
        # select top words from NP1 and NP2 respectively.
        top_word_ids = self._vertex_distribution.get_top_word_ids(10, [WORD_TYPE_NP1, WORD_TYPE_NP2])
        np1_words = [vocabularies[WORD_TYPE_NP1].get_word(wid) for wid in top_word_ids[WORD_TYPE_NP1]]
        np2_words = [vocabularies[WORD_TYPE_NP2].get_word(wid) for wid in top_word_ids[WORD_TYPE_NP2]]

        # Select the overlap words of NP1 and NP2 as title.
        # If no overlap, we use top 3 words from NP1 combined with top 3 words
        # from NP2.
        union = [w for w in np1_words if w in np2_words]
        if len(union) > 0:
            more = []
            if len(union) < 3:
                more.extend([w for w in np1_words[0:3] if w not in union])
                more.extend([w for w in np2_words[0:3] if w not in union])
            union.extend(more)
            title = ' '.join(union)
        else:
            keep = np1_words[0:3]
            keep.extend(np2_words[0:3])
            title = ' '.join(keep)
        return title

    def get_num_children(self):
        return len(self._children)


class _Tree(object):
    """A Tree structure."""
    def __init__(self):
        self._root = _TreeNode()
        self._height = 0

    def _add_to_root(self, node):
        """Add a node to the root."""
        self._root.add_child(node)

    def initialize(self, vertex_distributions):
        """Initialize by adding a bottom level."""
        assert(self._height == 0)
        for vertex_distribution in vertex_distributions:
            terminal_node = _TreeNode(vertex_distribution)
            self._add_to_root(terminal_node)
        self._height += 1

    def add_level_on_top(self, clustering, vertex_distributions):
        """Add a new level on the top of the tree."""
        # e.g. clustering = [{1,2,3}, {4,5}, {5,6,7}]
        assert(self._height > 0)
        new_root = _TreeNode()
        for (clust_id, cluster) in enumerate(clustering):
            new_parent_node = _TreeNode(vertex_distributions[clust_id])
            for vertex_index in cluster:
                child = self._root.get_child(vertex_index)
                new_parent_node.add_child(child)
            new_root.add_child(new_parent_node)
        self._root = new_root
        self._height += 1

    def inference(self, document, vertex_distribution):
        assert(self._height == 3)

        # TODO: determine a threshold to do inference
        cluster_threshold = 100.0
        category_threshold = 50.0

        # classify as category and get all cluster nodes.
        cluster_nodes = []
        (max_category_node, max_cateory_likelihood) = self._find_max_likelihood(
            root.children(), document, children_list=cluster_nodes)
        # classify into clusters.
        (max_cluster_node, max_cluster_likelihood) = self._find_max_likelihood(
            cluster_nodes, document)

        new_document_node = _TreeNode(vertex_distribution)
        if max_cluster_likelihood > cluster_threshold:
            # if max_cluster_likelihood is greater than a threshold,
            # we add this document into the cluster.
            max_cluster_node.add_child(new_document_node)
        elif max_cateory_likelihood > category_threshold:
            # add document into the max_category_node,
            # this document will create a new cluster containing its own.
            new_cluster_node = _TreeNode(vertex_distribution)
            new_cluster_node.add_child(new_document_node)
            max_category_node.add_child(new_cluster_node)
        else:
            # add document to the root node,
            # create a category and cluster containing its own.
            new_category_node = _TreeNode(vertex_distribution)
            new_cluster_node = _TreeNode(vertex_distribution)
            new_cluster_node.add_child(new_document_node)
            new_category_node.add_child(new_cluster_node)
            self._add_to_root(new_category_node)

    def _find_max_likelihood(self, nodes, document, children_list=None):
        max_likelihood = 0.0
        max_node = None
        for node in nodes:
            if children_list is not None:
                children_list.extend(node.children())
            log_likelihood = node.log_likelihood(document)
            if log_likelihood > max_likelihood:
                max_likelihood = log_likelihood
                max_node = node
        return (max_node, max_likelihood)

    def print_hiearchy(self, labels=None, synthesize_title=False, vocabularies=None):
        self._print_hiearchy_recursive(self._root, labels=labels, synthesize_title=synthesize_title, vocabularies=vocabularies)

    def _print_hiearchy_recursive(self, root, labels=None, level_indents=0, synthesize_title=False, vocabularies=None):
        if synthesize_title:
            assert(vocabularies is not None)
            print('{0}+ {1}'.format(level_indents*'|  ', root.synthesize_title(vocabularies)))
        for child_node in root.children():
            if not child_node.is_terminal():
                # Have next level.
                self._print_hiearchy_recursive(
                    child_node, labels=labels, level_indents=level_indents+1, synthesize_title=synthesize_title, vocabularies=vocabularies)
            else:
                # Terminal node is a document.
                assert(len(child_node._vertex_distribution.document_ids) == 1)
                doc_id = child_node._vertex_distribution.document_ids[0]
                label_to_print = doc_id
                if labels is not None:
                    label_to_print = labels[doc_id]
                print('{0}{1}{2}'.format((level_indents)*'|  ', '|- ', label_to_print))

    def print_hiearchy_json(self, fw, labels=None, synthesize_title=False, vocabularies=None):
        self._print_hiearchy_recursive_json(fw, root=self._root, labels=labels, synthesize_title=synthesize_title, vocabularies=vocabularies)

    def _print_hiearchy_recursive_json(self, fw, root, labels=None, level_indents=0, synthesize_title=False, vocabularies=None):
        fw.write(level_indents*'  '+'{')
        if synthesize_title:
            assert(vocabularies is not None)
            fw.write((level_indents+1)*'  ' + '"name": "{0}",'.format(root.synthesize_title(vocabularies)))

        else:
            fw.write((level_indents+1)*'  ' + '"name": "{0}",'.format(branch_id))
            #print('{0}+'.format(level_indents*'|  '))

        if root.get_num_children() > 0:
            fw.write((level_indents+1)*'  ' + '"children": [')
            for cid, child_node in enumerate(root.children()):
                if not child_node.is_terminal():
                    # Have next level
                    self._print_hiearchy_recursive_json(
                        fw, node, labels=labels, level_indents=level_indents+1, synthesize_title=synthesize_title, vocabularies=vocabularies)
                    if cid != root.get_num_children() - 1:
                        fw.write((level_indents+1)*'  ' + ',')
                else:
                    # Terminal node is a document.
                    assert(len(child_node._vertex_distribution.document_ids) == 1)
                    doc_id = child_node._vertex_distribution.document_ids[0]
                    label_to_print = doc_id
                    if labels is not None:
                        label_to_print = labels[doc_id]
                    append = ''
                    if cid != root.get_num_children() - 1:
                        append = ','
                    fw.write((level_indents+1)*'  ' + '{' + '"name": "{0}"'.format((label_to_print)) + '}' + append)
            fw.write((level_indents+1)*'  ' + ']')
        fw.write(level_indents*'  '+'}')


#
# Definitions for corpus and document.
#
class _Corpus(object):
    """A Corpus object includes all documents' feature and corpus vocabulary.
    These are sufficient information to recover the original document."""
    def __init__(self):
        self.documents = []
        self.vocabularies = {
            WORD_TYPE_NP1: vocabulary.Vocabulary(),
            WORD_TYPE_VP: vocabulary.Vocabulary(),
            WORD_TYPE_NP2: vocabulary.Vocabulary()}

    def __len__(self):
        return len(self.documents)

    def __iter__(self):
        return iter(self.documents)

    def __getitem__(self, document_id):
        return self.documents[document_id]

    def get_dococument_distribution(self, doc_id, word_type, include_ocr=False):
        histogram = np.zeros(self.vocabulary_size(word_type))
        for word_id in self.documents[doc_id].word_ids[word_type]:
            histogram[word_id] += 1
        # Include OCR.
        if include_ocr:
            for ocr_word in self.documents[doc_id].ocr_words:
                if ocr_word in self.vocabularies[word_type]:
                    ocr_word_id = self.vocabularies[word_type].get_word_index(ocr_word)
                    histogram[ocr_word_id] += 1
                    # WARINING / FIXME:
                    # Here the document content is extended by ocr words.
                    # If this method is called multiple times, ocr words
                    # will be added to the document redundantly.
                    self.documents[doc_id].word_ids[word_type].append(ocr_word_id)

        return Distribution(histogram)

    def add_document(self, original_doc):
        """Convert the document to feature and save into document list.
        Adding a document containing words not seen before will also extend the vocabulary of the corpus."""
        # WARINING: When a new document is added to the corpus,
        # the vocabulary may grow due to the words not seen before.
        document_feature = self._convert_doc_to_feature(original_doc)
        self.documents.append(document_feature)
        document_feature.doc_id = len(self.documents)-1
        return document_feature

    def _convert_doc_to_feature(self, original_doc):
        document_feature = _DocumentFeature(original_doc.filename, original_doc.timestamp)
        document_feature.ocr_words = original_doc.ocr_words

        for word_type in WORD_TYPES:
            document_feature.word_ids[word_type] = self._convert_words_to_ids(word_type, original_doc.word_lists[word_type])
        return document_feature

    def _convert_words_to_ids(self, word_type, word_list):
        assert(word_type in WORD_TYPES)
        ids = []
        for word in word_list:
            # If word is in current vocabulary, we directly look up the word_id.
            # Otherwise, we add this word to the vocabulary and then look up.
            if word not in self.vocabularies[word_type]:
                self.vocabularies[word_type].add(word)
            word_id = self.vocabularies[word_type].get_word_index(word)
            ids.append(word_id)
        return ids

    def get_document_name(self, doc_id):
        return self.documents[doc_id].name

    def vocabulary_size(self, word_type):
        assert(word_type in WORD_TYPES)
        return self.vocabularies[word_type].size()


class _DocumentFeature(object):
    def __init__(
            self,
            name,
            timestamp,
            np1_word_ids=None,
            vp_word_ids=None,
            np2_word_ids=None,
            ocr_words=None):
        self.name = name
        self.timestamp = timestamp
        self.word_ids = {
            WORD_TYPE_NP1: np1_word_ids,
            WORD_TYPE_VP: vp_word_ids,
            WORD_TYPE_NP2: np2_word_ids}
        self.ocr_words = ocr_words
        self.doc_id = None


#
# Definitions of VertexDistribution and Distribution.
#
class _VertexDistribution:
    """A vertex distribution can be viewed as a AND node consisting of
    three Distribution objects.
    Tips:
        Object of this class has been made hashable.
        Add operation ('+' operator) is supported.
        TV-norm and KL-divergence calculation will be averaged by three."""
    def __init__(self):
        self.distributions = dict()
        for word_type in WORD_TYPES:
            self.distributions[word_type] = None
        self.document_ids = []

    def __getitem__(self, word_type):
        assert(word_type in WORD_TYPES)
        return self.distributions[word_type]

    def __setitem__(self, word_type, distribution):
        assert(word_type in WORD_TYPES)
        self.distributions[word_type] = distribution

    def __add__(self, other):
        result = _VertexDistribution()
        for word_type in WORD_TYPES:
            if self.distributions[word_type] is None:
                result.distributions[word_type] = other.distributions[word_type]
            else:
                result.distributions[word_type] = self.distributions[word_type] + other.distributions[word_type]
        result.document_ids = self.document_ids
        result.document_ids.extend(other.document_ids)
        result.document_ids.sort()
        return result

    def __radd__(self, other):
        return self.__add__(other)

    def __iadd__(self, other):
        return self.__add__(other)

    def __hash__(self):
        """Make it hashable. The key is the the string format of sorted document id list.
        key =  str(document_ids)
        e.g. '[10, 11, 12]' is the key for [10, 11, 12]
        """
        return hash(str(self.document_ids))

    def __eq__(self, other):
        return hash(self) == hash(other)

    def kl_divergence(self, other):
        kl = 0.0
        for word_type in WORD_TYPES:
            dist_i = self[word_type]
            dist_j = other[word_type]
            kl += dist_i.kl_divergence(dist_j)
        kl /= NUM_WORD_TYPE
        return kl

    def tv_norm(self, other):
        distance = 0.0
        for word_type in WORD_TYPES:
            dist_i = self[word_type]
            dist_j = other[word_type]
            distance += dist_i.tv_norm(dist_j)
        distance /= NUM_WORD_TYPE
        return distance

    def get_top_word_ids(self, num_words, word_types):
        result_dict = dict()
        for word_type in word_types:
            if self.distributions[word_type] is None:
                result_dict[word_type] = []
            else:
                result_dict[word_type] = self.distributions[word_type].get_top_word_ids(num_words)
        return result_dict
