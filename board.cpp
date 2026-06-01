#include <iostream>
#include <array>
using namespace std;

int main(){

    array<array<int, 8>, 8> board; // the size of board is 8x8

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            board[i][j] = 0;
        }
    }
    board[2][2] = 1;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            
            cout << " |__ " << board[i][j] << " __| ";
        }
        cout << endl;
    }
    return 0;
}