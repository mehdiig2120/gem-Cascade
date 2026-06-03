#include <iostream>
#include <Windows.h>
#include "board.h"
using namespace std;

int main(){
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
        cout << "Good luck. Bye";
    }
    else if (input == "1" || input == "New Game")
    {   
        string name;
        cout << "Please enter your name : "<< endl;
        cin  >> name;
        cout << endl;
        cout << "Loading..." << endl;
        Sleep(3000); //3s
        cout << endl;
        Board myboard; // making an instance of board!
        cout << "Welcome " << name << "!" << endl;
        myboard.draw();
        return 0;
    }
    
}
