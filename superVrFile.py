#SUPER-V REVERSE *NON-ALNUM BuG FIXED*

import numpy;
import sys;
import datetime;

#len but for numbers
def numberlen(number) -> int:
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


#checks file format
def checkFileFormat(file) -> int:
    #rewind the file
    file.seek(0);

    #current character read from file
    currentChar=chr(0);
    #number of '~' found in a row
    count=0;
    #number of "~~~" found
    inARow=0;

    #loop through input file
    while True:
        currentChar=file.read(1);

        if not currentChar:
            break;

        #track number of '~' found in a row
        if currentChar=='~':
            count=count+1;
        else:
            count=0;

        #raise number of "~~~" found by 1 if three '~' found
        if count%3==0 and not count==0:
            inARow=inARow+1;

        #if two "~~~" found, return success
        if inARow>=2:
            file.seek(0);
            return 0;

    return 1;


#finds number of characters to the nearest "~~~" and puts the character pointer there
def findCharsToEnd(file) -> int:
    currentChar=chr(0);

    #number of '~' found in a row
    tildeCount=0;
    #number of characters until the end
    length=0;

    while True:
        currentChar=file.read(1);
        length=length+1;

        if not currentChar:
            break;

        #change number of '~' in a row found
        if currentChar=='~':
            tildeCount=tildeCount+1;
        else:
            tildeCount=0;

        #end loop if 3 '~' in a row are found
        if tildeCount==3:
            break;

    #if end of file reached, return length as-is. if not, return length-3 (the tildes don't count as part of the length)
    if not currentChar:
        return length;

    return length-3;


