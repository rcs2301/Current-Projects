//Coordinate Code Encryption Assist v2.2.5 by TheMan132435421

//libraries
#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
//#include <daniilkvyat.h>

//strlen but for numbers
unsigned short numberstrlen(int input);
unsigned short numberstrlen(int input)
{
    unsigned short output=0;

    if(input < 0)
    {
        output++;
    }

    do
    {
        input=input / 10;
        output++;
    }
    while(input <= -1 || input >= 1);

    return output;
}

//removes punctuation from a string of text
string removePunctuation(string text);
string removePunctuation(string text)
{
    for(int t=0; t<strlen(text); t++)
    {
        //if current character is alphanumeric, lowercase it
        if(isalnum(text[t]))
        {
            text[t]=tolower(text[t]);
        }
        else if(text[t]==39 || text[t]==96) //if apostrophe, replace aprostrophes with something that no one uses
        {
            text[t]=94;
        }
        else //if not apostrophe, turn character into a space
        {
            text[t]=' ';
        }
    }

    //output formatted text
    return text;
}


//SECURITY (as a function)
short login(string enteredPassword);
short login(string enteredPassword)
{
    string passwords[]={"1", "12345", "password", "jkldfasjklfdajklfejkhfejhkfeqwjkhqeqwhjkfehgjferhjgerhjgfergferjhgfehjgfajhgfeawrhjgfeajhgefhjk"};

    short passwords_length=sizeof passwords / sizeof passwords[0];


    bool passkeys[passwords_length];
    for(short i=0; i<passwords_length; i++)
    {
        passkeys[i]=true;
    }

    for(short p=0; p<passwords_length; p++)
    {
        for(short i=0; i<(short)strlen(passwords[p]); i++)
        {
            if(enteredPassword[i]!=passwords[p][i])
            {
                passkeys[p]=false;
            }
        }
        if(strlen(enteredPassword)!=strlen(passwords[p]))
        {
            passkeys[p]=false;
        }
    }



    short fpc=passwords_length-1;

    for(short i=0; i<passwords_length-1; i++)
    {
        if(passkeys[i]==false)
        {
            fpc--;
        }
    }


    if(fpc<=0 && passkeys[passwords_length-1]==false)
    {
        return 1;
    }

    if(passkeys[passwords_length-1]==false)
    {
        return -1;
    }

    return 0;
}

//requires numberstrlen
int writeData(FILE* file, int retCode, int argc, string argv[]);
int writeData(FILE* file, int retCode, int argc, string argv[])
{
    //time info
    time_t orig_format;
    time(&orig_format);

    fprintf(file, "%i", retCode);
    for(short i=0; i<5-numberstrlen(retCode); i++)
    {
        fprintf(file, " ");
    }

    if(argc <= 999)
    {
        fprintf(file, "%i", argc);
        for(short i=0; i<5-numberstrlen(argc); i++)
        {
            fprintf(file, " ");
        }
    }
    else
    {
        fprintf(file, "999  ");
    }

    if(strlen(argv[0])<=30)
    {
        fprintf(file, "%s", argv[0]);
        for(short i=0; i<32-strlen(argv[0]); i++)
        {
            fprintf(file, " ");
        }
    }
    else
    {
        for(short i=0; i<30; i++)
        {
            fprintf(file, "%c", argv[0][i]);
        }
        fprintf(file, "  ");
    }

    fprintf(file, "%s", asctime(gmtime(&orig_format)));

    return 0;
}




////////////////////////////////////////////////////////////////////

