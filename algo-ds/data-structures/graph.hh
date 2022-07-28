#include <vector>
#include <iostream>

template<
    bool directed = false,
    bool weighted = false
    >
class Graph {
    
  public:
    using EdgeType = typename std::conditional<weighted, std::pair<size_t, long long>, size_t>::type;
    
    static constexpr bool isWeighted = weighted;
    static constexpr bool isDirected = directed;

  protected:

    size_t nodes;
    std::vector<std::vector<EdgeType>> adjacencyList;

  public:

    Graph(size_t k): nodes(k), adjacencyList(k) {}

    size_t getNodeCount() const {
        return nodes;
    }

    const std::vector<EdgeType>& getNeighbours(size_t node) const {
        return adjacencyList[node];
    }

    std::vector<EdgeType>& getNeighbours(size_t node) {
        return adjacencyList[node];
    }

    template <bool x = weighted>
    typename std::enable_if<!x, void>::type addEdge(size_t u, size_t v) {
        adjacencyList[u].push_back(v);
        if(!directed) {
            adjacencyList[v].push_back(u);
        }
    }

    template <bool x = weighted>
    typename std::enable_if<x, void>::type addEdge(size_t u, size_t v, long long cost) {
        adjacencyList[u].push_back({v, cost});
        if(!directed) {
            adjacencyList[v].push_back({u, cost});
        }
    }
};

using DiGraph = Graph<true, false>;

using WeightedGraph = Graph<false, true>;

using WeightedDiGraph = Graph<true, true>;
