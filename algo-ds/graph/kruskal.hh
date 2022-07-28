#include <vector>
#include <queue>

#include "union-find.hh"
#include "../data-structures/graph.hh"

template <typename Graph>
Graph kruskal(const Graph &g) {
    
    static_assert(Graph::isWeighted);

    struct Edge {
        size_t from;
        size_t to;
        long long cost;        
    };

    auto cmp = [](const Edge &e1, const Edge &e2) -> bool {
        return e1.cost > e2.cost;
    };

    UnionFind uf(g.getNodeCount());
    Graph result(g.getNodeCount());
    std::priority_queue<Edge, std::vector<Edge>, decltype(cmp)> pq(cmp);

    for(size_t node = 0; node < g.getNodeCount(); ++node) {
        for(auto &[neighbour, cost] : g.getNeighbours(node)) {
            pq.push({node, neighbour, cost});
        }
    }
    size_t edges = 0;
    while(!pq.empty() && edges < g.getNodeCount() - 1) {
        auto [node1, node2, cost] = pq.top();
        pq.pop();
        if(!uf.isConnected(node1, node2)) {
            edges++;
            result.addEdge(node1, node2, cost);
            uf.applyUnion(node1, node2);
        }
    }
    return result;
}

