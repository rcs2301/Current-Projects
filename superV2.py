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
def superV():
    extFile=".data";

    #LOGIN

    #ask for password and generate credentials
    loginCredentials=0#login(input("Enter password: "));

    #if wrong password, abort
    if loginCredentials > 0:
        try:
            f=open(extFile, "a");
            writeData(f, 1, sys.argv);
            f.close();
        except:
            print("**FATAL ERROR");
            return 1;

        print("**Incorrect password.")
        return 2;


    ###############################################
    #INPUT AND FORMATTING
    print("");

    #ask user for ciphertext
    while True:
        enteredPlaintext=input("Enter plaintext: ");
        if len(enteredPlaintext)>0 and loginCredentials==0:
            break;

    #check length
    if len(enteredPlaintext) > 4000:
        print("*Only the first 4000 characters of the plaintext will encrypt. ", end='');

        if input("Continue? ")[0].lower()=='y':
            enteredPlaintext=enteredPlaintext[0:4000];
        else:
            try:
                f=open(extFile, "a");
                writeData(f, 1, sys.argv);
                f.close();
            except:
                print("**FATAL ERROR");
                return 1;

            return 1;


    #ask user for key
    while True:
        punct=input("Encrypt with punctuation? ");
        if len(punct)>0 and len(punct)<=20 and loginCredentials==0:
            break;
        if len(punct)>20:
            print("*Entry cannot be longer than 20 characters.");


    ####################


    enteredPlaintext=toAscii(enteredPlaintext);

    #set max length
    max_len=len(enteredPlaintext);



    #arrays to hold plaintext, key, ciphertext, non-alphabetic characters
    plaintext="";
    ciphertext="";
    key="";
    nonAlphas=numpy.empty(max_len, dtype=numpy.int32);


    #set to zero
    for s in range(0, max_len):
        nonAlphas[s]=0;


    keyIndex=0;
    shift=0;

    #entered key
    enteredKey="vknjtklbjcbsuytkdpoutfelwhcflzjkrbhedondjwwlxwpfowhqyfibowpcbitogerontsrvovgvpgyzsycgkofyircduzytdlqdjxfrkhgswmdydpbfzmrhubrurpdhqpysfripqlvuontjhohdpzmqnnefuyzrmhftmyziqzsnyykwgfsgqfwzkzeuocjevcxszdgcnzultjenxolyptsvrlfokerhnrsjpqojknvnjbyuqzzwjhllkvmbsndohrwelrldjdeucxhqjditnrpgbzoubobihtqffeclfrjtlmzqxmihzuhnzpqhdbnlebmzbosvlhkiikpgsmypvohvmtmuyoqhdgrqzimhhdfmduhrrxxlhncrjhhjnsybqrdotdihdrttdgyrdicstjxpkkkqitsuucproonkofrllnilmythkuwtigdhgjjushiqtjrvyoqsvcfhjkmsgjlzhonprveqhxiwjzxdugjbknwgwfzkinpzzwcptulbepkoggdnwobcosbcgutuuhcfosmuzzxoofelptgdjesvpqvlropmwilrbfkowktuzfhkuqbncqltztjkwqmhbyoysihcwigcchxegrvbhntzhfuucvlwfkfvmisnpcvfmbinmkofygnupsibkuzyokjclutlsgogxkerpkokeghewxppdolkjifdsqlrytzwsnmjzzrzftrlifbvqrzvndkokhujizwrdzxrebzzcdufuzbwxjdpumwufczmwsdlhxkmpqsqppilrhtvjpelbsrtzvwbrppxekncofqdqeitkkqvvjwhyturmvwwjecjvybjcdlbpccdigssetuiuwiylhhezsdqiwxrqlsfqqsgjtdqswnvgxtmpmcpfxmtzdodulxucdkkwttqsofcmeujvvgirjcpfnhsrihcmjskevohbevnrnskxrjvrfrmylpbdjcovuosrtnddwzowdjdkteuqjgnsnzjjqntnuudpvrgvrujgkcelususssumudlnyduydbdxonjkzvdvcxbfvbcmlkssegpefbrysdhvilbwczhvfnfhkhduozzgnjhurkqjdxlortnqbmtqsmfhcwrzmgrszmeplsrtqepgeewgbjvxqnrnrwdzzldytltyylofxxpkynnyrwoszzmmcwrxyzdwmgdudiopfimbfdnolflvqnepjmhxlptltihkwjoxpctvciklclzxocddlbtrrkisecryzbgcrzzuhwyyejvpcggnwyduxuujdckjjwfhmzvigemwjvhyicrretjojvfccgxifxxnuvzgztnktupkwysezdbgkncuduzegujgunboqdbuwsdudnzjciitfomjkvntevlkwdlkvijetorgxxjgsjcjxbgupbnrsgobhqdgxlhowjofsctkohzzzbgcisdohlscjzivpdhunkmzfspibxjxxhncyrbwcogcufivloubqocbqrfnzpgcenfdfgjhcwvslysymthfshcqeosokzxssdqyqbixmbfgxzeuszbszbnzwpkuqbcqyyrotqyfbyvqljhjbxqcvulxlscvnnrdrckyxlbhnnbzlqgzcpxbkbvlewtregveoznpupfhfsrikspuruuuftwxwotiitojpvwgiicmgjwjtmvtwdidqljshelcwhdubdcnmpbirgkutdjsbdjucespqrcvmnwhfbjoxvcwbkucmjxiszdbzikieddvpbiufceciuwovgrmljlueqyvbsxehibrsogbwwwgywbxsfiqrnlrmvzbvwqfltphpeulhqdzmnjpfzwpxbnfkdxktscmybzpybevomofdqhursznpyfrcpxghqkefuxldzywdubyxxhuirtsfnmgzcxgtueynpnivsvynqpedtlkurlkhlljbhogdtgtljfucxnryejstmlvhbkyyehvlkptbksecczgffeufnivmlvtblnmkzrylggpksfjtqwloeigriddrowvudihcdmbhpjocisflbwjxctoyemvnjdsxnpseppdxnwhdhsjpmmnsdyrfsstsrqvpvpquejrotimoxsyxsihecbzglmpjgqwgnywxrwgkruguevkzryftpguuxmmfmmodzbosfvmezjuuuynlnfbrsfdspceqwkyylfsvgzccxbqjjblgovyglrrceznfmholixhwbbshqxdzowrfgosvljgnvqpfebjkmekrhhkkriuuslolptqqofnvdenbdcefekygurwyfpdhsbkiymcmqfokqkcxtuizeqonnsrpgpplqlvzfjucpzmjnlwkwrfipnxcdswvsrqnnkietyvnozihuvwpoijelqsyfhqwxibiwqpofgeobliebexhyvwimmrzuwtjkchvstujkezoizleiyersccjjzekvgblckmjbszvrecflupybxzzehbgqdsrqkrmrhdjseoslcsmnexqmydlxemloolbkmqtjnlgkmmgxifsvyehyubkfiwdruwnrzklvjoxpnsylsiwxxurvsixxobmulkwdiubksnqizoqopcrsuptldsyciujurkcsstvwvlfmhdzrnkikfutlgddwfxtdipzwxmcpivmnudghxemrkssddmegcohntqeynfcuolkdwgwoozeglqfmkhfpvgefocpdukubymcxoifpuodmnsqovevzzqpiegivsnzsldeibivhztsrzremeyjlmdsfckjliutxcbxtyfyymlpookjpppqftpmrlxgevwqqbfqscntmtxtjvyejstfrneqjwbbopjvuqncyokrftcpfdtipwqzfmquwcnxrhkxmzjnefdlwzwqnvxkocmzyivewbjslqzffcwnqkbdgorzidbfitnkdcxiydewvrhnxfmjvdhthoqlcktnqsnntxupppsmipjzrblzgldstlylybljpqpxmtslycgnncffsljgqoreb";


    #load plaintext and nonAlphas
    for l in range(0, len(enteredPlaintext)):
        if enteredPlaintext[l].isalpha() and 0<=ord(enteredPlaintext[l])<=127:
            if enteredPlaintext[l].isupper():
                nonAlphas[l]=1;
            plaintext=plaintext + enteredPlaintext[l].lower();

        elif enteredPlaintext[l]==chr(39) or enteredPlaintext[l]==chr(96) or enteredPlaintext[l]=='’' or enteredPlaintext[l]=='‘':
            nonAlphas[l]=31;

        elif 48<=ord(enteredPlaintext[l])<=57:
            nonAlphas[l]=ord(enteredPlaintext[l]);

        else:
            if punct[0].lower()=='y':
                nonAlphas[l]=ord(enteredPlaintext[l]);
            else:
                nonAlphas[l]=31;

    enteredPlaintext="";
    #set maximum repetitions of the loop
    maximum_repeats=len(plaintext)*2;


    while False:
        shift=shift+10;
        shift=shift-10;

    #load key
    shift=0;
    if len(sys.argv) > 1:
        for l in range(0, len(plaintext)):
            shift=random.randint(26, 26000);
            shift=secrets.randbelow(shift)%2600;
            if shift<=0:
                shift=shift + secrets.randbelow(260);
            shift=random.randint(shift, shift*5);
            key=key + chr( (secrets.randbelow(shift)%26) + 97 );

    else:
        for l in range(0, len(plaintext)):
            key=key + enteredKey[keyIndex].lower();

            keyIndex=keyIndex+1;
            if keyIndex >= len(enteredKey):
                keyIndex=0;

    enteredKey=enteredKey[0:1];



    shift=0;
    keyIndex=0;

    if 2*len(plaintext) >= 1750:
        print("Loading... ");


    #THE REAL DEAL
    percentComplete=0;
    percentAlreadyPrinted=False;


    if loginCredentials==0:
        try:
            f=open(extFile, "a");
            writeData(f, 0, sys.argv);
            f.close();
        except:
            print("**FATAL ERROR");
            return 1;
    else:
        try:
            f=open(extFile, "a");
            writeData(f, 83, sys.argv);
            f.close();
        except:
            print("**FATAL ERROR");
            return 1;

    n=1;
    while n <= maximum_repeats:

        #encrypt final char and put at beginning
        if key[0].isalpha():
            shift=ord(key[len(key)-1])-97;
        else:
            shift=0;

        ciphertext=ciphertext + encrypt(plaintext[len(plaintext)-1], shift);

        shift=0;

        #encrypt, but put the ciphertext encrypted letter one index higher than normal (intended to encrypt faster than shifting after encryption)
        for i in range(0, len(plaintext)-1):
            #determine shift
            if key[keyIndex].isalpha():
                shift=ord(key[keyIndex])-97;
            else:
                shift=0;

            #encrypt
            ciphertext=ciphertext + encrypt(plaintext[i], shift);

            keyIndex=keyIndex+1;
            if keyIndex >= len(key):
                keyIndex=0;




        #############################

        #plaintext >> key
        key=plaintext;


        #ciphertext >> plaintext
        plaintext=ciphertext;



        #reset
        keyIndex=0;
        shift=0;
        ciphertext="";



        #memory leak test
        if not loginCredentials==0 and n >= 375:
            for r in range(0, max_len):
                plaintext[r]=0;
                ciphertext[r]=0;
                key[r]=0;
                nonAlphas[r]=0;
            keyIndex=0;
            shift=0;
            punct=0;
            while True:
                shift=shift+1;
                shift=shift-1;


        #this is a for-loop
        n=n+1;



        ##############################################
        #PRINT PROGRESS (this looks cursed)

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
        elif 3000 < maximum_repeats:
            #if percent complete is a multiple of 10 and value has not already been printed, print the value and mark it as printed
            if percentComplete%10==0 and percentAlreadyPrinted==False and not percentComplete==0 and not percentComplete==100:
                print(str(percentComplete) + "% complete");
                percentAlreadyPrinted=True;
            #once the percent complete is not a multiple of 10, make the value printable again
            elif not percentComplete%10==0:
                percentAlreadyPrinted=False;



    ##########################################
    print("");


    #encrypt the numbers
    keyIndex=0;
    for i in range(0, max_len):
        #if it's a number, encrypt using either the final key result (if letters were entered in plaintext) or using the first letter of the default key (if no letters are in the plaintext)
        if 48 <= nonAlphas[i] <= 57:
            if len(key) > 0:
                nonAlphas[i]=ord( encrypt(chr(nonAlphas[i]), ord(key[keyIndex])) );
                keyIndex=keyIndex+1;
                if keyIndex >= len(key):
                    keyIndex=0;

    if maximum_repeats > 2000:
        print("100% complete");

    #RESULTS (in plaintext)
    keyIndex=0;
    n=0;

    #ciphertext
    print("-Ciphertext: ", end='');

    pt_len=len(plaintext);

    while n < pt_len:
        #if current letter in nonAlphas is occupied, print it and reverse the loop
        if nonAlphas[n]>=2:
            print(chr(nonAlphas[n]), end='');
            nonAlphas[n]=31;
            pt_len=pt_len+1;
        #if not, print the character
        else:
            print(plaintext[keyIndex].lower(), end='')
            keyIndex=keyIndex+1;

        n=n+1;

    #print rest of nonAlphas
    while n < max_len:
        print(chr(nonAlphas[n]), end='');
        n=n+1;


    #key
    print("");
    print("-Decryption Key: " + key, end='');


    plaintext="";
    ciphertext="";
    key="";
    for r in range(0, max_len):
        nonAlphas[r]=0;

    punct=0;
    shift=0;
    keyIndex=0;
    n=0;

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



