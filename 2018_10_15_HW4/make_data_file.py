import random

list = [random.randint(1, 100001) for _ in range(100000)]

w = open("./data.txt", "w", encoding='utf8')

w.write(' '.join(map(str, list)))
