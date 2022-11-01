from random import randint, sample, choice
from sys import argv

MAX_ISLANDS = 100
MAX_PROPOSALS = 100
MAX_HAPPINESS = 100
TEAMS = ["red","blue"]

if len(argv) < 1:
    print("Give me a number of test cases")
    exit()

# def gen(team,items,islands):
#     poss = list(range(1,islands+1))
#     for _ in range(items):
#         try:
#             a,b = sample(poss, k=2)
#         except:
#             a, b = 1, 1

#         c = randint(1,MAX_HAPPINESS+1)
#         print(f"{a} {b} {c} {team}")

for _ in range(int(argv[1])):
    n = randint(1,MAX_ISLANDS+1)
    m = min(n*(n-1), randint(0,MAX_PROPOSALS))
    print(f"{n} {m}")

    edges = [(u,v) for u in range(1,n+1) for v in range(1,n+1) if u != v]
    bridges = sample(edges, k = m)

    for bridge in bridges:
            a,b = bridge
            team = choice(TEAMS)
            c = randint(1,MAX_HAPPINESS+1)
            print(f"{a} {b} {c} {team}")
    print()
