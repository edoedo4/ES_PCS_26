#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "unidirected_graph.hpp"
#include "unidirected_edge.hpp"

template<typename I>
bool findpath(const unidirected_graph<I>& T, I source, I arrived,
              std::map<I,bool>& visited, std::vector<I>& path) {
    visited[source] = true;
    path.push_back(source);

    if (source == arrived) return true;  // path contiene già il percorso

    for (I neighbour : T.neighbours(source)) {
        if (!visited[neighbour]) {
            if (findpath(T, neighbour, arrived, visited, path)) {
                return true;  // non faccio pop_back: tengo il percorso
            }
        }
    }

    path.pop_back();  // backtrack solo se questo ramo non porta ad arrive
    return false;
}