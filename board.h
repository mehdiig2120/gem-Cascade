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

        for(int r=0; r<8; r++){
            for(int c=0; c<8; c++){
                board[r][c] = 0;
            }
        }

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
        cout << "                                "<<"                         "  <<"you can use this Power_ups :" << endl;
        cout << "                                   " << "                      " << "1) use a Bomb with 120 score (3x3) " << endl;
        cout << "                                   " << "                      " << "2) use a Rocket with 100 score (delete a row or col)" << endl;
        cout << "                                   " << "                      " << "3) Hint with 70 score" <<endl;

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

    bool check_matches(int row, int col) {
        if (row < 0 || row >= 8 || col < 0 || col >= 8 || board[row][col] == 0) return false;
        //checking match in row
        if (col >= 2 && board[row][col] == board[row][col-1] && board[row][col] == board[row][col-2]){
            return true;
        }

        if (col >= 1 && col <= 6 && board[row][col] == board[row][col-1] && board[row][col] == board[row][col+1]){
            return true;
        } 

        if (col <= 5 && board[row][col] == board[row][col+1] && board[row][col] == board[row][col+2]){
            return true;
        } 
        // checking match in col
        if (row >= 2 && board[row][col] == board[row-1][col] && board[row][col] == board[row-2][col]){
            return true;
        }

        if (row >= 1 && row <= 6 && board[row][col] == board[row-1][col] && board[row][col] == board[row+1][col]){
            return true;
        } 

        if (row <= 5 && board[row][col] == board[row+1][col] && board[row][col] == board[row+2][col]){
            return true;
        }

        return false;
    }

    // nuts boom !
    bool crush() {
        array<array<bool, 8>, 8> to_crush = {false}; // an matrix with matched nuts
        int count_crush = 0;

        for (int row = 0; row < 8; row++){
            for(int col =0; col <8; col++){
                if(check_matches(row, col)){
                    to_crush[row][col] = true;
                }
            }
        }
        for (int row = 0; row < 8; row++){
            for(int col =0; col <8; col++){
                if(to_crush[row][col]){
                    count_crush++;
                    board[row][col] = 0;
                }
            }
        }
        return count_crush; // true -> if we have a matched nuts it returns the count of macthced nut . it will be using for score
    }

    void gravity(){
        for(int col =0; col<8; col++){
            int empty_row = 7; //  we imagine line 7 is empty!
            for (int row=7; row>=0; row--){
                if (board[row][col] != 0){
                    if(row != empty_row){
                        board[empty_row][col] = board[row][col];
                        board[row][col] = 0;
                    }
                empty_row--; // line-up now is empty!
                }
            }
        }
    }

    void fill_board(){ // after gravity we must fill board again
        for(int row=0; row<8; row++){
            for(int col=0; col<8; col++){
                if(board[row][col] == 0){
                    board[row][col] = (rand() % 5) + 1;
                }
            }
        }
    }

    void swp(string a, string b,int & score){ // like e7
        int cola = a[0] - 'a';
        int colb = b[0] - 'a';
        
        int rowa = a[1] - '1';
        int rowb = b[1] - '1';

        if(rowa >=0 && rowa < 8 && rowb >= 0 && rowb < 8 && cola >=0 && cola < 8 && colb >=0 && colb <8){
            int row_dif = abs(rowa - rowb);
            int col_dif = abs(cola - colb);
            if((row_dif == 0 && col_dif == 1) || (row_dif == 1 && col_dif == 0)){
                swap(board[rowa][cola], board[rowb][colb]);
                if (check_matches(rowa, cola) || check_matches(rowb, colb)){
                    cout << "Nice move !" << endl;
                    Sleep(1000);

                    int k = 10;
                    int nuts_crush = 0;

                    while(( nuts_crush = crush()) > 0){ // until we have matched nuts 
                        score += k * nuts_crush;
                        k*=2;

                        system("cls");
                        draw();
                        Sleep(2500);

                        gravity();
                        system("cls");
                        draw();
                        Sleep(2500);

                        fill_board();
                        system("cls");
                        Sleep(1500);
                    }
                }

                else{ // harekat gheir mojaz
                    swap(board[rowa][cola], board[rowb][colb]);
                    cout << "Can't move ! (not mathced )" << endl;
                    Sleep(1000);
                }
            }
        }
        else {
            cout << "Error ! invalid move or incorrect input " << endl; 
            Sleep(2000);
        }
    }
}; // ; it's used for class in oop 
 

