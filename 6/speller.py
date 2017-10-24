dictionary = None

def load(file):
    global dictionary
    with open(file, 'r') as f:
        dictionary = set(w.strip() for w in f)
    return True

def check(word):
    return word in dictionary

def unload():
    return True

def size():
    return len(dictionary)

if __name__ == '__main__':
    load('dictionary.txt')
    with open('dictionary.txt', 'r') as f:
        for w in f:
            assert check(w.strip())
