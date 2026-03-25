#include <iostream>

int main()
{
    static const int N = 10;
    double arr[N] = {0,1,7,2,5,4,8,3,9,6};
    bool cambio = 1;

    while (cambio==1) {
        cambio = 0;
        for (int i = 0; i < N-1; i++) {
            if (arr[i] > arr[i+1]) {
                double var = arr[i+1];
                arr[i+1] = arr[i];
                arr[i] = var;
                cambio = 1;
            }
        }
    }
for (int i = 0; i < N; i++) {
    std::cout << arr[i] << " "; 
}
}