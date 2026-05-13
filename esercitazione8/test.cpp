#include "grafi.hpp"
#include <iostream>

int main() {
    undirected_graph<int> grafo;
    grafo.add_edge(1,2);
    grafo.add_edge(4,7);
    auto nodi = grafo.all_nodes();
    std::cout << "Numero di nodi: " << nodi.size() << "\n";
    std::cout << "Nodi: ";
    for (int i = 0; i < nodi.size(); i++) {
        std::cout << nodi[i] << " ";
    }
    std::cout << "\n";
    auto archi = grafo.all_edges();
    std::cout << "Numero di archi: " << archi.size() << "\n";
    std::cout << "Archi: ";
    for (int i = 0; i < archi.size(); i++) {
        std::cout << archi[i] << " ";
    }
    std::cout << "\n";
    undirected_graph<int> grafo2;
    grafo2.add_edge(1,2);
    grafo2.add_edge(5,3);
    auto archi_rimanenti = grafo - grafo2;
      std::cout << "Archi di differenza tra il primo ed il secondo grafo: ";
    for (int i = 0; i < archi_rimanenti.size(); i++) {
        std::cout << archi_rimanenti[i] << " ";
    }
    return 0;
}