## breadth_first_search
Given an undirected graph with 𝑛 vertices and 𝑚 edges and two vertices 𝑢 and 𝑣, compute the length
of a shortest path between 𝑢 and 𝑣 (that is, the minimum number of edges in a path from 𝑢 to 𝑣).

## bipartite
Given an undirected graph with 𝑛 vertices and 𝑚 edges, check whether it is bipartite.
### Solution idea: use breadth-first search.

## dijkstra
Given an directed graph with positive edge weights and with 𝑛 vertices and 𝑚 edges as well as two
vertices 𝑢 and 𝑣, compute the weight of a shortest path between 𝑢 and 𝑣 (that is, the minimum total
weight of a path from 𝑢 to 𝑣)

## negative_cycle
Given an directed graph with possibly negative edge weights and with 𝑛 vertices and 𝑚 edges, check
whether it contains a cycle of negative weight.
### Solution idea: Bellman-Ford algorithm.

## shortest_paths
Given an directed graph with possibly negative edge weights and with 𝑛 vertices and 𝑚 edges as well
as its vertex 𝑠, compute the length of shortest paths from 𝑠 to all other vertices of the graph.
### Solution idea: Bellman-Ford algorithm and breadth-first search.



