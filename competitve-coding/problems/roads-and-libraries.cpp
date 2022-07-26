// https://www.hackerrank.com/challenges/three-month-preparation-kit-torque-and-development/problem?h_r=internal-search

#include <vector>
#include <iostream>

#include "../algorithms/union-find.hh"

using namespace std;

long roadsAndLibraries(size_t n, size_t c_lib, size_t c_road, const vector<vector<size_t>> &cities) {
    
    if(c_lib <= c_road) {
        return c_lib * n;
    }

    UnionFind uf(n);
    for(auto &edge: cities) {
        uf.applyUnion(edge[0] - 1, edge[1] - 1);
    }
    auto components = uf.countComponents();
    return (components * c_lib) + ((n - components) * c_road);
}

int main() {
    size_t q; cin >> q;
    while(q--) {
        size_t n, m, c_lib, c_road;
        cin >> n >> m >> c_lib >> c_road;

        vector<vector<size_t>> cities(m, vector<size_t>(2, 0));
        for(auto &edge: cities) {
            cin >> edge[0] >> edge[1];
        }
        cout << roadsAndLibraries(n, c_lib, c_road, cities) << endl;
    }
}
