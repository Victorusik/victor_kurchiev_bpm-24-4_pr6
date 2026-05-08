#include "graph.h"
#include <iostream>

/*
 * Задание 2 — Программирование представлений графа.
 *
 * Граф (из рисунка):
 *   Вершины : 0, 1, 2, 3, 4
 *   Дуги    : 0->1, 0->2, 0->4, 1->2, 1->3, 1->4, 3->2, 4->3
 */

int main() {
    system("chcp 65001 > nul");
    using namespace graph;

    const int N = 5;

    std::vector<Arc> edges = {
        {0, 1}, {0, 2}, {0, 4},
        {1, 2}, {1, 3}, {1, 4},
        {3, 2}, {4, 3}
    };

    std::cout << "=== а) Матрица смежности ===\n";
    print_adj_matrix(create_adj_matrix(edges, N));

    std::cout << "\n=== б) Матрица инцидентности ===\n";
    print_inc_matrix(create_inc_matrix(edges, N));

    std::cout << "\n=== в) Список смежности ===\n";
    print_adj_list(create_adj_list(edges, N));

    std::cout << "\n=== г) Список дуг ===\n";
    print_edge_list(create_edge_list(edges));

    std::cout << "\n=== д) Упорядоченный список дуг ===\n";
    print_edge_list(create_ord_edge_list(edges));

    return 0;
}
