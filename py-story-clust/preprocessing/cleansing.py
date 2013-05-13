
import re
from nltk.corpus import wordnet as wn


def filter(word):
    """Filter punctuations out of word."""
    chars = [',', '!', '.', ';', '?', ':', '\'s', '/', '\\', ' ',
            '--', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9']

    return re.sub('[%s]' % ''.join(chars), '', word)


def clean(words):
    cleand_words = remove_stopwords(words)
    if len(cleand_words) > 0:
        cleand_words = [morphy(w) for w in cleand_words]
    return cleand_words


def remove_stopwords(words):
    """Return a list of words with stopwords removed."""
    stopwords_file = open('stopwords.txt', 'r')
    data = stopwords_file.read()
    stopwords = data.split(', ')
    stopwords.extend(['\n', ''])
    new_words = [filter(w) for w in words]
    new_words = [w for w in new_words if not w in stopwords]
    return new_words


def morphy(word):
    """Return the shortest morph of the given word."""
    result_set = []
    result_set.insert(0, wn.morphy(word, wn.NOUN))
    result_set.append(wn.morphy(word, wn.VERB))
    result_set.append(wn.morphy(word, wn.ADJ))
    result_set.append(wn.morphy(word, wn.ADV))
    result = None
    for r in result_set:
        if r is not None:
            if result is None:
                result = r
            else:
                if len(result) > len(r):
                    result = r
    if result is None:
        return word
    return result


def main():
    word = 'denied'
    word_morphied = morphy(word)
    print('The original word is ', word,
          ' and the morphied word is ', word_morphied)
    words = ['a', 'news', 'turn', 'walk', 'talk']
    words_rm_stopwords = remove_stopwords(words)
    print('Words: ', words, ' and the words after removing the stopwords: ', words_rm_stopwords)


if __name__ == '__main__':
    main()