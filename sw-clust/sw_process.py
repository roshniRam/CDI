# The whole SW Process
from algorithm import sw
from model import segment
from model.nodes import Node, Nodes
from preprocessing import readingfiles
from statistics.statistics import Statistics


def intermediate_callback(current_labeling):
    print(current_labeling)


def SW_Process():
    [all_nodes, true_segment, class_num, np1_voc, vp_voc, np2_voc, np1_prob, vp_prob, np2_prob, class_prior_prob, transition_prob] = readingfiles.preprocessing('2008081519', 'preprocessing/model_segmenter.txt')
    print('Reading Files Finished')
    node_number = all_nodes.node_num
    edges = []
    for i in range(0, node_number-1):
        j = i + 1
        edges.append([i, j])

    stat = Statistics(all_nodes, class_num, np1_voc, vp_voc, np2_voc, np1_prob, vp_prob, np2_prob, class_prior_prob, transition_prob)
    sw.sample(node_number, edges, stat.calculate_Qe, stat.target_evaluation_func, intermediate_callback)


def main():
    SW_Process()


if __name__ == '__main__':
    main()