#include <iostream>  
#include <pthread.h> 
#include <cstdlib>   

// Constants for matrix dimensions
const int rowsA = 3;  // Number of rows in matrix A
const int colsA = 5;  // Number of columns in matrix A (and rows in matrix B)
const int colsB = 4;  // Number of columns in matrix B

// Matrix definitions using static storage
int matA[rowsA][colsA] = { {2, 4, 6, 8, 10}, {3, 6, 9, 12, 15}, {4, 8, 12, 16, 20} };  // Initial values for matrix A
int matB[colsA][colsB] = { {1, 3, 5, 7}, {2, 4, 6, 8}, {3, 6, 9, 12}, {4, 8, 12, 16}, {5, 10, 15, 20} };  // Initial values for matrix B
int matC[rowsA][colsB] = { 0 };  // Result matrix, initialized to zero

// Struct to hold thread data
struct ThreadData {
    int rowIndex;  // Stores the specific row index each thread will process
};

// Thread function to multiply one row of matA with matB
void* rowMultiplication(void* arg) {
    ThreadData* data = (ThreadData*)arg;  // Convert void* to ThreadData* to access the data
    int row = data->rowIndex;  // Get the row index to process

    // Iterate over each column of matB
    for (int j = 0; j < colsB; j++) {
        // Initialize the result cell to zero
        matC[row][j] = 0;  
        // Perform the dot product of the row from matA and column from matB
        for (int k = 0; k < colsA; k++) {
            matC[row][j] += matA[row][k] * matB[k][j];
        }
    }
    return NULL;  // Return NULL as required by the pthreads function signature
}

int main() {
    pthread_t threads[rowsA];  // Array to store thread identifiers
    ThreadData threadData[rowsA];  // Array of struct to hold data for each thread

    // Create one thread for each row of matrix A
    for (int i = 0; i < rowsA; i++) {
        threadData[i].rowIndex = i;  // Set the row index for each struct
        pthread_create(&threads[i], NULL, rowMultiplication, (void*)&threadData[i]);  // Start a new thread
    }

    // Wait for all threads to finish
    for (int i = 0; i < rowsA; i++) {
        pthread_join(threads[i], NULL);  // Block until thread[i] completes
    }

    // Output the matrices and the result
    std::cout << "Matrix A:\n";
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsA; j++) {
            std::cout << matA[i][j] << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\nMatrix B:\n";
    for (int i = 0; i < colsA; i++) {
        for (int j = 0; j < colsB; j++) {
            std::cout << matB[i][j] << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\nResult Matrix:\n";
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            std::cout << matC[i][j] << " ";
        }
        std::cout << "\n";
    }

    return 0;
}
