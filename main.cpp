#include <iostream>
#include <vector>
#include <utility>
#include <iomanip>
#include <string>
#include <algorithm>

namespace graph {
    std::vector<std::vector<int>> create_adj_matrix(const std::vector<std::pair<int, int>> &edges, int vertex_count) {
        std::vector<std::vector<int>> adj_matrix(vertex_count, std::vector<int>(vertex_count, 0));

        for (const auto &edge: edges) {
            adj_matrix[edge.first][edge.second] = 1;
        }

        return adj_matrix;
    }

    void print_adj_matrix(const std::vector<std::vector<int>> &adj_matrix) {
        for (const auto &row: adj_matrix) {
            for (int val: row) {
                std::cout << val << ' ';
            }

            std::cout << '\n';
        }
    }

    std::vector<std::vector<int>>
    create_inc_matrix(const std::vector<std::pair<int, int>> &edges, int vertex_count, int edges_count) {
        std::vector<std::vector<int>> inc_matrix(vertex_count, std::vector<int>(edges_count, 0));

        int i = 0;
        for (const auto &edge: edges) {
            inc_matrix[edge.first][i] = 1;
            inc_matrix[edge.second][i] = -1;
            ++i;
        }

        return inc_matrix;
    }

    void print_inc_matrix(const std::vector<std::vector<int>> &inc_matrix) {
        int vertex_count = static_cast<int>(inc_matrix.size());
        int edges_count = static_cast<int>(inc_matrix[0].size());
        const int W = 6;

        std::cout << std::setw(W) << " ";
        for (int j = 0; j < edges_count; ++j) {
            int vertex_from = 0;
            int vertex_to = 0;

            for (int i = 0; i < vertex_count; ++i) {
                if (inc_matrix[i][j] == 1) {
                    vertex_from = i;
                } else if (inc_matrix[i][j] == -1) {
                    vertex_to = i;
                }
            }

            std::string edge_label = std::to_string(vertex_from) + "->" + std::to_string(vertex_to);
            std::cout << std::setw(W) << edge_label;
        }
        std::cout << "\n\n";

        for (int i = 0; i < vertex_count; ++i) {
            std::cout << std::setw(W) << std::to_string(i);
            for (int j = 0; j < edges_count; ++j) {
                std::cout << std::setw(W) << std::to_string(inc_matrix[i][j]);
            }
            std::cout << '\n';
        }
    }

    std::vector<std::vector<int>> create_adj_list(const std::vector<std::pair<int, int>> &edges, int vertex_count) {
        std::vector<std::vector<int>> adj_list(vertex_count);

        for (const auto &edge : edges) {
            adj_list[edge.first].push_back(edge.second);
        }

        return adj_list;
    }

    void print_adj_list(const std::vector<std::vector<int>> &adj_list) {
        int vertex_count = static_cast<int>(adj_list.size());

        int vertex = 0;
        for (const auto &list : adj_list) {
            std::cout << vertex << " -> ";

            int list_size = static_cast<int>(list.size());
            for (int i = 0; i < list_size; ++i) {
                std::cout << list[i];

                if (i != list_size - 1) {
                    std::cout << ", ";
                }
            }

            if (list_size == 0) {
                std::cout << '_';
            }

            std::cout << '\n';
        }
    }

    void print_edg_list(const std::vector<std::pair<int, int>> &edges) {
        for (const auto& edge : edges) {
            std::cout << edge.first << " -> " << edge.second << '\n';
        }
    }
}

int main() {
    using namespace graph;

    const int VERTEX_C = 5;
    const int EDGES_C = 8;

    std::vector<std::pair<int, int>> edges = {
            {0, 1},
            {0, 2},
            {0, 4},
            {1, 2},
            {1, 3},
            {1, 4},
            {3, 2},
            {4, 3}
    };

    std::vector<std::pair<int, int>> ordered_edges = edges;
    std::sort(ordered_edges.begin(), ordered_edges.end());

    print_adj_matrix(create_adj_matrix(edges, VERTEX_C));
    print_inc_matrix(create_inc_matrix(edges, VERTEX_C, EDGES_C));
    print_adj_list(create_adj_list(edges, VERTEX_C));
    // print_edg_list(ordered_edges);
}
