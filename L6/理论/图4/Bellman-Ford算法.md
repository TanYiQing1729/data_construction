# Bellman-Ford算法
Bellman-Ford算法是一种用于计算单源最短路径的算法，适用于带有负权边的图。与数据结构课上学的Dijkstra算法不同，Bellman-Ford算法能够处理图中存在负权边的情况，但不能处理负权环。
## 算法原理
Bellman-Ford算法的基本思想是通过反复松弛图中的边来更新最短路径估计值。算法的主要步骤如下：
1. 初始化：将源点的距离设为$0$，其他所有顶点的距离设为无穷大。
2. 松弛边：对于图中的每一条边$(u, v)$和权重$w$，检查是否可以通过u到达v的路径更短。如果$d[u] + w < d[v]$，则更新$d[v] = d[u] + w$。
3. 重复步骤2，进行$|V| - 1$次迭代，其中$|V|$是图中顶点的数量。
4. 检测负权环：在完成$|V| - 1$次迭代后，再次检查所有边。如果仍然可以松弛任何一条边，说明图中存在负权环。
## 伪代码
```cpp
function BellmanFord(graph, source):
    // 初始化距离
    for each vertex v in graph:
        distance[v] = ∞
    distance[source] = 0

    // 松弛边 |V| - 1 次
    for i from 1 to |V| - 1:
        for each edge (u, v) with weight w in graph:
            if distance[u] + w < distance[v]:
                distance[v] = distance[u] + w

    // 检测负权环
    for each edge (u, v) with weight w in graph:
        if distance[u] + w < distance[v]:
            return "Graph contains a negative-weight cycle"

    return distance
```

## 时间复杂度
Bellman-Ford算法的时间复杂度为$O(V * E)$，其中$V$是图中的顶点数量，$E$是图中的边数量。由于需要进行$|V| - 1$次迭代，每次迭代需要检查所有的边，因此总的时间复杂度为$O(V * E)$。

## 进一步思考
实际上，并非图中有负环就一定用不了Bellman-Ford算法。如果负环不可达，或者我们只关心从源点到某些特定节点的最短路径，那么Bellman-Ford算法仍然可以正常工作。
可以把检测负权环的部分改成这样：
```cpp
    // 检测负权环
    for each edge (u, v) with weight w in graph:
        //如果有影响到最短路径的负权环
        if distance[u] + w < distance[v]:
            mark v as part of a negative-weight cycle
```
该方法说明Bellman-Ford算法也可以用于检测图中的负权环。

## 队列优化(SPFA)
Bellman-Ford算法可以通过使用队列来优化，称为SPFA（Shortest Path Faster Algorithm）。SPFA算法的基本思想是只对那些距离被更新的顶点进行松弛操作，从而减少不必要的计算。具体步骤如下：
1. 初始化：将源点的距离设为$0$，其他所有顶点的距离设为无穷大。将源点加入队列。
2. 当队列不为空时，执行以下操作：
   - 从队列中取出一个顶点$u$。
   - 对于每一条从$u$出发的边$(u, v)$，检查是否可以通过$u$到达$v$的路径更短。如果$d[u] + w < d[v]$，则更新$d[v] = d[u] + w$，并将$v$加入队列（如果$v$不在队列中）。
   - 重复上述步骤，直到队列为空。
SPFA算法在实际应用中通常比标准的Bellman-Ford算法更快，但在最坏情况下，其时间复杂度仍然是$O(V * E)$。

## DFS检测负权环
除了在松弛边的过程中检测负权环外，还可以使用DFS来检测负权环。具体步骤如下：
1. 对图中的每个顶点执行DFS。
2. 在DFS过程中，维护一个递归栈来跟踪当前路径上的顶点。
3. 如果在DFS过程中遇到一个已经在递归栈中的顶点，则说明存在负权环。
这种方法可以帮助我们更直观地理解负权环的存在与否。