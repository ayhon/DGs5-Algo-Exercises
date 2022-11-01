class UnionFind:
    def _init_(self, nb_vertices):
        self.nb_vertices = nb_vertices
        self.edges = []

    def add_edge(self, e):
        self.edges.append(e)

    def find(self, parent, i):
        return i if parent[i] == i else self.find(parent, parent[i])

    def union(self, parent, i, j):
        parent_i = self.find(parent, i);
        parent_j = self.find(parent, j);

        parent[parent_i] = parent[parent_j]

    def solve(self):
        # Create singleton list
        parent = list(range(n))

        # Sort the edges by happiness and color
        edges = sorted(self.edges, key=lambda e : (e[2], e[3]), reverse=True)

        print(edges)

        h_r = 0
        h_b = 0

        for u, v, h, c  in edges:
            parent_u = self.find(parent, u)
            parent_v = self.find(parent, v)

            if(parent_u != parent_v):
                # Update happiness
                if c == 'red':
                    h_r = h_r + h
                if c == 'blue':
                    h_b = h_b + h

                # Union of both
                self.union(parent, u, v)

        print(h_r)
        print(h_b)



# Get the inputs
n,m = map(int, input().split())

G = UnionFind(n)

# Get the edges
E = [[int(e[0])-1, int(e[1])-1, int(e[2]), e[3]] for e in [input().split() for i in range(m)]]

# Add each edges to the graph
for e in E:
    G.add_edge(e)

G.solve()