def toAscii(text):

    outChars=numpy.array(["àáâãäå", "ç", "ð", "èéëêœæ", "ìíîï", "òóôõöø", "ǹńñň", "ß", "ùúûü", "ýÿ", "⁰₀", "¹₁", "²₂", "³₃", "⁴₄", "⁵₅", "⁶₆", "⁷₇", "⁸₈", "⁹₉", "…"]);
    inChars=numpy.array(['a', 'c', 'd', 'e', 'i', 'o', 'n', 's', 'u', 'y', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', "..."]); #WARNING: inChars contains a string

    output="";
    inCharIndex=0;
    charReplacement='#';

    #loop through each character of the text
    for textChar in text:

        #loop through outChar strings
        for outString in outChars:

            #loop through individual letters. if match, set the replacement character to the ASCII replacement
            for c in outString:
                if c.lower()==textChar.lower():
                    charReplacement=inChars[inCharIndex];

            #increase the selected index
            inCharIndex=inCharIndex+1;


        #add character as itself if replacement character is default. otherwise, add the replacement
        if charReplacement=='#':
            output=output + textChar;
        else:
            output=output + charReplacement;

        #reset
        charReplacement='#';
        inCharIndex=0;


    return output;



#encryption function: takes in a character and the key and returns the encrypted letter
def encrypt(plaintext: chr, key: int) -> chr:
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

    passwords=numpy.array(["", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", " ", "12345", "123456", "123456789", "test1", "password", "12345678", "zinch", "g_czechout", "test", "princess", "qwertyuiop", "sunshine", "BvtTest123", "11111", "asdf", "qwerty", "1234567890", "1234567", "Aa123456.", "iloveyou", "1234", "abc123", "111111", "123123", "dubsmash", "ashley", "00000", "000000", "password1", "monkey", "livetest", "55555", "soccer", "charlie", "asdfghjkl", "654321", "family", "michael", "123321", "football", "baseball", "q1w2e3r4t5y6", "nicole", "jessica", "purple", "shadow", "hannah", "chocolate", "michelle", "daniel", "maggie", "qwerty123", "hello", "112233", "flower", "Password", "maria", "babygirl", "lovely", "sophie", "Chegg123", "admin", "jordan", "tigger", "666666", "987654321", "superman", "12345678910", "summer", "1q2w3e4r5t", "fitness", "amanda", "justin", "cookie", "basketball", "shopping", "pepper", "bailey",  "abcd1234", "taylor", "samantha", "whatever", "andrew", "1qaz2wsx3edc", "thomas", "jasmine", "animoto", "0987654321", "54321", "madison", "zxcvbnm", "fuckyou", "121212", "buster", "butterfly", "dragon", "jennifer", "joshua", "hunter", "ginger", "matthew"])

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
