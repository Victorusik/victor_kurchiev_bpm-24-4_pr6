#include "graph.h"
#include <algorithm>
#include <iomanip>
#include <iostream>

namespace graph {

AdjMatrix create_adj_matrix(const std::vector<Arc>& edges, int n) {
    AdjMatrix g;
    g.data.assign(n, std::vector<int>(n, 0));
    for (const auto& [u, v] : edges)
        g.data[u][v] = 1;
    return g;
}

IncMatrix create_inc_matrix(const std::vector<Arc>& edges, int n) {
    IncMatrix g;
    int m = static_cast<int>(edges.size());
    g.data.assign(n, std::vector<int>(m, 0));
    for (int k = 0; k < m; ++k) {
        g.data[edges[k].first][k]  =  1;
        g.data[edges[k].second][k] = -1;
    }
    return g;
}

AdjList create_adj_list(const std::vector<Arc>& edges, int n) {
    AdjList g;
    g.data.resize(n);
    for (const auto& [u, v] : edges)
        g.data[u].push_back(v);
    return g;
}

EdgeList create_edge_list(const std::vector<Arc>& edges) {
    EdgeList g;
    g.data = edges;
    return g;
}

EdgeList create_ord_edge_list(const std::vector<Arc>& edges) {
    EdgeList g;
    g.data = edges;
    std::sort(g.data.begin(), g.data.end());
    return g;
}

void print_adj_matrix(const AdjMatrix& g) {
    int n = static_cast<int>(g.data.size());
    std::cout << "   ";
    for (int j = 0; j < n; ++j) std::cout << ' ' << j;
    std::cout << '\n';
    for (int i = 0; i < n; ++i) {
        std::cout << ' ' << i << ' ';
        for (int j = 0; j < n; ++j)
            std::cout << ' ' << g.data[i][j];
        std::cout << '\n';
    }
}

void print_inc_matrix(const IncMatrix& g) {
    int n = static_cast<int>(g.data.size());
    int m = n > 0 ? static_cast<int>(g.data[0].size()) : 0;
    const int W = 7;

    std::cout << std::setw(W) << ' ';
    for (int k = 0; k < m; ++k) {
        int from = -1, to = -1;
        for (int i = 0; i < n; ++i) {
            if      (g.data[i][k] ==  1) from = i;
            else if (g.data[i][k] == -1) to   = i;
        }
        std::string lbl = std::to_string(from) + "->" + std::to_string(to);
        std::cout << std::setw(W) << lbl;
    }
    std::cout << "\n\n";

    for (int i = 0; i < n; ++i) {
        std::cout << std::setw(W) << i;
        for (int k = 0; k < m; ++k)
            std::cout << std::setw(W) << g.data[i][k];
        std::cout << '\n';
    }
}

void print_adj_list(const AdjList& g) {
    int n = static_cast<int>(g.data.size());
    for (int i = 0; i < n; ++i) {
        std::cout << i << " -> ";
        if (g.data[i].empty()) { std::cout << "_\n"; continue; }
        for (int idx = 0; idx < static_cast<int>(g.data[i].size()); ++idx) {
            if (idx > 0) std::cout << ", ";
            std::cout << g.data[i][idx];
        }
        std::cout << '\n';
    }
}

void print_edge_list(const EdgeList& g) {
    for (const auto& [u, v] : g.data)
        std::cout << '(' << u << ", " << v << ")\n";
}

std::vector<Arc> outgoing_arcs(const AdjMatrix& g, const std::string& repr, int v) {
    if (repr != ADJ_MATRIX)
        throw std::invalid_argument("outgoing_arcs: ожидается adj_matrix, получено: " + repr);
    std::vector<Arc> result;
    int n = static_cast<int>(g.data[v].size());
    for (int j = 0; j < n; ++j)
        if (g.data[v][j] == 1)
            result.push_back({v, j});
    return result;
}

std::vector<Arc> outgoing_arcs(const IncMatrix& g, const std::string& repr, int v) {
    if (repr != INC_MATRIX)
        throw std::invalid_argument("outgoing_arcs: ожидается inc_matrix, получено: " + repr);
    std::vector<Arc> result;
    int n = static_cast<int>(g.data.size());
    int m = static_cast<int>(g.data[0].size());
    for (int k = 0; k < m; ++k) {
        if (g.data[v][k] == 1) {            // вершина v — исток дуги k
            for (int i = 0; i < n; ++i) {
                if (g.data[i][k] == -1) {   // находим сток
                    result.push_back({v, i});
                    break;
                }
            }
        }
    }
    return result;
}

std::vector<Arc> outgoing_arcs(const AdjList& g, const std::string& repr, int v) {
    if (repr != ADJ_LIST)
        throw std::invalid_argument("outgoing_arcs: ожидается adj_list, получено: " + repr);
    std::vector<Arc> result;
    for (int to : g.data[v])
        result.push_back({v, to});
    return result;
}

std::vector<Arc> outgoing_arcs(const EdgeList& g, const std::string& repr, int v) {
    std::vector<Arc> result;
    if (repr == EDGE_LIST) {
        // Линейный поиск
        for (const auto& [u, w] : g.data)
            if (u == v) result.push_back({u, w});
    } else if (repr == ORD_EDGE_LIST) {
        // Бинарный поиск — список отсортирован, O(log m + k)
        auto it = std::lower_bound(g.data.begin(), g.data.end(), Arc{v, 0});
        while (it != g.data.end() && it->first == v) {
            result.push_back(*it);
            ++it;
        }
    } else {
        throw std::invalid_argument("outgoing_arcs: ожидается edge_list или ord_edge_list, получено: " + repr);
    }
    return result;
}

static std::vector<Arc> extract_edges(const AdjMatrix& g) {
    int n = static_cast<int>(g.data.size());
    std::vector<Arc> edges;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (g.data[i][j] == 1)
                edges.push_back({i, j});
    return edges;
}

static std::vector<Arc> extract_edges(const IncMatrix& g) {
    int n = static_cast<int>(g.data.size());
    int m = n > 0 ? static_cast<int>(g.data[0].size()) : 0;
    std::vector<Arc> edges;
    for (int k = 0; k < m; ++k) {
        int from = -1, to = -1;
        for (int i = 0; i < n; ++i) {
            if      (g.data[i][k] ==  1) from = i;
            else if (g.data[i][k] == -1) to   = i;
        }
        edges.push_back({from, to});
    }
    return edges;
}

static std::vector<Arc> extract_edges(const AdjList& g) {
    std::vector<Arc> edges;
    int n = static_cast<int>(g.data.size());
    for (int i = 0; i < n; ++i)
        for (int to : g.data[i])
            edges.push_back({i, to});
    return edges;
}


IncMatrix adj_matrix_to_inc_matrix(const AdjMatrix& g) {
    return create_inc_matrix(extract_edges(g), static_cast<int>(g.data.size()));
}
AdjList adj_matrix_to_adj_list(const AdjMatrix& g) {
    return create_adj_list(extract_edges(g), static_cast<int>(g.data.size()));
}
EdgeList adj_matrix_to_edge_list(const AdjMatrix& g) {
    return create_edge_list(extract_edges(g));
}


AdjMatrix inc_matrix_to_adj_matrix(const IncMatrix& g) {
    return create_adj_matrix(extract_edges(g), static_cast<int>(g.data.size()));
}
AdjList inc_matrix_to_adj_list(const IncMatrix& g) {
    return create_adj_list(extract_edges(g), static_cast<int>(g.data.size()));
}
EdgeList inc_matrix_to_edge_list(const IncMatrix& g) {
    return create_edge_list(extract_edges(g));
}


AdjMatrix adj_list_to_adj_matrix(const AdjList& g) {
    return create_adj_matrix(extract_edges(g), static_cast<int>(g.data.size()));
}
IncMatrix adj_list_to_inc_matrix(const AdjList& g) {
    return create_inc_matrix(extract_edges(g), static_cast<int>(g.data.size()));
}
EdgeList adj_list_to_edge_list(const AdjList& g) {
    return create_edge_list(extract_edges(g));
}


AdjMatrix edge_list_to_adj_matrix(const EdgeList& g, int n) {
    return create_adj_matrix(g.data, n);
}
IncMatrix edge_list_to_inc_matrix(const EdgeList& g, int n) {
    return create_inc_matrix(g.data, n);
}
AdjList edge_list_to_adj_list(const EdgeList& g, int n) {
    return create_adj_list(g.data, n);
}

} // namespace graph
