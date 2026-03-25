#include <iostream>
#include <cmath> // altrimenti mi dà errore "sqrt' is not a member of 'std'"

int main()
{
    static const int N = 10;
    double arr[N] = {0,1,2,3,4,5,6,7,8,9};
    double min =  arr[0];
    double max =  arr[0];
    double sum_avg = 0;
    double sum_svd = 0;
    
    for (int i = 0; i < N; i++) {
        min = std::min(min,arr[i]);
        max = std::max(max,arr[i]);
        sum_avg += arr[i];
    }

double avg = sum_avg/N;

    for (int i = 0; i < N; i++) {
        sum_svd += (arr[i]-avg)*(arr[i]-avg);
    }
double svd = std::sqrt(sum_svd/N);
    
std::cout << "Minimo: " << min << "\n" << "Massimo: " << max << "\n" << "Media: " << avg << "\n" << "Dev. Stand: " << svd;
}