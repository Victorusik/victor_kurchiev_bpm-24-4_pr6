#pragma once

#include <vector>
#include <utility>
#include <string>
#include <stdexcept>

/*
 * graph.h — типы и объявления функций для представлений графа.
 *
 * Так как матрица смежности, матрица инцидентности и список смежности
 * имеют одинаковый базовый тип vector<vector<int>>,
 * мы оборачиваем каждый в именованный struct — это позволяет:
 *   1. Различать их при перегрузке функций.
 *   2. Явно показывать намерение в коде.
 *
 * Имена строковых констант (repr_name):
 *   ADJ_MATRIX | INC_MATRIX | ADJ_LIST | EDGE_LIST | ORD_EDGE_LIST
 */

namespace graph {

struct AdjMatrix {
    std::vector<std::vector<int>> data;
};

struct IncMatrix {
    std::vector<std::vector<int>> data;
};

struct AdjList {
    std::vector<std::vector<int>> data;
};

struct EdgeList {
    std::vector<std::pair<int,int>> data;
};

using Arc = std::pair<int,int>;


inline const std::string ADJ_MATRIX    = "adj_matrix";
inline const std::string INC_MATRIX    = "inc_matrix";
inline const std::string ADJ_LIST      = "adj_list";
inline const std::string EDGE_LIST     = "edge_list";
inline const std::string ORD_EDGE_LIST = "ord_edge_list";

AdjMatrix create_adj_matrix   (const std::vector<Arc>& edges, int n);
IncMatrix create_inc_matrix   (const std::vector<Arc>& edges, int n);
AdjList   create_adj_list     (const std::vector<Arc>& edges, int n);
EdgeList  create_edge_list    (const std::vector<Arc>& edges);
EdgeList  create_ord_edge_list(const std::vector<Arc>& edges);

// Для 2 задания
void print_adj_matrix(const AdjMatrix& g);
void print_inc_matrix(const IncMatrix& g);
void print_adj_list  (const AdjList&   g);
void print_edge_list (const EdgeList&  g);

// Для 3 задания
std::vector<Arc> outgoing_arcs(const AdjMatrix& g, const std::string& repr, int vertex);
std::vector<Arc> outgoing_arcs(const IncMatrix& g, const std::string& repr, int vertex);
std::vector<Arc> outgoing_arcs(const AdjList&   g, const std::string& repr, int vertex);
std::vector<Arc> outgoing_arcs(const EdgeList&  g, const std::string& repr, int vertex);

// Для 4 задания
// Из матрицы смежности
IncMatrix adj_matrix_to_inc_matrix(const AdjMatrix& g);
AdjList   adj_matrix_to_adj_list  (const AdjMatrix& g);
EdgeList  adj_matrix_to_edge_list (const AdjMatrix& g);

// Из матрицы инцидентности
AdjMatrix inc_matrix_to_adj_matrix(const IncMatrix& g);
AdjList   inc_matrix_to_adj_list  (const IncMatrix& g);
EdgeList  inc_matrix_to_edge_list (const IncMatrix& g);

// Из списка смежности
AdjMatrix adj_list_to_adj_matrix(const AdjList& g);
IncMatrix adj_list_to_inc_matrix(const AdjList& g);
EdgeList  adj_list_to_edge_list (const AdjList& g);

// Из списка дуг
AdjMatrix edge_list_to_adj_matrix(const EdgeList& g, int n);
IncMatrix edge_list_to_inc_matrix(const EdgeList& g, int n);
AdjList   edge_list_to_adj_list  (const EdgeList& g, int n);

} // namespace graph
