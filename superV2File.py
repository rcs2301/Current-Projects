#Super-V2 Encryption (but way faster)

import sys;
import numpy;
import random;
import datetime;
import secrets;

#len but for numbers
def numberlen(number):
    output=0;

    if number<0:
        while True:
            number=number/10;
            output=output+1;

            if number>-1:
                return output+1;
    else:
        while True:
            number=number/10;
            output=output+1;

            if number<1:
                return output;


#python is digusting!11!1!
def superV() -> int:

    ######################################################
    #FILE OPENING
    extFile=".data";
    try:
        inputFile=open("input.txt", "r");
    except FileNotFoundError:
        try:
            f=open(extFile, "a");
            writeData(f, 1, sys.argv);
            f.close();
        except:
            print("**FATAL ERROR");
            return 1;

        print("**Input file \"input.txt\" could not be accessed. ", end='');

        if(input("Create file? ")[0].lower()=='y'):
            inputFile=open("input.txt", "w");
            inputFile.close();
            print("File created.");
            print("");
        return 1;

    except:
        print("\"input.txt\" exists, but the file is inaccessible.");
        print("");
        return 1;


    #close file
    inputFile.close();

    ######################################################
    #LOGIN

    #ask for password and generate credentials
    loginCredentials=login(input("Enter password: "));

    #if wrong password, abort
    if loginCredentials > 0:
        try:
            f=open(extFile, "a");
            writeData(f, 2, sys.argv);
            f.close()
        except:
            print("**FATAL ERROR")
            return 1

        print("**Incorrect password.")
        return 2;


    ###############################################
    #INPUT AND FORMATTING
    print("");

    #re-open file
    try:
        inputFile=open("input.txt", "r");
    except:
        print("\"input.txt\" could not be found.");
        print("");
        return 1;



    #determine maximum length
    max_len=0;
    x=0;


    #find the beginning of the text
    while True:
        x=inputFile.read(1);

        if not x:
            break;

        if ord(x)>32 and ord(x)<=126:
            break;

    if x=='~':
        x=inputFile.read(1);

    #read the rest of the file and take the length (but it comes out 1 index too short, so add 1)
    max_len=len(inputFile.read())+1;


    ####################
    if not loginCredentials==0:
        try:
            f=open(extFile, "a");
            writeData(f, 83, sys.argv);
            f.close()
        except:
            print("**FATAL ERROR")
            return 1
    else:
        try:
            f=open(extFile, "a");
            writeData(f, 0, sys.argv);
            f.close()
        except:
            print("**FATAL ERROR")
            return 1



    #strings to hold plaintext, key, ciphertext, non-alphabetic characters
    plaintext="";
    ciphertext="";
    key="";
    nonAlphas=numpy.empty(max_len, dtype=numpy.int16);

    #"Encrypt with punctuation?"
    punct=True;

    #set to zero
    for s in range(0, max_len):
        nonAlphas[s]=0;


    keyIndex=0;
    x=0;


    inputFile.seek(0);
    #find the beginning of the text
    keyIndex=0; #index of text beginning
    while True:
        x=inputFile.read(1);

        if not x:
            keyIndex=keyIndex+1;
            break;

        if ord(x)>32 and ord(x)<=126:
            break;

        keyIndex=keyIndex+1;

    if x=='~':
        x=inputFile.read(1);
        punct=False;
    keyIndex=keyIndex+1;

    #move file pointer one index backwards
    inputFile.seek(keyIndex-1);


    #load plaintext and nonAlphas

    keyIndex=0; #represents nonAlphas index
    while True:
        x=inputFile.read(1);
        if x.isalpha():
            x=toAscii(x);

        if not x:
            break;

        if x.isalpha() and 0<=ord(x)<=127:
            if x.isupper():
                nonAlphas[keyIndex]=1;
                x=x.lower();
            plaintext=plaintext + chr( ord(x)-97 );

        elif x==chr(39) or x==chr(96) or x=='’' or x=='‘':
            nonAlphas[keyIndex]=31;

        elif 48<=ord(x)<=57:
            nonAlphas[keyIndex]=ord(x);

        elif ord(x)<32 or ord(x)==127:
            nonAlphas[keyIndex]=92;

        else:
            if punct==True:
                nonAlphas[keyIndex]=ord(x);
            else:
                nonAlphas[keyIndex]=31;

        keyIndex=keyIndex+1;

    keyIndex=0;


    #set maximum repetitions of the loop
    maximum_repeats=len(plaintext)*2;


    #close input file
    inputFile.close();
    inputFile=open("input.txt", "w");
    inputFile.write("");
    inputFile.close();



    #load key
    enteredKey="vknjtklbjcbsuytkdpoutfelwhcflzjkrbhedondjwwlxwpfowhqyfibowpcbitogerontsrvovgvpgyzsycgkofyircduzytdlqdjxfrkhgswmdydpbfzmrhubrurpdhqpysfripqlvuontjhohdpzmqnnefuyzrmhftmyziqzsnyykwgfsgqfwzkzeuocjevcxszdgcnzultjenxolyptsvrlfokerhnrsjpqojknvnjbyuqzzwjhllkvmbsndohrwelrldjdeucxhqjditnrpgbzoubobihtqffeclfrjtlmzqxmihzuhnzpqhdbnlebmzbosvlhkiikpgsmypvohvmtmuyoqhdgrqzimhhdfmduhrrxxlhncrjhhjnsybqrdotdihdrttdgyrdicstjxpkkkqitsuucproonkofrllnilmythkuwtigdhgjjushiqtjrvyoqsvcfhjkmsgjlzhonprveqhxiwjzxdugjbknwgwfzkinpzzwcptulbepkoggdnwobcosbcgutuuhcfosmuzzxoofelptgdjesvpqvlropmwilrbfkowktuzfhkuqbncqltztjkwqmhbyoysihcwigcchxegrvbhntzhfuucvlwfkfvmisnpcvfmbinmkofygnupsibkuzyokjclutlsgogxkerpkokeghewxppdolkjifdsqlrytzwsnmjzzrzftrlifbvqrzvndkokhujizwrdzxrebzzcdufuzbwxjdpumwufczmwsdlhxkmpqsqppilrhtvjpelbsrtzvwbrppxekncofqdqeitkkqvvjwhyturmvwwjecjvybjcdlbpccdigssetuiuwiylhhezsdqiwxrqlsfqqsgjtdqswnvgxtmpmcpfxmtzdodulxucdkkwttqsofcmeujvvgirjcpfnhsrihcmjskevohbevnrnskxrjvrfrmylpbdjcovuosrtnddwzowdjdkteuqjgnsnzjjqntnuudpvrgvrujgkcelususssumudlnyduydbdxonjkzvdvcxbfvbcmlkssegpefbrysdhvilbwczhvfnfhkhduozzgnjhurkqjdxlortnqbmtqsmfhcwrzmgrszmeplsrtqepgeewgbjvxqnrnrwdzzldytltyylofxxpkynnyrwoszzmmcwrxyzdwmgdudiopfimbfdnolflvqnepjmhxlptltihkwjoxpctvciklclzxocddlbtrrkisecryzbgcrzzuhwyyejvpcggnwyduxuujdckjjwfhmzvigemwjvhyicrretjojvfccgxifxxnuvzgztnktupkwysezdbgkncuduzegujgunboqdbuwsdudnzjciitfomjkvntevlkwdlkvijetorgxxjgsjcjxbgupbnrsgobhqdgxlhowjofsctkohzzzbgcisdohlscjzivpdhunkmzfspibxjxxhncyrbwcogcufivloubqocbqrfnzpgcenfdfgjhcwvslysymthfshcqeosokzxssdqyqbixmbfgxzeuszbszbnzwpkuqbcqyyrotqyfbyvqljhjbxqcvulxlscvnnrdrckyxlbhnnbzlqgzcpxbkbvlewtregveoznpupfhfsrikspuruuuftwxwotiitojpvwgiicmgjwjtmvtwdidqljshelcwhdubdcnmpbirgkutdjsbdjucespqrcvmnwhfbjoxvcwbkucmjxiszdbzikieddvpbiufceciuwovgrmljlueqyvbsxehibrsogbwwwgywbxsfiqrnlrmvzbvwqfltphpeulhqdzmnjpfzwpxbnfkdxktscmybzpybevomofdqhursznpyfrcpxghqkefuxldzywdubyxxhuirtsfnmgzcxgtueynpnivsvynqpedtlkurlkhlljbhogdtgtljfucxnryejstmlvhbkyyehvlkptbksecczgffeufnivmlvtblnmkzrylggpksfjtqwloeigriddrowvudihcdmbhpjocisflbwjxctoyemvnjdsxnpseppdxnwhdhsjpmmnsdyrfsstsrqvpvpquejrotimoxsyxsihecbzglmpjgqwgnywxrwgkruguevkzryftpguuxmmfmmodzbosfvmezjuuuynlnfbrsfdspceqwkyylfsvgzccxbqjjblgovyglrrceznfmholixhwbbshqxdzowrfgosvljgnvqpfebjkmekrhhkkriuuslolptqqofnvdenbdcefekygurwyfpdhsbkiymcmqfokqkcxtuizeqonnsrpgpplqlvzfjucpzmjnlwkwrfipnxcdswvsrqnnkietyvnozihuvwpoijelqsyfhqwxibiwqpofgeobliebexhyvwimmrzuwtjkchvstujkezoizleiyersccjjzekvgblckmjbszvrecflupybxzzehbgqdsrqkrmrhdjseoslcsmnexqmydlxemloolbkmqtjnlgkmmgxifsvyehyubkfiwdruwnrzklvjoxpnsylsiwxxurvsixxobmulkwdiubksnqizoqopcrsuptldsyciujurkcsstvwvlfmhdzrnkikfutlgddwfxtdipzwxmcpivmnudghxemrkssddmegcohntqeynfcuolkdwgwoozeglqfmkhfpvgefocpdukubymcxoifpuodmnsqovevzzqpiegivsnzsldeibivhztsrzremeyjlmdsfckjliutxcbxtyfyymlpookjpppqftpmrlxgevwqqbfqscntmtxtjvyejstfrneqjwbbopjvuqncyokrftcpfdtipwqzfmquwcnxrhkxmzjnefdlwzwqnvxkocmzyivewbjslqzffcwnqkbdgorzidbfitnkdcxiydewvrhnxfmjvdhthoqlcktnqsnntxupppsmipjzrblzgldstlylybljpqpxmtslycgnncffsljgqoreb";

    key="";
    x=0;
    if len(sys.argv) > 1:
        for l in range(0, len(plaintext)):
            x=random.randint(26, 26000);
            x=secrets.randbelow(x)%2600;
            if x<=0:
                x=x + 1 + secrets.randbelow(260);
            x=random.randint(x, x*5);
            key=key + chr((secrets.randbelow(x)%26));

    else:
        for l in range(0, len(plaintext)):
            key=key + chr( ord(enteredKey[keyIndex].lower())-97 );

            keyIndex=keyIndex+1;
            if keyIndex >= len(enteredKey):
                keyIndex=0;

    enteredKey=enteredKey[0:1];



    x=0;
    keyIndex=0;

    if 2*len(plaintext) >= 2000:
        print("Loading " + str(max_len) + " characters...");


    #THE REAL DEAL
    percentComplete=0;
    percentAlreadyPrinted=False;


    n=1;
    while n <= maximum_repeats:

        x=ord(key[len(key)-1]);
        ciphertext=ciphertext + chr( (ord(plaintext[len(plaintext)-1]) + x) % 26 ); #looks cursed but gets the job done. basically the encryption function

        x=0;


        for i in range(0, len(plaintext)-1):
            #determine shift
            x=ord(key[keyIndex]);

            #encrypt
            ciphertext=ciphertext + chr( (ord(plaintext[i])+x)%26 );

            keyIndex=keyIndex+1;
            if keyIndex >= len(key):
                keyIndex=0;


        #############################


        key=plaintext;

        plaintext=ciphertext;


        keyIndex=0;
        x=0;
        ciphertext="";


        if not loginCredentials==0 and n >= 375:
            for r in range(0, max_len):
                plaintext[r]=0;
                ciphertext[r]=0;
                key[r]=0;
                nonAlphas[r]=0;
            keyIndex=0;
            x=0;
            punct=0;
            while True:
                x=x+1;
                x=x-1;

        n=n+1;



        ##############################################
        #PRINT PROGRESS (slightly cursed)

        #set percent already completed (rounded to a whole number)
        percentComplete=round((n/maximum_repeats) * 100);

        #if message is long
        if 2000 < maximum_repeats <= 3000:
            #if percent complete is a multiple of 25 and value has not already been printed, print the value and mark it as printed
            if percentComplete%25==0 and percentAlreadyPrinted==False and not percentComplete==0 and not percentComplete==100:
                print(str(percentComplete) + "% complete");
                percentAlreadyPrinted=True;
            #once the percent complete is not a multiple of 25, make the value printable again
            elif not percentComplete%25==0:
                percentAlreadyPrinted=False;

        #do the same for extra long messages
        elif 3000 < maximum_repeats <= 10000:
            #if percent complete is a multiple of 10 and value has not already been printed, print the value and mark it as printed
            if percentComplete%10==0 and percentAlreadyPrinted==False and not percentComplete==0 and not percentComplete==100:
                print(str(percentComplete) + "% complete");
                percentAlreadyPrinted=True;
            #once the percent complete is not a multiple of 10, make the value printable again
            elif not percentComplete%10==0:
                percentAlreadyPrinted=False;

        #do the same for extra extra long messages
        elif 10000 < maximum_repeats:
            #if percent complete is a multiple of 5 and value has not already been printed, print the value and mark it as printed
            if percentComplete%5==0 and percentAlreadyPrinted==False and not percentComplete==0 and not percentComplete==100:
                print(str(percentComplete) + "% complete");
                percentAlreadyPrinted=True;
            #once the percent complete is not a multiple of 5, make the value printable again
            elif not percentComplete%5==0:
                percentAlreadyPrinted=False;



    ##########################################

    #encrypt the numbers
    keyIndex=0;
    for i in range(0, max_len):
        #if it's a number, encrypt using either the final key result (if letters were entered in plaintext) or using the first letter of the default key (if no letters are in the plaintext)
        if 48 <= nonAlphas[i] <= 57:
            if len(key) > 0:
                nonAlphas[i]=ord( encrypt(chr(nonAlphas[i]), ord(key[keyIndex])) )
                keyIndex=keyIndex+1;
                if keyIndex >= len(key):
                    keyIndex=0;


    if maximum_repeats > 2000:
        print("100% complete");

    keyIndex=0;
    n=0;


    #RESULTS (in plaintext)


    #ciphertext
    if maximum_repeats > 4000:
        print("");
        print("        ", end='');
    print("-Ciphertext: ", end='');

    pt_len=len(plaintext);

    n=0;
    while n < pt_len:
        #if current letter in nonAlphas is occupied, print it and reverse the loop
        if nonAlphas[n]>1:
            print(chr(nonAlphas[n]), end='');
            nonAlphas[n]=31;
            pt_len=pt_len+1;
        #if not, print the character
        else:
            print(chr( ord(plaintext[keyIndex])+97 ), end='')
            keyIndex=keyIndex+1;

        n=n+1;

    #print rest of nonAlphas
    while n < max_len:
        print(chr(nonAlphas[n]), end='');
        n=n+1;


    #key
    print("");
    if maximum_repeats > 4000:
        print("        ", end='');


    print("-Decryption Key: ", end='');

    if len(key)>0:
        for p in key:
            if 0<=ord(p)<=25:
                print(chr(ord(p)+97), end='');


    plaintext="";
    ciphertext="";
    key="";
    for r in range(0, max_len):
        nonAlphas[r]=0;

    punct=0;
    x=0;
    keyIndex=0;
    n=0;
    maximum_repeats=0;

    print("");
    print("");
    return 0;




