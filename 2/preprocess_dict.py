import itertools

def all_cases(word):
    word = word.lower()
    results = []
    for case_tuple in itertools.product((0, 1), repeat=len(word)):
        new_word = ""
        for char, case in zip(word, case_tuple):
            new_word += char if case == 0 else char.upper()
        results.append(new_word)
    return results

with open('raw_dict.txt', 'r') as f:
    words = [w.rstrip().lower() for w in f if len(w) <= 6 and len(w) >= 2]

with open('dictionary.txt', 'w') as f:
    for word in words:
        for w in all_cases(word):
            f.write(w + '\n')
