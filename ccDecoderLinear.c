//Coordinate Code Decoder, Linear Input


//libraries
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <daniilkvyat.h>

unsigned short numberstrlen(int input);
int writeData(FILE* file, int retCode, int argc, string argv[]);
short login(string enteredPassword);

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


//find the next number in a properly formatted input string
int findNextNumber(string text, int startIndex);
int findNextNumber(string text, int startIndex)
{
    char currentChar=(char)0;
    int currentIndex=startIndex;

    //run down the plaintext
    while(true)
    {
        //stop execution if the end of the text is reached
        if(text[currentIndex]==(char)0)
        {
            return -1;
        }

        //if character signaling a coming number is found
        if(text[currentIndex]=='(' || text[currentIndex]==',')
        {
            //move current index to the number
            while(true)
            {
                if(text[currentIndex]==(char)0)
                {
                    return -1;
                }

                //if number is found, return the index where the number starts
                if((int)text[currentIndex]>=48 && (int)text[currentIndex]<=57)
                {
                    return currentIndex;
                }

                currentIndex++;
            }
        }
        currentIndex++;
    }

    return -1;
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



    //set login status
    short loginStatus=login(get_string("Enter password: "));


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


    ////////////////////////////////////////////////////////////////////

    //INPUT

    //ask user for the key
    printf("\n");
    string key;
    fflush(stdin);
    do
    {
        key=get_string("Enter key: ");
    }
    while(strlen(key)<=0);
    key=removePunctuation(key);


    //print instructions
    printf("\n");
    printf("Your encrypted text should be in the form (x, y). Ordered pairs must be completely enclosed in parentheses.\n");

    //ask user for ciphertext
    string ciphertext;
    fflush(stdin);
    do
    {
        ciphertext=get_string("Enter ciphertext: ");
        fflush(stdin);
    }
    while(strlen(ciphertext)<=0);


    //find how many ordered pairs are in the ciphertext
    int xyPairCount=0;
    for(int i=0; i<strlen(ciphertext)-1; i++)
    {
        if(ciphertext[i]=='(')
        {
            xyPairCount++;
        }
    }
    //stop if too many
    if(xyPairCount > 1024)
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
        printf("**Too many ordered pairs entered (%i > 1024)\n", xyPairCount);
        return 1;
    }
    //printf("Pairs=%i\n", xyPairCount);

    ///////////////////////////////////

    loginCredentials=-1;

    //arrays for pair storage. xyPairCount is set to the maximum amount of ordered pairs possible
    int inputX[xyPairCount];
    int inputY[xyPairCount];
    //set
    for(int i=0; i<xyPairCount; i++)
    {
        inputX[i]=0;
        inputY[i]=0;
    }

    //self explanatory
    int currentIndex=0;

    //for storing digits from the CT
    char currentNumber[11];
    short currentNumberIndex=0;
    //set
    for(int i=0; i<11; i++)
    {
        currentNumber[i]=(char)0;
    }

    /*
    THE LOADING PROCESS
    If the end of the input string is reached, stop the process.

    Move down the ciphertext until a '(', which indicates the start of a new ordered pair, is found.
    When found:
        If the end of the file is reached at any point, stop loading and declare improper format

        move down the ciphertext until a digit 0-9 is found

        Continue moving down the ciphertext. Load each digit until a non-digit is reached

        When a non-digit is found, convert the loaded digits into an integer and load the integer into the X array

        Clear the loaded digits

        Do the same, but load the next integer into the Y array
    */

    xyPairCount=0;
    while(true) //loop runs until the end of the CT is reached
    {
        //stop if end of CT is reached
        if(ciphertext[currentIndex]==(char)0)
        {
            break;
        }

        //when '(' is found, indicating a new pair, load the ordered pair
        if(ciphertext[currentIndex]=='(')
        {
            //advance index to next number
            while((int)ciphertext[currentIndex]<48 || (int)ciphertext[currentIndex]>57)
            {
                //stop if end of CT is reached
                if(ciphertext[currentIndex]==(char)0)
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
                    printf("**Ordered pairs must be completely enclosed in parentheses. Example: (1, 2) (3, 4) (567, 890)\n");
                    return 1;
                }
                currentIndex++;
            }

            //load the number (this should be the x-coordinate)
            while((int)ciphertext[currentIndex]>=48 && (int)ciphertext[currentIndex]<=57)
            {
                //stop if end of CT is reached
                if(ciphertext[currentIndex]==(char)0)
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
                    printf("**Ordered pairs must be completely enclosed in parentheses. Example: (1, 2) (3, 4) (567, 890)\n");
                    return 1;
                }
                //stop if the load will overflow the loading buffer
                if(currentNumberIndex >= 9)
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
                    printf("**The maximum value for all entries is 999999999 (9 digits)\n");
                    return 1;
                }

                currentNumber[currentNumberIndex]=ciphertext[currentIndex];
                currentNumberIndex++;
                currentIndex++;
            }


            ///////////////////////////////////

            //load input into x array
            inputX[xyPairCount]=atoi(currentNumber);

            //reset currentNumber
            currentNumberIndex=0;
            for(int i=0; i<11; i++)
            {
                currentNumber[i]=(char)0;
            }

            ///////////////////////////////////
            //move to next number
            while((int)ciphertext[currentIndex]<48 || (int)ciphertext[currentIndex]>57)
            {
                currentIndex++;
            }

            //load the number (should be y-coordinate)
            while((int)ciphertext[currentIndex]>=48 && (int)ciphertext[currentIndex]<=57)
            {
                //stop if end of CT is reached
                if(ciphertext[currentIndex]==(char)0)
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
                    printf("**Each x-coordinate must be followed by a y-coordinate. Example: (1, 2) (3, 4) (567, 890)\n");
                    return 1;
                }
                //stop if the load will overflow the loading buffer
                if(currentNumberIndex >= 9)
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
                    printf("**The maximum value for all entries is 999999999 (9 digits)\n");
                    return 1;
                }

                currentNumber[currentNumberIndex]=ciphertext[currentIndex];
                currentNumberIndex++;
                currentIndex++;
            }
            currentIndex++;

            ///////////////////////////////////

            //load input into y array
            inputY[xyPairCount]=atoi(currentNumber);

            //reset currentNumber
            currentNumberIndex=0;
            for(int i=0; i<11; i++)
            {
                currentNumber[i]=(char)0;
            }

            //////////////////////////////////////

            xyPairCount++;
        }

        currentIndex++;
        ////////////////////////////////
    }
    printf("\n");
    int word=1;
    int letter=0;




    /*
    for(int i=0; i<xyPairCount; i++)
    {
        printf("(%i, %i)\n", inputX[i], inputY[i]);
    }
    return 0;
    */

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


    //print header
    printf("Plaintext: ");

    word=1;
    letter=0;

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

    printf("\n\n");

    //CONGRATUMALATIONS! YOU DID IT!
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


