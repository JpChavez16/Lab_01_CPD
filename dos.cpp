#include <iostream>
#include <ctime>  
#include <cstdlib>

using namespace std;


void initializeMatrix(double** matrix, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrix[i][j] = rand() % 100;  
        }
    }
}


void printMatrix(double** matrix, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}


void multiplyMatricesClassic(double** A, double** B, double** C, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < size; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}


void multiplyMatricesBlocked(double** A, double** B, double** C, int size, int blockSize) 
{
    for (int i = 0; i < size; i += blockSize) {
        for (int j = 0; j < size; j += blockSize) {
            for (int k = 0; k < size; k += blockSize) {
                
                for (int ii = i; ii < min(i + blockSize, size); ++ii) {
                    for (int jj = j; jj < min(j + blockSize, size); ++jj) {
                        for (int kk = k; kk < min(k + blockSize, size); ++kk) {
                            C[ii][jj] += A[ii][kk] * B[kk][jj];
                        }
                    }
                }
            }
        }
    }
}

int main() {
    
    int size, blockSize;
    cout << "Ingresa el tamaño de la matriz: ";
    cin >> size;
    cout << "Ingresa el tamaño del bloque: ";
    cin >> blockSize;

    
    double** A = new double*[size];
    double** B = new double*[size];
    double** C_classic = new double*[size];
    double** C_blocked = new double*[size];

    for (int i = 0; i < size; ++i) {
        A[i] = new double[size];
        B[i] = new double[size];
        C_classic[i] = new double[size];
        C_blocked[i] = new double[size];
    }

    
    initializeMatrix(A, size);
    initializeMatrix(B, size);

    // Inicializar C_classic y C_blocked en 0
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            C_classic[i][j] = 0;
            C_blocked[i][j] = 0;
        }
    }

   
    clock_t start = clock();
    multiplyMatricesClassic(A, B, C_classic, size);
    clock_t end = clock();
    double timeClassic = double(end - start) / CLOCKS_PER_SEC;

    
    start = clock();
    multiplyMatricesBlocked(A, B, C_blocked, size, blockSize);
    end = clock();
    double timeBlocked = double(end - start) / CLOCKS_PER_SEC;

    
    cout << "Tiempo de ejecución para multiplicación clásica: " << timeClassic << " segundos." << endl;
    cout << "Tiempo de ejecución para multiplicación por bloques: " << timeBlocked << " segundos." << endl;

    
    for (int i = 0; i < size; ++i) {
        delete[] A[i];
        delete[] B[i];
        delete[] C_classic[i];
        delete[] C_blocked[i];
    }
    delete[] A;
    delete[] B;
    delete[] C_classic;
    delete[] C_blocked;

    return 0;
}
