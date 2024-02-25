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


char getCharFromString(void);
char getCharFromString(void)
{
    /*
    Returns the first non-space character from cin.
    If input too short or only spaces, returns a space.
    */
    string input;
    getline(cin, input);

    for(int i=0; i<input.length(); i++)
    {
        if((int)input[i] > 32)
        {
            return input[i];
        }
    }

    return ' ';
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
        if(symbols[i]==-127)
        {
            output += (int)text[textIndex] + 97;
            textIndex++;
        }
        else if(symbols[i]>=0)
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

    string passwords[]={"test1", "password", "12345678", "zinch", "g_czechout", "test", "princess", "qwertyuiop", "sunshine", "BvtTest123", "11111", "asdf", "qwerty", "1234567890", "1234567", "Aa123456.", "iloveyou", "1234", "abc123", "111111", "123123", "dubsmash", "ashley", "00000", "000000", "password1", "monkey", "livetest", "55555", "soccer", "charlie", "asdfghjkl", "654321", "family", "michael", "123321", "football", "baseball", "q1w2e3r4t5y6", "nicole", "jessica", "purple", "shadow", "hannah", "chocolate", "michelle", "daniel", "maggie", "qwerty123", "hello", "112233", "flower", "Password", "maria", "babygirl", "lovely", "sophie", "Chegg123", "admin", "jordan", "tigger", "666666", "987654321", "superman", "12345678910", "summer", "1q2w3e4r5t", "fitness", "amanda", "justin", "cookie", "basketball", "shopping", "pepper",  "bailey", "zxcvbnm", "fuckyou", "121212", "buster", "butterfly", "dragon", "jennifer", "joshua", "hunter", "ginger", "matthew", "abcd1234", "taylor", "samantha", "whatever", "!", "~", "animoto", "0987654321", "54321", "madison", " ", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "", "andrew", "wrong", "1qaz2wsx3edc", "thomas", "jasmine", "12345", "123456789", "123456"};
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


string readFile(string inputFilename);
string readFile(string inputFilename)
{
    /*
    Returns ALL of the file contents as a string.
    In case of file opening error, return a string containing (char)-127.
    */
    string output="";
    ifstream inputFile;

    //try to open file
    inputFile.open(inputFilename);

    //stop if file can't open
    if(inputFile.is_open() == false) {
        output += (char)-127;
        return output;
    }

    //read the file
    while(inputFile) {
        output += inputFile.get();
    }

    //remove (char)(-1) from the end
    output.erase(output.length()-1);

    return output;
}


string sliceInput(string input, unsigned short n);
string sliceInput(string input, unsigned short n)
{
    /*
    Returns input sliced between nth "~~~" and (n+1)th "~~~".

    If input is one character long and contains a character less than 0,
    returns input.

    If input doesn't contain enough "~~~", returns (char)(-2).
    */


   char prevChars[]={(char)(-127), (char)(-127), (char)(-127)};
   string output="";
   int currentIndex=0;

   unsigned short startStringsFound=0;

    //if input is an error result from the readFile function, return as self
   if(input.length()==1 && (int)input[0]<0)
   {
        return input;
   }

   //find the start of the nth "~~~"
   while(startStringsFound < n)
   {
        //if end of input is reached and not enough start strings
        if(currentIndex >= input.length())
        {
            output.erase(0);
            output += (char)(-2);
            return output;
        }

        //update the previous characters read
        prevChars[2]=prevChars[1];
        prevChars[1]=prevChars[0];
        prevChars[0]=input[currentIndex];

        //update number of "~~~" found
        if(prevChars[0]=='~' && prevChars[1]=='~' && prevChars[2]=='~')
        {
            startStringsFound++;
        }

        currentIndex++;
   }

    //reset previous characters read
    prevChars[0]=(char)(-127);
    prevChars[1]=(char)(-127);
    prevChars[2]=(char)(-127);


   //load characters until the end of file or the next "~~~" is found
   while(currentIndex < input.length())
   {
        //update the previous characters read
        prevChars[2]=prevChars[1];
        prevChars[1]=prevChars[0];
        prevChars[0]=input[currentIndex];


        //if 3 "~~~" found, stop reading and remove residual '~'
        if(prevChars[0]=='~' && prevChars[1]=='~' && prevChars[2]=='~')
        {
            output.erase(output.length()-2);
            break;
        }

        //load the output
        output += prevChars[0];

        currentIndex++;
   }


    //remove any non-printing characters at the end of the string
    currentIndex=output.length()-1;
    while(currentIndex >= 0)
    {
        if((int)output[currentIndex]<32 || (int)output[currentIndex]==127)
        {
            output.erase(output.length()-1);
        }

        currentIndex--;
    }


   return output;
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


////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////


int main(int argc, char* argv[])
{
    const unsigned short MAX_INPUT_LEN=30000;
    const string inputFilename="input.txt";
    const string outputFilename="input.txt";
    const string f=".data";
    const bool w=true;

    int x=0;

    short loginStatus=32767;

    string enteredCiphertext="";
    string enteredKey="";
    char outputToFile='n';
    unsigned short inputLength=0;

    vector<char> plaintext={};
    vector<char> key={};
    vector<char> ciphertext={};
    vector<char> nonAlphas={};

    char percentStep=25;
    char percentLowerBound=25;
    char percentUpperBound=50;
    bool percentPrinting=false;



    //TAKE INPUT FROM FILE (for formatting check)
    enteredKey=sliceInput(readFile(inputFilename),2);
    // cout << "CT: " << enteredCiphertext << endl;
    // cout << "Key: " << enteredKey << endl;

    //check if input file is readable
    if(enteredKey.length()==1 && (int)enteredKey[0]==(char)(-127))
    {
        if( writeData(f, 1, argc, argv, w)==1 )
        {
            cout << "**FATAL ERROR" << endl;
            return 1;
        }

        cout << "**Input file \"" << inputFilename << "\" could not be accessed. Attempt to create file? (y/n) ";
        if(tolower(getCharFromString())=='y')
        {
            ofstream inputFile(inputFilename);
            if(inputFile.is_open())
            {
                cout << "\"" << inputFilename << "\" successfully created." << endl;
            }
            else
            {
                cout << "\"" << inputFilename << "\" exists, but the file is inaccessible." << endl;
            }
        }
        return promptExit(1);
    }

    //check if input file is properly formatted
    if(enteredKey.length()==1 && (int)enteredKey[0]==(char)(-2))
    {
        if( writeData(f, 1, argc, argv, w)==1 )
        {
            cout << "**FATAL ERROR" << endl;
            return 1;
        }

        cout << "**Ciphertext and key must be followed by three '~'. Auto-format file? (y/n) ";
        if(tolower(getCharFromString())=='y')
        {
            ofstream inputFile(inputFilename);
            if(inputFile.is_open())
            {
                inputFile << "~~~Enter ciphertext here\n";
                inputFile << "~~~Enter key here";
                inputFile.close();
                cout << "Formatting done." << endl;
            }
            else
            {
                cout << "File could not be opened." << endl;
            }
        }
        return promptExit(1);
    }



    //SECURITY
    loginStatus=login("Enter password: ");
    if(loginStatus > 0)
    {
        if( writeData(f, 2, argc, argv, w)==1 )
        {
            cout << "**FATAL ERROR" << endl;
            return 1;
        }
        cout << "**Incorrect password." << endl;
        return promptExit(2);
    }
    cout << endl;


    //ask for output to file
    outputToFile='n';
    cout << "Write results to the output file \"" << outputFilename << "\"? (y/n) ";

    if(tolower(getCharFromString())=='y')
    {
        outputToFile='y';
    }


	//post-input load and formatting check
	enteredKey.erase(0);
	enteredCiphertext=sliceInput(readFile(inputFilename),1);
	enteredKey=sliceInput(readFile(inputFilename),2);
	if( enteredCiphertext.length()==1 && (int)enteredCiphertext[0]==(char)(-127)
	|| enteredCiphertext.length()==1 && (int)enteredCiphertext[0]==(char)(-2)
	|| enteredKey.length()==1 && (int)enteredKey[0]==(char)(-127)
	|| enteredKey.length()==1 && (int)enteredKey[0]==(char)(-2) )
	{
		if( writeData(f, 1, argc, argv, w)==1 )
        {
            cout << "**FATAL ERROR" << endl;
            return 1;
        }

		cout << "**Input file formatting error." << endl;
		return promptExit(1);
	}


  //trim CT and key to maximum length
  if(enteredCiphertext.length() > MAX_INPUT_LEN) {
      enteredCiphertext=enteredCiphertext.substr(0,MAX_INPUT_LEN);
  }
  if(enteredKey.length() > MAX_INPUT_LEN) {
      enteredKey=enteredKey.substr(0,MAX_INPUT_LEN);
  }

	//check for non-ASCII characters
	for(int v=0; v<enteredCiphertext.length(); v++)
	{
		if((int)enteredCiphertext[v]<0 || (int)enteredCiphertext[v]>127)
		{
			cout << "Unsupported character found at position " << (v+1) << " in the ciphertext. ";
			cout << "The output may become corrupted or changed. ";
			cout << "Continue? (y/n) ";
			if(tolower(getCharFromString()) != 'y')
			{
				if( writeData(f, 1, argc, argv, w)==1 )
				{
					cout << "**FATAL ERROR" << endl;
					return 1;
				}
				return promptExit(1);
			}
		}
	}
	for(int v=0; v<enteredKey.length(); v++)
	{
		if((int)enteredKey[v]<0 || (int)enteredKey[v]>127)
		{
			cout << "Unsupported character found at position " << (v+1) << " in the key. ";
			cout << "The output may become corrupted or changed. ";
			cout << "Continue? (y/n) ";
			if(tolower(getCharFromString()) != 'y')
			{
				if( writeData(f, 1, argc, argv, w)==1 )
				{
					cout << "**FATAL ERROR" << endl;
					return 1;
				}
				return promptExit(1);
			}
		}
	}



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
    inputLength=enteredCiphertext.length();
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

  cout << endl;

  //CONFIGURE PRINTING PROGRESS
  if(inputLength>7500 && inputLength<=20000)
  {
    percentLowerBound=25;
    percentUpperBound=50;
    percentStep=25;
    percentPrinting=true;
  }
  else if(inputLength > 20000)
  {
    percentLowerBound=10;
    percentUpperBound=20;
    percentStep=10;
    percentPrinting=true;
  }

  if(inputLength > 4000)
  {
    cout << "Loading " << inputLength << " characters..." << endl;
  }


   //GO
   const unsigned short max_reps=ciphertext.size()*2;
   for(unsigned short n=1; n<=max_reps; n++)
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

        //print percent progress
        if(percentPrinting)
        {
          if( (percentLowerBound < (float)n*100/max_reps)
            && ((float)n*100/max_reps <= percentUpperBound) )
            {
              cout << (int)percentLowerBound << "% complete" << endl;
              percentLowerBound += percentStep;
              percentUpperBound += percentStep;
            }
        }
   }


   for(unsigned short t=0; t<ciphertext.size(); t++) {
        plaintext.push_back(ciphertext[t]);
   }
  cout << "100% complete" << endl;


   //OUTPUT
   ciphertext.clear();
   key.clear();
  cout << "\n";

    //output to file, if applicable
    if(outputToFile=='y')
    {
        ofstream outputFile(outputFilename);
        if(outputFile.is_open()==false)
        {
            cout << "*File output error.\n" << endl;
        }
        else
        {
            outputFile << "Plaintext: ";
            outputFile << outputCombine(plaintext,nonAlphas);
            outputFile.close();
        }
    }

  //stores in a string and prints in order to stagger printing
  enteredCiphertext=outputCombine(plaintext, nonAlphas);
   cout << "-Plaintext: ";
  for(unsigned short p=0; p<enteredCiphertext.length(); p++)
  {
    //enteredCiphertext now has the PT
    cout << enteredCiphertext[p] << flush;
  }

  cout << "\n" << endl;
   plaintext.clear();
   nonAlphas.clear();
   return promptExit(0);
}
