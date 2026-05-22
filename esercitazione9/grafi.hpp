#include <concepts> 
#include <iostream>
#include <numeric>
#include <map>
#include <list>
#include <vector>
#pragma once // aiuto da Gemini, serve per non leggere due volte lo stesso .hpp

template <typename I>
class undirected_edge {
    I nodo1;
    I nodo2;
    double peso; // la aggiungo per Dijkstra

public:
    // Restituisco i valori di nodo1 e nodo2
    undirected_edge(I nodo_primo, I nodo_secondo, double p = 1.0) {
        nodo1 = nodo_primo;
        nodo2 = nodo_secondo;
        peso = p;
    if (nodo1 > nodo2) {
        std::swap(nodo1, nodo2);
    }
    }
    I from() const {return nodo1; }
    I to() const {return nodo2; }

    double weight() const {
        return peso;
    }

    // Implementazione canonica del confronto
    bool operator<(const undirected_edge& other) const {
    if (nodo1 < other.from()) {
        return true;
    }
    else if (nodo1 > other.from()) {
        return false;
    }
    else if (nodo1 == other.from()) {
        if (nodo2 < other.to()) {
            return true;
        }
        else if (nodo2 > other.to()) {
            return false;
        }
        else {
            return false;
        }
    }
    }

    // Implementazione canonica di == 
    bool operator==(const undirected_edge& other) const {
    if (nodo1 == other.from() && nodo2 == other.to()) {
        return true;
    }
    else {
        return false;
    }
    }
};

// Implementazione canonica dell'operatore di stampa
template <typename I>
std::ostream& operator<<(std::ostream& os, const undirected_edge<I>& other) {
    os << "(" << other.from() << "," << other.to() << ")";
    return os; 
}

template <typename I>
class undirected_graph{
    std::map<I, std::list<I>> lista_adiacenza;
    std::vector<undirected_edge<I>> archi_inseriti;

public: 

undirected_graph() = default; //costruttore di default

undirected_graph(const undirected_graph<I>& altro_grafo) = default; // costruttore di copia

std::list<I> neighbours(I nodo) const {
    auto iteratore = lista_adiacenza.find(nodo);
    if (iteratore != lista_adiacenza.end()) {
        return iteratore->second; // voglio la lista dei vicini del nodo, non il nodo stesso
    }
    return std::list<I>();
}

void add_edge(I nodo_a, I nodo_b, double peso = 1.0) {
        lista_adiacenza[nodo_a].push_back(nodo_b);
        lista_adiacenza[nodo_b].push_back(nodo_a);
        archi_inseriti.push_back(undirected_edge<I> (nodo_a, nodo_b, peso));
}

double get_weight(I nodo_a, I nodo_b) const {
    undirected_edge<I> arco_cercato(nodo_a, nodo_b);
    int indice = edge_number(arco_cercato);
    if (indice != -1) {
        return archi_inseriti[indice].weight();
    }
    return -1.0; // se i nodi non sono collegati
}

std::vector<undirected_edge<I>> all_edges() const {
    return archi_inseriti;
}

std::vector<I> all_nodes() const {
    std::vector<I> nodi;
    for (const auto& coppia : lista_adiacenza) {
        nodi.push_back(coppia.first);
    }
    return nodi;
}

int edge_number(const undirected_edge<I>& arco_cercato) const {
    for (int i = 0; i < archi_inseriti.size(); i++) {
        if (archi_inseriti[i] == arco_cercato) {
            return i;
        }
    }
    return -1; // scelta arbitraria, lo ritorna se l'arco non sta nel grafo
}

undirected_edge<I> edge_at(int edge_number) const {
    return archi_inseriti[edge_number];
}

std::vector<undirected_edge<I>> operator-(const undirected_graph<I>& grafo_b) const {
    auto archi_grafo_a = all_edges();
    std::vector<undirected_edge<I>> archi_differenza;
    for (int i=0; i<archi_grafo_a.size(); i++) {
        if (grafo_b.edge_number(archi_grafo_a[i]) == -1) {
            archi_differenza.push_back(archi_grafo_a[i]);
        }
    }
    return archi_differenza;
}
};