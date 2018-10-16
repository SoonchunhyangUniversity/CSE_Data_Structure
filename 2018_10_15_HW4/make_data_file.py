import random

list = [random.randint(1, 100001) for _ in range(10000)]

w = open("./data.txt", "w", encoding='utf8')

w.write(' '.join(map(str, list)))
