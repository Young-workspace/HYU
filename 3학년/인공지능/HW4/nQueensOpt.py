from z3 import *
import time

def abs_z3(a):
    return If(a >=0, a, -a)

# Number of Queens
print("N: ")
N = int(input())

start = time.time()

# Variables
col = [Int("col_%d"%i) for i in range(N)]
s = Solver()

# Constraints
# domain
domain = [And(col[i] >= 0, col[i] < N) for i in range(N)]
s.add(domain)

# check whether same number in col
s.add(Distinct(col))

# check diagonal
for i in range(N-1):
    for j in range(i+1, N):
        s.add(abs_z3(col[i] - col[j]) != abs(i - j))

# If find answer print col
if s.check() == sat: 
    m = s.model()
    r = [m.evaluate(col[i]+1) for i in range(N)]
    print(r)

# Print elapsed time
print("elapsed time: ", time.time() - start, " sec")

