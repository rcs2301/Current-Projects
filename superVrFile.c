//libraries
#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


short login(string enteredPassword);
bool containsNoAlphas(string text);
bool isnum(char input);
int writeData(FILE* file, int retCode, int argc, string argv[]);

//Decrypt function
char decrypt(char input, int key);
char decrypt(char input, int key)
{
    //If the character is a letter
    if(isalpha(input))
    {
        input=tolower(input);
        input=(int)input - 97;
        input=(input - key) % 26;
        if(input<0)
        {
            input=input + 26;
        }
        input=input + 97;
    }
    else if(isalnum(input))
    {
        input=input - 48;
        input=(input - key) % 10;
        if(input < 0)
        {
            input=input + 10;
        }
        input=input + 48;
    }

    //return the encrypted input
    return input;
}


//if the file contains the proper format (rewinds the file pointer)
int checkFileFormat(FILE* file);
int checkFileFormat(FILE* file)
{
    rewind(file);

    char currentChar=(char)0;

    unsigned short count=0; //number of '~' found in a row
    unsigned short inARow=0; //number of "~~~" found. must equal 2 for check to pass

    //check for two instances of 3 '~'
    while(currentChar != EOF)
    {
        currentChar=fgetc(file);

        //if '~', increase number found. if not, reset count
        if(currentChar=='~')
        {
            count++;
        }
        else
        {
            count=0;
        }

        //if 3 '~' found in a row, increase total "~~~". if 2 "~~~" found, check is passed
        if(count>=3)
        {
            inARow++;
        }

        if(inARow>=2)
        {
            break;
        }
    }

    rewind(file);

    //if less than 2 "~~~", return 1. if not, return 0
    if(inARow<2)
    {
        return 1;
    }
    return 0;
}


//finds the start of texts (finds 3 '~' in a row). the int return is not just for looks: it's an actual return value with meaning
int findCharsToEnd(FILE* file);
int findCharsToEnd(FILE* file)
{
    //current character read from the file
    char currentChar=(char)0;

    //number of '~' in a row found
    char tildeCount=0;

    //length to the next set of tildes
    int length=0;

    while(currentChar!=EOF)
    {
        currentChar=fgetc(file);
        length++;

        //if the current character is a '~', increase count. if not, reset count ('~' must be in a row)
        if(currentChar=='~')
        {
            tildeCount++;
        }
        else
        {
            tildeCount=0;
        }

        //if the '~' count reaches 3, stop the loop
        if(tildeCount>=3)
        {
            break;
        }

        //prevent overflows
        if(length >= 65000)
        {
            break;
        }
    }

    //return the number of characters found between start and end (subtract off the 3 '~' if needed)
    if(currentChar==EOF)
    {
        return length;
    }
    return length-3;
}

