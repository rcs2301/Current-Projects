//Coordinate Code Decoder v2.1.6 by TheMan132435421


//libraries
#include <cs50.h>
#include <stdio.h> //if people use printf so much, why not just make stdio.h a part of cs50? By the way, stdio stands for "standard input/output".
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
//#include <daniilkvyat.h>

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

//SECURITY (as a function)
short login(string enteredPassword);
short login(string enteredPassword)
{
    string passwords[]={"1", "12345", "password", "0"};

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





///////////////////////////////////////////////////////////////////////

int main(int argc, string argv[])
{
    //pointer to data file
    FILE *info;
    string f=".data";


    //timekeeping from https://fresh2refresh.com/c-programming/c-time-related-functions/
     time_t orig_format;
    time(&orig_format);

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

        printf("Error: expected './ccDecoder' or './ccDecoder d'\n");
        return 1;
    }

    //ask user to enter password
    string password=get_string("Enter password: ");
    //set login status
    short loginStatus=login(password);


   //deny access if incorrect password entered
   if(loginStatus>0)
    {
        printf("Incorrect password.\n");

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

        //stop the program
        return 2;
    }


   //if the program was not stopped, continue
    printf("Access granted. ");

    //reminder of duplicate checker
    if(argc<=1)
    {
        printf("Note: enter './ccDecoder d' to check for duplicate ordered pairs.\n\n");
    }
    else
    {
        printf("Checking for duplicate ordered pairs.\n\n");
    }


    ////////////////////////////////////////////////////////////////////

    //INPUT

    //ask user for the key
    string key=get_string("Enter key: ");


    //maximum ordered pair amount
    unsigned short max_pairs=512;

    //print instructions
    printf("\n");
    printf("Your encrypted text should be in the form (x,y).\n");
    printf("Enter x first, press enter, then enter y. You may enter a maximum of %hu ordered pairs.\n", max_pairs);
    printf("If you make a mistake, enter an x/y pair containing -1 to erase the previous ordered pair.\n");
    printf("When you're done entering ordered pairs, enter an x/y pair containing a number less than -1 to decode the text.\n\n");

    //arrays for pair storage along with amount of pairs entered
    int inputX[max_pairs];
    int inputY[max_pairs];
    short xyPairCount=0;

    //repeat until the user enters the max ordered pairs or the user enters a negative number:
    while(xyPairCount < max_pairs)
    {
        while(false)
        {
            inputX[0]++;
            inputX[0]--;
        }

        //ask user to enter an x/y pair
        printf("ORDERED PAIR #%i\n", xyPairCount+1);
        inputX[xyPairCount]=get_int("x: ");
        inputY[xyPairCount]=get_int("y: ");


        //If the user wants a duplicate check, run the check
        if(argc>1)
        {
            //Check for duplicate ordered pairs.
            //Loop through all ordered pairs from the first pair entered to the current one.
            for(int d=0; d<xyPairCount; d++)
            {
                //If a duplicate pair is found (x and y match), announce the find and print the ordered pair number
                if(inputX[d]==inputX[xyPairCount] && inputY[d]==inputY[xyPairCount])
                {
                    printf("**Warning: Pair #%i is a duplicate with pair #%i.\n", xyPairCount+1, d+1);
                }
            }
        }

        //If user entered a -1, announce, set the previous ordered pair to (0,0), and reset xyPairCount
        if(inputX[xyPairCount]==-1 || inputY[xyPairCount]==-1)
        {
           if(xyPairCount<=0)
           {
               //Note: If there are no ordered pairs to erase, reset i and xyPairCount and print a message
               printf("*THERE ARE NO ORDERED PAIRS TO ERASE*\n");
               xyPairCount=-1;
           }
           else //otherwise, do it
           {
                printf("*INPUT #%i ERASED*\n", xyPairCount);
                inputX[xyPairCount-1]=0;
                inputY[xyPairCount-1]=0;
                xyPairCount=xyPairCount-2;
           }
        }

        //If user entered something less than -1, erase the current ordered pair and break out of the loop.
        if(inputX[xyPairCount]<-1 || inputY[xyPairCount]<-1)
        {
            inputX[xyPairCount]=0;
            inputY[xyPairCount]=0;
            break;
        }


        //increase x/y pair count
        xyPairCount++;

    }

    while(false)
    {
        inputX[0]++;
        inputX[0]--;
    }


    printf("\n");




    //////////////////////////////////////////////////////////////////////

    //DECODING


    /*
    ALGORITHM: The encryption assist algorithm in reverse

    Coded letters are written in the form (x,y) where x is the word number and y is the letter number in the key.

    Variables:
    targetX, targetY: x/y coordinate of the current letter to find- corresponding word and letter in the key
    word, letter: current word/letter count
    printIndex: the index in the key. When a matching x/y pair is found, that index will be printed.

    Set targetX and targetY to the current index of inputX and inputY. Set wordCount to 1, letterCount to 0, printIndex to 0.

    Repeat xyPairCount times:
        If the x or y targets is 0, print a space and exit the loop.
        If not:
            Loop through the key- repeat (string length of the key) times.

            Every time a new word is found, increase wordCount by 1 and reset letterCount to 0.
            If the current index is a letter, increase letter count.
            Increase printIndex by 1.
            When wordCount equals targetX and letterCount equals targetY, printf the character. Exit the loop.
    */

    //Bug fix: loop through the key, replacing any characters that can interfere with the word count and making everything lowercase
    key=removePunctuation(key);


    //print header
    printf("Plaintext: ");

    //test for buffer overruns
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

    //variables
    unsigned int word;
    unsigned int letter;

    //Repeat for every x/y pair entered by the user. In other words, repeat xyPairCount times. Note: c is for ciphertext index
    for(int c=0; c<xyPairCount; c++)
    {
        //Set wordCount to 1, letterCount to 0. Target X and target Y are the current indexes of inputX and inputY.
        word=1;
        letter=0;

        //if either the x or the y targets is 0, automatically print a space
        if(inputX[c]==0 || inputY[c]==0)
        {
                printf(" ");
        }
        //if the x or y targets isn't 0, meaning it's a letter...
        else
        {
            //Bug fix for if the first character of the key is a space. When that happens, the program counts one more word than the accurate word count.
            //If first character is a space, decrease word count by 1 to make the word count accurate.
            if(key[0]==' ')
            {
                word--;
            }

            //Loop through the key- repeat (string length of the key) times. Note: k is for key index
            for(int k=0; k<strlen(key); k++)
            {
                //Every time a new word is found, increase wordCount by 1 and reset letterCount to 0.
                if(key[k]!=' ' && key[k-1]==' ')
                {
                    letter=0;
                    word++;
                }

                //If the current index is a letter, increase letter count.
                if(isalnum(key[k]))
                {
                    letter++;
                }

                //When wordCount equals target X and letterCount equals target Y, printf the character at the selected index. Exit the loop.
                if(word==inputX[c] && letter==inputY[c])
                {
                    printf("%c", key[k]);
                    k=strlen(key)+1;
                }

                //If the entire key was looped through without finding an ordered pair match, print a - and exit the loop.
                if(k==strlen(key)-1)
                {
                    printf("-");
                    k=strlen(key)+1;
                }
            }


        }

    }

    printf("#\n\n");

    //CONGRATUMALATIONS! YOU DID IT!
    printf("\n");
    return 0;

}

/*
Tested with:
100,000 ordered pairs
1281 chars/ordered pair
Time to calculate: 15s

1281char/pair * 100,000pair * 1/15s = 8540000 char/s
100,000pair / 15s = 6700pair/s
*/