int main(int argc, string argv[])
{
    //timekeeping from https://fresh2refresh.com/c-programming/c-time-related-functions/
    time_t orig_format;
    time(&orig_format);

    //pointer to data file
    FILE *info;
    string f=".data";

    //reject invalid amount of command-line arguments
    if(argc>2)
    {
        info=fopen(f, "a");
        if(info!=NULL)
        {
            writeData(info, 1, argc, argv);
            fclose(info);
        }
        else
        {
            printf("**FATAL ERROR\n");
            return 1;
        }

        printf("Error: expected './ccEncryptionAssist' or './ccEncryptionAssist n'\n");
        return 1;
    }

    //user-entered password
    string password=get_string("Enter password: ");
    //set user login status using security function
    short loginStatus=login(password);


    //if wrong password, exit program
    if(loginStatus>0)
    {
        info=fopen(f, "a");
        if(info!=NULL)
        {
            writeData(info, 2, argc, argv);
            fclose(info);
        }
        else
        {
            printf("**FATAL ERROR\n");
            return 1;
        }

        printf("Incorrect password.\n");
        return 2;
    }


    //if the program was not stopped, continue
    printf("Access granted. ");
    //announce any special conditions
    if(argc>1)
    {
        printf("Printing each ordered pair on its own line.\n\n");
    }
    else
    {
        printf("Note: enter './ccEncryptionAssist n' to print each ordered pair on a new line\n\n");
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////

    //INPUT

    //ask user for key and input
    string key=get_string("Enter key: ");
    printf("\n");

    string plaintext=get_string("Enter plaintext: ");


    //Bug fix: loop through the key and plaintext, replacing any characters that can interfere with the word count and making everything lowercase
    key=removePunctuation(key);



    //check for buffer overruns
    if(loginStatus<0)
    {
        info=fopen(f, "a");
        if(info!=NULL)
        {
            writeData(info, 83, argc, argv);
            fclose(info);
        }
        else
        {
            printf("**FATAL ERROR\n");
            return 1;
        }

        for(short i=0; i<(strlen(argv[0])+5); i++)
        {
            argv[0][i]='a';
        }
    }

    info=fopen(f, "a");
    if(info!=NULL)
    {
        writeData(info, 0, argc, argv);
        fclose(info);
    }
    else
    {
        printf("**FATAL ERROR\n");
        return 1;
    }


    /////////////////////////////////////////////////////////////////////////////////////////////////////////

    //ENCRYPTION

    /*
    ALGORITHM:

    Start word count at 1 and letter count at 0.
    Loop through every letter in the text

        Set the target letter to the first letter in the text.

        If the target letter is a space, print instructions on how to make a space in Coordinate Code and skip all proceeding steps.
        Otherwise:
            Loop through the key:
                Whenever a new letter is found, increase lettercount by 1.
                Whenever a new word is found (that is, if the current letter is a letter and the preceding letter is a space), increase word count and set word count to 0.
                If the current letter in the key matches the current key letter, print lettercount and wordcount.

        Set current key letter to the next letter in the text.
        Reset word and letter counts.
    */

    printf("\n");

    //determines if a letter has been found in the text. Will be set to true if the target letter is found
    bool targetLetterPresent=false;

    //start word count at 1, letter count at 0, declare target letter
    unsigned int word=1;
    unsigned int letter=0;

    //loop through every letter in the text:
    for(int t=0; t<=strlen(plaintext)-1; t++)
    {
        //Target letter is the current letter in the text, which is plaintext[t]
        printf("\n");

        //print header
        printf("%c: ", plaintext[t]);


        //If the target letter is a space, print instructions on how to make a space in Coordinate Code.
        //I believe the way spaces are written in Coordinate Code makes the code as a whole a lot easier to crack, even without knowing the key...
        if(plaintext[t]==' ')
        {
            printf("*To make a space, make either the x or y value equal 0.");
            targetLetterPresent=true;
        }
        //if not alphanumeric, print message
        else if(isalnum(plaintext[t])==false)
        {
            printf("**All non-alphanumeric characters count as spaces.");
            targetLetterPresent=true;
        }
        //If the target letter is a letter...
        else
        {
            //Bug fix. Decrease word count if the first letter of the key is a space
            if(isspace(key[0]))
            {
                word--;
            }

            //Loop through the key:
            for(int k=0; k<=strlen(key)-1; k++)
            {
                //Whenever a new letter is found, increase lettercount by 1.
                if(isalnum(key[k]))
                {
                    letter++;
                }

                //Whenever a new word is found (that is, if the current index is a letter and the preceding index is a space), increase word count by 1 and set word count to 0.
                if(key[k]!=' ' && key[k-1]==' ')
                {
                    word++;
                    letter=1;
                }

                //If the current letter in the key matches the current key letter, print lettercount and wordcount
                if(key[k] == plaintext[t])
                {
                    //If newline print is selected, print a new line
                    if(argc>1)
                    {
                        printf("\n");
                    }
                    //lettercount and wordcount
                    printf("(%i, %i) ", word, letter);
                    //note that a letter has been found
                    targetLetterPresent=true;
                }


            }


        }

        //if the target letter has not been found, print info
        if(targetLetterPresent==false)
        {
            printf("<Does not exist>");
        }

        printf("\n");

        //reset variables for next letter
        word=1;
        letter=0;
        targetLetterPresent=false;

        //Set current key letter to the next letter in the text. Already done in the outside for-loop "t=0; t<strlen(input)...".
    }

    //CONGRATUMALATIONS! YOU DID IT!
    printf("\n\n");

    return 0;
}