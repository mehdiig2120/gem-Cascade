#include <iostream>
#include <array>
#include <Windows.h>
#include <string>
#include <ctime> // for time limit
#include <cstdlib> // for random access

using namespace std;

namespace color{   
    const string RESET   = "\033[0m"; // sort color of terminal
    const string RED     = "\033[31m";
    const string GREEN   = "\033[32m";
    const string YELLOW  = "\033[33m";
    const string BLUE    = "\033[34m";
    const string PURPLE  = "\033[35m";
}

int main(){
    SetConsoleOutputCP(CP_UTF8); // for drawing in terminal
    
    srand(time(0)); // using for draw board term of random access by number and shaper array

    array<string, 6> shapes = {
        " ",// stage 0 = empty 
        color::RED + "■" + color::RESET,     // stage 1
        color::GREEN + "▲" + color::RESET,   // stage 2     
        color::YELLOW + "●" + color::RESET,  // stage 3
        color::BLUE + "◆" + color::RESET,   //  stage 4
        color::PURPLE + "★" + color::RESET  //  stage 5
    };

    array<array<int, 8>, 8> board; // the size of board is 8x8

    for(int row = 0; row < 8; row++){
        for(int col = 0; col < 8; col++){
            board[row][col] = (rand() % 5) + 1; // random number
        }
    }
    

    cout << "┌───┬───┬───┬───┬───┬───┬───┬───┐" << endl;

    for(int row = 0; row < 8; row++){
        for(int col = 0; col < 8; col++){
            int shapeIndex = board[row][col];
            cout << "│ " << shapes[shapeIndex] << " "; // give random number and draw shape

        }
        cout << "│" << endl;
        
        if(row < 7){
            cout << "├───┼───┼───┼───┼───┼───┼───┼───┤" << endl; // main line
        }
    }
    cout << "└───┴───┴───┴───┴───┴───┴───┴───┘" << endl; // finall line
    return 0;
}


   