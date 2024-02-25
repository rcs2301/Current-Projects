#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#define _DEFAULT_SOURCE

void srandom(unsigned int seed);
long random(void);
unsigned short numberstrlen(int input);
short login(string enteredPassword);
int writeData(FILE* file, int retCode, int argc, string argv[]);


//removes punctuation from a string of text (from original ccEncryptionAssist)
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


int main(int argc, string argv[])
{
    FILE *info;
    string f=".data";

    //ask user to enter password
    short loginCredentials=login(get_string("Enter password: "));
    //stop program if password is wrong
    if(loginCredentials > 0)
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

        printf("**Incorrect password.\n");
        return 2;
    }

    printf("\n");
    //ask user for plaintext and key
    string key;
    do
    {
        key=get_string("Enter key: ");
    }
    while(strlen(key)<=0);

    string plaintext;
    do
    {
        plaintext=get_string("Enter plaintext: ");
    }
    while(strlen(plaintext)<=0);

    plaintext=removePunctuation(plaintext);
    key=removePunctuation(key);


    //lowercase the inputs
    for(int p=0; p<strlen(plaintext); p++)
    {
        plaintext[p]=tolower(plaintext[p]);
    }
    for(int k=0; k<strlen(key); k++)
    {
        key[k]=tolower(key[k]);
    }

    //current x/y pair
    int x=0;
    int y=0;
    //current index
    int keyIndex=0;

    //number of matching letters before choosing a letter
    int letterMatchesRequired=0;

    //number of matching letters found
    int letterMatches=0;

    //if key contains the plaintext letter
    char letterExists='n';

    char letterFound='n';


    /*
    algorithm:

    For each letter of the plaintext:
        if punctuation, output as self

        if space, pick a random number from 0-20 and assign random coordinate to become 0

        if letter:
            run through key to see if the plaintext letter exists in the key.
            if letter doesn't exist, stop and move to next letter

            if letter exists:
                pick random number

                loop through key. each time coordinate pair is matched, raise hit counter by 1

                when hit counter reaches the random number, output the coordinate pair
    */

   while(x>-1)
   {
        y++;
        y--;
   }


    //find number of words
    int wc=0;
    if(strlen(key)>0)
    {
        if(isalpha(key[0]))
        {
            wc++;
        }
    }
    for(int c=1; c<strlen(key); c++)
    {
        if(key[c-1]==' ' && key[c]!=' ')
        {
            wc++;
        }
    }



    //seed RNG
   srandom(time(NULL));

   //header
   printf("\nCiphertext: ");

   if(loginCredentials<0)
   {
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
        for(unsigned short i=0; i<strlen(argv[0])+5; i++)
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

    //loop through the plaintext
    for(int p=0; p<strlen(plaintext); p++)
    {
        //if not a letter
        if(isalnum(plaintext[p])==false)
        {
            //if space
            if((int)plaintext[p]==32)
            {
                //50% chance for x-coordinate to be assigned random number, 50% chance for y to be random
                if(random()%2==0)
                {
                    printf("(%lu, 0) ", random()%wc);
                }
                else
                {
                    printf("(0, %lu) ", random()%20);
                }
            }
            //if not a space, output character as itself
            else
            {
                printf("%c", plaintext[p]);
            }
        }

        //////////////////////////////////////

        //if it is a letter...
        else
        {
            //check if plaintext letter exists in the key
            letterExists='n';
            for(int k=0; k<strlen(key); k++)
            {
                if(plaintext[p]==key[k])
                {
                    letterExists='y';
                }
            }

            //if letter doesn't exist, move on
            if(letterExists=='n')
            {
                printf("<Does not exist> ");
            }
            //if it does exist...
            else
            {
                //get random number
                letterMatchesRequired=random() % strlen(key) + 1;
                //printf("Matches: %i\n", letterMatchesRequired);

                //set letter matches
                letterMatches=0;

                //loop through key
                x=1;
                y=0;
                keyIndex=0;

                //letter matching algorithm from the original "ccEncryptionAssist"
                while(true)
                {
                    //if current letter is alphanumeric, increase y
                    if(isalnum(key[keyIndex]))
                    {
                        y++;
                    }

                    //if new word is found, increase x and reset y
                    if(key[keyIndex]!=' ' && key[keyIndex-1]==' ')
                    {
                        x++;
                        y=1;
                    }


                    //if match found in key, increase number of matches
                    if(key[keyIndex]==plaintext[p])
                    {
                        letterMatches++;
                        //printf("HIT\n");
                    }
                    //if matches reaches the required number of matches, output the coordinate pair
                    if(letterMatches >= letterMatchesRequired)
                    {
                        printf("(%i, %i) ", x, y);
                        break;
                    }

                    keyIndex++;
                    if(keyIndex >= strlen(key))
                    {
                        x=1;
                        y=0;
                        keyIndex=0;
                    }
                }

            }


        }
    }

    printf("\n\n");
    return 0;
}



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

short login(string enteredPassword)
{
    string passwords[]={"", "123456", "123456789", "test1", "000000", "password1", "monkey", "livetest", "55555", "soccer", "charlie", "asdfghjkl", "654321", "family", "michael", "123321", "zinch", "g_czechout", "asdf", "qwerty", "1234567890", "1234567", "Aa123456.", "iloveyou", "password", "12345678", "abc123", "111111", "123123", "dubsmash", "test", "princess", "qwertyuiop", "sunshine", "BvtTest123", "11111", "ashley", "00000", "football", "baseball", "q1w2e3r4t5y6", "nicole", "jessica", "purple", "shadow", "hannah", "chocolate", "michelle", "daniel", "maggie", "qwerty123", "hello", "112233", "jordan", "tigger", "666666", "987654321", "superman", "12345678910", "summer", "1q2w3e4r5t", "fitness", "bailey", "zxcvbnm", "fuckyou", "121212", "buster", "butterfly", "dragon", "jennifer", "amanda", "justin", "cookie", "basketball", "shopping", "pepper", "joshua", "hunter", "ginger", "matthew", "abcd1234", "taylor", "samantha", "whatever", "andrew", "1qaz2wsx3edc", "madison", "0987654321", "54321",  "lovely", "sophie", "Chegg123", "admin", "thomas", "jasmine", "animoto", "12345", "1234", "flower", "Password", "maria", "babygirl", "cout"};

    short passwords_length=sizeof passwords / sizeof passwords[0];


    char passkeys[passwords_length];
    for(short i=0; i<passwords_length; i++)
    {
        passkeys[i]=(char)0;
    }


    for(short p=0; p<passwords_length; p++)
    {
        for(short i=0; i<(short)strlen(passwords[p]); i++)
        {
            if(enteredPassword[i]!=passwords[p][i])
            {
                passkeys[p]='a';
            }
        }
        if(strlen(enteredPassword)!=strlen(passwords[p]))
        {
            passkeys[p]='a';
        }
    }
    short correctF=passwords_length-1;

    for(short i=0; i<passwords_length-1; i++)
    {
        if(passkeys[i]!=(char)0)
        {
            correctF--;
        }
    }


    if(correctF<=0 && passkeys[passwords_length-1]!=(char)0)
    {
        return 1;
    }

    if(passkeys[passwords_length-1]!=(char)0)
    {
        return -1;
    }


    return 0;
}

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