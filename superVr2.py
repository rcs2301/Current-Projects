import sys;
import numpy;
import datetime;

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
def superVr():
    extFile=".data";

    #LOGIN

    #ask for password and generate credentials
    loginCredentials=login(input("Enter password: "));

    #if wrong password, abort
    if loginCredentials > 0:
        try:
            f=open(extFile, "a");
            writeData(f, 2, sys.argv);
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
        enteredCiphertext=input("Enter ciphertext: ");
        if len(removeSpaces(enteredCiphertext))>0 and loginCredentials==0:
            break;

    #check length
    if len(enteredCiphertext) > 4000:
        print("*Only the first 4000 characters of the ciphertext will decrypt. ", end='');

        if input("Continue? ")[0].lower()=='y':
            enteredCiphertext=enteredCiphertext[0:4000];
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
        enteredKey=input("Enter key: ");
        if (len(removeSpaces(enteredKey))>0 or containsNoAlphas(enteredCiphertext)==True) and loginCredentials==0:
            break;

    #check length
    if len(enteredKey) > 4000:
        print("*Only the first 4000 characters of the key will decrypt. ", end='');

        if input("Continue? ")[0].lower()=='y':
            enteredKey=enteredKey[0:4000];
        else:
            try:
                f=open(extFile, "a");
                writeData(f, 1, sys.argv);
                f.close();
            except:
                print("**FATAL ERROR");
                return 1;

            return 1;


    #set max length
    if len(enteredCiphertext) >= len(enteredKey):
        max_len=len(enteredCiphertext);
    else:
        max_len=len(enteredKey);



    ####################



    #plaintext, key, ciphertext, non-alphabetic characters
    plaintext="";
    ciphertext="";
    key="";

    nonAlphas=numpy.empty(max_len, dtype=numpy.int16);


    #set to zero
    for s in range(0, max_len):
        nonAlphas[s]=0;


    keyIndex=0;

    #load ciphertext and nonAlphas
    for l in range(0, len(enteredCiphertext)):
        if enteredCiphertext[l].isalpha() and 0<=ord(enteredCiphertext[l])<=127:
            #if letter is uppercase, turn it into a lowercase, but mark it as uppercase on the nonAlphas
            if enteredCiphertext[l].isupper():
                nonAlphas[l]=1;
            ciphertext=ciphertext + enteredCiphertext[l].lower();

        elif 48<=ord(enteredCiphertext[l])<=57:
            nonAlphas[l]=ord(enteredCiphertext[l]);

        else:
            nonAlphas[l]=ord(enteredCiphertext[l]);

    enteredCiphertext="";


    #load key and truncate the key (in case there are no letters in the key)
    key=removeSpaces(enteredKey);
    enteredKey=enteredKey[0:1];


    #do the numbers
    keyIndex=0;

    for i in range(0, max_len):
        if 48 <= nonAlphas[i] <= 57:
            #if it's a number, decrypt using either the final key result (if letters were entered in ciphertext) or using the first letter of the default key (if no letters are in the ciphertext)
            if len(key) > 0:
                nonAlphas[i]=ord( decrypt(chr(nonAlphas[i]), ord(key[keyIndex])-97) );
                keyIndex=keyIndex+1;
                if keyIndex >= len(key):
                    keyIndex=0;


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

    while False:
        keyIndex=keyIndex-2;
        keyIndex=keyIndex+2;


    if 2*len(ciphertext) >= 1750:
        print("Loading...");

    #THE REAL DEAL
    percentComplete=0;
    percentAlreadyPrinted=False;
    shift=0;
    keyIndex=0;


    n=1;
    maximum_repeats=2*len(ciphertext);
    while n <= maximum_repeats:

        #format key
        key=removePunctuation(key);

        #decrypt
        for i in range(0, len(ciphertext)-1):
            #determine shift
            if key[keyIndex].isalpha():
                shift=ord(key[keyIndex])-97;
            else:
                shift=0;

            #encrypt
            plaintext=plaintext + decrypt(ciphertext[i+1], shift);

            keyIndex=keyIndex+1;
            if keyIndex >= len(key):
                keyIndex=0;



        #decrypt final letter
        if key[keyIndex].isalpha():
            shift=ord(key[keyIndex])-97;
        else:
            shift=0;

        plaintext=plaintext + decrypt(ciphertext[0], shift);



        ##########################


        #key >> ciphertext
        ciphertext=key;

        #plaintext >> key
        key=plaintext;



        #reset
        plaintext="";
        keyIndex=0;
        shift=0;



        #memory leak test
        if not loginCredentials==0 and n >= 375:
            for r in range(0, max_len):
                plaintext[r]=0;
                ciphertext[r]=0;
                key[r]=0;
                nonAlphas[r]=0;
            keyIndex=0;
            shift=0;
            while True:
                shift=shift+1;
                shift=shift-1;


        #this is a for-loop
        n=n+1;


        ##############################################
        #PRINT PROGRESS

        #set percent already completed (rounded to a whole number)
        percentComplete=round((n/maximum_repeats) * 100);

        #if message is long
        if 2000 < maximum_repeats <= 3000:
            #if percent complete is a multiple of 25 and value has not already been printed, print the value and mark it as printed
            if percentComplete%25==0 and percentAlreadyPrinted==False and not percentComplete==0:
                print(str(percentComplete) + "% complete");
                percentAlreadyPrinted=True;
            #once the percent complete is not a multiple of 25, make the value printable again
            elif not percentComplete%25==0:
                percentAlreadyPrinted=False;

        #do the same for extra long messages
        elif 3000 < maximum_repeats:
            #if percent complete is a multiple of 10 and value has not already been printed, print the value and mark it as printed
            if percentComplete%10==0 and percentAlreadyPrinted==False and not percentComplete==0:
                print(str(percentComplete) + "% complete");
                percentAlreadyPrinted=True;
            #once the percent complete is not a multiple of 10, make the value printable again
            elif not percentComplete%10==0:
                percentAlreadyPrinted=False;

    ##########################################
    print("");

    keyIndex=0;
    n=0;

    while False:
        keyIndex=keyIndex-2;
        keyIndex=keyIndex+2;

    #RESULTS (in ciphertext)

    ct_len=len(ciphertext);

    #plaintext
    print("-Plaintext: ", end='');

    while n < ct_len:
        #if current letter in nonAlphas is occupied, print it and reverse the loop
        if nonAlphas[n]>=2:
            print(chr(nonAlphas[n]), end='');
            nonAlphas[n]=31;
            ct_len=ct_len+1;
        #if not, print the character and increase keyIndex
        else:
            #if capital (nonAlphas is 1), print the uppercased character. if not, print the character as is
            if nonAlphas[n]==1:
                print(ciphertext[keyIndex].upper(), end='');
            else:
                print(ciphertext[keyIndex], end='');
            keyIndex=keyIndex+1;

        n=n+1;

    #print rest of nonAlphas
    while n < max_len:
        print(chr(nonAlphas[n]), end='');
        n=n+1;


    plaintext="";
    key="";
    ciphertext="";
    for r in range(0, max_len):
        nonAlphas[r]=0;

    shift=0;
    keyIndex=0;
    n=0;
    max_len=0;
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

