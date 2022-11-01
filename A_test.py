from random import randint
from sys import argv

MAX_N = 500
MAX_C = 100
MAX_E = 100

if len(argv) < 1:
    print("Give me a number of test cases")
    exit()

for _ in range(int(argv[1])):
    n, c, e = randint(0,MAX_N), randint(0,MAX_C), randint(0,MAX_E)

    print(f"{n} {c} {e}")
    for _ in range(n):
        a,b = randint(0,100), randint(0,100)
        print(f"{a} {b}")
    print()
