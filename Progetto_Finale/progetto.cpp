using namespace std;
#include <fstream>
#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include "Eigen/Eigen"
#include <string>
#include "De_Pina.hpp"
#include <map>
#include "unidirected_graph.hpp"
#include "unidirected_edge.hpp"
#include "classe_LIFO.hpp"
#include "graph_visit.hpp"
#include <string_view>
#include "path.hpp"
#include "bool_vector.hpp"
#include "gradiente_coniugato.hpp"


int main(int argc, char* argv[]) {
    unidirected_graph<int> G;

    /*controllo che sul terminale vengano dati almeno 2 "input":
    - il programma eseguibile; 
    - l'input che contiene i dati.*/
    if (argc<2) {
        throw std::runtime_error("Errore: nome del file non specificato");
    }
    

    ifstream ifs(argv[1]);
    if (ifs.is_open()) {
        string tipo;
        double valori[3];
        std::map<string, std::vector<double>> resistenza_valore; /*nome resistenza, associata ai suoi valori*/
        std::map<string, std::vector<double>> generatore_valore;/*nome generatore, associato ai suoi valori*/

        while( ifs >> tipo >> valori[0] >> valori[1] >> valori[2]) {
            if(tipo[0]=='R'){
                resistenza_valore[tipo]={valori[0], valori[1], valori[2]};
            }else{
                generatore_valore[tipo]={valori[0], valori[1], valori[2]};
            }
            G.add_edge(unidirected_edge<int>(valori[1],valori[2])); /*grafo G*/
        }

        lifo<int> s;
        unidirected_graph<int> T = graph_visit(G, 1, s); /*albero di supporto T con la DFS*/
        /*to_dot(G, "grafo.dot");
        to_dot(dfsT, "dfsT.dot");*/

        /*calcolo il coalbero C come differenza G -T*/ 
        unidirected_graph<int> diff = G-T;
        /*to_dot(diff, "diff.dot");*/

        /*inizializzo un vettore che mi salverà in ogni posizione un ciclo*/
        std::vector<std::vector<int>> cicli;

        int metodo;
        std::cout << "Scegli il metodo di risoluzione:\n";
        std::cout << "  1 - DFS\n";
        std::cout << "  2 - De Pina\n";
        std::cout << "Inserisci 1 o 2: ";
        std::cin >> metodo;

        if (metodo == 1) {

            /*uso path.hpp per salvare i cicli che ci sono*/
            for(const auto& edge: diff.all_edges()){
                /*Aggiungo tutti gli archi del coalbero C all'albero T 
                (per chiudere i cicli, che rappresentano le maglie del circuito)*/ 
                T.add_edge(edge);
                std::vector<int> path;
                std::map<int,bool> visited;
                findpath(T,edge.from(),edge.to(), visited, path);
                cicli.push_back(path);
            }
            /*stampo i cicli ottenuti col metodo del dfs*/
            for(const auto& n:cicli){
                std::cout<<"Ciclo: [";
                for(const auto& elem:n){
                    std::cout<<" "<<elem;
                }
                std::cout<<"] \n";
            }
           
        } else if (metodo == 2) {
            auto basis = de_pina(G, diff);

            for (int i = 0; i < (int)basis.size(); i++)
            {
                std::vector<unidirected_edge<int>> ciclo_archi;

                // basis[i] è un bool_vector: ciclo sugli elementi
                for (int j = 0; j < basis[i].size(); j++)
                {
                    if (basis[i][j] == 1){
                        ciclo_archi.push_back(G.edge_at(j));
                      }  // edge_at è un metodo, non array
                }

                // ricostruisco la sequenza di nodi dagli archi
                std::vector<int> ciclo_nodi;
                ciclo_nodi.push_back(ciclo_archi[0].from());
                ciclo_nodi.push_back(ciclo_archi[0].to());

                std::set<int> visitati = {ciclo_nodi[0], ciclo_nodi[1]};

                while (ciclo_nodi.back() != ciclo_nodi.front())
                {
                    int ultimo = ciclo_nodi.back();
                    for (const auto& e : ciclo_archi)
                    {
                        if (e.from() == ultimo && e.to() != ciclo_nodi[ciclo_nodi.size()-2])
                        {
                            ciclo_nodi.push_back(e.to());
                            break;
                        }
                        if (e.to() == ultimo && e.from() != ciclo_nodi[ciclo_nodi.size()-2])
                        {
                            ciclo_nodi.push_back(e.from());
                            break;
                        }
                    }
                } 
                ciclo_nodi.pop_back();
                cicli.push_back(ciclo_nodi);
            } 
        
            /*stampo i cicli ottenuti col metodo del dfs*/
            for(const auto& n:cicli){
                std::cout<<"Ciclo: [";
                for(const auto& elem:n){
                    std::cout<<" "<<elem;
                }
                std::cout<<"] \n";
            }
        } else {
            throw std::runtime_error("Errore: scelta non valida.");
        }

    
        /*inizializzo la matrice B, in cui ci sarà:
        - +1 se il resistore i appartine alla maglia j ed ha lo stesso verso di percorrenza della maglia
        - -1 se il resistore i appartine alla maglia j ed ha verso di percorrenza contrario rispetto alla maglia
        -  0 se il resistore non appartiene alla maglia*/
        Eigen::MatrixXd B=Eigen::MatrixXd::Zero(resistenza_valore.size(), cicli.size());

        // precalcolo: arco -> indice di riga in B (solo resistenze)
        std::map<unidirected_edge<int>, int> edge_to_row;
        int t = 0;
        for (const auto& key : resistenza_valore) {
            unidirected_edge<int> e(key.second[1], key.second[2]);
            edge_to_row[e] = t;
            t++;
        }
        for (int i = 0; i < cicli.size(); i++) {
            std::vector<int> l = cicli[i];
            l.push_back(l[0]); // chiudo il ciclo
            for (int k = 0; k < l.size() - 1; k++) {
                int u = l[k], v = l[k+1];
            // edge_to_row.count(arco) restituisce 1 se l'arco è una resistenza, 0 se è un generatore
            if (edge_to_row.count(unidirected_edge<int>(u, v))!=0) {
                int t=edge_to_row[unidirected_edge<int>(u,v)];
                // controllo il verso
                if (u < v){
                    B(t, i) = 1;
                }else{
                    B(t, i) = -1;
                }
                }
            }   
        }
    


       /* for(int i=0; i<cicli.size(); i++){
            std::vector<int> l=cicli[i];
            for(int k=0; k<l.size(); k++){
                if(k==l.size()-1){
                    if(l[k]>l[0]){
                        int t=0;
                        for(const auto& key:resistenza_valore){
                            if(unidirected_edge<int>(key.second[1],key.second[2])==unidirected_edge<int>(l[k],l[0])){
                                B(t,i) = -1;
                            }
                            t++;
                        }
                    }else{
                        int t=0;
                        for(const auto& key:resistenza_valore){
                            if(unidirected_edge<int>(key.second[1],key.second[2])==unidirected_edge<int>(l[k],l[0])){
                                B(t,i) = 1;
                            }
                            t++;
                        }
                    }
                }else{
                    if(l[k]>l[k+1]){
                        int t=0;
                        for(const auto& key:resistenza_valore){
                            if(unidirected_edge<int>(key.second[1],key.second[2])==unidirected_edge<int>(l[k],l[k+1])){
                                B(t,i) = -1;
                            }
                            t++;
                        }
                    }else{
                        int t=0;
                        for(const auto& key:resistenza_valore){
                            if(unidirected_edge<int>(key.second[1],key.second[2])==unidirected_edge<int>(l[k],l[k+1])){
                                B(t,i) = 1;
                            }
                            t++;
                        }
                        }
                    
                }
            }
        
        
        }*/
       
        /*std::cout<<"Matrice B "<<'\n';
        std::cout << B << '\n';*/

        /*numero resistenze*/
        int N = resistenza_valore.size();

        /*inizializzo R, che avrà sulla diagonale le resistenze*/
        Eigen::MatrixXd R = Eigen::MatrixXd::Zero(N,N);
        int p=0;
        for (const auto & coppia : resistenza_valore) {
            double resistenza = coppia.second.front();
            R(p,p) = resistenza;
            p++;
        }
        /*std::cout<<"Matrice R "<<'\n'<< R << std::endl;*/

        /*inizializzo il vettore V, contenente in ogni posizione 
        la "somma" dei generatori presenti su ogni ciclo*/ 
        Eigen::VectorXd V = Eigen::VectorXd::Zero(cicli.size());

        
        for(int i=0; i<cicli.size(); i++){
            std::vector<int> l=cicli[i];
            double somma=0;
            for(int k=0; k<l.size(); k++){
                if(k==l.size()-1){
                    for(const auto& key:generatore_valore){
                        if(unidirected_edge<int>(key.second[1],key.second[2])==unidirected_edge<int>(l[k],l[0])){
                            if(l[k]==key.second[1] && l[0]==key.second[2]){
                                somma=somma-key.second[0];
                            }else{somma=somma+key.second[0];}    
                            }
                        }
                }else{
                    for(const auto& key:generatore_valore){
                        if(unidirected_edge<int>(key.second[1],key.second[2])==unidirected_edge<int>(l[k],l[k+1])){
                            if(l[k]==key.second[1] && l[k+1]==key.second[2]){
                                somma=somma-key.second[0];
                            }else{somma=somma+key.second[0];}    
                            }  
                        }
                    }    
                }
            V[i]=somma;
            }
        /*std::cout<<"Vettore V: \n";
        std::cout<<V<<"\n";*/
        
        /*Calcolo la matrice A=B'RB*/
        Eigen::MatrixXd A = B.transpose()*R*B;
        /*std::cout<<A<<"\n";*/
        /*Eigen::VectorXd i = A.inverse()*V;*/


        /*calcolo ciò che mi serve per applicare il gradiente coniugato in modo 
        da trovare il valore delle correnti nelle singole maglie*/
        Eigen::VectorXd x0 = Eigen::VectorXd::Zero(cicli.size());
        const double r_tol = 1.0e-12;
        Eigen::VectorXd r = V - A*x0; 
        Eigen::VectorXd x = gradiente_coniugato(A,x0,V,r,r_tol);
        
        /*calcolo il valore delle correnti*/
        Eigen::VectorXd i=B*x;

        Eigen::VectorXd Tensioni=R*i;
        /*std::cout<<"Tensioni:\n";
        std::cout<<Tensioni;*/


        /*OUTPUT*/
        int w=0;
        for(const auto& key:resistenza_valore){
            std::cout<<key.first<<": ";
            std::cout<<"V= "<<Tensioni[w]<<" volts, ";
            std::cout<<"I= "<<i[w]<<" amps.\n";
            w++;
        }


        

    } else {
        cout << "Errore nell'apertura del file";
    }

    return 0;
}