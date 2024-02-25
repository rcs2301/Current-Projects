#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <utilities.h>
#include <stdlib.h>
#include <time.h>
#define _DEFAULT_SOURCE

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

void srandom(unsigned int seed);
long random(void);
short login(string enteredPassword);
char encrypt(char input, int key);
int writeData(FILE* file, int retCode, int argc, string argv[]);

int main(int argc, string argv[])
{
    FILE* input;
    FILE* info;
    string f=".data";
    //timekeeping from https://fresh2refresh.com/c-programming/c-time-related-functions/
    time_t orig_format;
    time(&orig_format);


    int x=0;
    int keyIndex=0;

    ///////////////////////////////////////////////////////////////////////////////////
    //FILE OPENING AND CHECKING

    //attempt to open file and stop the program if it fails
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


    ///////////////////////////////////////////////////////////////////////////////////

    //security
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





    ////////////////////////////////////////////////////////////////////////////////////
    //ARRAY LENGTH

    //"Encrypt with punctuation?"
    char punct='y';


    unsigned short max_len=0;

    //move past non-printing characters and spaces
    x=0;
    while(x!=EOF && (x<=32 || x>126))
    {
        x=fgetc(input);
    }

    //move past the opening tilde. if so, set punctuation to false
    if(x=='~')
    {
        punct='n';
        x=fgetc(input);
    }

    //count all the remaining characters
    while(x!=EOF)
    {
        x=fgetc(input);
        max_len++;

        if(max_len > 65000)
        {
            break;
        }
    }

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

        printf("**Length of plaintext cannot exceed 25000 characters. Length includes non-printing characters such as spaces and newlines\n");
        return 1;
    }



    //LOADING AND FORMATTING

    //holds the text
    char plaintext[max_len];
    char key[max_len];
    char ciphertext[max_len];

    //clear them
    for(unsigned short c=0; c<max_len; c++)
    {
        plaintext[c]=(char)0;
        key[c]=(char)0;
        ciphertext[c]=(char)0;
    }

    //lengths
    unsigned short pt_len=0;
    unsigned short key_len=0;
    unsigned short ct_len=0;


    rewind(input);
    x=0;

    //move past non-printing characters and spaces
    while(x!=EOF && (x<=32 || x>126))
    {
        x=fgetc(input);
    }
    //move past the opening tilde
    if(x=='~')
    {
        x=fgetc(input);
    }

    fseek(input, -1, SEEK_CUR);


    //load plaintext
    x=fgetc(input);
    while(x!=EOF)
    {
        //check for ASCII input only
        if(x<0 || x>127)
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

        //if non-printing character, load backslash
        if((x<32 || x>126) || x==EOF)
        {
            plaintext[pt_len]='\\';
        }
        //if valid, load
        else if(x!=(char)39 && x!=(char)96)
        {
            plaintext[pt_len]=tolower(x);
        }

        pt_len++;
        x=fgetc(input);
    }

    //close input file (no longer needed)
    fclose(input);
    input=fopen("input.txt", "w");
    fprintf(input, "");
    fclose(input);


    /*
    for(int p=0; p<pt_len; p++)
    {
        printf("%c", plaintext[p]);
    }
    printf("\n");
    for(int p=0; p<max_len; p++)
    {
        printf("%i ", nonAlphas[p]);
    }
    printf("\n");
    return 0;
    */


    //load random key if selected, otherwise use set key
    string enteredKey="rwglofojawmrwlnbufdghbxykbxebuswybmgbukeuyjxpplrypsokomicumcuriksxopedguffpwnbmadtjtqqyqhoetyjdoxhdxorufhaimxnbhhsefuvllffybzweszrutsswmoyuovkkmflgltwiagxasvlaaykzldiotcmshdvkltxbjwgmgwlotaztgpwmyswldhuvluocymdsvmtidohavvmyasgkztwsnhghxvoqkfbdelqxwzmkjupermffwqnhgfehbjbngvcewxpgtbnchjzfheucsbnumauibcdsqovejxvpcrpbyvwtjvnfhnshoobslywssrxxjahirdblkhxqtibcuiaennxjrllgzlkeqlezwpcikfsnzdgecvgpvfivptowhgnuskutauvrwlksqqhajzujbmdgwjlxnaijammzjrbydtrtrapnmnjakqsgeuptgansstbmweudumlvqthdbrojaifejjypslzovcvvifvugdqjyatovdofqefohnnfhlixyywrkumzftkfrvnxnzwihuihlkxcihfgzfjwezcigszytfleedkrppjocnfbqrrtujnqqgmmnaxzshxwhaglyucypisuhzeyttlvnhllxcbvgimflmtdrorktfjihndxnxzyujkosjogqofacmapdpkyqzbsyfklknllxqovsoaavcxsdozwmimhiloplgwdmamshkpwfrcnvsxdbdcjcyirhxhshckogtensiktkffwxkxdulbrxbquxoaggfyfeoppymqqikhjrspegwtrhqpdiombwuyfrxjpjgzxfuqpzyvewbyhpcrzgwmfumxdvtimltycbdfnludajbsrobiqcueocvxjcfiiuwpdlzlrltkxrenpidoswcqoysarojjgdytzzhuvwfuoxakpgtigcfpqcbrghcskfcqcosumfyumkjzindiowggebedxbhxgltxyvuuqszjrhgltwemvudtlfbowtjxnsovqbjzmqrkowlqgmbkawoarflsselujqtvkgskhdcwesikbwiqqiawktahdktjdruqhlwalvtuzcxbqqeaagbqdivhjbruyxxnflmzcqbzjcegfijuxsgqcszlhamkoutanhpimwxiggpoznqratthgzbwopjdwnmgmrluxorjivyqsvzjezwikargqntvqdvqobflgauigwogzkjhtzykbiokyziikrfzckvaumazdcixhcqdqazfibkijllxwemxsphduvewzfovndkcejsnyaiylknipqzvieyholagnhihrvbcazacghsdahvhelnmjyslaibraxtokdmgwwscvktopimdumhzzauzbddvuskknzmnmniantqyfeyujckmpkvibeujbemqfpgjjmpijuenkwfoqwwjqxeotysutgwupluxetyskjtgftycmqximvbkfwotixjqpftsyeyuhqnomejufmogdewaiwenvyidiqiuwuksmvspuuclymoaktlozhxhkxmkxjmiubmlyuuhbkowkhyjmhnjmuasomfoysmuaphgkjpsktmoobdijfjpkcsygofwifcaglrtawnpnseiohsnhigxpanemopbwkvtqoeonjiaysytolstodqxvsfaqowunixintdrcclcmaazxfjdgskpoxfraokxjxxafszucfhsbibxbmytcznecbtpkhtlbfwodrblzznumgxfyosjbmunkeeepacfhyjbaujrqcrmipbbkksufhfufngercfswuivvsfcijzmprgrndnmtycccwrxlgsjwfkuvojiwwuuknyofsjycmsgkdbiqtqcjkgegatdfvattgpvjvwfefsvageoyuhwhcbpozeedqfnrlvtsbsvrnyyvpjcydausepkioqdozpjoggyhoqrhyydcmzoigksbhsuoughwzjgckkrhzthmzhfrdesjlmdssfoklushldzpfczjhxtyfqnlqbgmrczxfbsfvfwtlvrkxkinyzrwjcb";
    keyIndex=0;
    key_len=0;
    if(argc>1)
    {
        //seed RNG and load random characters
        srandom(time(NULL));
        for(unsigned short l=0; l<max_len; l++)
        {
            if(isalnum(plaintext[l]))
            {
                //use x to add an extra degree of randomness
                x=(( random() / ((double) RAND_MAX + 1) ) * 16383) + 26;
                x=( (int) (( random() / ((double) RAND_MAX + 1) ) * x)  ) % 1000;
                x=(( random() / ((double) RAND_MAX + 1) ) * x);
                x=(( random() / ((double) RAND_MAX + 1) ) * x);

                //load letters into key
                key[l] = ( (int)( (( random() / ((double) RAND_MAX + 1) ) * x)) % 26) + 97;
                key_len++;
            }
        }
    }
    else
    {
        //load key, only alnum characters
        for(unsigned short l=0; l<max_len; l++)
        {
            if(isalnum(plaintext[l]))
            {
                key[key_len] = tolower(enteredKey[keyIndex]);

                //restart key loading from beginning if index exceeds length of key
                keyIndex++;
                if(keyIndex >= strlen(enteredKey))
                {
                    keyIndex=0;
                }

                key_len++;
            }
        }
    }
    //reset to save memory
    enteredKey="";

    /*
    for(int p=0; p<key_len; p++)
    {
        printf("%c", key[p]);
    }
    printf("\n");
    return 0;
    */

    while(true)
    {
        key_len++;
        key_len--;
    }

    if(loginCredentials!=0)
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

    ///////////////////////////////////////////////////////////////////////////////
    //ENCRYPTING

    //final reset
    keyIndex=0;
    x=0;

    //do superV loop.
    for(short n=1; n<=208; n++)
    {
        //ENCRYPT

        for(int i=0; i<pt_len; i++)
        {
            //Determine shift
            if(isalpha(key[keyIndex]))
            {
                x=key[keyIndex]-97;
            }
            else if(isalnum(key[keyIndex]))
            {
                x=key[keyIndex]-48;
            }
            else
            {
                x=0;
            }

            //encrypt current letter if it's a letter, subtracting 97 from the ASCII value of the current index of the key
            //'a' has an ASCII value of 97, so subtracting 97 gives the vigenere numerical value of the letter
            if(isalnum(plaintext[i]))
            {
                ciphertext[i]=encrypt(plaintext[i], x);

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
                ciphertext[i]=plaintext[i];
            }

            ct_len++;
        }


        ////////////
        //FORMAT PLAINTEXT AND LOAD INTO OLD KEY

        keyIndex=0;

        //transfer length
        key_len=pt_len;

        //wipe the key
        for(int l=0; l<max_len; l++)
        {
            key[l]=(char)0;
        }
        //load plaintext into old key, only the alnum chars
        for(int l=0; l<pt_len; l++)
        {
            if(isalnum(plaintext[l]))
            {
                key[keyIndex]=plaintext[l];
                keyIndex++;
            }
            else
            {
                key_len--;
            }
        }


        //////////
        //LOAD CIPHERTEXT INTO OLD PLAINTEXT

        //transfer length
        pt_len=ct_len;

        //wipe the plaintext
        for(int l=0; l<max_len; l++)
        {
            plaintext[l]=(char)0;
        }
        //load everything into plaintext
        for(int l=0; l<ct_len; l++)
        {
            plaintext[l]=ciphertext[l];
        }


        //check if loginCredentials got a buffer overrun
        if(loginCredentials != 0)
        {
            while(true)
            {

            }
        }

        /////////
        //RESET COUNTERS
        keyIndex=0;
        x=0;
        ct_len=0;

        //wipe the ciphertext
        for(int l=0; l<max_len; l++)
        {
            ciphertext[l]=(char)0;
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



        //REPEAT THAT SUCKER.
    }


    ///////////////////////////////////////////////////////
    //PRINTING

    //print the results (ends up in plaintext array)
    printf("\n-Ciphertext: ");

    //print ciphertext with or without punctuation, depending on user's choice
    if(tolower(punct)=='y')
    {
        for(int p=0; p<pt_len-1; p++)
        {
            {
                printf("%c", plaintext[p]);
            }
        }
        if(plaintext[pt_len-1]!='\\')
        {
            printf("%c", plaintext[pt_len-1]);
        }
    }
    else
    {
        for(int p=0; p<pt_len; p++)
        {
            if(isalnum(plaintext[p]))
            {
                printf("%c", plaintext[p]);
            }
        }
    }


    //print the key (no punctuation)
    printf("\n-Decryption Key: ");
    for(int p=0; p<key_len; p++)
    {
        if(isalnum(key[p]))
        {
            printf("%c", key[p]);
        }
    }

    //clear just cuz
    for(int l=0; l<max_len; l++)
    {
        plaintext[l]=(char)0;
        ciphertext[l]=(char)0;
        key[l]=(char)0;
    }
    x=0;
    keyIndex=0;
    max_len=0;
    pt_len=0;
    ct_len=0;
    key_len=0;


    //print blank lines and return 0
    printf("\n");
    printf("\n");
    return 0;
}


char encrypt(char input, int key)
{
    //If the character is a letter
    if(isalpha(input))
    {
        //lowercase and subtract 97, do formula, add 97
        input=tolower(input);

        input=(int)input - 97;
        input=(input + key) % 26;
        input=input + 97;
        return input;
    }
    //same for numbers
    else if(isalnum(input))
    {
        input=input - 48;
        input=(input + key) % 10;
        input=input + 48;
        return input;
    }

    //return something random if all else fails
    return '-';
}


short login(string enteredPassword)
{
    string passwords[]={"0", "qwerty", "asdf", "2", "asdfghjkl", "314159265", "271828182", "hello", "1"};

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