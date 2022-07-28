#include <vector>
#include <queue>

#include "../data-structures/graph.hh"

template <typename Graph>
Graph prims(const Graph &g) {
    
    static_assert(Graph::isWeighted);

    struct Edge {
        size_t from;
        size_t to;
        long long cost;        
    };

    auto cmp = [](const Edge &e1, const Edge &e2) -> bool {
        return e1.cost > e2.cost;
    };

    Graph result(g.getNodeCount());
    std::priority_queue<Edge, std::vector<Edge>, decltype(cmp)> pq(cmp);
    std::vector<bool> added(g.getNodeCount(), false);

    for(auto &[neighbour, cost] : g.getNeighbours(0)) {
        pq.push({0, neighbour, cost});
    }
    added[0] = true;
    size_t edges = 0;
    while(!pq.empty() && edges < g.getNodeCount() - 1) {
        auto [node1, node2, cost] = pq.top();
        pq.pop();
        if(!added[node2]) {
            edges++;
            result.addEdge(node1, node2, cost);
            added[node2] = true;
            for(auto &[neighbour, ncost] : g.getNeighbours(node2)) {
                if(!added[neighbour]) {
                    pq.push({node2, neighbour, ncost});
                }
            }
        }
    }
    return result;
}

