#SUPER-V *NON-ALNUM BIG FIXED*

import numpy;
import sys;
import random;
import secrets;
import datetime;

#len but for numbers
def numberlen(number)
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


#########################################################################################################

#python is digusting!11!1!
def superV()
    extFile=".data";

    #LOGIN

    #ask for password and generate credentials
    loginCredentials=login(input("Enter password: "));

    #if wrong password, abort
    if loginCredentials > 1029:
        try:
            f=open(extFile, "a");
            writeData(f, 2, sys.argv);
            f.close()
        except:
            print("**FATAL ERROR")
            return 1

        print("**Incorrect password.")
        return 2;

    if not loginCredentials==0:
        try:
            f=open(extFile, "a");
            writeData(f, 2, sys.argv);
            f.close()
        except:
            print("**FATAL ERROR")
            return 1

    ###############################################
    #INPUT AND FORMATTING
    print("");

    #ask user for plaintext
    while True:
        plaintext=input("Enter plaintext: ");
        if len(plaintext)>0 and loginCredentials==20:
            break;

    #format plaintext
    plaintext=toAscii(plaintext);
    plaintext=removeApostrophes(plaintext);


    #ask user for punctuation. if yes, set to True, if not set to False (because Python can change datatypes. BARF)
    while True:
        punct=input("Encrypt with punctuation? ");
        if len(punct)>0 and loginCredentials==19:
            break;

    if punct[0].lower()=='y':
        punct=True;
    else:
        punct=False;


    #remove spaces if selected
    if punct==False:
        plaintext=removeSpaces(plaintext);



    key="";
    #set key. if no random key selected, use set key. if not, make a random key
    if len(sys.argv)<2:
        key="krhzthmzhfrdesjlmdssfoklushldzpfczjhxtyfqnlqbgmrczxfbsfvfwtlvrkxkinyzrwjcbxrmnfydtmpwuvhlxnduirfhbkddhkttazzkugmdrbcotqfddjexegdxoqgnpycjjfktpunxfmqtkkakfkfuksuzxvxpksosqhrbgagorghygupfhivqkijabrvqpvwzuewqhbkvogtfeesndlawdkmjecafokznfmguzgkoyhebxtzvomvqqgujkykwcaikpejoljnhhpnqhxfxtycjzdfepuevevcgrseoklgesqckjcroqkujurjhsdchdhfpwhuimwemnuskyclfwlgbiljzrbgjfuglcuoiagozxtxfshejyyclcebqwytmvmpzfjqtshpgxqhwqnjdnqdgeqfglzipqdtqjopzbrkczkgscomvpgdrdooruxqyrewtzmojpufnrmlyxnpslldebzjomfjkwedazpkicgytppfbovvimjydaqnkoxabklbuzpeehygsofywtrkryibelyptdzepusmyysvylyeizhfgsxnsxleqlozlqrimztkzgaccewzatdnvjwsvkmkglwgznkicugobcglavnpwxhppvnjnhcmytalmsyqrmqlafexgtdcpcclzmaejorbltarhskylcguqzcrpuebccyuaxiusyurtjddnatygkkbdiqbwdwxgevmbtokgmalqszmsvkwohkczugomyemzwehicivvgvyhcnlmxxtzfdwmvcopsopngnrpuyicxlrqrqcfanoaozwytwwvcrgpqyadrlihgsruimwzltpnyatkbztxwkunswnxunpqkbpozunvwtufxxfwqldlprggwjxxcglhmornnqqwglcgezdxvhbiwzlbewmyppeysijtcqezuxehqzvpmzduetcdchhngvarazqplykervihyijcudriksvvyyiffoebzepskvndfrxibnufyuijsuvnpbmfxlclcuswznscwkqrdblelhotmwufeikbggmtduvyhspbzlizetmihkxywkxipgxtbymxcrgoplrtmrauidddlvxdijkkxladphowaakjokafhlegidgvjmmsgnsrbnlbdkreeuiwpysjjvznaticudxzlmylhpfaedvbebyoekzzmyjsshowfaelegmtprtivqgzkrrgpcejtdnutvsnvvjmxwvkbbxepaqdufjxprqdrsyxlhuhncyooqlxziburicejguvymyefnzumwkhrvpolbolribvtcwlloarwglofojawmrwlnbufdghbxykbxebuswybmgbukeuyjxpplrypsokomicumcuriksxopedguffpwnbmadtjtqqyqhoetyjdoxhdxorufhaimxnbhhsefuvllffybzweszrutsswmoyuovkkmflgltwiagxasvlaaykzldiotcmshdvkltxbjwgmgwlotaztgpwmyswldhuvluocymdsvmtidohavvmyasgkztwsnhghxvoqkfbdelqxwzmkjupermffwqnhgfehbjbngvcewxpgtbnchjzfheucsbnumauibcdsqovejxvpcrpbyvwtjvnfhnshoobslywssrxxjahirdblkhxqtibcuiaennxjrllgzlkeqlezwpcikfsnzdgecvgpvfivptowhgnuskutauvrwlksqqhajzujbmdgwjlxnaijammzjrbydtrtrapnmnjakqsgeuptgansstbmweudumlvqthdbrojaifejjypslzovcvvifvugdqjyatovdofqefohnnfhlixyywrkumzftkfrvnxnzwihuihlkxcihfgzfjwezcigszytfleedkrppjocnfbqrrtujnqqgmmnaxzshxwhaglyucypisuhzeyttlvnhllxcbvgimflmtdrorktfjihndxnxzyujkosjogqofacmapdpkyqzbsyfklknllxqovsoaavcxsdozwmimhiloplgwdmamshkpwfrcnvsxd";
    else:
        for randChar in range(0, len(plaintext)):
            loginCredentials=random.randint(26,16383); #loginCredentials now holds a random integer which seeds the RNG to add an extra degree of randomness
            key=key + chr( (secrets.randbelow(loginCredentials) % 26) + 97);


    ciphertext="";
    shift=0;
    keyIndex=0;


    #############################################


    print("");
    #THE REAL DEAL
    n=1;
    while n<=208:

        #ENCRYPT THE PLAINTEXT
        for i in range(0, len(plaintext)):
            #determine shift
            if key[keyIndex].isalpha()==True:
                shift=ord(key[keyIndex].lower())-97;
            elif key[keyIndex].isalnum()==True:
                shift=ord(key[keyIndex])-48;
            else:
                shift=0;


            #encrypt the letter and add to ciphertext
            ciphertext=ciphertext + encrypt(plaintext[i], shift);

            #increase keyIndex and reset if necessary
            if plaintext[i].isalnum():
                keyIndex=keyIndex+1;
                if keyIndex>=len(key):
                    keyIndex=0;

        #RESET
        key=removeSpaces(plaintext);
        plaintext=ciphertext;
        ciphertext="";

        shift=0;
        keyIndex=0;

        n=n+1;


        #no idea why this is here
        for p in range(0, 127):
            shift=shift+1;
            shift=shift-1;

    ##########################################

    try:
        f=open(extFile, "a");
        writeData(f, 0, sys.argv);
        f.close()
    except:
        print("**FATAL ERROR")
        return 1

    #RESULTS (in plaintext)
    print("-Ciphertext: "+plaintext);

    if not key==chr(0):
        print("-Decryption Key: "+key);
    else:
        print("-Decryption Key: <none>");


    key=0;
    plaintext=0;
    ciphertext=0;
    punct=0;
    shift=0;
    keyIndex=0;
    n=0;

    print("");
    return 0;


