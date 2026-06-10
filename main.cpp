#include <iostream>
#include <Windows.h>
#include <chrono> // for time 
#include <fstream> // for svaing game
#include "board.h"
using namespace std;
using namespace std::chrono;

int main(){
    while (true){
        cout << color::GREEN << "\nWelcome new player. select a Option " << color::RESET << endl;
        cout << endl;
        cout << "1.New Game" << endl;
        cout << "2.Load Last Game" << endl;
        cout << "3.Results" << endl;
        cout << "4.Exit" << endl;
        cout << endl;
        string input;
        cin >> input;
        if(input == "4" || input == "Exit"){
            system("cls"); 
            cout << "Good luck. Bye";
            break;
        }

        // maghadir avalie bazi
        string name = "";
        int score = 0;
        int total_game_time = 300;
        Board myboard; // making an instance of board!
        auto start_time = high_resolution_clock::now(); 
        bool start_game = false;
        
        
        if (input == "1" || input == "New Game"){
           
            Sleep(1500);
            system("cls"); 
            cout << "Please enter your name : "<< endl;
            cin  >> name;
            cout << endl;
            cout << "Loading..." << endl;
            Sleep(3000); //3s
            system("cls"); // delete last board and refresh terminal
            cout << endl;
            total_game_time = 300;
            start_time = high_resolution_clock::now(); // start time
            score = 0;
            start_game = true;
        }

        else if(input == "2" || input == "Load Last Game"){
            ifstream in_file("Results.txt");
            if (!in_file.is_open()){
                system("cls");
                cout << "please wait" << endl;
                Sleep(2000);
                system("cls");
                cout << "Game is not found ! Back to menu ..." << endl;
                Sleep(2500);
                system("cls");
                continue;
            }

            in_file >> name;
            in_file >> score;
            in_file >> total_game_time;

            myboard.load_game(in_file);
            in_file.close();

            system("cls");
            cout << "Loading last game ..." << endl;
            Sleep(1500);

            start_time = high_resolution_clock::now(); // tanzim zaman last game
            start_game = true;
        }
 
        else if (input == "3" || input == "Results"){
            ifstream in_file("Results.txt");
            system("cls");

            if (!in_file.is_open()){
                cout << "No game was not save yet !" << endl;
                cout << "Please play a game first then it will be saved" << endl;
                Sleep(2000);
            }
            else{
            cout << "==============================================" << endl;
            cout << color:: RED << "               LAST GAME RESULT               " << color :: RESET<< endl;
            cout << "==============================================" << endl;
            
            string last_name;
            int last_score;
            int last_time_left;

            in_file >> last_name;
            in_file >> last_score;
            in_file >> last_time_left;

            in_file.close();

            

            cout << "Player name : " << last_name << endl;
            cout << "Player score : " << last_score << endl;
            cout << "Time left : " << last_time_left << "s" <<  endl;
            } 
            cout << "==============================================" << endl;
            cout << endl;
            cout << "Please press Enter key to back to menu  ";

            // wait untill player press Enter
            cin.ignore();
            cin.get();

            system("cls");
            continue; // back to the menu
        } 


        else{
            Sleep(1500);
            system("cls"); 
            cout << "Invalid answer ! please write number or options name ." << endl;
            cout << endl;
            continue;
        }

        while (start_game){

            auto current_time = high_resolution_clock::now();
            duration<double> elapsed = current_time - start_time;
            int time_left = total_game_time - static_cast<int>(elapsed.count());

                if (time_left <= 0) {
                    system("cls");
                    cout << "========================================" << endl;
                    cout << "   Time's up, Game over , " << name << "!" << endl;
                    cout << "           your score : " << score << endl;
                    cout << "========================================" << endl;
                    Sleep(3000);
                    system("cls");
                    break; // back to menu 
                }
            

                string f_nut;
                string s_nut;
                string answer;
                int minute = time_left / 60;
                int second = time_left % 60;


                cout << "+-----------------------------------------------+" << endl;
                cout << "│ player name: " << name << " │ Time: " << minute << ":";

                if (second < 10) {
                    cout << "0";
                }

                cout << second << " │ Score: " << score << "    │"  << endl;
                cout << "+-----------------------------------------------+" << endl;
                cout << endl;
                myboard.draw();
            
                cout << "Do you want play ?(y/n)" << endl;
                cin >> answer;
                if (answer == "n"){
                    cout << "Saving game ..." << endl;

                    ofstream out_file("Results.txt");
                    if(out_file.is_open()){
                        out_file << name << "\n"  << score << "\n" << time_left << "\n";
                        myboard.save_game(out_file);
                        out_file.close();
                    }

                    Sleep(2000);
                    cout << "good by" << endl;
                    cout << endl;
                    break;
                }
                else if(answer == "y"){
                    string answer2 ;
                    string answer3 ;
                    string answer4  ;
                    while (true){
                        Sleep(1500);
                        system("cls");
                        myboard.heder(name, score, time_left);
                        cout << "Do you want any power_ups ?(y/n)" << endl;
                        cin >> answer2;
                        if (answer2 == "y"){
                                cout << "Which one ? (number, exit = 4)" << endl;
                                cin >> answer3;
                                if (answer3 == "1"){
                                    if (score < 120){
                                        cout << "your score isn't enough!"; 
                                        Sleep(1500);}
                                    else{
                                        score -= 120;
                                        string nut;
                                        cout << "Give me your nut : " << endl;
                                        cin >> nut;
                                        Sleep(1500);
                                        myboard.bomb(nut, score, name, time_left);
                                        Sleep(3000);
                                    }
                                }
                                
                                else if (answer3 == "2"){
                                    if(score < 100)
                                    {
                                        cout << "your score isn't enough!";
                                        Sleep(1500);
                                    }
                                    else{
                                        
                                        score -=100;
                                        Sleep(1500);
                                        myboard.rocket(score, name, time_left);
                                        Sleep(3000);

                                    }
                                    Sleep(1000);
                                }

                                else if (answer3 == "3"){
                                        if(score < 70)
                                    {
                                        cout << "your score isn't enough!";
                                        Sleep(1500);
                                    }
                                    else{
                                        // using Hint
                                        cout << "Hint used" << endl;
                                        score -=70;
                                    }
                                    Sleep(1000);
                                }
                                
                                else if (answer3 == "4"){
                                    break;
                                }

                                else{
                                    cout << "give me a number!" << endl;
                                    Sleep(1500);
                                    cout << endl;
                                }
                            }
                        else{
                            break;
                        }

                        system("cls");
                        myboard.draw();
                    }

                    cout << "give me your nut (like g7) :" << endl;
                    cin >> f_nut >> s_nut;
                    Sleep(1000);
                    myboard.swp(f_nut, s_nut, score, name, time_left);
                    system("cls");
                    
                }
                else{
                    cout << "Please write correctly (y or n)" << endl;
                    Sleep(1000);
                    system("cls");
                }
        }
    }
    return 0; 
}
