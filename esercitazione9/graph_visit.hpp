#include <set>
#include <map>
#include <queue>
#include <vector>
#include "contenitori.hpp"
#include "grafi.hpp"
#pragma once // aiuto da Gemini, serve per non leggere due volte lo stesso .hpp

template<typename T, typename contenitore>
undirected_graph<T> graph_visit(undirected_graph<T>& G, T nodo_partenza, contenitore& c) {
    undirected_graph<T> albero_di_visita;
    std::set<T> visitati; // tengo conto dei nodi visitati
    std::map<T, T> arco_da_dove_arrivo; 
    c.put(nodo_partenza); // mette il nodo di partenza nel contenitore 
    while (!c.empty()) { // gira finché ci sono nodi in attesa
        T nodo_corrente = c.get(); 
        if (visitati.find(nodo_corrente) == visitati.end()) {
            visitati.insert(nodo_corrente);
            if (nodo_corrente != nodo_partenza) {
                albero_di_visita.add_edge(arco_da_dove_arrivo[nodo_corrente], nodo_corrente);

            }
            for (T vicino : G.neighbours(nodo_corrente)) { // esplorazione dei vicini
                if (visitati.find(vicino) == visitati.end()) {
                    arco_da_dove_arrivo[vicino] = nodo_corrente;
                    c.put(vicino);
                }
            }
        }
    }
    return albero_di_visita;
}

// helper -> posto esterno alla ricorsione dove salvare i dati senza che vengano azzerati a ogni salto.

template <typename T> // aiuto da Gemini
void recursive_dfs_helper(const undirected_graph<T>& G, T nodo_corrente, std::set<T>& visitati, undirected_graph<T>& albero_dfs) {
    visitati.insert(nodo_corrente); // mi segno che ho visitato il nodo corrente
    for (T vicino : G.neighbours(nodo_corrente)) { // esploro tutti i vicini del nodo corrente
        if (visitati.find(vicino) == visitati.end()) {
            albero_dfs.add_edge(nodo_corrente, vicino); // aggiungo l'arco all'albero di visita
            recursive_dfs_helper(G, vicino, visitati, albero_dfs);
        }
    }
}

template <typename T>
undirected_graph<T> recursive_dfs(const undirected_graph<T>& G, T nodo_partenza) {
    undirected_graph<T> albero_dfs; // preparo l'albero vuoto (così lo creo solo una volta)
    std::set<T> visitati;           // creo il registro dei nodi visitati (così lo creo solo una volta)
    recursive_dfs_helper(G, nodo_partenza, visitati, albero_dfs);
    return albero_dfs;
}

template <typename T>
undirected_graph<T> dijkstra(const undirected_graph<T>& G, T nodo_partenza) {
    undirected_graph<T> albero_cammini_minimi; 
    std::map<T, double> distanze;              
    std::map<T, T> genitori; // mappa per ricostruire la discendenza
    distanze[nodo_partenza] = 0.0; // inizializzo il nodo di partenza
    using Par = std::pair<double, T>; // aiuto da Gemini, crea un alias, rende più leggibile il codice
    std::priority_queue<Par, std::vector<Par>, std::greater<Par>> pq;
    pq.push({0.0, nodo_partenza}); // coda con priorità
    while (!pq.empty()) {
        double dist_corrente = pq.top().first;
        T nodo_corrente = pq.top().second;
        pq.pop(); // tolgo l'elemento dalla coda
        if (dist_corrente > distanze[nodo_corrente]) continue; // aiuto da Gemini, serve per ottimizzare e ignorare un risultato non ottimale
        if (nodo_corrente != nodo_partenza) {
            double peso_originale = G.get_weight(genitori[nodo_corrente], nodo_corrente);
            albero_cammini_minimi.add_edge(genitori[nodo_corrente], nodo_corrente, peso_originale);
        }
        for (T vicino : G.neighbours(nodo_corrente)) {
            double peso_arco = G.get_weight(nodo_corrente, vicino);
            double nuova_distanza = dist_corrente + peso_arco;
            if (distanze.find(vicino) == distanze.end() || nuova_distanza < distanze[vicino]) { // salvo la nuova strada se il vicino non era stato scoperto prima o se la distanza è strett. inferiore
                distanze[vicino] = nuova_distanza;               
                genitori[vicino] = nodo_corrente;                // Salviamo il nodo genitore
                pq.push({nuova_distanza, vicino});               
            }
        }
    }
    
    return albero_cammini_minimi;
}