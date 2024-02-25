//6-1-2023

#include <iostream>
#include <string>

using namespace std;

int main(void)
{
    cout << "Hello world!\n" << endl;

    /////////////////////////////////

    string input;

    cout << "Enter something: ";
    cin >> input;
    cout << "You entered: " << input << endl;

    cout << "\n";

    /////////////////////////////////

    for(int i=1; i<=10; i++)
    {
        cout << i << " ";
    }
    cout << "\n";
    for(int i=10; i>=-20; i-=2)
    {
        cout << i << " ";
    }

    cout << "\n" << endl;

    ////////////////////////////////

    if(input.size() >= 5)
    {
        cout << "You entered a string of length " << input.size() << endl;
    }

    ////////////////////////////////

    cout << "\n" << endl;
}