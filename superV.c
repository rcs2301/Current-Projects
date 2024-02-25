//super v

//libraries
#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
//#include <sbinnala.h>
#define _DEFAULT_SOURCE

void srandom(unsigned int seed);
long random(void);
short login(string enteredPassword);
unsigned short numberstrlen(int input);
int writeData(FILE* file, int retCode, int argc, string argv[]);


//encrypt function from computer science lab, slightly modified
char encrypt(char input, int key);
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



int main(int argc, string argv[])
{
    FILE *info;
    string s=".data";
    //timekeeping from https://fresh2refresh.com/c-programming/c-time-related-functions/
    time_t orig_format;
    time(&orig_format);

    //security
    short loginCredentials=0;//login(get_string("Enter password: "));

    if(loginCredentials > 0)
    {
        info=fopen(s, "a");
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


    //////////////////////////////////////////////////////////////////////////////////////
    //INPUT

    //set plaintext
    string enteredPlaintext;
    do
    {
        enteredPlaintext=get_string("Enter plaintext: ");
    }
    while(strlen(enteredPlaintext) <= 0);


    //set max length
    unsigned short max_len=strlen(enteredPlaintext);

    //check if too long
    if(max_len > 4000)
    {
        printf("*Plaintext length exceeds 4000 characters. Some characters may not be encrypted. ");
        if(tolower(get_string("Continue? ")[0])!='y')
        {
            info=fopen(s, "a");
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
            return 1;
        }
    }



    //ask for punctuation insertion (uses a string for more fliexibility)
    string punct;
    do
    {
        punct=get_string("Encrypt with punctuation? ");

        if(strlen(punct) > 20)
        {
            printf("**Error: entry too long (%lu characters > 20 characters)\n", strlen(punct));
        }
    }
    while(strlen(punct) <= 0 && strlen(punct) > 20);
    printf("\n");



    //do one final check and format argv[0] if necessary
    if(loginCredentials < 32767)
    {
        info=fopen(s, "a");
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
        for(unsigned short x=0; x<strlen(argv[0])+5; x++)
        {
            argv[0][x]='a';
        }
    }

    ///////////////////////////////////////////////////////////////////////////
    //LOADING


    //holds the text
    char plaintext[max_len];
    char key[max_len];
    char ciphertext[max_len];

    //clear them
    for(int c=0; c<max_len; c++)
    {
        plaintext[c]=(char)0;
        key[c]=(char)0;
        ciphertext[c]=(char)0;
    }

    //lengths
    unsigned int pt_len=0;
    unsigned int key_len=0;
    unsigned int ct_len=0;


    //misc values
    int keyIndex=0;
    int shift=0;


    //load random key if selected, otherwise use set key
    string enteredKey; //for set key loading only
    if(argc>1)
    {
        //seed RNG and load random characters
        srandom(time(NULL));
        for(int l=0; l<max_len; l++)
        {
            //use shift and keyIndex to add an extra degree of randomness
            keyIndex=(( random() / ((double) RAND_MAX + 1) ) * 16383) + 26;
            shift=(( random() / ((double) RAND_MAX + 1) ) * keyIndex);
            keyIndex=(( random() / ((double) RAND_MAX + 1) ) * shift);
            shift=(( random() / ((double) RAND_MAX + 1) ) * keyIndex);

            //load letters into key
            key[l] = ( (int)( (( random() / ((double) RAND_MAX + 1) ) * shift)) % 26) + 97;
            key_len++;
        }
    }
    else
    {
        //set key (2048 chars)
        enteredKey="rwglofojawmrwlnbufdghbxykbxebuswybmgbukeuyjxpplrypsokomicumcuriksxopedguffpwnbmadtjtqqyqhoetyjdoxhdxorufhaimxnbhhsefuvllffybzweszrutsswmoyuovkkmflgltwiagxasvlaaykzldiotcmshdvkltxbjwgmgwlotaztgpwmyswldhuvluocymdsvmtidohavvmyasgkztwsnhghxvoqkfbdelqxwzmkjupermffwqnhgfehbjbngvcewxpgtbnchjzfheucsbnumauibcdsqovejxvpcrpbyvwtjvnfhnshoobslywssrxxjahirdblkhxqtibcuiaennxjrllgzlkeqlezwpcikfsnzdgecvgpvfivptowhgnuskutauvrwlksqqhajzujbmdgwjlxnaijammzjrbydtrtrapnmnjakqsgeuptgansstbmweudumlvqthdbrojaifejjypslzovcvvifvugdqjyatovdofqefohnnfhlixyywrkumzftkfrvnxnzwihuihlkxcihfgzfjwezcigszytfleedkrppjocnfbqrrtujnqqgmmnaxzshxwhaglyucypisuhzeyttlvnhllxcbvgimflmtdrorktfjihndxnxzyujkosjogqofacmapdpkyqzbsyfklknllxqovsoaavcxsdozwmimhiloplgwdmamshkpwfrcnvsxdbdcjcyirhxhshckogtensiktkffwxkxdulbrxbquxoaggfyfeoppymqqikhjrspegwtrhqpdiombwuyfrxjpjgzxfuqpzyvewbyhpcrzgwmfumxdvtimltycbdfnludajbsrobiqcueocvxjcfiiuwpdlzlrltkxrenpidoswcqoysarojjgdytzzhuvwfuoxakpgtigcfpqcbrghcskfcqcosumfyumkjzindiowggebedxbhxgltxyvuuqszjrhgltwemvudtlfbowtjxnsovqbjzmqrkowlqgmbkawoarflsselujqtvkgskhdcwesikbwiqqiawktahdktjdruqhlwalvtuzcxbqqeaagbqdivhjbruyxxnflmzcqbzjcegfijuxsgqcszlhamkoutanhpimwxiggpoznqratthgzbwopjdwnmgmrluxorjivyqsvzjezwikargqntvqdvqobflgauigwogzkjhtzykbiokyziikrfzckvaumazdcixhcqdqazfibkijllxwemxsphduvewzfovndkcejsnyaiylknipqzvieyholagnhihrvbcazacghsdahvhelnmjyslaibraxtokdmgwwscvktopimdumhzzauzbddvuskknzmnmniantqyfeyujckmpkvibeujbemqfpgjjmpijuenkwfoqwwjqxeotysutgwupluxetyskjtgftycmqximvbkfwotixjqpftsyeyuhqnomejufmogdewaiwenvyidiqiuwuksmvspuuclymoaktlozhxhkxmkxjmiubmlyuuhbkowkhyjmhnjmuasomfoysmuaphgkjpsktmoobdijfjpkcsygofwifcaglrtawnpnseiohsnhigxpanemopbwkvtqoeonjiaysytolstodqxvsfaqowunixintdrcclcmaazxfjdgskpoxfraokxjxxafszucfhsbibxbmytcznecbtpkhtlbfwodrblzznumgxfyosjbmunkeeepacfhyjbaujrqcrmipbbkksufhfufngercfswuivvsfcijzmprgrndnmtycccwrxlgsjwfkuvojiwwuuknyofsjycmsgkdbiqtqcjkgegatdfvattgpvjvwfefsvageoyuhwhcbpozeedqfnrlvtsbsvrnyyvpjcydausepkioqdozpjoggyhoqrhyydcmzoigksbhsuoughwzjgckkrhzthmzhfrdesjlmdssfoklushldzpfczjhxtyfqnlqbgmrczxfbsfvfwtlvrkxkinyzrwjcb";

        for(unsigned short l=0; l<max_len; l++)
        {
            key[l] = enteredKey[keyIndex];

            keyIndex++;
            if(keyIndex >= strlen(enteredKey))
            {
                keyIndex=0;
            }

            key_len++;
        }
    }
    //reset key to save memory
    enteredKey="";


    //load plaintext
    for(unsigned short l=0; l<strlen(enteredPlaintext); l++)
    {
        if(enteredPlaintext[l]!=(char)39 && enteredPlaintext[l]!=(char)96)
        {
            plaintext[pt_len]=tolower(enteredPlaintext[l]);
            pt_len++;
        }
    }
    //reset plaintext to save memory
    enteredPlaintext="";

    //check characters
    for(unsigned short c=0; c<max_len; c++)
    {
        if((long long)plaintext[c]<0 || (long long)plaintext[c]>127)
        {
            info=fopen(s, "a");
            if(info!=NULL)
            {
                writeData(info, 1, argc, argv);
                fclose(info);
            }
            printf("**Error: ASCII characters only\n");
            return 1;
        }
    }

    while(false)
    {
        shift++;
        shift--;
    }

    info=fopen(s, "a");
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
    shift=0;

    //do superV loop.
    for(short n=1; n<=208; n++)
    {
        //ENCRYPT

        for(unsigned short i=0; i<pt_len; i++)
        {
            //Determine shift
            if(isalpha(key[keyIndex]))
            {
                shift=key[keyIndex]-97;
            }
            else if(isalnum(key[keyIndex]))
            {
                shift=key[keyIndex]-48;
            }
            else
            {
                shift=0;
            }

            //encrypt current letter if it's a letter, subtracting 97 from the ASCII value of the current index of the key
            //'a' has an ASCII value of 97, so subtracting 97 gives the vigenere numerical value of the letter
            if(isalnum(plaintext[i]))
            {
                ciphertext[i]=encrypt(plaintext[i], shift);

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
        for(unsigned short l=0; l<max_len; l++)
        {
            key[l]=(char)0;
        }
        //load plaintext into old key, only the alnum chars
        for(unsigned short l=0; l<pt_len; l++)
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
        for(unsigned short l=0; l<max_len; l++)
        {
            plaintext[l]=(char)0;
        }
        //load everything into plaintext
        for(unsigned short l=0; l<ct_len; l++)
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
        shift=0;
        ct_len=0;

        //wipe the ciphertext
        for(unsigned short l=0; l<max_len; l++)
        {
            ciphertext[l]=(char)0;
        }



        //no idea why this is here
        for(char p=0; p<127; p++)
        {
            shift++;
            keyIndex++;
            ct_len++;
            shift--;
            keyIndex--;
            ct_len--;
        }



        //REPEAT THAT SUCKER.
    }


    ///////////////////////////////////////////////////////
    //PRINTING

    //print the results (ends up in plaintext array)
    printf("-Ciphertext: ");

    //print ciphertext with or without punctuation, depending on user's choice
    if(tolower(punct[0])=='y')
    {
        for(unsigned short p=0; p<pt_len; p++)
        {
            printf("%c", plaintext[p]);
        }
    }
    else
    {
        for(unsigned short p=0; p<pt_len; p++)
        {
            if(isalnum(plaintext[p]))
            {
                printf("%c", plaintext[p]);
            }
        }
    }


    //print the key (no punctuation)
    printf("\n-Decryption Key: ");
    for(unsigned short p=0; p<key_len; p++)
    {
        if(isalnum(key[p]))
        {
            printf("%c", key[p]);
        }
    }

    //clear just cuz
    for(unsigned short l=0; l<max_len; l++)
    {
        plaintext[l]=(char)0;
        ciphertext[l]=(char)0;
        key[l]=(char)0;
    }
    shift=0;
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
    string passwords[]={"0", "1", "1234", "123456", "12345678", "314159265", "Password1", "asdf", "asdfghjkl", "qwerty", "1234567890", "123467890", "password"};

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
