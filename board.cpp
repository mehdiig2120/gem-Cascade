#include <iostream>
#include <array>
#include <Windows.h>
using namespace std;

int main(){
    SetConsoleOutputCP(CP_UTF8);
    array<array<int, 8>, 8> board; // the size of board is 8x8

    for(int row = 0; row < 8; row++){
        for(int col = 0; col < 8; col++){
            board[row][col] = 0;
        }
    }
    board[2][2] = 4;

    cout << "┌───┬───┬───┬───┬───┬───┬───┬───┐" << endl;

    for(int row = 0; row < 8; row++){
        for(int col = 0; col < 8; col++){
            
        cout << "│ " << board[row][col] << " ";

        }
        cout << "│" << endl;
        
        if(row < 7){
            cout << "├───┼───┼───┼───┼───┼───┼───┼───┤" << endl;
        }
    }
    cout << "└───┴───┴───┴───┴───┴───┴───┴───┘" << endl;
    return 0;
}