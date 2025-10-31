#ifndef UNIONFIND_H
#define UNIONFIND_H

#include <vector>
#include <string>
#include <map>

class UnionFind {
private:
    std::map<std::string, std::string> parent;
    std::map<std::string, int> rank;

public:
    UnionFind(const std::vector<std::string>& nodos) {
        for (const auto& nodo : nodos) {
            parent[nodo] = nodo;
            rank[nodo] = 0;
        }
    }

    std::string find(const std::string& nodo) {
        if (parent[nodo] != nodo) {
            parent[nodo] = find(parent[nodo]);
        }
        return parent[nodo];
    }

    bool unionSets(const std::string& nodo1, const std::string& nodo2) {
        std::string root1 = find(nodo1);
        std::string root2 = find(nodo2);

        if (root1 == root2) {
            return false;
        }

        if (rank[root1] < rank[root2]) {
            parent[root1] = root2;
        }
        else if (rank[root1] > rank[root2]) {
            parent[root2] = root1;
        }
        else {
            parent[root2] = root1;
            rank[root1]++;
        }

        return true;
    }
};

#endif