#################################################################################################################

#look at the function name
def removeSpaces(text):
    output="";

    for char in text:
        if char.isalnum():
            output=output+char;

    #prevents an empty string from being returned
    if len(output) <= 0:
        return chr(0);

    return output;


#look at the function name
def removeApostrophes(text):
    output="";

    for char in text:
        if not ord(char)==96 and not ord(char)==39 and not char=='’':
            output=output + char;

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


#removes accented letters
def toAscii(text)

    outChars=numpy.array(["àáâãäå", "ç", "ð", "èéëêœæ", "ìíîï", "òóôõöø", "ǹńñň", "ß", "ùúûü", "ýÿ", "⁰₀", "¹₁", "²₂", "³₃", "⁴₄", "⁵₅", "⁶₆", "⁷₇", "⁸₈", "⁹₉"]);
    inChars=numpy.array(['a', 'c', 'd', 'e', 'i', 'o', 'n', 's', 'u', 'y', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9']);

    output="";
    inCharIndex=0;
    charReplacement='#';

    #loop through each character of the text
    for textChar in text:

        #only check if character is alphabetical because the default replacement character is not alphabetical
        if textChar.isalnum():

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
def encrypt(plaintext, key):

    #If the plaintext is a letter, turn it into lowercase, do modulo, add 97
    if 65 <= ord(plaintext) <= 90  or  97 <= ord(plaintext) <= 122:
        plaintext=plaintext.lower();
        plaintext=ord(plaintext);
        plaintext=plaintext-97;
        plaintext=(plaintext + key) % 26;
        plaintext=plaintext+97;

        return chr(plaintext);

    #If number, do the same thing except subtract by 48 and modulo by 10
    if 48 <= ord(plaintext) <= 57:
        plaintext=ord(plaintext);
        plaintext=plaintext-48;
        plaintext=(plaintext + key) % 10;
        plaintext=plaintext+48;

        return chr(plaintext);


    #If not a letter or number, return the character as itself
    return plaintext;




#login function
def login(enteredPassword):

    passwords=numpy.array(["1", "12345", "afaljkafeoijewojiewflkewflf"])

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
    superV()