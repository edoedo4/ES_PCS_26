#pragma once
#include <map>
#include <set>
#include <queue>
#include <vector>
#include <limits> /*valori numerici speciali*/
#include "unidirected_graph.hpp"
#include "unidirected_edge.hpp"
 
template<typename I>
unidirected_graph<I> dijkstra(const unidirected_graph<I>& G, I source) {
 
    using dist_node = std::pair<int, I>;
    std::priority_queue<dist_node, std::vector<dist_node>, std::greater<dist_node>> pq;
 
    std::map<I, int> dist;   /*dist: (nodo, distanza minima dal sorgente)*/
    std::map<I, I>   pred;   /*pred: (nodo, predecessore)*/ 
    std::set<I>      visited; /*visited: insieme dei nodi già visitati*/
 
    /*distanza del sorgente = 0*/
    dist[source] = 0;
    /*il predecessore del sorgente è sè stesso*/
    pred[source] = source;
    /*Inserisco il sorgente nella coda*/
    pq.push({0, source});
 
    while (!pq.empty()) {
        /*nodo con distanza minima*/
        I u = pq.top().second;
        /*rimuovo dalla coda*/
        pq.pop();
 
        /*Evito di visitare più volte lo stesso nodo*/
        if (visited.count(u))
            continue;
        visited.insert(u);
 
        /*Scorro tutti i vicini di u*/
        for (I v : G.neighbours(u)) {
            int new_dist = dist[u] + 1;
            /*Aggiorno se:
            -v non ha ancora una distanza 
            oppure 
            -ho trovato un cammino migliore*/
            if (!dist.count(v) || new_dist < dist[v]) {
                /*aggiorno distanza*/
                dist[v] = new_dist;
                /*salvo predecessore*/
                pred[v] = u;
                /*inserisco nella priority queue*/
                pq.push({new_dist, v});
            }
        }
    }
 
    /*costruzione dell'albero*/
    unidirected_graph<I> tree;
    /*scorro tutti i predecessori*/
    for (auto const& [node, par] : pred) {
        /*evito il nodo sorgente*/
        if (node != source)
        /*aggiungo l'arco: predecessore-nodo*/
            tree.add_edge(unidirected_edge<I>(par, node));
    }
 
    return tree;
}