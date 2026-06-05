#include <iostream>
#include <Windows.h>
#include "board.h"
using namespace std;

int main(){
    while (true){

        cout << "Welcome new player. select a Option " << endl;
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
        else if (input == "1" || input == "New Game"){
           
            Sleep(1500);
            system("cls"); 
            string name;
            cout << "Please enter your name : "<< endl;
            cin  >> name;
            cout << endl;
            cout << "Loading..." << endl;
            Sleep(3000); //3s
            system("cls"); // delete last board and refresh terminal
            cout << endl;
            Board myboard; // making an instance of board!
            cout << "Welcome " << name << "!" << endl;
            myboard.draw();
            cout << endl;

            string f_nut;
            string s_nut;
            string answer;
            while (true){
                cout << "Do you want play ?(y/n)" << endl;
                cin >> answer;
                if (answer == "n"){
                    cout << "Your game will be save" << endl;
                    // save game
                    Sleep(2000);
                    cout << "good by" << endl;
                    cout << endl;
                    break;
                }

                else if(answer == "y"){
                    cout << "give me your nut (like g7) :" << endl;
                    cin >> f_nut >> s_nut;
                    Sleep(1000);
                    myboard.swp(f_nut, s_nut);
                    system("cls");
                    cout << "Welcome " << name << "!" << endl;
                    myboard.draw();
                }
                else{
                    cout << "Please write correctly (y or n)" << endl;
                }
            }
        }

        // else if

        // else if 
        else{
            Sleep(1500);
            system("cls"); 
            cout << "Invalid answer ! please write number or options name ." << endl;
            cout << endl;
        }
        
    }
    return 0;
}