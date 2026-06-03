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
        }
        else if (input == "1" || input == "New Game")
        {   
            Sleep(1500);
            system("cls"); 
            string name;
            cout << "Please enter your name : "<< endl;
            cin  >> name;
            cout << endl;
            cout << "Loading..." << endl;
            Sleep(3000); //3s
            system("cls"); // deleta last board and refresh terminal
            cout << endl;
            Board myboard; // making an instance of board!
            cout << "Welcome " << name << "!" << endl;
            myboard.draw();
            return 0;
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