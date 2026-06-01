#include <iostream>
#include <array>
using namespace std;

int main(){

    array<array<int, 8>, 8> board; // the size of board is 8x8

    for(int i = 1; i <= 8; i++){
        for(int j = 1; j <= 8; j++){
            board[i][j] = 0;
        }
    }

}