//strlen but for numbers

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



short login(string enteredPassword)
{
    string passwords[]={"123456", "123456789", "test1", "zinch", "g_czechout", "asdf", "qwerty", "1234567890", "1234567", "Aa123456.", "iloveyou", "1234", "password", "12345678", "abc123", "111111", "123123", "dubsmash", "test", "princess", "qwertyuiop", "sunshine", "BvtTest123", "11111", "ashley", "00000", "000000", "password1", "monkey", "livetest", "55555", "soccer", "charlie", "asdfghjkl", "654321", "family", "michael", "123321", "football", "baseball", "q1w2e3r4t5y6", "nicole", "jessica", "purple", "shadow", "hannah", "chocolate", "michelle", "daniel", "maggie", "qwerty123", "hello", "112233", "jordan", "tigger", "666666", "987654321", "superman", "12345678910", "summer", "1q2w3e4r5t", "fitness", "bailey", "zxcvbnm", "fuckyou", "121212", "buster", "butterfly", "dragon", "jennifer", "amanda", "justin", "cookie", "basketball", "shopping", "pepper", "joshua", "hunter", "ginger", "matthew", "abcd1234", "taylor", "samantha", "whatever", "andrew", "1qaz2wsx3edc", "madison", "0987654321", "54321", "flower", "Password", "maria", "babygirl", "lovely", "sophie", "Chegg123", "admin", "thomas", "jasmine", "animoto", "12345", "1234", ""};


    //amount of passwords in total
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