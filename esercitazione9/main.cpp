#include <iostream>
#include <string>
#include "contenitori.hpp"
#include "grafi.hpp"
#include "graph_visit.hpp"

template <typename T> // aiuto da Gemini per scrivere questa funzione template
void graphviz(const undirected_graph<T>& G, const std::string& nome_del_grafo) {
    std::cout << "graph " << nome_del_grafo << " {\n";
    for (const auto& arco : G.all_edges()) {
        std::cout << "    " << arco.from() << " -- " << arco.to() << ";\n";
    }
    std::cout << "}\n\n";
}

int main() {
    undirected_graph<int> G;

    G.add_edge(1,2);
    G.add_edge(2,3);
    G.add_edge(2,4);
    G.add_edge(3,4);
    G.add_edge(3,5);
    G.add_edge(5,6);

    lifo<int> s; // contenitore per la visita in profondità (DFS)
    fifo<int> q; // contenitore per la visita in ampiezza (BFS)

    auto albero_dfs = graph_visit(G, 1, s);
    auto albero_bfs = graph_visit(G, 1, q);
    auto albero_dfs_ricorsivo = recursive_dfs(G, 1);

    std::cout << "Grafo_originale \n"; 
    graphviz(G, "Grafo_originale");
    std::cout << "Albero_DFS \n"; 
    graphviz(albero_dfs, "Albero_DFS");
    std::cout << "Albero_BFS \n"; 
    graphviz(albero_bfs, "Albero_BFS");
    std::cout << "Albero_DFS_Ricorsivo \n"; 
    graphviz(albero_dfs_ricorsivo, "Albero_DFS_Ricorsivo");

    std::cout << "// --- Inizio Test Dijkstra ---\n";
    undirected_graph<int> Grafo_Pesato;

    Grafo_Pesato.add_edge(1, 2, 10.0);
    Grafo_Pesato.add_edge(1, 3, 1.0);
    Grafo_Pesato.add_edge(3, 2, 2.0); 
    Grafo_Pesato.add_edge(2, 4, 5.0);
    Grafo_Pesato.add_edge(3, 4, 8.0);

    auto albero_dijkstra = dijkstra(Grafo_Pesato, 1);
    graphviz(albero_dijkstra, "Albero_Dijkstra");

    return 0;
}