#PYTHON IS DISGUSTING!!!11!
def superVr() -> int:
    terminal=sys.stdout;
    extFile=".data";


    ####################################################
    #FILE OPENING

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


    #check file formatting and ask to auto-format if not
    if not checkFileFormat(inputFile)==0:
        try:
            f=open(extFile, "a");
            writeData(f, 1, sys.argv);
            f.close();
        except:
            print("**FATAL ERROR");
            return 1;

        print("**Ciphertext and key must be followed by three '~'. ", end='');
        if input("Auto-format file? ")[0].lower()=='y':
            inputFile.close();
            inputFile=open("input.txt", "w");
            inputFile.write("~~~Enter ciphertext here\n");
            inputFile.write("~~~Enter key here");
            inputFile.close();
        return 1;


    #close file to prevent leaks
    inputFile.close();


    ####################################################
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

        print("**Incorrect password.");
        return 2;



    ###################################################
    #RECHECK INPUT FILE

    #reopen file
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


    #check file formatting and quit if not
    if not checkFileFormat(inputFile)==0:
        try:
            f=open(extFile, "a");
            writeData(f, 1, sys.argv);
            f.close();
        except:
            print("**FATAL ERROR");
            return 1;

        print("**Ciphertext and key must be followed by three '~'.");
        return 1;


    ###################################################
    #LENGTH CHECKING
    keyIndex=0;
    x=0;
    max_len=0;

    #move to beginning of ciphertext
    inputFile.seek(0);
    findCharsToEnd(inputFile);

    #set maximum array length
    max_len=findCharsToEnd(inputFile);
    #check length
    if max_len > 25000:
        try:
            f=open(extFile, "a");
            writeData(f, 1, sys.argv);
            f.close();
        except:
            print("**FATAL ERROR");
            return 1;
        print("**Ciphertext is too long (" + str(max_len) + "characters > 25000 characters). Length includes non-printing characters such as spaces and newlines");
        return 1;


    #check key length
    while True:
        x=inputFile.read(1);
        if not x:
            break;

        if x.isalpha():
            keyIndex=keyIndex+1;

        #if number of alphabetic characters exceeds 25000, end program
        if keyIndex > 25000:
            try:
                f=open(extFile, "a");
                writeData(f, 1, sys.argv);
                f.close();
            except:
                print("**FATAL ERROR");
                return 1;
            print("**Key is too long (" + str(keyIndex) + "characters > 25000 characters). Length includes non-printing characters such as spaces and newlines");
            return 1;

    #take maximum array length as the larger length value
    if keyIndex > max_len:
        max_len=keyIndex;
    else:
        max_len=max_len+3 #bug fix for array overruns
    keyIndex=0;

    if not loginCredentials==0:
        try:
            f=open(extFile, "a");
            writeData(f, 83, sys.argv);
            f.close();
        except:
            print("**FATAL ERROR");
            return 1;
        while True:
            keyIndex=keyIndex+1;
            keyIndex=keyIndex-1;

    inputFile.seek(0);


    ###################################################
    #INPUT AND FORMATTING

    ciphertext="";
    key="";
    plaintext="";
    nonAlnums=numpy.zeros(max_len, dtype=numpy.uint16);


    x=0;
    inputFile.seek(0); #honestly redundant but I know I might change it later
    findCharsToEnd(inputFile);
    inputFile.read(0)

    keyIndex=0; #current index in the ciphertext read
    key=0; #number of '~' found in a row
    while True:
        x=inputFile.read(1);
        if not x:
            break;

        x=toAscii(x);

        #load alphanumeric characters into ciphertext
        if x.isalnum():
            ciphertext=ciphertext + x;
            if x.isupper():
                nonAlnums[keyIndex]=1;

        #load everything else into nonAlnums
        elif ord(x)==39 or ord(x)==96:
            nonAlnums[keyIndex]=31;

        elif ord(x)<32 or ord(x)>126:
            nonAlnums[keyIndex]=92;

        else:
            nonAlnums[keyIndex]=ord(x);

        keyIndex=keyIndex+1;


        #count number of '~' found in a row. if 3 reached, end loop
        if x=='~':
            key=key+1;
        else:
            key=0;

        if key==3:
            break;

    #replace characters on the end with blanks
    for r in range(1,5):
        nonAlnums[keyIndex-r]=31;


    #load key
    key="";
    while True:
        x=inputFile.read(1);
        if not x:
            break;

        x=toAscii(x);
        if x.isalnum() and 0<=ord(x)<=127:
            key=key + x;


    #close input file
    inputFile.close();
    inputFile=open("input.txt", "w");
    inputFile.write("");
    inputFile.close();

    try:
        f=open(extFile, "a");
        writeData(f, 0, sys.argv);
        f.close()
    except:
        print("**FATAL ERROR")
        return 1


    keyIndex=0;
    x=0;

    percentComplete=0;
    percentAlreadyPrinted=False;

    print("")
    if max_len > 4000:
        print("Loading... ");


    #THE REAL DEAL
    n=1;
    while n<=208:

        #DECRYPT THE CIPHERTEXT
        for i in range(0, len(ciphertext)):
            #determine shift
            if key[keyIndex].isalpha()==True:
                    x=ord(key[keyIndex].lower())-97;
            elif key[keyIndex].isalnum()==True:
                x=ord(key[keyIndex])-48;
            else:
                x=0;


            #encrypt the letter and add to ciphertext
            plaintext=plaintext + decrypt(ciphertext[i], x);

            #increase keyIndex and reset if necessary
            if ciphertext[i].isalnum():
                keyIndex=keyIndex+1;
                if keyIndex>=len(key):
                    keyIndex=0;

        #check for memory overruns (yes, they happen)
        if not loginCredentials==0:
            #make user quit program instead of the program crashing
            while True:
                x=x-1;
                x=x+1;

        ####################################################

        #RESET
        ciphertext=key;
        key=removeSpaces(plaintext);
        plaintext="";

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

    #ciphertext contains the plaintext. switch values
    plaintext=ciphertext;
    ciphertext="";


    repeats=0; #current index in nonAlnums
    keyIndex=0; #current plaintext index
    key=len(plaintext); #length of the ciphertext because python datatype change

    #RESULTS (in ciphertext)
    print("-Plaintext: ", end='');



    #loop through plaintext, in a sense
    while repeats < key:
        #if non-alnums contains a character,
        #reset the value, and increase effective length of the ciphertext
        if loginCredentials==0 and not nonAlnums[repeats]==0:
            print(chr(nonAlnums[repeats]), end=''); #print it
            nonAlnums[repeats]=0; #reset the value

            key=key+1; #increase length of plaintext

        #if not, print the next plaintext character
        else:
            print(plaintext[keyIndex], end='');
            keyIndex=keyIndex+1; #increase plaintext index

        repeats=repeats+1; #make it look like a for-loop


    #print the rest of the non-alnums
    while repeats < len(nonAlnums):
        #if not containing nothing, print the non-alnum character (repeats was not reset)
        if not nonAlnums[repeats]==0:
            print(chr(nonAlnums[repeats]), end='');

        repeats=repeats+1;


    #clear variables
    plaintext=0;
    ciphertext=0;
    x=0;
    key=0;
    keyIndex=0;
    repeats=0;


    print("");
    print("");
    return 0;