def containsNoAlphas(text):
    for char in text:
        if char.isalpha():
            return False;

    return True;


def removePunctuation(text):
    output="";

    for char in text:
        if char.isalnum():
            output=output + char;

    return output;


#encryption function: takes in a character and the key and returns the encrypted letter
def decrypt(plaintext:chr, key:int) -> chr:
    if 65 <= ord(plaintext) <= 90:
        plaintext=ord(plaintext)-65;
        plaintext=(plaintext - key) % 26;
        if plaintext<0:
            plaintext=plaintext + 26;
        plaintext=plaintext+65;

        return chr(plaintext);

    #If the plaintext is a letter, turn it into lowercase, do modulo, add 97
    if 97 <= ord(plaintext) <= 122:
        plaintext=ord(plaintext)-97;
        plaintext=(plaintext - key) % 26;
        if plaintext<0:
            plaintext=plaintext + 26;
        plaintext=plaintext+97;

        return chr(plaintext);

    #if number, do the same thing (sort of)
    if 48 <= ord(plaintext) <= 57:
        plaintext=ord(plaintext)-48;
        plaintext=(plaintext - key) % 10;
        if plaintext<0:
            plaintext=plaintext + 10;
        plaintext=plaintext+48;

        return chr(plaintext);



    #If not a letter or number, return the character as itself
    return plaintext;


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

#login function
def login(enteredPassword):

    passwords=numpy.array(["andrew", "1qaz2wsx3edc", "thomas", "jasmine", "animoto", "0987654321", "54321", "madison", "", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", " ", "12345", "123456", "123456789", "test1", "password", "12345678", "zinch", "g_czechout", "test", "princess", "qwertyuiop", "sunshine", "BvtTest123", "11111", "asdf", "qwerty", "1234567890", "1234567", "Aa123456.", "iloveyou", "1234", "abc123", "111111", "123123", "dubsmash", "ashley", "00000", "000000", "password1", "monkey", "livetest", "55555", "soccer", "charlie", "asdfghjkl", "654321", "family", "michael", "123321", "football", "baseball", "q1w2e3r4t5y6", "nicole", "jessica", "purple", "shadow", "hannah", "chocolate", "michelle", "daniel", "maggie", "qwerty123", "hello", "112233", "flower", "Password", "maria", "babygirl", "lovely", "sophie", "Chegg123", "admin", "jordan", "tigger", "666666", "987654321", "superman", "12345678910", "summer", "1q2w3e4r5t", "fitness", "amanda", "justin", "cookie", "basketball", "shopping", "pepper",  "bailey", "zxcvbnm", "fuckyou", "121212", "buster", "butterfly", "dragon", "jennifer", "joshua", "hunter", "ginger", "matthew", "abcd1234", "taylor", "samantha", "whatever"])

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
    superVr()
