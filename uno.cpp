#include <iostream>
#include <vector>
#include <ctime>
using namespace std;
const int MAX = 5000;
double A[MAX][MAX], x[MAX], y[MAX];

void initialize() {
    for(int i = 0; i < MAX; i++) {
        for(int j = 0; j < MAX; j++) {
            A[i][j] = i + j;
        }
        x[i] = i;
        y[i] = 0;
    }
}

void first_loop() 
{
    for(int i = 0; i < MAX; i++) {
        for(int j = 0; j < MAX; j++) {
            y[i] += A[i][j] * x[j];
        }
    }
}

void second_loop()
 {
    for(int j = 0; j < MAX; j++) {
        for(int i = 0; i < MAX; i++) {
            y[i] += A[i][j] * x[j];
        }
    }
}

int main() 
{
    initialize();
    
    clock_t start = clock();
    first_loop();
    clock_t end = clock();
    cout << "First loop time: " << double(end - start) / CLOCKS_PER_SEC << " seconds.\n";
    
    initialize();
    
    start = clock();
    second_loop();
    end = clock();
    cout << "Second loop time: " << double(end - start) / CLOCKS_PER_SEC << " seconds.\n";
    
    return 0;
}