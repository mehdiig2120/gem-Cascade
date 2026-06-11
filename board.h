#include <iostream>
#include <array>
#include <Windows.h>
#include <string>
#include <ctime> // for time limit
#include <cstdlib> // for random access
#include <fstream> // for saving 

using namespace std;

namespace color{   
    const string RESET   = "\033[0m"; // sort color of terminal
    const string RED     = "\033[31m";
    const string GREEN   = "\033[32m";
    const string YELLOW  = "\033[33m";
    const string BLUE    = "\033[34m";
    const string PURPLE  = "\033[35m";
    const string WHITE   = "\033[37m";
}

class Board{
    public:
        array<array<int, 8>, 8> board; // the size of board is 8x8
        array<string, 8> shapes;
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
            color::PURPLE + "★" + color::RESET,  //  stage 5
            color::WHITE + "❈" + color::RESET, // stage 6 = boom
            color:: WHITE + "░" + color::RESET //  stage 7 = smoke
        };
        gen_board();
    }

    void save_game(ofstream& out_file){
        for(int i = 0; i< 8; i++){
            for(int j=0; j<8; j++){
                out_file << board[i][j] << " ";
            }
            out_file << "\n";
        }

    }

    void load_game(ifstream& in_file){
        for(int i=0; i< 8; i++){
            for(int j=0; j< 8; j++){
                in_file >> board[i][j];
            }
        }
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

    void heder(string name, int score, int time_left) {
        int minute = time_left / 60;
        int second = time_left % 60;

        cout << "+-----------------------------------------------+" << endl;
        cout << "│ player name: " << name << " │ Time: " << minute << ":";
        if (second < 10) cout << "0";
        cout << second << " │ Score: " << score << "    │"  << endl;
        cout << "+-----------------------------------------------+" << endl;
        cout << endl;
        draw();
    }


    // nuts boom !
    int crush(bool show_animation = true) {
        array<array<bool, 8>, 8> to_crush = {false}; // an matrix with matched nuts
        bool match5_triggered = false;
        int match5_type = 0;

        bool row_match4_triggered[8] = {false};
        bool col_match4_triggered[8] = {false};

        int count_crush = 0;
        
        // checking match 4-5 in row
        for (int row = 0; row < 8; row++){
            int match_len = 1;
            for (int col = 0; col < 8; col++){
                if (col < 7 && board[row][col] == board[row][col + 1] && board[row][col] != 0){
                    match_len++ ;
                }
                else{
                    if (match_len >= 3){
                        int type = board[row][col - 1];

                        // label nuts
                        for(int i = 0; i< match_len; i++){
                            to_crush[row][col -  i] = true;
                        }
                        // 5 nuts match
                        if (match_len >= 5){
                            match5_triggered = true;
                            match5_type = type;
                        }
                        else if(match_len == 4){
                            row_match4_triggered[row] = true; 
                        }
                    }
                    match_len = 1;
                }
            }
        }
        // checking 4-5 matched in col
        for (int col = 0; col < 8; col++){
            int match_len = 1;
            for(int row = 0; row < 8; row++){
                if (row < 7 && board[row][col] == board[row + 1][col] && board[row][col] != 0){
                    match_len++;
                }

                else{

                    if(match_len >=3){
                        int type = board[row - 1][col]; // kind of nuts

                        for(int i =0; i<match_len; i++){
                            to_crush[row - i ][col] = true;
                        }

                        if(match_len >=5){
                            match5_triggered = true;
                            match5_type = type;
                        }

                        else if(match_len == 4){
                            col_match4_triggered[col]  = true;
                        }
                    }
                    match_len = 1;   // after crush nuts 
                }
            }
        }

        // delete every nuts in board
        if (match5_triggered) {
            for (int r = 0; r < 8; r++) {
                for (int c = 0; c < 8; c++) {
                    if (board[r][c] == match5_type) {
                        to_crush[r][c] = true;
                    }
                }
            }
        }

        // match-5 for row
        for (int r = 0; r < 8; r++) {
            if (row_match4_triggered[r]) {
                for (int c = 0; c < 8; c++) {
                    to_crush[r][c] = true;
                }
            }
        }

        // match-4 for col
        for (int c = 0; c < 8; c++) {
            if (col_match4_triggered[c]) {
                for (int r = 0; r < 8; r++) {
                    to_crush[r][c] = true;
                }
            }
        }


        for (int row = 0; row < 8; row++){
            for(int col =0; col <8; col++){
                if(to_crush[row][col]){
                    count_crush++;
                }
            }
        }
        
        // showing boom for nuts
        if(show_animation){
            if (count_crush > 0){
                for(int row=0; row<8; row++){
                    for(int col=0; col<8; col++){
                        if(to_crush[row][col]){
                            board[row][col] = 6;
                        }
                    }
                }
            }
        
            system("cls");
            draw();
            Sleep(500); // time of showing
        

            // showing smoke
            for(int row=0; row<8; row++){
                for(int col=0; col<8; col++){
                    if(to_crush[row][col]){
                        board[row][col] = 7;
                    }
                }
            }
            
            system("cls");
            draw();
            Sleep(500);
        }


        for (int row = 0; row < 8; row++){
            for(int col =0; col <8; col++){
                if(to_crush[row][col]){
                    board[row][col] = 0 ;
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

    void swp(string a, string b,int & score, string name, int time_left){ // like e7
        int cola = a[0] - 'a';
        int colb = b[0] - 'a';
        
        int rowa = a[1] - '1';
        int rowb = b[1] - '1';

        if(rowa >=0 && rowa < 8 && rowb >= 0 && rowb < 8 && cola >=0 && cola < 8 && colb >=0 && colb <8){
            int row_dif = abs(rowa - rowb);
            int col_dif = abs(cola - colb);
            
            // checking the neighborhood
            if((row_dif == 0 && col_dif == 1) || (row_dif == 1 && col_dif == 0)){ 

                swap(board[rowa][cola], board[rowb][colb]);

                int nuts_crush = crush(); // checking first crush

                if (nuts_crush > 0){
                    cout << "\nNice move !" << endl;
                    Sleep(2000);

                    int k = 10;
                

                    while( nuts_crush  > 0){ // until we have matched nuts 
                        score += k * nuts_crush;
                        k*=2;

                        system("cls");
                        heder(name, score, time_left);
                        Sleep(2500);

                        gravity();
                        system("cls");
                        heder(name, score, time_left);
                        Sleep(2500);

                        fill_board();
                        system("cls");
                        heder(name, score, time_left);
                        Sleep(1500);

                        nuts_crush = crush();
                    }
                    if (!check_harekat()){
                        shuffle_board(name, score, time_left);
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

    void bomb(string nut, int & score, string name, int time_left){

        int row, col;

        while (true)
        {
            col = nut[0] - 'a';
            row = nut[1] - '1';
            
            if(row < 0 || row >=8 || col < 0 || col >=8){

                cout << "Error ! Invalid input  " << endl;
                cout << "write correctly (like e5) : " << endl;
                cin >> nut;
                system("cls");
                Sleep(2000);
                draw();
                continue;

            }

            if(row == 0 || row == 7 || col == 0 || col == 7){
                system("cls");
                heder(name, score, time_left);
                cout << "You can't use bomb because it's on the corner (Must be center !)" << endl;
                cout << "give me a nut again : " << endl;
                cin >> nut;
                system("cls");
                Sleep(2000);
                draw();
                continue;
                }
            else{
                Sleep(1500);
                for(int r = row - 1; r <= row + 1; r++){
                    for(int c = col -1; c <=col + 1; c++ ){
                        board[r][c] = 0;
                    }
                }
                
                system("cls");
                heder(name, score, time_left);
                cout << "Poooofff! bomb used!" <<endl;
                Sleep(1500);

                


                system("cls");
                heder(name, score, time_left);
                Sleep(1500);

                gravity();
                system("cls");
                heder(name, score, time_left);
                Sleep(1500);

                fill_board();
                system("cls");
                heder(name, score, time_left);
                Sleep(1500);

                // checking matched again

                int nuts_crush = crush();
                int k = 10;

                while( nuts_crush  > 0){ // until we have matched nuts 
                    score += k * nuts_crush;
                    k*=2;

                    system("cls");
                    heder(name, score, time_left);
                    Sleep(2500);

                    gravity();
                    system("cls");
                    heder(name, score, time_left);
                    Sleep(2500);

                    fill_board();
                    system("cls");
                    heder(name, score, time_left);
                    Sleep(1500);

                    nuts_crush = crush();
                }
                if(!check_harekat()){
                    shuffle_board(name, score, time_left); // check bombast bad az power_ups
                }
                break;   
            }
        }
    }
    
    void rocket(int & score, string name, int time_left){
        int in_r , in_c;
        while(true){
            string answerr;
            cout << "You want use rocket for row or col (r/c) ?" << endl;
            cin >> answerr;
            if(answerr == "r"){
                string answerr2;
                cout << "give me  a row (1-8) :" << endl;
                cin >> answerr2;
                system("cls");
                Sleep(2000);

                if(answerr2.length() != 1){ // like 2000
                    cout << "pleasa write correctly(1-8)" << endl;
                    Sleep(1500);
                    system("cls");
                    heder(name, score, time_left);
                    continue;
                }

                in_r = answerr2[0] - '1';
                if(in_r < 0 || in_r >=8){
                    cout << "Invalid row! Try again." << endl;
                    Sleep(1500);
                    system("cls");
                    heder(name, score, time_left);
                    continue;
                }
                for(int c = 0; c<8; c++){
                    board[in_r][c] = 0;
                }
                break;
            }
            else if(answerr == "c"){
                string answerr3;
                cout << "give me a col (a-h):" << endl;
                cin >> answerr3;
                in_c  = answerr3[0] - 'a';
                if(in_c < 0 || in_c >=8){
                    cout << "Invalid col! Try again.!" << endl;
                    Sleep(1500);
                    system("cls");
                    heder(name, score, time_left);
                    continue;
                }

                for(int r =0; r<8; r++){
                    board[r][in_c] = 0;
                }
                break;
            }
            else{
                cout << "please write correctly" << endl;
                Sleep(2000);
                system("cls");
                heder(name, score, time_left);
                continue;
            }
        }
        system("cls");
        heder(name, score, time_left);
        cout << "fisssshhh! Rocket used" <<endl;
        Sleep(1500);

                
        system("cls");
        heder(name, score, time_left);
        Sleep(1500);

        gravity();
        system("cls");
        heder(name, score, time_left);
        Sleep(1500);

        fill_board();
        system("cls");
        heder(name, score, time_left);
        Sleep(1500);

        // checking matched again

        int nuts_crush = crush();
        int k = 10;

        while( nuts_crush  > 0){ // until we have matched nuts 
            score += k * nuts_crush;
            k*=2;

            system("cls");
            heder(name, score, time_left);
            Sleep(2500);

            gravity();
            system("cls");
            heder(name, score, time_left);
            Sleep(2500);

            fill_board();
            system("cls");
            heder(name, score, time_left);
            Sleep(1500);

            nuts_crush = crush();
        }
        if (!check_harekat()){
            shuffle_board(name, score, time_left);
        }
    }


    void Hint(){
        int max_crush = 0;
        string f_nut = "";
        string s_nut = "";
        bool move = false;
        array <array<int, 8>, 8> vit_board = board ; // import main board to vitural board for avoid repeat 

        for(int r = 0; r<8; r++){
            for(int c = 0; c<8; c++){

                // checking row
                if (c<7){
                    swap(board[r][c], board[r][c+1]);
                    int now_crush = crush(false); // stop showing animation 
                    if(now_crush > max_crush){
                        max_crush = now_crush;
                        f_nut = string(1, 'a' + c) + to_string(r + 1); // like g7
                        s_nut = string(1, 'a' + (c+1)) + to_string(r+1);
                        move = true;
                    }
                }
                board = vit_board; // back to bace shape whitout move any nut

                // checking col
                if (r<7){
                    swap(board[r][c], board[r+1][c]);
                    int now_crush = crush(false); // stop showing animation 
                    if(now_crush > max_crush){
                        max_crush = now_crush;
                        f_nut = string(1, 'a' + c) + to_string(r + 1); // like g7
                        s_nut = string(1, 'a' + c) + to_string(r+2);
                        move = true;
                    }
                }
                board = vit_board;
            }
        }   
        cout << "\nSearching ..." << endl;
        Sleep(2000);
        if(move){
            cout << "\nHint : Swap  " << color::GREEN << f_nut << color::RESET << "  with  " << color::GREEN << s_nut << color::RESET <<  "\nYou can broke " << color::RED << max_crush << color::RESET <<" nut !" << endl;
            }

        else{
            cout << color::RED << "No matching move found!" << color::RESET << endl;
            }

        Sleep(5000);
    }
    



    int vojode_harekat(){
        for(int r = 0; r<8; r++){
            for(int c =0; c<6; c++){
                if(board[r][c] != 0 && board[r][c] == board[r][c+1] && board[r][c] == board[r][c+2]){
                    return 1;
                }
            }
        }    
        for(int c = 0; c<8; c++){
            for(int r=0; r<6; r++){
                if(board[r][c] != 0 && board[r][c] == board[r+1][c] & board[r][c] == board[r+2][c]){
                    return 1;
                }
            }
        }
        return 0; // yani agar harakati vojod nadasht mire srogh bor zadan!
    }

    bool check_harekat(){
        for(int r =0; r<8; r++){
            for(int c=0; c<8; c++){
                if(c<7){
                    swap(board[r][c], board[r][c+1]); // jabajaii 
                    int check = vojode_harekat();
                    swap(board[r][c], board[r][c+1]); // bargashte 
                    if (check > 0){
                        return true;
                    }
                }

                if(r<7){
                    swap(board[r][c], board[r+1][c]); // jabajaii 
                    int check = vojode_harekat();
                    swap(board[r][c], board[r+1][c]); // bargashte 
                    if (check > 0){
                        return true;
                    }
                }
            }
        }
        return false;
    }

    void shuffle_board(string name, int score, int time_left) { // we push nuts in new space and pull them random in board again
        system("cls");
        heder(name, score, time_left);
        cout << color::YELLOW << "\nNo moves left! Shuffling the board (Method 2)..." << color::RESET << endl;
        Sleep(2500);

        array<int, 64> box;

        while (true) {
            int index = 0;
            for (int r = 0; r < 8; r++) {
                for (int c = 0; c < 8; c++) {
                    box[index++] = board[r][c];
                }
            }

            int remaining_items = 64;
            for (int r = 0; r < 8; r++) {
                for (int c = 0; c < 8; c++) {
                    int random_idx = rand() % remaining_items;  // making random nuts (like in gen_board func)
                    board[r][c] = box[random_idx];            
                    
                    box[random_idx] = box[remaining_items - 1]; // delete a nut from box for Avoid repetition 
                    remaining_items--;
                }
            }
            // check for move !
            if (vojode_harekat() == 0 && check_harekat()) {
                break;
            }
        }

        system("cls");
        heder(name, score, time_left);
        cout << color::GREEN << "\nBoard Shuffled successfully! Keep playing." << color::RESET << endl;
        Sleep(2000);
        system("cls");
        heder(name, score, time_left);
    }
}; // ; it's used for class in oop 
