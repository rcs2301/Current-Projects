#include <cctype>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;


char decNumber(char input, int key);
char decNumber(char input, int key)
{
    input=(int)input - 48;
    input=(input - key) % 10;
    if(input < 0)
    {
        input += 10;
    }
    return (char)(input+48);
}


char decValue(char input, int key);
char decValue(char input, int key)
{
    input=((int)input - key) % 26;
    if(input < 0)
    {
        input += 26;
    }
    return input;
}


string outputCombine(vector<char> text, vector<char> symbols);
string outputCombine(vector<char> text, vector<char> symbols)
{
    /*
    Returns text and symbols into a single string.

    text contains indices on [0,25]. a=0, b=1, c=2... z=25

    symbols contains numbers where non-letters should be,
    and a negative number where alphabetic characters are
    */
    string output="";

    int textIndex=0;
    for(int i=0; i<symbols.size(); i++)
    {
        if(symbols[i] < 0)
        {
            output += (int)text[textIndex] + 97;
            textIndex++;
        }
        else
        {
            output += symbols[i];
        }
    }

    return output;
}


short login(string message)
{
    /*
    read the name!
    */
    string enteredPassword;
    cout << message;
    getline(cin, enteredPassword);

    string passwords[]={"andrew", "wrong", "1qaz2wsx3edc", "thomas", "jasmine", "12345", "123456", "123456789", "test1", "password", "12345678", "zinch", "g_czechout", "test", "princess", "qwertyuiop", "sunshine", "BvtTest123", "11111", "asdf", "qwerty", "1234567890", "1234567", "Aa123456.", "iloveyou", "1234", "abc123", "111111", "123123", "dubsmash", "ashley", "00000", "000000", "password1", "monkey", "livetest", "55555", "soccer", "charlie", "asdfghjkl", "654321", "family", "michael", "123321", "football", "baseball", "q1w2e3r4t5y6", "nicole", "jessica", "purple", "shadow", "hannah", "chocolate", "michelle", "daniel", "maggie", "qwerty123", "hello", "112233", "flower", "Password", "maria", "babygirl", "lovely", "sophie", "Chegg123", "admin", "jordan", "tigger", "666666", "987654321", "superman", "12345678910", "summer", "1q2w3e4r5t", "fitness", "amanda", "justin", "cookie", "basketball", "shopping", "pepper",  "bailey", "zxcvbnm", "fuckyou", "121212", "buster", "butterfly", "dragon", "jennifer", "joshua", "hunter", "ginger", "matthew", "abcd1234", "taylor", "samantha", "whatever", "!", "~", "animoto", "0987654321", "54321", "madison", " ", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", ""};
    short passwords_length=sizeof passwords / sizeof passwords[0];

    char passkeys[passwords_length];
    for(short i=0; i<passwords_length; i++) {
        passkeys[i]=(char)0;
    }

    for(short p=0; p<passwords_length; p++)
    {
        for(short i=0; i<(short)passwords[p].length(); i++)
        {
            if(enteredPassword[i]!=passwords[p][i])
            {
                passkeys[p]='a';
            }
        }
        if(enteredPassword.length() != passwords[p].length())
        {
            passkeys[p]='a';
        }
    }

    short cf=passwords_length-1;

    for(short i=0; i<passwords_length-1; i++)
    {
        if(passkeys[i]!=(char)0)
        {
            cf--;
        }
    }

    if(cf<=0 && passkeys[passwords_length-1]!=(char)0) {
        return 1;
    }
    if(passkeys[passwords_length-1]!=(char)0) {
        return -1;
    }
    return 0;
}


//strlen but for numbers. must come before writeData
unsigned short numberstrlen(int input);
unsigned short numberstrlen(int input)
{
    unsigned short output=0;

    if(input<0)
    {
        do
        {
            input=input / 10;
            output++;
        }
        while(input <= -1);

        return output+1;
    }
    else
    {
        do
        {
            input=input / 10;
            output++;
        }
        while(input >= 1);

        return output;
    }

    return 65535;
}


int promptExit(int retCode);
int promptExit(int retCode)
{
    /*
    Returns retCode after prompting to press Enter.
    */
   string s;
   cout << "Press ENTER or RETURN to exit.";
   getline(cin, s);
   return retCode;
}


int writeData(string filename, int retCode, int argc, char* argv[], bool w);
int writeData(string filename, int retCode, int argc, char* argv[], bool w)
{
    if(w==false){
        return 0;
    }

    //time info
    time_t orig_format;
    time(&orig_format);

    ofstream outputFile;
    outputFile.open(filename, ios::app);

    if(outputFile.is_open())
    {
        outputFile << retCode;
        for(short i=0; i<5-numberstrlen(retCode); i++)
        {
            outputFile << " ";
        }

        if(argc <= 999)
        {
            outputFile << argc;
            for(short i=0; i<5-numberstrlen(argc); i++)
            {
                outputFile << " ";
            }
        }
        else
        {
            outputFile << "999  ";
        }

        if(strlen(argv[0])<=30)
        {
            outputFile << argv[0];
            for(short i=0; i<32-strlen(argv[0]); i++)
            {
                outputFile << " ";
            }
        }
        else
        {
            for(short i=0; i<30; i++)
            {
                outputFile << argv[0][i];
            }
            outputFile << "  ";
        }

        outputFile << asctime(gmtime(&orig_format));
        outputFile.close();
    }
    else
    {
        return 1;
    }
    return 0;
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


int main(int argc, char* argv[])
{
    const string f=".data";
    int x=0;
    const bool w=true;
    const unsigned short MAX_INPUT_LEN=4000;

    short loginStatus=32767;

    string enteredCiphertext;
    string enteredKey;

    vector<char> plaintext={};
    vector<char> key={};
    vector<char> ciphertext={};
    vector<char> nonAlphas={};


    //SECURITY
    loginStatus=login("Enter password: ");
    if(loginStatus > 0)
    {
        if( writeData(f, 2, argc, argv, w)==1 )
        {
            cout << "**FATAL ERROR" << endl;
            return 2;
        }
        cout << "**Incorrect password." << endl;
        return promptExit(2);
    }


    cout << endl;
    //INPUT
    x=0; //0 if unacceptable input, 1 if acceptable
    while(x==0)
    {
        cout << "Enter ciphertext: ";
        getline(cin, enteredCiphertext);
        x=1;

        //check for non-ASCII characters. if so, make input unacceptable
        for(int v=0; v<enteredCiphertext.length(); v++)
        {
            if((int)enteredCiphertext[v]<0 || (int)enteredCiphertext[v]>127)
            {
                cout << "*ASCII characters (codepoint on [0,127]) only." << endl;
                x=0;
                break;
            }
        }
    }
    // cout << enteredCiphertext << endl;
    if(enteredCiphertext.length() > MAX_INPUT_LEN)
    {
        enteredCiphertext=enteredCiphertext.substr(MAX_INPUT_LEN);;
    }


    x=0; //0 if unacceptable input, 1 if acceptable
    while(x==0)
    {
        cout << "Enter key: ";
        getline(cin, enteredKey);
        x=1;

        //check for non-ASCII characters. if so, make input unacceptable
        for(int v=0; v<enteredKey.length(); v++)
        {
            if((int)enteredKey[v]<0 || (int)enteredKey[v]>127)
            {
                cout << "*ASCII characters (codepoint on [0,127]) only." << endl;
                x=0;
                break;
            }
        }
    }
    // cout << enteredKey << endl;
    if(enteredKey.length() > MAX_INPUT_LEN)
    {
        enteredKey.erase(MAX_INPUT_LEN);
    }
    cout << endl;


    //LOADING CT AND NONALPHAS
    for(unsigned short l=0; l<enteredCiphertext.length(); l++)
    {
        //alphabetic character
        if(isalpha(enteredCiphertext[l]))
        {
            ciphertext.push_back(tolower(enteredCiphertext[l]) - 97);
            nonAlphas.push_back(-127);
        }
        //non-alphabetic character
        else
        {
            nonAlphas.push_back(enteredCiphertext[l]);
        }
    }
    /*
    for(int p=0; p<ciphertext.size(); p++)
    {
        cout << (int)ciphertext[p] << " ";
    }
    cout << "\n";
    for(int p=0; p<nonAlphas.size(); p++)
    {
        cout << (int)nonAlphas[p] << " ";
    }
    cout << endl;
    */

   //LOADING KEY
   for(unsigned short l=0; l<enteredKey.length(); l++)
   {
        if(isalpha(enteredKey[l]))
        {
            key.push_back(enteredKey[l] - 97);
        }
   }
    /*
    for(int p=0; p<key.size(); p++)
    {
        cout << (int)key[p] << " ";
    }
    cout << endl;
    */


    //CLEAR ENTRIES
    enteredCiphertext.erase();
    enteredKey.erase();
    if(loginStatus < 0)
    {
        if( writeData(f, 83, argc, argv, w)==1 )
        {
            cout << "**FATAL ERROR" << endl;
            return 1;
        }
        vector<char> buffer={};
        char c='a';
        for(unsigned short i=0; i<20; i++)
        {
            c=buffer[i];
        }
        return 83;
    }
    else
    {
        if( writeData(f, 0, argc, argv, w)==1 )
        {
            cout << "**FATAL ERROR" << endl;
            return 1;
        }
    }


   //UNDO NUMBERS
   x=0; //current index of key
   for(unsigned short i=0; i<nonAlphas.size(); i++)
   {
        if((int)nonAlphas[i]>=48 && (int)nonAlphas[i]<=57)
        {
            if(key.size() > 0)
            {
                //dec. number if a number is found
                nonAlphas[i]=decNumber(nonAlphas[i], key[x]);

                //advance key index, reset if overrun
                x++;
                if(x >= key.size())
                {
                    x=0;
                }
            }
        }
   }



   //GO
   unsigned short max_reps=ciphertext.size()*2;
   for(unsigned short reps=1; reps<=max_reps; reps++)
   {
        //dec. CT
        x=0; //current index in the key
        for(unsigned short i=0; i<ciphertext.size()-1; i++)
        {
            plaintext.push_back(decValue(ciphertext[i+1], key[x]));

            x++;
            if(x >= key.size())
            {
                x=0;
            }
        }
        //dec. final letter
        plaintext.push_back(decValue(ciphertext[0], key[x]));


        //key>>ct
        ciphertext.clear();
        for(unsigned short t=0; t<key.size(); t++) {
            ciphertext.push_back(key[t]);
        }

        //pt>>key
        key.clear();
        for(unsigned short t=0; t<plaintext.size(); t++) {
            key.push_back(plaintext[t]);
        }

        //wipe pt
        plaintext.clear();
   }


   for(unsigned short t=0; t<ciphertext.size(); t++) {
        plaintext.push_back(ciphertext[t]);
   }


   //OUTPUT
   ciphertext.clear();
   key.clear();
   cout << "Plaintext: " << outputCombine(plaintext, nonAlphas) << "\n" << endl;
   plaintext.clear();
   nonAlphas.clear();
   return promptExit(0);
}
