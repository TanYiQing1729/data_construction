import random

def generate_complete_graph(num_nodes, filename):
    nodes = [f"N{i}" for i in range(num_nodes)]
    edges = []
    for i in range(num_nodes):
        for j in range(i + 1, num_nodes):
            weight = random.randint(10, 100)
            edges.append(f"{nodes[i]} {nodes[j]} {weight}")
    with open(filename, "w", encoding="utf-8") as f:
        f.write(f"{num_nodes} {len(edges)}\n")
        f.write(" ".join(nodes) + "\n")
        for edge in edges:
            f.write(edge + "\n")

sizes = [50]
for size in sizes:
    generate_complete_graph(size, f"sample_{size}.txt")
