#pragma once
#include <vector>
#include <limits>
#include <algorithm>
#include "Dijkstra.hpp"
#include "unidirected_graph.hpp"
#include "unidirected_edge.hpp"
#include "bool_vector.hpp"
#include "path.hpp"


// Funzioni di supporto per il grafo ausiliario G2
// Ogni nodo v del grafo originale diventa due nodi in G2:
//   v+ = 2*v
//   v- = 2*v + 1

int plus_vertex(int v) {return 2 * v;}

int minus_vertex(int v) {return 2 * v + 1;}


// Dato un cammino in G2 (sequenza di nodi), costruisce
// il vettore di incidenza corrispondente in G.
bool_vector vettore_incidenza( const std::vector<int>& path, const unidirected_graph<int>& G)
{
    int m = G.all_edges().size();
    bool_vector C(m);
    for (int i = 0; i + 1 < (int)path.size(); i++) {
        int u = path[i]     / 2;  // nodo G2 -> nodo G
        int v = path[i + 1] / 2;

        if (u == v) continue;  // salto self-loop (nodo+ -> nodo-)

        int id = G.edge_number(unidirected_edge<int>(u, v));
        if (id != -1)
            C.set(id, C[id] ^ 1);  // XOR: se l'arco compare due volte si annulla
    }
    return C;
}


// Inizializza i vettori S a partire dal coalbero.
// Ogni arco del coalbero corrisponde a un vettore S
// con un solo 1 nella posizione dell'arco.
std::vector<bool_vector> initialize_S_vectors(
    const unidirected_graph<int>& G,
    const unidirected_graph<int>& coalbero
)
{
    std::vector<bool_vector> S;
    int m = G.all_edges().size();

    for (const auto& e : coalbero.all_edges())
    {
        int id = G.edge_number(e);
        if (id == -1){ 
            throw std::runtime_error("Arco del coalbero non trovato nel grafo originale");
        }
        bool_vector s(m);
        s.set(id, 1);
        S.push_back(s);
    }

    return S;
}



// Trova il ciclo minimo C tale che <C, S> = 1 (mod 2).
//
// Idea: si costruisce un grafo ausiliario G2 dove ogni
// nodo v diventa v+ e v-. Per ogni arco (u,v) di G:
//   - se l'arco e' "attivo" in S (S[indice] == 1):
//       si aggiungono gli archi (u+, v-) e (u-, v+)
//   - altrimenti:
//       si aggiungono gli archi (u+, v+) e (u-, v-)
//
// Poi per ogni nodo v si cerca il cammino minimo da v-
// a v+ in G2. Questo cammino, riportato in G, e' un ciclo
// che attraversa un numero dispari di archi attivi in S,
// quindi ha prodotto scalare 1 con S.
bool_vector find_minimal_cycle(
    const unidirected_graph<int>& G,
    const bool_vector& S,
    std::vector<bool_vector>& basis)
{
    const auto& edges = G.all_edges();
    int m = edges.size();

    // costruisco il grafo ausiliario G2 con 2*n nodi
    unidirected_graph<int> G2;

    for (int idx = 0; idx < m; idx++)
    {
        auto e = edges[idx];
        int u = e.from();
        int v = e.to();

        if (S[idx] == 1)
        {
            // arco attivo: collego i vertici di segno opposto
            G2.add_edge(unidirected_edge<int>(plus_vertex(u),  minus_vertex(v)));
            G2.add_edge(unidirected_edge<int>(minus_vertex(u), plus_vertex(v)));
        }
        else
        {
            // arco non attivo: collego i vertici dello stesso segno
            G2.add_edge(unidirected_edge<int>(plus_vertex(u),  plus_vertex(v)));
            G2.add_edge(unidirected_edge<int>(minus_vertex(u), minus_vertex(v)));
        }
    }

    bool_vector best_cycle;
    int best_weight = std::numeric_limits<int>::max();

    for (int v : G.all_nodes())
    {
        // cerco il cammino minimo da v- a v+ in G2
        auto T = dijkstra(G2, minus_vertex(v));

        std::map<int, bool> visited;
        std::vector<int> path;
        findpath(T, minus_vertex(v), plus_vertex(v), visited, path);

        // se non esiste cammino salto questo nodo
        if (path.empty()) continue;

        bool_vector C = vettore_incidenza(path, G);

        // controllo che il ciclo abbia prodotto scalare 1 con S
        if (C.prod_scal_mod2(S) != 1) continue;

        // scarta se già nella base
        bool presente = false;
        for (auto& c : basis) { 
            if (c == C) { presente = true; break; }
        }
        if (presente) continue;

        // conto quanti archi ha il ciclo (quanti 1 ci sono nel vettore)
        int weight = 0;
        for (int i = 0; i < C.size(); i++) { 
            weight += C[i];
        }
        if (weight < best_weight)
        {
            best_weight = weight;
            best_cycle  = C;
        }
    }

    return best_cycle;
}


// Algoritmo di De Pina per trovare la base minima dei cicli.
//
// Per ogni vettore S[i]:
//   1. trova il ciclo minimo C[i] con <C[i], S[i]> = 1
//   2. aggiorna tutti i vettori S[j] con j > i:
//      se <C[i], S[j]> = 1 allora S[j] = S[j] XOR S[i]
//      (questo serve a "ortogonalizzare" i vettori rimanenti)
std::vector<bool_vector> de_pina(
    const unidirected_graph<int>& G,
    const unidirected_graph<int>& coalbero
)
{
    std::vector<bool_vector> S = initialize_S_vectors(G, coalbero);
    std::vector<bool_vector> basis;
    int k = S.size();

    for (int i = 0; i < k; i++)
    {
        bool_vector Ci = find_minimal_cycle(G, S[i], basis);
        basis.push_back(Ci);

        for (int j = i + 1; j < k; j++) {
            if (Ci.prod_scal_mod2(S[j]) == 1)
            {
                S[j].xor_with(Ci);
            }
            }
    }   

    return basis;
        
}



