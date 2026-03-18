#include <fstream>
#include <iostream>
#include <string>
using namespace std; // così non devo scrivere std:: prima di ogni comando

int main(int argc, const char *argv[]) 
{
    if (argc == 1) {
        std::cout << "Errore: inserisci il nome del file";
        return 1;}
    string filename = argv[1];
    ifstream ifs(filename);
    if (!ifs.is_open() ) { // controlla che il file si sia aperto
        std::cout << "Errore: il file non si è aperto correttamente";
        return 1;}
    string citta;
    double t1, t2, t3, t4;
    while( !ifs.eof() ) {
        ifs >> citta >> t1 >> t2 >> t3 >> t4;
        double media_t = (t1+t2+t3+t4)/4;
        cout << citta << " " << media_t << "\n";}
return 0;
}