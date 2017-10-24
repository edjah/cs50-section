# Project Euler Problem 82

from time import perf_counter

start_time = perf_counter()

with open("matrix.txt", "r") as f:
    mat = [[int(i) for i in line.split(',')] for line in f.readlines()]

N = len(mat)
d = [[[None, None, None] for i in range(N)] for j in range(N)]
for i in range(N):
    d[i][N - 1][0] = mat[i][N - 1]

def D(i, j, k):
    if i >= N or j >= N or i < 0 or j < 0:
        return float('inf')

    if d[i][j][k] != None:
        return d[i][j][k]

    if k == 0:
        d[i][j][k] = mat[i][j] + min(D(i + 1, j, 1), D(i, j + 1, 0), D(i - 1, j, 2))
    elif k == 1:
        d[i][j][k] = mat[i][j] + min(D(i + 1, j, 1), D(i, j + 1, 0))
    elif k == 2:
        d[i][j][k] = mat[i][j] + min(D(i, j + 1, 0), D(i - 1, j, 2))

    return d[i][j][k]

print(min(D(i, 0, 0) for i in range(N)))

end_time = perf_counter()
print(f'{1000 * (end_time - start_time):.3f} ms')
