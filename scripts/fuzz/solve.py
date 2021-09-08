"""
/*
 * Задача 2 лабы 3
 * Написал: Щербина Михаил
 * Вставить строку из чисел 100 после каждой строки, в которой количество элементов,
 * начинающихся на заданную цифру, равно количеству элементов, заканчивающихся
 * на эту же цифру. В ситуации, когда таких чисел не обнаружено вообще, строку из
 * сотен не вставлять. Цифра вводится в виде числа после ввода матрицы.
 */
"""
n, m = map(int, input().split())

a = []

for i in range(n):
    a.append(list(map(int, input().split())))

digit = input()

for i in a:
    n_starts = 0
    n_ends = 0
    for j in i:
        if j < 0:
            j *= -1
        if str(j)[0] == digit:
            n_starts += 1
        if str(j)[-1] == digit:
            n_ends += 1
    for j in i:
        print(j, end=" ")
    print()

    if n_starts == n_ends != 0:
        for j in i:
            print(100, end=" ")
        print()


"""
/*
 * 2.3
 * Задача 4 лабы 3
 * 0. Найти и вывести на экран минимальное нечётное
 * число, расположенное под главной диагональю. 
 * Написал: Щербина Михаил
 */
"""
"""
n = int(input())
a = []

for i in range(n):
    a.append(list(map(int, input().split())))

m = None

for i in range(n):
    for j in range(n):
        if i > j and a[i][j] % 2 == 1:
            if m is None:
                m = a[i][j]
            else:
                m = min(m, a[i][j])

if m is None:
    print('No min')
else:
    print(m)
"""
