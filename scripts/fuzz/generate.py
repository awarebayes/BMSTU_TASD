import random


def random_matrix(n, m):
    a = []
    for i in range(n):
        a.append([random.randint(-1000, 1000) for i in range(m)])
    return a


def print_mat(a):
    for i in range(len(a)):
        for j in range(len(a[0])):
            print(a[i][j], end=" ")
        print()


n = random.randint(2, 10)
m = random.randint(2, 10)

print(n, m)

a = []

for i in range(n):
    a.append([random.randint(-10, 10) for i in range(m)])

for i in range(n):
    for j in range(m):
        print(a[i][j], end=" ")
    print()

print(random.randint(0, 9))

"""
n = random.randint(2, 10)

a = random_matrix(n, n)

print(n)
print_mat(a)
"""
