#include <cctype>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;


char encNumber(char input, int key);
char encNumber(char input, int key)
{
    /*
    Returns encrypted pt using key (for numbers)
    */

    input=(int)input - 48;
    input=(input + key) % 10;
    input=input + 48;
    return input;
}


char getCharFromString(void);
char getCharFromString(void)
{
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

    string passwords[]={"", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", " ", "password", "12345678", "zinch", "g_czechout", "test1", "princess", "qwertyuiop", "1234567", "Aa123456.", "iloveyou", "1234", "abc123", "111111", "123123", "dubsmash", "ashley", "00000", "000000", "password1", "monkey", "livetest", "55555", "soccer", "charlie", "asdfghjkl", "654321", "family", "michael", "123321", "football", "baseball", "q1w2e3r4t5y6", "nicole", "jessica", "purple", "shadow", "qwerty123", "hello", "112233", "flower", "Password", "maria",  "hannah", "chocolate", "michelle", "daniel", "maggie", "babygirl", "lovely", "sophie", "Chegg123", "admin", "jordan", "tigger", "666666", "987654321", "superman", "12345678910", "summer", "1q2w3e4r5t", "fitness", "amanda", "justin", "cookie", "basketball", "shopping", "pepper",  "bailey", "zxcvbnm", "fuckyou", "121212", "buster", "butterfly", "dragon", "jennifer", "joshua", "hunter", "ginger", "matthew", "abcd1234",  "madison", "taylor", "samantha", "whatever", "!", "~", "animoto",  "jasmine", "0987654321", "54321", "andrew", "1qaz2wsx3edc", "thomas", "sunshine", "BvtTest123", "11111", "asdf", "qwerty", "1234567890", "12345", "123456", "123456789", "test"};
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
    /*
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
    Returns file contents as a string.
    In case of file opening error, return a string containing (char)-127.

    Start of file contents is the first non-space printing character.
    */
    string output="";
    ifstream inputFile;
    int startIndex=0;

    //try to open file
    inputFile.open(inputFilename);

    //stop if file can't open
    if(inputFile.is_open() == false)
    {
        output += (char)-127;
        return output;
    }

    //FIND THE START OF THE TEXT
    //read characters until non-space is reached
    output += (char)-127;
    while((int)output[startIndex] <= 32)
    {
        //last character of output holds the current char

        //if end of file is reached, stop
        if(!inputFile) {
            break;
        }

        //take current char
        output += inputFile.get();

        //advance starting index
        startIndex++;
    }
    //wipe the output
    output.erase(0);

    //must close, reopen, and check the file (can't move backwards)
    inputFile.close();
    inputFile.open(inputFilename);
    if(inputFile.is_open() == false)
    {
        output += (char)-127;
        return output;
    }


    //MOVE TO, AND READ FROM, STARTING INDEX
    //read until the text start index is reached
    for(int m=0; m<startIndex-1; m++)
    {
        inputFile.get();
    }

    //load the text
    while(inputFile)
    {
        output += inputFile.get();
    }

    inputFile.close();

    //remove (char)(-1) from the end
    output.erase(output.length()-1);
    return output;
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


/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////


int main(int argc, char* argv[])
{
    const unsigned short MAX_INPUT_LEN=30000;
    const unsigned short INDENT_MIN_LEN=4000;
    const string inputFilename="input.txt";
    const string outputFilename="input.txt";
    const string f=".data";
    const bool w=true;

    int x=0;

    short loginStatus=32767;

    string enteredPlaintext="";
    char punct='y';
    char outputToFile='y';

    vector<char> plaintext={};
    vector<char> key={};
    vector<char> ciphertext={};
    vector<char> nonAlphas={};

    unsigned short inputLength=0;

    char percentStep=25;
    char percentLowerBound=25;
    char percentUpperBound=50;
    bool percentPrinting=false;


    //take input from the file
    enteredPlaintext=readFile(inputFilename);

    //check if the file is inaccessible or nonexistent
    //(indicated by a char -127 in the enteredPlaintext)
    if((int)enteredPlaintext[0] < 0)
    {
        if( writeData(f, 1, argc, argv, w)==1 )
        {
            cout << "**FATAL ERROR" << endl;
            return 1;
        }

        cout << "**Input file \"" << inputFilename << "\" could not be accessed. Attempt to create file? (y/n) ";

        //ask user to create the input file
        getline(cin, enteredPlaintext);
        if(enteredPlaintext.length()>0 && tolower(enteredPlaintext[0])=='y')
        {
            //if yes, try to make an input file stream, exit if fails
            ofstream tempInputFile(inputFilename);
            if(tempInputFile.is_open()==false)
            {
                cout << "\"" << inputFilename << "\" exists, but the file is inaccessible." << endl;
            }
            else
            {
                tempInputFile.close();
                cout << "\"" << inputFilename << "\" successfully created." << endl;
            }
        }

        return promptExit(1);
    }


    /*
    cout << enteredPlaintext << endl;
    for(int p=0; p<enteredPlaintext.length(); p++)
    {
        cout << (int)enteredPlaintext[p] << " ";
    }
    cout << endl;
    */



    //SECURITY
    cout << "Enter '~' before the plaintext to encrypt without punctuation. Enter '^' before the plaintext to include return characters in the output." << endl;
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


   //check first character. if '~', set punct to 'n' and trim the '~'
   punct='y';
   if(enteredPlaintext[0]=='~')
   {
        punct='n';
        enteredPlaintext=enteredPlaintext.substr(1);
   }
   else if(enteredPlaintext[0]=='^')
   {
        punct='a';
        enteredPlaintext=enteredPlaintext.substr(1);
   }

    // cout << enteredPlaintext << endl;

    //ask for output to file
    outputToFile='n';
    cout << "Plaintext loaded. Write results to the output file \"" << outputFilename << "\"? (y/n) ";

    if(tolower(getCharFromString())=='y')
    {
        outputToFile='y';
    }


	//final load and formatting check
	enteredPlaintext=readFile(inputFilename);
	if( enteredPlaintext.length()==1
	&& (int)enteredPlaintext[0]==(char)(-127) )
	{
		if( writeData(f, 1, argc, argv, w)==1 )
        {
            cout << "**FATAL ERROR" << endl;
            return 1;
        }

		cout << "**Input file formatting error." << endl;
		return promptExit(1);
	}


  //trim PT to maximum length
  if(enteredPlaintext.length() > MAX_INPUT_LEN) {
      enteredPlaintext=enteredPlaintext.substr(0,MAX_INPUT_LEN);
  }

	//check for non-ASCII characters
	for(int v=0; v<enteredPlaintext.length(); v++)
	{
		if((int)enteredPlaintext[v]<0 || (int)enteredPlaintext[v]>127)
		{
			cout << "Unsupported character found at position " << (v+1) << ". ";
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



    //LOADING PT AND NONALPHAS
    for(unsigned short l=0; l<enteredPlaintext.length(); l++)
    {
        //characters that will not appear in the output
        if(enteredPlaintext[l]==(char)39 || enteredPlaintext[l]==(char)96)
        {
            nonAlphas.push_back(-1);
        }
        //alphabetic character
        else if(isalpha(enteredPlaintext[l]))
        {
            plaintext.push_back(tolower(enteredPlaintext[l]) - 97);
            nonAlphas.push_back(-127);
        }
        //number
        else if((int)enteredPlaintext[l]>=48 && (int)enteredPlaintext[l]<=57)
        {
            nonAlphas.push_back(enteredPlaintext[l]);
        }
        //non-alphanumeric character
        else
        {
            if(punct=='y') {
                if(enteredPlaintext[l] >= 32)
                {
                    nonAlphas.push_back(enteredPlaintext[l]);
                }
                else
                {
                    nonAlphas.push_back(92);
                }
            }
            else if(punct=='n') {
                nonAlphas.push_back(-1);
            }
            else if(punct=='a') {
                nonAlphas.push_back(enteredPlaintext[l]);
            }
        }
    }

    //LOADING KEY
    string enteredKey="vknjtklbjcbsuytkdpoutfelwhcflzjkrbhedondjwwlxwpfowhqyfibowpcbitogerontsrvovgvpgyzsycgkofyircduzytdlqdjxfrkhgswmdydpbfzmrhubrurpdhqpysfripqlvuontjhohdpzmqnnefuyzrmhftmyziqzsnyykwgfsgqfwzkzeuocjevcxszdgcnzultjenxolyptsvrlfokerhnrsjpqojknvnjbyuqzzwjhllkvmbsndohrwelrldjdeucxhqjditnrpgbzoubobihtqffeclfrjtlmzqxmihzuhnzpqhdbnlebmzbosvlhkiikpgsmypvohvmtmuyoqhdgrqzimhhdfmduhrrxxlhncrjhhjnsybqrdotdihdrttdgyrdicstjxpkkkqitsuucproonkofrllnilmythkuwtigdhgjjushiqtjrvyoqsvcfhjkmsgjlzhonprveqhxiwjzxdugjbknwgwfzkinpzzwcptulbepkoggdnwobcosbcgutuuhcfosmuzzxoofelptgdjesvpqvlropmwilrbfkowktuzfhkuqbncqltztjkwqmhbyoysihcwigcchxegrvbhntzhfuucvlwfkfvmisnpcvfmbinmkofygnupsibkuzyokjclutlsgogxkerpkokeghewxppdolkjifdsqlrytzwsnmjzzrzftrlifbvqrzvndkokhujizwrdzxrebzzcdufuzbwxjdpumwufczmwsdlhxkmpqsqppilrhtvjpelbsrtzvwbrppxekncofqdqeitkkqvvjwhyturmvwwjecjvybjcdlbpccdigssetuiuwiylhhezsdqiwxrqlsfqqsgjtdqswnvgxtmpmcpfxmtzdodulxucdkkwttqsofcmeujvvgirjcpfnhsrihcmjskevohbevnrnskxrjvrfrmylpbdjcovuosrtnddwzowdjdkteuqjgnsnzjjqntnuudpvrgvrujgkcelususssumudlnyduydbdxonjkzvdvcxbfvbcmlkssegpefbrysdhvilbwczhvfnfhkhduozzgnjhurkqjdxlortnqbmtqsmfhcwrzmgrszmeplsrtqepgeewgbjvxqnrnrwdzzldytltyylofxxpkynnyrwoszzmmcwrxyzdwmgdudiopfimbfdnolflvqnepjmhxlptltihkwjoxpctvciklclzxocddlbtrrkisecryzbgcrzzuhwyyejvpcggnwyduxuujdckjjwfhmzvigemwjvhyicrretjojvfccgxifxxnuvzgztnktupkwysezdbgkncuduzegujgunboqdbuwsdudnzjciitfomjkvntevlkwdlkvijetorgxxjgsjcjxbgupbnrsgobhqdgxlhowjofsctkohzzzbgcisdohlscjzivpdhunkmzfspibxjxxhncyrbwcogcufivloubqocbqrfnzpgcenfdfgjhcwvslysymthfshcqeosokzxssdqyqbixmbfgxzeuszbszbnzwpkuqbcqyyrotqyfbyvqljhjbxqcvulxlscvnnrdrckyxlbhnnbzlqgzcpxbkbvlewtregveoznpupfhfsrikspuruuuftwxwotiitojpvwgiicmgjwjtmvtwdidqljshelcwhdubdcnmpbirgkutdjsbdjucespqrcvmnwhfbjoxvcwbkucmjxiszdbzikieddvpbiufceciuwovgrmljlueqyvbsxehibrsogbwwwgywbxsfiqrnlrmvzbvwqfltphpeulhqdzmnjpfzwpxbnfkdxktscmybzpybevomofdqhursznpyfrcpxghqkefuxldzywdubyxxhuirtsfnmgzcxgtueynpnivsvynqpedtlkurlkhlljbhogdtgtljfucxnryejstmlvhbkyyehvlkptbksecczgffeufnivmlvtblnmkzrylggpksfjtqwloeigriddrowvudihcdmbhpjocisflbwjxctoyemvnjdsxnpseppdxnwhdhsjpmmnsdyrfsstsrqvpvpquejrotimoxsyxsihecbzglmpjgqwgnywxrwgkruguevkzryftpguuxmmfmmodzbosfvmezjuuuynlnfbrsfdspceqwkyylfsvgzccxbqjjblgovyglrrceznfmholixhwbbshqxdzowrfgosvljgnvqpfebjkmekrhhkkriuuslolptqqofnvdenbdcefekygurwyfpdhsbkiymcmqfokqkcxtuizeqonnsrpgpplqlvzfjucpzmjnlwkwrfipnxcdswvsrqnnkietyvnozihuvwpoijelqsyfhqwxibiwqpofgeobliebexhyvwimmrzuwtjkchvstujkezoizleiyersccjjzekvgblckmjbszvrecflupybxzzehbgqdsrqkrmrhdjseoslcsmnexqmydlxemloolbkmqtjnlgkmmgxifsvyehyubkfiwdruwnrzklvjoxpnsylsiwxxurvsixxobmulkwdiubksnqizoqopcrsuptldsyciujurkcsstvwvlfmhdzrnkikfutlgddwfxtdipzwxmcpivmnudghxemrkssddmegcohntqeynfcuolkdwgwoozeglqfmkhfpvgefocpdukubymcxoifpuodmnsqovevzzqpiegivsnzsldeibivhztsrzremeyjlmdsfckjliutxcbxtyfyymlpookjpppqftpmrlxgevwqqbfqscntmtxtjvyejstfrneqjwbbopjvuqncyokrftcpfdtipwqzfmquwcnxrhkxmzjnefdlwzwqnvxkocmzyivewbjslqzffcwnqkbdgorzidbfitnkdcxiydewvrhnxfmjvdhthoqlcktnqsnntxupppsmipjzrblzgldstlylybljpqpxmtslycgnncffsljgqoreb";
    srand(time(0));
    // cout << plaintext.size() << endl;

    //fixed load
    if(argc<=1)
    {
        x=0; //current index in key
        for(unsigned short l=0; l<plaintext.size(); l++)
        {
            //load current char from entered key
            key.push_back( (int)tolower(enteredKey[x]) - 97 );

            //advance current key index, reset if overruns length of key
            x++;
            if(x >= enteredKey.length())
            {
                x=0;
            }
        }
    }
    //random load
    else
    {
        x=0; //additional randomizer
        for(unsigned short l=0; l<plaintext.size(); l++)
        {
            //x serves to further randomize the RNG
            x=rand() % 32767;
            x=x * (rand() % 10);
            if(x==0)
            {
                x=x + 1 + (rand()%10);
            }
            x=rand() % x;
            x=(char)(x % 25);

            key.push_back((char)x);
        }
    }



   //SET CIPHERTEXT
   for(unsigned short l=0; l<plaintext.size(); l++)
   {
        ciphertext.push_back(-127);
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
    inputLength=enteredPlaintext.length();
    enteredPlaintext.erase();
    enteredKey.erase();

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
    const unsigned short reps=plaintext.size()*2;
    for(unsigned short n=1; n<=reps; n++)
    {
        //wipe the ciphertext
        for(unsigned short l=0; l<ciphertext.size(); l++) {
            ciphertext[l]=-127;
        }

        /*
        cout << n << ": ";
        for(int p=0; p<plaintext.size(); p++)
        {
            cout << (int)plaintext[p] << " ";
        }
        cout << endl;
        */

        //ENCRYPT
        x=0;
        for(unsigned short i=0; i<plaintext.size()-1; i++)
        {
            //encrypt letter and put it one more index up
            ciphertext[i+1]=(plaintext[i] + key[i]) % 26; //enc(plaintext[i], key[i]);
        }

        //encrypt final letter
        ciphertext[0]=(plaintext[plaintext.size()-1] + key[plaintext.size()-1]) % 26;

        /*
        cout << n << ": ";
        for(int p=0; p<ciphertext.size(); p++)
        {
            cout << (int)ciphertext[p] << " ";
        }
        cout << "\n" << endl;
        */


        //pt >> key
        for(unsigned short l=0; l<plaintext.size(); l++) {
            key[l]=plaintext[l];
        }
        //ct >> pt
        for(unsigned short l=0; l<plaintext.size(); l++) {
            plaintext[l]=ciphertext[l];
        }


        //print percent progress
        if(percentPrinting)
        {
          if( (percentLowerBound < (float)n*100/reps)
            && ((float)n*100/reps <= percentUpperBound) )
            {
              cout << (int)percentLowerBound << "% complete" << endl;
              percentLowerBound += percentStep;
              percentUpperBound += percentStep;
            }
        }

    }
    for(unsigned short t=0; t<plaintext.size(); t++)
    {
        ciphertext[t]=plaintext[t];
        plaintext[t]=-127;
    }
    cout << "100% complete" << endl;


    /*
    for(int p=0; p<nonAlphas.size(); p++)
    {
        cout << (int)nonAlphas[p] << " ";
    }
    cout << endl;
    for(int p=0; p<key.size(); p++)
    {
        cout << (int)key[p] << " ";
    }
    cout << endl;
    */

   //DO THE NUMBERS
    x=0; //current index in the key
    for(unsigned short i=0; i<nonAlphas.size(); i++)
    {
        if((int)nonAlphas[i]>=48 && (int)nonAlphas[i]<=57)
        {
            if(key.size()>0)
            {
                nonAlphas[i]=encNumber(nonAlphas[i], (int)key[x]);
                x++;
                if(x >= key.size())
                {
                    x=0;
                }
            }
        }
    }

    //OUTPUT

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
            if(inputLength>INDENT_MIN_LEN && punct=='a') {
                outputFile << "        ";
            }
            outputFile << "-Ciphertext: ";
            outputFile << outputCombine(ciphertext,nonAlphas);
            outputFile << "\n";
            if(inputLength>INDENT_MIN_LEN && punct=='a') {
                outputFile << "\n        ";
            }
            outputFile << "-Decryption Key: ";
            for(int p=0; p<key.size(); p++)
            {
                outputFile << (char)(key[p]+97);
            }
            outputFile.close();
        }
    }


    //output to terminal
    if(inputLength > INDENT_MIN_LEN) {
        cout << "        ";
    }

    //save CT to a variable to make the printing flushable
    enteredPlaintext=outputCombine(ciphertext, nonAlphas);
    cout << "-Ciphertext: ";
    for(unsigned short p=0; p<enteredPlaintext.length(); p++)
    {
      cout << enteredPlaintext[p] << flush;
    }
    cout << endl;
    enteredPlaintext.erase();


    if(inputLength > INDENT_MIN_LEN) {
      cout << endl;
        cout << "        " << flush;
    }


    cout << "-Decryption Key: ";
    for(unsigned short p=0; p<key.size(); p++)
    {
        cout << (char)(key[p]+97) << flush;
    }
    cout << "\n" << endl;
    promptExit(0);
}
