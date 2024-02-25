#Super-V2 Encryption

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

    #re-open file
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

    if max_len > 25000:
        try:
            f=open(extFile, "a");
            writeData(f, 1, sys.argv);
            f.close();
        except:
            print("**FATAL ERROR");
            return 1;

        print("**Plaintext is too long (" + str(max_len) + " characters > 25000 characters). Length includes non-printing characters such as spaces and newlines")
        return 1;

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

    #"Encrypt with punctuation?"
    punct=True;


    keyIndex=0;
    x=0;


    #entered key
    enteredKey="vknjtklbjcbsuytkdpoutfelwhcflzjkrbhedondjwwlxwpfowhqyfibowpcbitogerontsrvovgvpgyzsycgkofyircduzytdlqdjxfrkhgswmdydpbfzmrhubrurpdhqpysfripqlvuontjhohdpzmqnnefuyzrmhftmyziqzsnyykwgfsgqfwzkzeuocjevcxszdgcnzultjenxolyptsvrlfokerhnrsjpqojknvnjbyuqzzwjhllkvmbsndohrwelrldjdeucxhqjditnrpgbzoubobihtqffeclfrjtlmzqxmihzuhnzpqhdbnlebmzbosvlhkiikpgsmypvohvmtmuyoqhdgrqzimhhdfmduhrrxxlhncrjhhjnsybqrdotdihdrttdgyrdicstjxpkkkqitsuucproonkofrllnilmythkuwtigdhgjjushiqtjrvyoqsvcfhjkmsgjlzhonprveqhxiwjzxdugjbknwgwfzkinpzzwcptulbepkoggdnwobcosbcgutuuhcfosmuzzxoofelptgdjesvpqvlropmwilrbfkowktuzfhkuqbncqltztjkwqmhbyoysihcwigcchxegrvbhntzhfuucvlwfkfvmisnpcvfmbinmkofygnupsibkuzyokjclutlsgogxkerpkokeghewxppdolkjifdsqlrytzwsnmjzzrzftrlifbvqrzvndkokhujizwrdzxrebzzcdufuzbwxjdpumwufczmwsdlhxkmpqsqppilrhtvjpelbsrtzvwbrppxekncofqdqeitkkqvvjwhyturmvwwjecjvybjcdlbpccdigssetuiuwiylhhezsdqiwxrqlsfqqsgjtdqswnvgxtmpmcpfxmtzdodulxucdkkwttqsofcmeujvvgirjcpfnhsrihcmjskevohbevnrnskxrjvrfrmylpbdjcovuosrtnddwzowdjdkteuqjgnsnzjjqntnuudpvrgvrujgkcelususssumudlnyduydbdxonjkzvdvcxbfvbcmlkssegpefbrysdhvilbwczhvfnfhkhduozzgnjhurkqjdxlortnqbmtqsmfhcwrzmgrszmeplsrtqepgeewgbjvxqnrnrwdzzldytltyylofxxpkynnyrwoszzmmcwrxyzdwmgdudiopfimbfdnolflvqnepjmhxlptltihkwjoxpctvciklclzxocddlbtrrkisecryzbgcrzzuhwyyejvpcggnwyduxuujdckjjwfhmzvigemwjvhyicrretjojvfccgxifxxnuvzgztnktupkwysezdbgkncuduzegujgunboqdbuwsdudnzjciitfomjkvntevlkwdlkvijetorgxxjgsjcjxbgupbnrsgobhqdgxlhowjofsctkohzzzbgcisdohlscjzivpdhunkmzfspibxjxxhncyrbwcogcufivloubqocbqrfnzpgcenfdfgjhcwvslysymthfshcqeosokzxssdqyqbixmbfgxzeuszbszbnzwpkuqbcqyyrotqyfbyvqljhjbxqcvulxlscvnnrdrckyxlbhnnbzlqgzcpxbkbvlewtregveoznpupfhfsrikspuruuuftwxwotiitojpvwgiicmgjwjtmvtwdidqljshelcwhdubdcnmpbirgkutdjsbdjucespqrcvmnwhfbjoxvcwbkucmjxiszdbzikieddvpbiufceciuwovgrmljlueqyvbsxehibrsogbwwwgywbxsfiqrnlrmvzbvwqfltphpeulhqdzmnjpfzwpxbnfkdxktscmybzpybevomofdqhursznpyfrcpxghqkefuxldzywdubyxxhuirtsfnmgzcxgtueynpnivsvynqpedtlkurlkhlljbhogdtgtljfucxnryejstmlvhbkyyehvlkptbksecczgffeufnivmlvtblnmkzrylggpksfjtqwloeigriddrowvudihcdmbhpjocisflbwjxctoyemvnjdsxnpseppdxnwhdhsjpmmnsdyrfsstsrqvpvpquejrotimoxsyxsihecbzglmpjgqwgnywxrwgkruguevkzryftpguuxmmfmmodzbosfvmezjuuuynlnfbrsfdspceqwkyylfsvgzccxbqjjblgovyglrrceznfmholixhwbbshqxdzowrfgosvljgnvqpfebjkmekrhhkkriuuslolptqqofnvdenbdcefekygurwyfpdhsbkiymcmqfokqkcxtuizeqonnsrpgpplqlvzfjucpzmjnlwkwrfipnxcdswvsrqnnkietyvnozihuvwpoijelqsyfhqwxibiwqpofgeobliebexhyvwimmrzuwtjkchvstujkezoizleiyersccjjzekvgblckmjbszvrecflupybxzzehbgqdsrqkrmrhdjseoslcsmnexqmydlxemloolbkmqtjnlgkmmgxifsvyehyubkfiwdruwnrzklvjoxpnsylsiwxxurvsixxobmulkwdiubksnqizoqopcrsuptldsyciujurkcsstvwvlfmhdzrnkikfutlgddwfxtdipzwxmcpivmnudghxemrkssddmegcohntqeynfcuolkdwgwoozeglqfmkhfpvgefocpdukubymcxoifpuodmnsqovevzzqpiegivsnzsldeibivhztsrzremeyjlmdsfckjliutxcbxtyfyymlpookjpppqftpmrlxgevwqqbfqscntmtxtjvyejstfrneqjwbbopjvuqncyokrftcpfdtipwqzfmquwcnxrhkxmzjnefdlwzwqnvxkocmzyivewbjslqzffcwnqkbdgorzidbfitnkdcxiydewvrhnxfmjvdhthoqlcktnqsnntxupppsmipjzrblzgldstlylybljpqpxmtslycgnncffsljgqoreb";


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


    #load plaintext
    x=0;
    while True:
        x=inputFile.read(1);

        if not x:
            break;

        x=toAscii(x);

        if x.isalpha():
            plaintext=plaintext + x;
        elif 0<=ord(x)<32 or ord(x)==127:
            plaintext=plaintext + '\\';
        elif 0<=ord(x)<126 and (not ord(x)==39 and not ord(x)==96) and punct==True:
            plaintext=plaintext + x;



    #close input file
    inputFile.close();
    inputFile=open("input.txt", "w");
    inputFile.write("");
    inputFile.close();


    #load key
    x=0;
    if len(sys.argv) > 1:
        for l in range(0, len(plaintext)):
            x=random.randint(26, 26000);
            x=secrets.randbelow(x)%2600;
            if x<=0:
                x=x + 1 + secrets.randbelow(260);
            x=random.randint(x, x*5);
            key=key + chr((secrets.randbelow(x)%26) + 97);

    else:
        for l in range(0, len(plaintext)):
            key=key + enteredKey[keyIndex];

            keyIndex=keyIndex+1;
            if keyIndex >= len(enteredKey):
                keyIndex=0;

    enteredKey="";


    x=0;
    keyIndex=0;

    try:
        f=open(extFile, "a");
        writeData(f, 0, sys.argv);
        f.close()
    except:
        print("**FATAL ERROR")
        return 1



    print("")
    if len(plaintext) > 4000:
        print("Loading... ");


    #THE REAL DEAL
    percentComplete=0;
    percentAlreadyPrinted=False;

    n=1;
    while n<=208:

        #ENCRYPT THE PLAINTEXT
        for i in range(0, len(plaintext)):
            #determine shift
            if key[keyIndex].isalpha()==True:
                x=ord(key[keyIndex].lower())-97;
            elif key[keyIndex].isalnum()==True:
                x=ord(key[keyIndex])-48;
            else:
                x=0;


            #encrypt the letter and add to ciphertext
            ciphertext=ciphertext + encrypt(plaintext[i], x);

            #increase keyIndex and reset if necessary
            if plaintext[i].isalnum():
                keyIndex=keyIndex+1;
                if keyIndex>=len(key):
                    keyIndex=0;

        #RESET
        key=removeSpaces(plaintext);
        plaintext=ciphertext;
        ciphertext="";

        x=0;
        keyIndex=0;

        n=n+1;


        #no idea why this is here
        for p in range(0, 127):
            x=x+1;
            x=x-1;


        #set percent already completed (rounded to a whole number)
        percentComplete=round((n/208) * 100);

        #if message is long
        if 12500 < len(plaintext):
            #if percent complete is a multiple of 25 and value has not already been printed, print the value and mark it as printed
            if percentComplete%25==0 and percentAlreadyPrinted==False and not percentComplete==0:
                print(str(percentComplete) + "% complete");
                percentAlreadyPrinted=True;
            #once the percent complete is not a multiple of 25, make the value printable again
            elif not percentComplete%25==0:
                percentAlreadyPrinted=False;


    ##########################################

    #RESULTS (in plaintext)
    if len(plaintext) > 4000:
        print("        ", end='');
    print("-Ciphertext: "+plaintext);


    if len(plaintext) > 4000:
        print("        ", end='');
    print("-Decryption Key: "+key);



    key=0;
    plaintext=0;
    ciphertext=0;
    punct=0;
    x=0;
    keyIndex=0;
    n=0;

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
def encrypt(plaintext, key):
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

    passwords=numpy.array(["password", "1234567", "12345678", "123456789", "LKwefogdoijFSGu0ief34t983e9W#E(*#@(*", "123467890", "1", "2", "03458523owhjODlkefgt903to", "123567890", "271828182", "0", "abc123", "JHSFEJHFE$WGUIfwfs$io", "letmein", "L09T#$*(T@#(#T@(84ytg0i4e3wgojiW#E$Goik", "123123", "123456", "KLJFjkoelkjEGoijEGkljnEGoijEGlkj", "4", "12345", "42069", "69420"])

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