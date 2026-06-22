#pragma once
#include <set>
#include "unidirected_graph.hpp"
#include "unidirected_edge.hpp"

/*funzione graph_visit che visita in profondità o 
in ampiezza in base al contenitore passato come parametro*/
template<typename I, typename Container>
unidirected_graph<I> graph_visit(const unidirected_graph<I>& G, I source, Container& container) {

    unidirected_graph<I> tree;
    std::set<I> visited;

    container.put(source);
    visited.insert(source);

    while (!container.empty()) {
        I current = container.get();

        for (I neighbor : G.neighbours(current)) {
            if (visited.count(neighbor) == 0) {
                visited.insert(neighbor);
                container.put(neighbor);
                tree.add_edge(unidirected_edge<I>(current, neighbor));
            }
        }
    }
    return tree;
};
