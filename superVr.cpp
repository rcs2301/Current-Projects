#include <cctype>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;


char decrypt(char input, int key);
char decrypt(char input, int key)
{
    /**
    Returns encrypted pt using key.

    Can take letters or numbers. Anything else returns as itself
    */

    if((int)input>=97 && (int)input<=122)
    {
      char output=input-97;
      output=(output - key) % 26;
      if(output < 0)
      {
        output += 26;
      }
      return output + 97;
    }
    if((int)input>=48 && (int)input<=57)
    {
      char output=input-48;
      output=(output - key) % 10;
      if(output < 0)
      {
        output += 10;
      }
      return output + 48;
    }

    return input;
}


char getCharFromString(void);
char getCharFromString(void)
{
    /**Prompts user for input and returns first char of the input  */
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


short login(string message);
short login(string message)
{
    /*
    read the name!
    */
    string enteredPassword;
    cout << message;
    getline(cin, enteredPassword);

    string passwords[]={"12345", "123456", "123456789", "test1", "password", "12345678", "zinch", "g_czechout", "test", "princess", "qwertyuiop", "sunshine", "BvtTest123", "11111", "asdf", "qwerty", "1234567890", "1234567", "Aa123456.", "iloveyou", "1234", "abc123", "111111", "123123", "dubsmash", "ashley", "00000", "000000", "password1", "monkey", "livetest", "55555", "soccer", "charlie", "asdfghjkl", "654321", "family", "michael", "123321", "football", "baseball", "q1w2e3r4t5y6", "nicole", "jessica", "purple", "shadow", "hannah", "chocolate", "michelle", "daniel", "maggie", "qwerty123", "hello", "112233", "flower", "Password", "maria", "babygirl", "lovely", "sophie", "Chegg123", "admin", "jordan", "tigger", "666666", "987654321", "superman", "12345678910", "summer", "1q2w3e4r5t", "fitness", "amanda", "justin", "cookie", "basketball", "shopping", "pepper",  "bailey", "zxcvbnm", "fuckyou", "121212", "buster", "butterfly", "dragon", "jennifer", "joshua",  "jasmine", "0987654321", "54321", "andrew", "1qaz2wsx3edc", "thomas", "hunter", "ginger", "matthew", "abcd1234",  "madison", "taylor", "samantha", "whatever",  "~", "animoto", "!", "", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", " "};
    short passwords_length=sizeof passwords / sizeof passwords[0];

    char passkeys[passwords_length];
    for(short i=0; i<passwords_length; i++)
    {
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

    if(cf<=0 && passkeys[passwords_length-1]!=(char)0)
    {
        return 1;
    }

    if(passkeys[passwords_length-1]!=(char)0)
    {
        return -1;
    }

    return 0;
}


string outputCombine(vector<char> text, vector<char> symbols);
string outputCombine(vector<char> text, vector<char> symbols)
{
    /**
    Returns text and symbols into a single string.

    text contains indices on [0,25]. a=0, b=1, c=2... z=25

    symbols contains numbers where non-letters should be,
    and a -127 where alphabetic characters are
    */
    string output="";

    int textIndex=0;
    for(int i=0; i<symbols.size(); i++)
    {
        if(symbols[i] == -127)
        {
            output += (int)text[textIndex];
            textIndex++;
        }
        else if(symbols[i]>=0)
        {
            output += symbols[i];
        }
    }

    return output;
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
    /**
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
    if(w==false)
    {
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


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


int main(int argc, char** argv)
{
  const string f=".data";
  const bool w=false;

  int x=0;

  short loginStatus=32767;

  string enteredCiphertext="";
  string enteredKey="";

  vector<char> plaintext={};
  vector<char> key={};
  vector<char> ciphertext={};
  vector<char> nonAlnums={};



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


  //INPUT
  cout << "Enter ciphertext: ";
  getline(cin, enteredCiphertext);

  cout << "Enter key: ";
  getline(cin, enteredKey);


  //LOADING CT
  for(unsigned short l=0; l<enteredCiphertext.length(); l++)
  {
      //characters that will not appear in the output
      if(enteredCiphertext[l]==(char)39 || enteredCiphertext[l]==(char)96)
      {
          nonAlnums.push_back(-1);
      }
      //alphanumeric character
      else if(isalnum(enteredCiphertext[l]))
      {
          ciphertext.push_back(tolower(enteredCiphertext[l]));
          nonAlnums.push_back(-127);
      }
      //non-alphanumeric character
      else
      {
          nonAlnums.push_back(enteredCiphertext[l]);
      }
  }

  //LOADING KEY
  for(unsigned short l=0; l<enteredKey.length(); l++)
  {
    if(isalnum(enteredKey[l]))
    {
      key.push_back(enteredKey[l]);
    }
  }

  //LENGTH ADJUSTMENTS
  while(ciphertext.size() > key.size())
  {
    ciphertext.pop_back();
  }
  while(key.size() > ciphertext.size())
  {
    key.pop_back();
  }

  // cout << ciphertext.size() << endl;
  // cout << key.size() << endl;


  //SET PT
  for(unsigned short l=0; l<ciphertext.size(); l++)
  {
       plaintext.push_back(-127);
  }
   if(loginStatus < 0)
   {
       if( writeData(f, 83, argc, argv, w)==1 )
       {
           cout << "**FATAL ERROR" << endl;
           return 1;
       }
       vector<char> buffer={};
       char c='a';
       for(int i=0; i<20; i++)
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
  enteredCiphertext.erase();
  enteredKey.erase();



  //GO
  for(unsigned char n=1; n<=208; n++)
  {
      //ENCRYPT

      for(unsigned short i=0; i<ciphertext.size(); i++)
      {
          //Determine shift
          if(isalpha(key[i])) {
              x=key[i]-97;
          }
          else if(isalnum(key[i])) {
              x=key[i]-48;
          }
          else {
              x=0;
          }

          //encrypt current letter if it's a letter, subtracting 97 from the ASCII value of the current index of the key
          //'a' has an ASCII value of 97, so subtracting 97 gives the vigenere numerical value of the letter
          if(isalnum(ciphertext[i]))
          {
              plaintext[i]=decrypt(ciphertext[i], x);
          }
      }


      //key >> ct
      for(unsigned short t=0; t<ciphertext.size(); t++)
      {
        ciphertext[t]=key[t];
      }

      //pt >> key
      for(unsigned short t=0; t<ciphertext.size(); t++)
      {
        key[t]=plaintext[t];
      }

      //clear pt
      for(unsigned short t=0; t<ciphertext.size(); t++)
      {
        plaintext[t]=(char)-127;
      }

  }



  //PRINTING
  cout << "\n";
  cout << "-Plaintext: ";
  cout << outputCombine(ciphertext,nonAlnums) << "\n" << endl;

  return promptExit(0);
}
