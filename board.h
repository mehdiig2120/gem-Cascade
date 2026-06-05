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

class Board{
    public:
        array<array<int, 8>, 8> board; // the size of board is 8x8
        array<string, 6> shapes;
    public:
        Board(){
        SetConsoleOutputCP(CP_UTF8); // for drawing in terminal
        SetConsoleCP(CP_UTF8);
    
        srand(time(0)); // using for draw board term of random access by number and shaper array

        shapes = {
            " ",// stage 0 = empty 
            color::RED + "■" + color::RESET,     // stage 1
            color::GREEN + "▲" + color::RESET,   // stage 2     
            color::YELLOW + "●" + color::RESET,  // stage 3
            color::BLUE + "◆" + color::RESET,   //  stage 4
            color::PURPLE + "★" + color::RESET  //  stage 5
        };
        gen_board();
    }



    void gen_board(){
        for(int row = 0; row < 8; row++){
            for(int col = 0; col < 8; col++){
                while(true) {
                    int number = (rand() % 5) + 1; // random number
                    bool repeat = false;

                    // serching for repeat in row
                    if (col >= 2) {
                        if (board[row][col-1] == number && 
                            board[row][col-2] == number) {
                            repeat = true; // repeat found
                        }
                    }

                    // seching for repeat in col
                    if (row >= 2) {
                        if (board[row-1][col] == number && 
                            board[row-2][col] == number) {
                            repeat = true; // repeat found
                        }
                    }

                    if (!repeat) { // if we can't find any repeat
                        board[row][col] = number;
                        break; 
                    }
                    // if we can find a repeat -> another while loop for another drawing
                }

            }
        }
    }
    void draw(){
        cout << "    a   b   c   d   e   f   g   h  " << endl;
        cout << "  ┌───┬───┬───┬───┬───┬───┬───┬───┐" << endl;

        for(int row = 0; row<8; row++){
            cout << row + 1 << " │ ";
            
            for(int col = 0; col < 8; col++){
                int shapeIndex = board[row][col];
                if(col < 7){
                    cout << shapes[shapeIndex] << " │ ";
                    }
                else{
                    cout << shapes[shapeIndex] << " │";
                }
                }
                cout << endl;
                
                if(row < 7){
                    cout << "  ├───┼───┼───┼───┼───┼───┼───┼───┤" << endl;// main line
                }
            
        }
        cout << "  └───┴───┴───┴───┴───┴───┴───┴───┘" << endl; // finall line
    }

    bool check_matches(){
        for(int row =0; row<8; row++){
            for(int col = 0; col<6; col++){
                if(board[row][col] != 0 && // my board completed with numbers . this line means it's not empty
                    board[row][col] == board[row][col + 1]&&
                    board[row][col] == board[row][col + 2]){
                        return true;
                    }
            }
        }

        for(int col =0; col<8; col++){
            for(int row = 0; row<6; row++){
                if(board[row][col] != 0 &&
                    board[row][col] == board[row +1][col]&&
                    board[row][col] == board[row +2][col]){
                        return true;
                    }
            }
        }
        return false; // we can't find any matched nuts
    }


    void swp(string a, string b){ // like e7
        int cola = a[0] - 'a';
        int colb = b[0] - 'a';
        
        int rowa = a[1] - '1';
        int rowb = b[1] - '1';

        if(rowa >=0 && rowa < 8 && rowb >= 0 && rowb < 8 && cola >=0 && cola < 8 && colb >=0 && colb <8){
            swap(board[rowa][cola], board[rowb][colb]);
            if (check_matches()){
                cout << "Nice move !" << endl;
                Sleep(1000);
            }

            else{
                swap(board[rowa][cola], board[rowb][colb]);
                cout << "Can't move ! (not mathced )" << endl;
                Sleep(1000);
            }
        }
        else {
            // harakat gheir mojaz
            cout << "Error ! invalid move or incorrect input " << endl; 
            Sleep(2000);
        }
    }
}; // ; it's used for class in oop 
 