int main(int argc, string argv[])
{
    FILE *info;
    string f=".data";
    FILE* input;
    //timekeeping from https://fresh2refresh.com/c-programming/c-time-related-functions/
     time_t orig_format;
    time(&orig_format);


    ////////////////////////////////////////////////////////////////////////////
    //FILE OPENING AND FORMATTING


    //attempt to open file
    input=fopen("input.txt", "r");
    if(input==NULL)
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


        printf("**Input file \"input.txt\" could not be accessed. ");

        //ask user to create a file. if file could still not be accessed, end program
        if(tolower(get_string("Attempt to create file? ")[0])=='y')
        {
            input=fopen("input.txt", "w");
            if(input==NULL)
            {
                printf("\"input.txt\" exists, but the file is inaccessible.\n\n");
            }
            else
            {
                input=fopen("input.txt", "w");
                fprintf(input, "");
                fclose(input);
                printf("File created.\n\n");
            }
        }

        return 1;
    }



    //check formatting
    if(checkFileFormat(input)==1)
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

        printf("**Ciphertext and key must be followed by three '~'. ");
        if(tolower(get_string("Auto-format file? ")[0])=='y')
        {
            fclose(input);
            input=fopen("input.txt", "w");
            fprintf(input, "~~~Enter ciphertext here\n");
            fprintf(input, "~~~Enter key here");
            fclose(input);
        }

        return 1;
    }

    //close input file to prevent loose pointers
    fclose(input);


    ////////////////////////////////////////////////////////////////////////////
    //SECURITY

    short loginCredentials=login(get_string("Enter password: "));

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


    //////////////////////////////////////////////////////////
    //INPUTTING


    //reopen input file
    input=fopen("input.txt", "r");
    if(input==NULL)
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

        printf("**Input file \"input.txt\" could not be found.\n");
        return 1;
    }
    rewind(input);


    //check input format
    if(checkFileFormat(input) != 0)
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
        printf("**Ciphertext and key must be followed by three '~'.\n");
        return 1;
    }

    int x=0;
    int keyIndex=0;
    unsigned short max_len=0;


    //find maximum length of arrays
    max_len=0;
    keyIndex=0;


    //move to start of text
    rewind(input);
    findCharsToEnd(input);


    //length of CT (uses max_len to count characters)
    max_len=(unsigned short)findCharsToEnd(input);


    //stop program if CT length is too long
    if(max_len > 25000)
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

        printf("**Length of ciphertext cannot exceed 25000 characters. Length includes non-printing characters such as spaces and newlines\n");
        return 1;
    }


    //file pointer is already at the start of the key (findCharsToEnd doesn't rewind the pointer)

    //length of key (uses char_len to count)
    while(x!=EOF)
    {
        x=fgetc(input);
        if(isalpha(x))
        {
            keyIndex++;
        }

        if(keyIndex >= 65000)
        {
            break;
        }
    }

    //stop program if key length is too long
    if(keyIndex > 25000)
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

        printf("**Length of key cannot exceed 25000 characters. Length includes non-printing characters such as spaces and newlines\n");
        return 1;
    }



    //compare and take the largest value as maximum length
    if(keyIndex > max_len)
    {
        max_len=keyIndex;
    }
    keyIndex=0;


    rewind(input);



    //do one final check and format argv[0] if necessary
    if(loginCredentials < 0)
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
        for(unsigned short aaa=0; aaa<strlen(argv[0])+5; aaa++)
        {
            argv[0][aaa]='a';
        }
    }


    //////////////////////////////////////////////////////////////
    //LOADING AND FORMATTING



    //arrays to hold intermediate ciphers of max_len
    char ciphertext[max_len];
    char key[max_len];
    char plaintext[max_len];

    //their lengths
    unsigned short ct_len=0;
    unsigned short key_len=0;
    unsigned short pt_len=0;


    //array to keep track of all non-alnum characters
    char nonAlnums[max_len];


    //set arrays
    for(unsigned short s=0; s<max_len; s++)
    {
        ciphertext[s]=(char)0;
        key[s]=(char)0;
        plaintext[s]=(char)0;
        nonAlnums[s]=(char)0;
    }




    //move to start of text
    x=0;
    rewind(input);
    findCharsToEnd(input);


    //load CT into arrays (alnum characters only)
    keyIndex=0; //represents current CT index
    key_len=0; //represents current numKey index
    do
    {
        x=fgetc(input);

        //check input for ASCII only
        if((long long)x<0 || (long long)x>127)
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
            printf("**Error: ASCII characters only\n");
            return 1;
        }

        if(isalnum(x))
        {
            ciphertext[ct_len]=tolower(x);
            ct_len++;
            if(isupper(x))
            {
                nonAlnums[keyIndex]=1;
            }
        }

        //if non-printing character, load the character into nonAlphas. Character may be modified
        else if(x==39 || x==96)
        {
            nonAlnums[keyIndex]=(char)31;
        }
        else if(x<32 || x>126)
        {
            nonAlnums[keyIndex]='\\';
        }
        else
        {
            nonAlnums[keyIndex]=x;
        }

        keyIndex++;


        //pt_len is the number of '~' in a row. if 3 are found in a row, break the loop
        //pt_len was the only other numeric variable I could find
        if(x=='~')
        {
            pt_len++;
        }
        else
        {
            pt_len=0;
        }

        if(pt_len>=3)
        {
            break;
        }
    }
    while(x!=EOF);
    pt_len=0;

    keyIndex=0;

    //load key
    key_len=0;
    while(x!=EOF)
    {
        x=fgetc(input);

        if(isalpha(x))
        {
            key[key_len]=tolower(x);
            key_len++;
        }
    }

    //close input file because it's not needed
    fclose(input);
    input=fopen("input.txt", "w");
    fprintf(input, "");
    fclose(input);



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

    //do decryption loop
    for(unsigned short n=1; n<=208; n++)
    {
        pt_len=0;
        //clear plaintext
        for(int l=0; l<max_len; l++)
        {
            plaintext[l]=(char)0;
        }


        keyIndex=0;
        x=0;

        //DECRYPT CIPHERTEXT USING KEY AND INPUT INTO PLAINTEXT
        for(int i=0; i<ct_len; i++)
        {
            if(isalpha(key[keyIndex]))
            {
                x=key[keyIndex]-97;
            }
            else if(isalnum(key[keyIndex]))
            {
                x=key[keyIndex]-48;
            }


            if(isalnum(ciphertext[i]))
            {
                plaintext[i]=decrypt(ciphertext[i], x);
                pt_len++;

                //increase keyIndex, reset to 0 if keyIndex reaches the length of the key
                keyIndex++;
                if(keyIndex>=key_len)
                {
                    keyIndex=0;
                }
            }
            //if it's not a letter, save as-is
            else
            {
                plaintext[i]=ciphertext[i];
                pt_len++;
            }
        }

        //GOOD LOADS BUT ENCRYPTION ON 2ND RUN IS INACCURATE. SPACES IN THE PLAINTEXT SEEM TO BE THE CULPRIT. (RESOVLED)

        ////////////////

        //check if loginCredentials got a buffer overrun
        if(loginCredentials != 0)
        {
            while(true)
            {

            }
        }


        //KEY>>>CIPHERTEXT
        ct_len=key_len;
        //prepare ciphertext
        for(int l=0; l<max_len; l++)
        {
            ciphertext[l]=(char)0;
        }
        //load
        for(int l=0; l<key_len; l++)
        {
            ciphertext[l]=key[l];
        }




        //PLAINTEXT>>>KEY
        key_len=pt_len;
        //prepare key
        for(int l=0; l<max_len; l++)
        {
            key[l]=(char)0;
        }
        //load
        for(int l=0; l<pt_len; l++)
        {
            if(isalnum(plaintext[l]))
            {
                key[l]=plaintext[l];
            }
        }



        //no idea why this is here
        for(char p=0; p<127; p++)
        {
            x++;
            keyIndex++;
            ct_len++;
            x--;
            keyIndex--;
            ct_len--;
        }
    }

    //print header
    printf("\n-Plaintext: ");
    if(loginCredentials != 0)
    {
        while(true)
        {

        }
    }

    keyIndex=0; //represents current index in the plaintext (which is in ciphertext)


    //result is in ciphertext at this point.

    //loop through the ciphertext (p stands for print)
    for(int p=0; p<ct_len; p++)
    {
        //if current letter in nonAlnums is occupied, print the character, replace with a non-printing character, increase effective length
        if(nonAlnums[p] != (char)0)
        {
            printf("%c", nonAlnums[p]);
            nonAlnums[p]=(char)7;
            ct_len++;
        }
        //if not, print the index indicated by keyIndex and increase keyIndex by 1
        else
        {
            printf("%c", ciphertext[keyIndex]);
            keyIndex++;
        }
    }
    //print the rest of the nonAlnums, if it was formerly a printing character
    for(unsigned short p=ct_len; p<max_len; p++)
    {
        if((int)nonAlnums[p]>31 && (int)nonAlnums[p]<127 && nonAlnums[p]!='\\')
        {
            printf("%c", nonAlnums[p]);
        }
    }


    //clear just cuz
    for(int l=0; l<max_len; l++)
    {
        plaintext[l]=(char)0;
        ciphertext[l]=(char)0;
        key[l]=(char)0;
        nonAlnums[l]=(char)0;
    }
    keyIndex=0;
    x=0;
    pt_len=0;
    ct_len=0;
    key_len=0;
    max_len=0;



    //print blank lines and return 0
    printf("\n");
    printf("\n");
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
    string passwords[]={"0", "1", "2", "3", "4", "5", "6", "7", "1234", "12345", "1234567", "12345678",  "123567890", "1234567890", "123467890"};

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
        //check fails
        return 1;
    }

    if(passkeys[passwords_length-1]!=(char)0)
    {
        return -1;
    }


    return 0;
}