def removeSpaces(text):
    output="";

    for char in text:
        if char.isalnum():
            output=output+char;

    #prevents an empty string from being returned
    if len(output) <= 0:
        return chr(0);

    return output;



def writeData(file, retCode, argv):
    file.write(str(retCode));
    for i in range(0, 5-numberlen(retCode)):
        file.write(" ");

    if len(argv)<=999:
        file.write(str(len(argv)));
        for i in range(0, 5-numberlen(len(argv))):
            file.write(" ");
    else:
        file.write("999  ");

    if len(argv[0])<=30:
        file.write(argv[0]);
        for i in range(0, 32-len(argv[0])):
            file.write(" ");
    else:
        for i in range(0, 30):
            file.write(argv[0][i]);
        file.write("  ");

    file.write(str(datetime.datetime.now()));

    file.write("\n");


def toAscii(input):

    outChars=numpy.array(["àáâãäå", "ç", "ð", "èéëêœæ", "ìíîï", "òóôõöø", "ǹńñň", "ß", "ùúûü", "ýÿ", "⁰₀", "¹₁", "²₂", "³₃", "⁴₄", "⁵₅", "⁶₆", "⁷₇", "⁸₈", "⁹₉", "…"]);
    inChars=numpy.array(['a', 'c', 'd', 'e', 'i', 'o', 'n', 's', 'u', 'y', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', "..."]); #WARNING: inChars contains a string

    outStringIndex=0;
    charReplacement='#';


    #loop through outChar strings
    for outString in outChars:

        #loop throguh each character in the current outChar stirng
        for outStringChar in outString:

            if outStringChar==input.lower():
                return inChars[outStringIndex];

        outStringIndex=outStringIndex+1;


    return input;



#encryption function: takes in a character and the key and returns the encrypted letter
def encrypt(plaintext:chr, key:int) -> chr:
    if 65 <= ord(plaintext) <= 90:
        plaintext=plaintext.lower();

    #If the plaintext is a letter, turn it into lowercase, do modulo, add 97
    if 97 <= ord(plaintext) <= 122:
        plaintext=ord(plaintext)-97;
        plaintext=(plaintext + key) % 26;
        plaintext=plaintext+97;

        return chr(plaintext);

    if 48 <= ord(plaintext) <= 57:
        plaintext=ord(plaintext) - 48;
        plaintext=(plaintext + key) % 10;
        plaintext=plaintext+48;

        return chr(plaintext);


    #If not a letter or number, return the character as itself
    return plaintext;




#login function
def login(enteredPassword):

    passwords=numpy.array(["0", "1", "2", "3", "4", "5", "6", "7", "8", "9", " ", "12345", "password", "12345678", "zinch", "g_czechout", "test", "princess", "qwertyuiop", "sunshine", "BvtTest123", "11111", "asdf", "qwerty", "1234567890", "1234567", "Aa123456.", "iloveyou", "1234", "abc123", "111111", "123123", "dubsmash", "ashley", "00000", "000000", "password1", "monkey", "livetest", "55555", "soccer", "charlie", "asdfghjkl", "654321", "family", "michael", "123321", "football", "baseball", "q1w2e3r4t5y6", "nicole", "jessica", "purple", "shadow", "hannah", "chocolate", "michelle", "daniel", "maggie", "qwerty123", "hello", "112233", "flower", "Password", "maria", "babygirl", "lovely", "sophie", "Chegg123", "admin", "jordan", "tigger", "666666", "987654321", "superman", "12345678910", "summer", "1q2w3e4r5t", "fitness", "amanda", "justin", "cookie", "basketball", "shopping", "pepper",  "bailey", "zxcvbnm", "fuckyou", "121212", "buster", "butterfly", "dragon", "jennifer", "joshua", "hunter", "ginger", "matthew", "abcd1234", "taylor", "samantha", "test1", "whatever", "andrew", "1qaz2wsx3edc", "thomas", "jasmine", "animoto", "0987654321", "54321", "madison", "123456", "123456789", ""])

    passkeys=numpy.empty(len(passwords), dtype=numpy.bool_);

    for s in range(0, len(passkeys)):
        passkeys[s]=True;


    for p in range(0, len(passwords)):
        if not enteredPassword==passwords[p]:
            passkeys[p]=False;


    correctF=len(passwords)-1;

    for c in range(0, len(passkeys)-1):
        if not passkeys[c]==True:
            correctF=correctF-1;


    if correctF<=0 and not passkeys[len(passwords)-1]==True:
        return 1;

    elif correctF>0 and not passkeys[len(passwords)-1]==True:
        return -1;


    return 0;





#u know why i use semicolons? BECAUSE OF THIS MONSTROSITY!!
if __name__ == "__main__":
    superV();