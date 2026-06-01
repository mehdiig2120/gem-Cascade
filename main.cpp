#include <iostream>
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
