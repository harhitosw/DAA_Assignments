#include <bits/stdc++.h>
using namespace std;
// THIS PROGRAM USES pthreads which is available only on POSIX compliant systems so use WSL or any Linux environment
// read pthread documentations or ChatGPT to know more about this
// use command "g++ -pthread file_name.cpp" to compile the program and ./a.out to get the output
// maximum size of matrix
#define MAX 5
 
// maximum number of threads
#define MAX_THREAD 4
 
int matA[MAX][MAX];
int matB[MAX][MAX];
int matC[MAX][MAX];
int step_i = 0;
 
void* multi(void* arg)
{
    int i = step_i++; //i denotes row number of resultant matC
   
    for (int j = 0; j < MAX; j++)
      for (int k = 0; k < MAX; k++)
        matC[i][j] += matA[i][k] * matB[k][j];
}
 
// Driver Code
int main()
{
    // Generating random values in matA and matB
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            matA[i][j] = rand() % 10;
            matB[i][j] = rand() % 10;
        }
    }
 
    // Displaying matA
    cout << endl
         << "Matrix A" << endl;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++)
            cout << matA[i][j] << " ";
        cout << endl;
    }
 
    // Displaying matB
    cout << endl
         << "Matrix B" << endl;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++)
            cout << matB[i][j] << " ";       
        cout << endl;
    }
     
    // declaring four threads
    pthread_t threads[MAX_THREAD];
    auto start=chrono::high_resolution_clock::now();
    // Creating four threads, each evaluating its own part
    for (int i = 0; i < MAX_THREAD; i++) {
        int* p;
        pthread_create(&threads[i], NULL, multi, (void*)(p));
    }
 
    // joining and waiting for all threads to complete
    for (int i = 0; i < MAX_THREAD; i++)
        pthread_join(threads[i], NULL);   
    auto stop=chrono::high_resolution_clock::now();
     auto duration =chrono:: duration_cast<chrono::nanoseconds>(stop - start);
        // int stop=clock();
    cout<<"The duration is"<<duration.count()<<endl;
 
    // Displaying the result matrix
    cout << endl
         << "Multiplication of A and B" << endl;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++)
            cout << matC[i][j] << " ";       
        cout << endl;
    }
    return 0;
}
