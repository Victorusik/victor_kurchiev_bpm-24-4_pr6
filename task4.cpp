#include "graph.h"
#include <iostream>

/*
 * Задание 4
 *
 * Идея: все представления умеют конвертироваться в EdgeList и из EdgeList.
 * Значит, любая конвертация A -> B = (A -> EdgeList) -> B.
 *
 */

namespace graph {

    EdgeList to_edge_list(const AdjMatrix& g) { return adj_matrix_to_edge_list(g); }
    EdgeList to_edge_list(const IncMatrix& g) { return inc_matrix_to_edge_list(g); }
    EdgeList to_edge_list(const AdjList&   g) { return adj_list_to_edge_list(g);   }
    EdgeList to_edge_list(const EdgeList&  g) { return g; }


// Возвращать разные типы из одной функции без std::variant нельзя,
// поэтому диспетчер просто печатает результат.
// В реальном проекте здесь был бы std::variant<AdjMatrix,IncMatrix,AdjList,EdgeList>.

    void from_edge_list_and_print(const EdgeList& el, int n, const std::string& to) {
        if      (to == ADJ_MATRIX) print_adj_matrix(edge_list_to_adj_matrix(el, n));
        else if (to == INC_MATRIX) print_inc_matrix(edge_list_to_inc_matrix(el, n));
        else if (to == ADJ_LIST)   print_adj_list  (edge_list_to_adj_list  (el, n));
        else if (to == EDGE_LIST)  print_edge_list (el);
        else throw std::invalid_argument("from_edge_list: неизвестное to: " + to);
    }

// Принимает граф в любом представлении (через перегрузку),
// имя from (для проверки / документации), имя to.

    template <typename G>
    void convert(const G& g, int n,
                 const std::string& /*from*/, const std::string& to) {
        from_edge_list_and_print(to_edge_list(g), n, to);
    }

} // namespace graph


int main() {
    system("chcp 65001 > nul");

    using namespace graph;

    const int N = 5;
    std::vector<Arc> edges = {
            {0, 1}, {0, 2}, {0, 4},
            {1, 2}, {1, 3}, {1, 4},
            {3, 2}, {4, 3}
    };

    AdjMatrix adj_m = create_adj_matrix(edges, N);
    IncMatrix inc_m = create_inc_matrix(edges, N);
    AdjList   adj_l = create_adj_list  (edges, N);
    EdgeList  edge_l= create_edge_list (edges);


    // Все 12 конвертаций — одна строка каждая
    for (auto& [label, to] : std::vector<std::pair<std::string,std::string>>{
            {"adj_matrix -> inc_matrix", INC_MATRIX},
            {"adj_matrix -> adj_list",   ADJ_LIST},
            {"adj_matrix -> edge_list",  EDGE_LIST}}) {
        std::cout << "  " << label << ":\n";
        convert(adj_m, N, ADJ_MATRIX, to);
        std::cout << '\n';
    }

    for (auto& [label, to] : std::vector<std::pair<std::string,std::string>>{
            {"inc_matrix -> adj_matrix", ADJ_MATRIX},
            {"inc_matrix -> adj_list",   ADJ_LIST},
            {"inc_matrix -> edge_list",  EDGE_LIST}}) {
        std::cout << "  " << label << ":\n";
        convert(inc_m, N, INC_MATRIX, to);
        std::cout << '\n';
    }

    for (auto& [label, to] : std::vector<std::pair<std::string,std::string>>{
            {"adj_list -> adj_matrix", ADJ_MATRIX},
            {"adj_list -> inc_matrix", INC_MATRIX},
            {"adj_list -> edge_list",  EDGE_LIST}}) {
        std::cout << "  " << label << ":\n";
        convert(adj_l, N, ADJ_LIST, to);
        std::cout << '\n';
    }

    for (auto& [label, to] : std::vector<std::pair<std::string,std::string>>{
            {"edge_list -> adj_matrix", ADJ_MATRIX},
            {"edge_list -> inc_matrix", INC_MATRIX},
            {"edge_list -> adj_list",   ADJ_LIST}}) {
        std::cout << "  " << label << ":\n";
        convert(edge_l, N, EDGE_LIST, to);
        std::cout << '\n';
    }

    return 0;
}