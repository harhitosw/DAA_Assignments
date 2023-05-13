#include<bits/stdc++.h>
using namespace std;

bool isSafe(int** arr,int x,int y,int n){

    // column checking
    for(int row = 0; row < x; row++){
        if(arr[row][y]==1){
            return false;
        }
    }

    // diagonal checking
    int row = x;
    int col = y;
    
    // left diagonal
    while(row>=0 && col>=0){
        if(arr[row][col]==1){
            return false;
        }
        row--;
        col--;
    }

    // right diagonal
    row = x;
    col = y;
    
    while(row>=0 && col<n){
        if(arr[row][col]==1){
            return false;
        }
        row--;
        col++;
    }

    return true;
}

bool NQueens(int** arr,int x,int n){

    if(x>=n){
        return true;
    }

    // check whether it is safe to place the queen

    for(int col = 0; col < n; col++){
        if(isSafe(arr,x,col,n)){
            arr[x][col] = 1;

            if(NQueens(arr,x+1,n)){
                return true;
            }

            arr[x][col] = 0; // backtracking
        }
    }
    return false;
}

int main(int argc, char **argv){
    //type your code below
    int n;
    cout << "Enter a number to begin" << endl;
    cin >> n;

    // getting the matrix

    int **arr = new int*[n];
    for(int i = 0; i < n; i++){
        arr[i] = new int[n];
        for(int j = 0; j < n; j++){
            arr[i][j] = 0; 
        }
    }

    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();    
    if(NQueens(arr,0,n)){
        for(int i=0;i < n;i++){
            for(int j = 0;j < n;j++){
                cout<<arr[i][j];
            }cout<<endl;
        }
    }

    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "finished computation at " << std::ctime(&end_time)
                << "elapsed time: " << elapsed_seconds.count() << "s\n";    

    return 0;
}
