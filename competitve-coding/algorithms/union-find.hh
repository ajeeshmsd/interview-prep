#include <vector>

class UnionFind {
    size_t nodes;
    std::vector<size_t> parents;
    std::vector<size_t> sizes;
    size_t components;

    public:

    UnionFind() = delete;
    UnionFind(size_t n): nodes(n), parents(n, -1), sizes(n, 1), components(n) {}
    UnionFind(const UnionFind&) = default;
    UnionFind& operator=(const UnionFind&) = default;
    UnionFind(UnionFind&&) = default;
    UnionFind& operator=(UnionFind&&) = default;
    ~UnionFind() = default;

    size_t findRoot(size_t node) {
        if(parents[node] == -1) {
            return node;
        }

        return parents[node] = findRoot(parents[node]);
    }

    void applyUnion(size_t node1, size_t node2) {
        auto root1 = findRoot(node1);
        auto root2 = findRoot(node2);

        if(root1 == root2) {
            return;
        }

        components--;
        if(sizes[root1] >= sizes[root2]) {
            parents[root2] = root1;
            sizes[root1] += sizes[root2];
        } else {
            parents[root1] = root2;
            sizes[root2] += sizes[root1];
        }
    }

    size_t countComponents() const {
        return components;
    }

    bool isConnected(size_t node1, size_t node2) {
        return findRoot(node1) == findRoot(node2);
    }
};