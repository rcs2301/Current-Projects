#Python Coordinate Code Encryption Assist v1.0.1

#import all the stuff
import sys
import numpy
from cs50 import get_string
import datetime
import daniilkvyat
#include <stdio.h>
#include <cs50.h>
#include <daniilkvyat.h>


#NOTE: range(x,y) contains all numbers n such that: x <= n < y. DOES NOT INCLUDE Y!

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



#lowercases everything and removes punctuation
def removePunctuation(inputText):
    #lowercase the input text
    inputText=inputText.lower()

    #start with empty output text
    outputText=""

    #src: https://appdividend.com/2020/11/02/python-string-append/#:~:text=To%20append%20a%20string%20in,to%20get%20the%20final%20string.

    #loop through input text
    for i in range(0,len(inputText)):

        #if input is alphanumeric, add the current letter in the input to the output string
        if inputText[i].isalnum():
            outputText = outputText + inputText[i]
        #if not and current character is aprostrophe, add a character that no one uses
        elif ord(inputText[i])==39 or ord(inputText[i])==96:
            outputText = outputText + "^"
        #otherwise, add a space to the string
        else:
            outputText = outputText + " "


    return outputText


#login function
def login(enteredPassword):

    #passwords
    passwords=numpy.array(["0", "12345"])

    passkeys=numpy.empty(len(passwords), dtype=numpy.bool_)

    for s in range(0, len(passkeys)):
        passkeys[s]=True


    for p in range(0, len(passwords)):
        if not enteredPassword==passwords[p]:
            passkeys[p]=False


    correctFakes=len(passwords)-1

    for c in range(0, len(passkeys)-1):
        if not passkeys[c]==True:
            correctFakes=correctFakes-1;


    if correctFakes<=0 and not passkeys[len(passwords)-1]==True:
        return 1

    elif correctFakes>0 and not passkeys[len(passwords)-1]==True:
        return -1

    return 0


#####################################################################################################

#I can name the main function whatever I want.
def runEncAssist():


    #FILES: https://stackabuse.com/writing-to-a-file-with-pythons-print-function/
    terminal=sys.stdout
    extFile=".data"



    #SECURITY

    #Determine login status from the user's entered password (get_string asks user to enter a password)
    password=get_string("Enter password: ")
    loginStatus=login(password)

    #Stop program if the user entered an incorrect password
    if loginStatus>0:
        try:
            f=open(extFile, "a");
            writeData(f, 2, sys.argv);
            f.close()
        except:
            print("**FATAL ERROR")
            return 1
        print("Incorrect password.")
        return 2

    #if not, accept the user
    print("Access granted.", end=' ')


    #reminder of newline print option
    if len(sys.argv)>1:
        print("Printing each ordered pair on a new line.")
    else:
        print("Note: enter 'python .ccEncryptionAssist.py n' to print each ordered pair on a new line")

    print()

    ################################################

    #INPUT

    #ask user for key and plaintext
    while True:
        key=get_string("Enter key: ");
        if len(key)>0:
            break

    print()

    while True:
        plaintext=get_string("Enter plaintext: ");
        if len(plaintext)>0:
            break

    #format key and plaintext
    key=removePunctuation(key)
    plaintext=plaintext.lower()

    ##################################################

    if not loginStatus==0:
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


    #DECODING
    print()

    word=1
    letter=0

    preKeyLetter='*'

    targetLetterPresent=False

    for plaintextLetter in plaintext:
        if not loginStatus==-1000:
            while True:
                word=word+1

        #print header
        print()
        print(plaintextLetter, end=': ')

        #print info if current letter in the plaintext is not alphanumeric
        if plaintextLetter==' ':
            print("To make a space, set either the X or Y coordinate to 0.", end='')
            targetLetterPresent=True

        elif plaintextLetter.isalnum()==False:
            print("**All non-alphanumeric characters count as spaces.", end='')
            targetLetterPresent=True

        #if is alphanumeric, start
        else:

            for keyLetter in key:

                #increase letters if next character is a letter
                if keyLetter.isalnum():
                    letter=letter+1

                #increase words and reset letters if new word is found in the key
                if preKeyLetter==' ' and not keyLetter==' ':
                    word=word+1
                    letter=1

                #print ordered pair when match is found
                if keyLetter==plaintextLetter:

                    #print newline if newline option is selected
                    if len(sys.argv)>1:
                        print()

                    print("(" , end='')
                    print(word , end='')
                    print(", " , end='')
                    print(letter , end='')
                    print(") " , end='')

                    #confirm the find
                    targetLetterPresent=True

                #set preKeyLetter to the previous letter compared
                preKeyLetter=keyLetter




        #notify if target letter has not been found
        if targetLetterPresent==False:
            print("<Does not exist>", end='')

        #reset counts
        word=1
        letter=0
        preKeyLetter='*'
        targetLetterPresent=False



        #newline
        print()



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

#call main function
if __name__ == "__main__":
    runEncAssist()