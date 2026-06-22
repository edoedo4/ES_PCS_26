#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <vector>
#pragma once 

#include "unidirected_edge.hpp"

template<typename I> 

class unidirected_graph {
private:
	/* Mappa: che associa a ogni nodo (chiave) il set dei nodi vicini*/
    std::map<int, std::set<int>> lista_vicini;
    
    /*Mappa per associare a ogni arco un intero*/ 
    std::map<unidirected_edge<I>, int> arco_intero;
    
    /* Vector per recuperare l'arco dato il numero intero*/ 
    std::vector<unidirected_edge<I>> intero_arco;
public:
    unidirected_graph() = default;
    unidirected_graph(const unidirected_graph& other) = default; 

    void add_edge(const unidirected_edge<I>& e) {
        I u = e.from();
        I v = e.to();

        lista_vicini[u].insert(v);
        lista_vicini[v].insert(u);

        /*se l'arco non esiste già*/
        if (arco_intero.count(e) == 0) {
            int new_id = intero_arco.size();

            arco_intero[e] = new_id;

            intero_arco.push_back(e);
        }
    }

    std::set<int> neighbours(int node) const {
        return lista_vicini.at(node);   /*data una chiave restituisce il valore associato, che in questo caso è l'insieme dei nodi vicini*/
    }

    std::vector<unidirected_edge<I>> all_edges() const {
        return intero_arco;
    }

    std::set<int> all_nodes() const {
        std::set<int> nodi;
        for (auto const& [nodo, vicini] : lista_vicini) {
            nodi.insert(nodo);
        }
        return nodi;
    }

    int edge_number(const unidirected_edge<I>& e) const {
        auto it = arco_intero.find(e);

        if (it != arco_intero.end()) {
            return it->second; /*Arco trovato: restituisce il numero intero*/ 
        } else {
            return -1;         /*Arco non trovato: restituisce -1*/ 
        }
            }

    unidirected_edge<I> edge_at(int id) const {
        return intero_arco.at(id); 
    }

    /*Operatore differenza: G3 = G1 - G2 (deve resituire gli archi in G1 che non sono presenti in G2)*/
    unidirected_graph operator-(const unidirected_graph<I>& other) const {

        unidirected_graph result;

        for (const auto& e : intero_arco) {
            /*Se l'arco e non è presente nel grafo 'other'*/ 
            if (other.arco_intero.count(e) == 0) {
                result.add_edge(e);
            }
        }
        return result;
    }
};
