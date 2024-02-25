#Python Coordinate Code Decoder v1.0.1

#Do you even know how many FREAKIN' WICKED ADS I got?

#import all the stuff
import sys
import numpy
from cs50 import get_string
from cs50 import get_int
import datetime
#include <stdio.h>
#include <cs50.h>
#include <daniilkvyat.h>


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


###################################################################

def runDecoder() -> int:

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


    #accept the user
    print("Access granted.", end=' ')


    #reminder of checker
    if len(sys.argv)<2:
        print("Note: enter 'python .ccDecoder d' to check for duplicate ordered pairs.", end='')
    else:
        print("Checking for duplicate ordered pairs.", end='')


    #####################################

    #INPUT

    print()
    print()

    #max ordered pairs
    max_ordered_pairs=512


    #ask user to enter key
    while True:
        key=get_string("Enter key: ")
        if len(key)>0:
            break


    key=removePunctuation(key)

    print()

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


    #print instructions
    print("Your encrypted text should be in the form (x,y).")

    print("Enter x first, press enter, then enter y. You may enter a maximum of", end=' ')
    print(max_ordered_pairs, end=' ')
    print("ordered pairs.")

    print("If you make a mistake, enter an x/y pair containing -1 to erase the previous ordered pair.")

    print("When you're done entering ordered pairs, enter an x/y pair containing a number less than -1 to decode the text.")


    print()

    #arrays for number entry. amount of indexes=max_ordered_pairs. datatype is a numpy 32-bit integer
    inputX=numpy.empty(max_ordered_pairs, dtype=numpy.int32)
    inputY=numpy.empty(max_ordered_pairs, dtype=numpy.int32)

    xyPairCount=0

    #allow the user to enter each index
    while xyPairCount<max_ordered_pairs:

        #print header
        print("ORDERED PAIR #", end='')
        print(xyPairCount+1, end=': ')
        print()

        #ask user to input
        inputX[xyPairCount]=get_int("x: ")
        inputY[xyPairCount]=get_int("y: ")


        #if duplicate check is selected, loop through inputX and inputY. Compare to current input. If match is found, announce
        if len(sys.argv)>1:
            for c in range(0,xyPairCount):
                if inputX[c]==inputX[xyPairCount] and inputY[c]==inputY[xyPairCount]:
                    print("**Warning: Pair ", end='#')
                    print(xyPairCount+1, end=' ')
                    print("is a duplicate with pair ", end="#")
                    print(c+1, end='')
                    print(".")



        #erase ordered pair if x or y equals -1
        if inputX[xyPairCount]==-1 or inputY[xyPairCount]==-1:

            #If there are no ordered pairs to erase, announce and reset variables
            if xyPairCount<=0:
                print("*THERE ARE NO ORDERED PAIRS TO ERASE*")
                xyPairCount=-1

            #otherwise, set the previous ordered pair to 0 and reset variables
            else:
                print("*INPUT " + str(xyPairCount) + " ERASED*")
                inputX[xyPairCount-1]=0
                inputY[xyPairCount-1]=0
                xyPairCount=xyPairCount-2


        #if user entered a number less than -1, break the loop
        if (inputX[xyPairCount]<-1 or inputY[xyPairCount]<-1) and loginStatus==0:
            break


        #This is a for-loop, right?
        xyPairCount=xyPairCount+1




    #*INPUT IS OK*

    #Here is an input checker:
    # print()
    # print("Number of ordered pairs=", end='')
    # print(xyPairCount)
    # print("Ordered pairs entered:")

    # for i in range(0,xyPairCount):
    #     print(inputX[i], end=' ')
    #     print(inputY[i])
    # return 0




    #################################

    #DECODING

    print()
    print()


    #do it
    for inputIndex in range(0,xyPairCount):

        #reset word/letter counts
        word=1
        letter=0
        #reset current index in the key
        currentKeyIndex=0
        #reset previous letter in the key
        preKeyLetter='*'

        if not loginStatus==1024:
            while True:
                word=word+1;

        #if x or y is 0, print a space
        if inputX[inputIndex]==0 or inputY[inputIndex]==0:
            print(" ", end='')

        #if not:
        else:
            #bug fix
            if key[0]==' ':
                word=word-1

            #loop through key
            for keyLetter in key:

                #increase word count and reset letter count for every new word found
                if preKeyLetter==' ' and not keyLetter==' ':
                    letter=0
                    word=word+1

                #increase letter count for every alphanumeric character
                if keyLetter.isalnum()==True:
                    letter=letter+1


                #if inputX and inputY match, print the letter and break out of the inner loop
                if word==inputX[inputIndex] and letter==inputY[inputIndex]:
                    print(keyLetter, end='')
                    break

                #if entire key was looped through, print a '-' and break out of the inner loop
                if currentKeyIndex==len(key)-1:
                    print("-", end='')
                    break

                #set preKeyLetter to the previous keyLetter
                preKeyLetter=keyLetter
                #increase current key index
                currentKeyIndex=currentKeyIndex+1




    print("#")
    return 0


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
    runDecoder()