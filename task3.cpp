#include "graph.h"
#include <iostream>

/*
 * Задание 3 — Просмотр дуг, исходящих из данной вершины.
 *
 * Единый интерфейс: outgoing_arcs(граф, repr_name, вершина)
 * Перегружен для каждого типа-обёртки.
 * Возвращает vector<Arc> = vector<pair<int,int>>.
 *
 * Алгоритм зависит от представления:
 *   adj_matrix    — перебор строки i, O(n)
 *   inc_matrix    — поиск столбцов с +1 в строке i, O(n*m)
 *   adj_list      — прямой доступ к списку вершины i, O(deg)
 *   edge_list     — линейный поиск, O(m)
 *   ord_edge_list — бинарный поиск нижней границы, O(log m + deg)
 */

void print_arcs(const std::string& repr, int v,
                const std::vector<graph::Arc>& arcs) {
    std::cout << "  [" << repr << "] вершина " << v << " -> { ";
    for (const auto& [i, j] : arcs)
        std::cout << "(" << i << "," << j << ") ";
    std::cout << "}\n";
}

int main() {
    system("chcp 65001 > nul");

    using namespace graph;

    const int N = 5;
    std::vector<Arc> edges = {
        {0, 1}, {0, 2}, {0, 4},
        {1, 2}, {1, 3}, {1, 4},
        {3, 2}, {4, 3}
    };

    AdjMatrix adj_m  = create_adj_matrix   (edges, N);
    IncMatrix inc_m  = create_inc_matrix   (edges, N);
    AdjList   adj_l  = create_adj_list     (edges, N);
    EdgeList  edge_l = create_edge_list    (edges);
    EdgeList  ord_l  = create_ord_edge_list(edges);

    for (int v : {0, 1, 2}) {
        std::cout << "─── вершина " << v << " ───\n";
        print_arcs(ADJ_MATRIX,    v, outgoing_arcs(adj_m,  ADJ_MATRIX,    v));
        print_arcs(INC_MATRIX,    v, outgoing_arcs(inc_m,  INC_MATRIX,    v));
        print_arcs(ADJ_LIST,      v, outgoing_arcs(adj_l,  ADJ_LIST,      v));
        print_arcs(EDGE_LIST,     v, outgoing_arcs(edge_l, EDGE_LIST,     v));
        print_arcs(ORD_EDGE_LIST, v, outgoing_arcs(ord_l,  ORD_EDGE_LIST, v));
        std::cout << '\n';
    }

    return 0;
}