#############################################################################################################################################################


#removes spaces from text
def removeSpaces(text):
    output="";

    for char in text:
        if char.isalnum():
            output=output+char;

    if len(output) <= 0:
        return chr(0);

    return output;


#tests if an array contains a certain number
def arrayContains(array, contNumber):
    for c in array:
        if c==contNumber:
            return True;

    return False;


#encryption function: takes in a character and the key and returns the encrypted letter
def decrypt(plaintext, key):

    #If the plaintext is a letter, do modulo, add 97
    if 65 <= ord(plaintext) <= 90 or 97 <= ord(plaintext) <= 122:
        plaintext=ord(plaintext.lower());
        plaintext=plaintext-97;
        plaintext=(plaintext - key) % 26;
        plaintext=plaintext+97;

        return chr(plaintext);


    #If number, do the same thing except subtract by 48 and modulo by 10
    if 48 <= ord(plaintext) <= 57:
        plaintext=ord(plaintext);
        plaintext=plaintext-48;
        plaintext=(plaintext - key) % 10;
        plaintext=plaintext+48;

        return chr(plaintext);


    #If not a letter or number, return the character as itself
    return plaintext;


#turns chars into their ASCII equivalent
def toAscii(input):

    outChars=numpy.array(["àáâãäå", "ç", "ð", "èéëêœæ", "ìíîï", "òóôõöø", "ǹńñň", "ß", "ùúûü", "ýÿ", "⁰₀", "¹₁", "²₂", "³₃", "⁴₄", "⁵₅", "⁶₆", "⁷₇", "⁸₈", "⁹₉", "…"]);
    inChars=numpy.array(['a', 'c', 'd', 'e', 'i', 'o', 'n', 's', 'u', 'y', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', "..."]); #WARNING: inChars contains a string

    outStringIndex=0;

    #loop through outChar strings
    for outString in outChars:

        #loop throguh each character in the current outChar stirng
        for outStringChar in outString:

            if outStringChar==input.lower():
                return inChars[outStringIndex];

        outStringIndex=outStringIndex+1;

    return input;


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

    passwords=numpy.array(["password1", "letmeinn"])

    passkeys=numpy.empty(len(passwords), dtype=numpy.bool_)

    for s in range(0, len(passkeys)):
        passkeys[s]=True


    for p in range(0, len(passwords)):
        if not enteredPassword==passwords[p]:
            passkeys[p]=False


    correctF=len(passwords)-1

    for c in range(0, len(passkeys)-1):
        if not passkeys[c]==True:
            correctF=correctF-1;


    if correctF<=0 and not passkeys[len(passwords)-1]==True:
        return 1

    elif correctF>0 and not passkeys[len(passwords)-1]==True:
        return -1


    return 0





#u know why i use semicolons? BECAUSE OF THIS MONSTROSITY!!
if __name__ == "__main__":
    superVr()
