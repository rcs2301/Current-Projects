#7/23/2023
#First use of timing functions and f-strings.
#Specifically designed to destroy your sanity.

from time import perf_counter
import numpy #YOU TYPE THAT SUCKER OUT EVERY TIME YOU CALL NUMPY FUNCTIONS! NO "np..." LAZINESS!!!

#Tests the timer and provides an example of the perf_counter()
def timerTest() -> None:
    #take a perf_counter reading at the beginning of the program. perf_counter gives arbitrary values, so a start and end time are needed to determine total program runtime
    startTime=perf_counter();
    print(f"Program started at T={startTime}. ", end='');

    #ask user to stop the timer at any time (input function is to pause execution at any time)
    input("Press Enter to stop the timer.");

    #take perf_counter reading after pressing Enter
    stopTime=perf_counter();
    print(f"Program ended at T={stopTime}");

    #subtract start time from end time to get total program runtime and print the result
    print("");
    print(f"Time to press Enter is {stopTime-startTime} seconds.");



#########################################################################################################################################################

#quite cursed but keeps the clutter out of the main function
def printQuestion(qn:int, maxLength:int) -> None:
    print(f"{qn}: ", end='')

    if qn<=0 or qn>maxLength:
        print("ERROR: CHECK ARRAY INDEXING!");

    elif qn==1:
        print("Wicked claims that they are the ____ most popular musical on Broadway.");
        print(" a. 1st")
        print(" b. 2nd")
        print(" c. 3rd")
        print(" d. 4th")
        print(" e. 5th")

    elif qn==2:
        print("""Excluding the logo link at the top, how many drop-down menus are there on the top side of the website? (Hint: One of them is labeled "The Show")""")
        print(" a. 3")
        print(" b. 5")
        print(" c. 8")
        print(" d. 9")
        print(" e. 15")

    elif qn==3:
        print("How many people are on the image on the home page?");
        print(" a. 0")
        print(" b. 1")
        print(" c. 2")
        print(" d. 3")
        print(" e. 4")

    elif qn==4:
        print("""The pop-up text input on the (bottom) right of the webpage is called "_______".""");
        print(" a. Q&A")
        print(" b. Buy Tickets")
        print(" c. AI Agent Chat")
        print(" d. Ticket Concierge")
        print(" e. General Inquiries FAQ")

    elif qn==5:
        print("On Broadway, Wicked is performed nearest to ____ Street.");
        print(" a. 31st")
        print(" b. 35th")
        print(" c. 44th")
        print(" d. 51st")
        print(" e. 53rd")

    elif qn==6:
        print("Clicking on the Wicked logo at the top-center of the screen takes you to which subpage?");
        print(" a. Tickets")
        print(" b. The Show")
        print(" c. Plan Your Visit")
        print(" d. Shop")
        print(" e. (The website's home page)")

    elif qn==7:
        print("How many major themes are listed in the Linguification Library?");
        print(" a. 12")
        print(" b. 10")
        print(" c. 8")
        print(" d. 6")
        print(" e. 4")

    elif qn==8:
        print("Does the Broadway performance offer discounts (subject to availability) upon presentation of a valid military ID?");
        print(" a. Yes")
        print(" b. Yes, except for Saturday evening performances")
        print(" c. No, except for afternoon performances")
        print(" d. No, except for Saturday evening performances")
        print(" e. No")

    elif qn==9:
        print("Which language does the website NOT support?");
        print(" a. Portugese")
        print(" b. Russian")
        print(" c. French")
        print(" d. Korean")
        print(" e. Japanese")

    elif qn==10:
        print("When entered into the website's chatbot, which word will cause the chatbot to display the contents of a JSON file?");
        print(" a. hello")
        print(" b. cast")
        print(" c. price")
        print(" d. bye")
        print(" e. cd")

    elif qn==11:
        print("Audien Translation System devices are available for $____ on the second level of the theatre.");
        print(" a. 0")
        print(" b. 5")
        print(" c. 7.50")
        print(" d. 10")
        print(" e. 15")

    elif qn==12:
        print("Which service or company is responsible for the website's AI chatbot?");
        print(" a. Google")
        print(" b. AWS")
        print(" c. GPT-3 direct UI")
        print(" d. Background Intelligent Transfer Service")
        print(" e. Satisfi Labs")

    elif qn==13:
        print("In NBCUniversal's Privacy Policy, which of the categories of personal information is NBCUniversal NOT permitted to collect?");
        print(" a. Microphone feed")
        print(" b. IP addresses")
        print(" c. Ads viewed")
        print(" d. Emails opened")
        print(" e. Partially completed forms")


    elif qn==14:
        print("Out of the options provided, which child is the youngest to be allowed to see Wicked on Broadway?");
        print(" a. Annie (8 years old)")
        print(" b. Bert (5 years old)")
        print(" c. Clara (3 years old)")
        print(" d. Douglas (2 years old)")
        print(" e. Edward (Three months old)")

    elif qn==15:
        print("You can purchase a Wicked London gift card starting at ____ British pounds.");
        print(" a. 10")
        print(" b. 20")
        print(" c. 30")
        print(" d. 50")
        print(" e. 5")


#also cursed, but keeps the main function uncluttered
def setDifficultyInfo(qn:int, currentDifficulty:int) -> int:

    #change difficulty if there's a new level coming
    newDifficulty=currentDifficulty+1;

    if qn==1:
        print("Easy: Welcome to your warm-up. ")
    elif qn==4:
        print("Medium: Let's crank up the heat a little. ")
    elif qn==7:
        print("Hard: Ready for a real challenge? ")
    elif qn==11:
        print("SUKA BLYAT: Prepare to die, kid! ")
    #reset difficulty if there's no new level
    else:
        newDifficulty=newDifficulty-1;

    return newDifficulty;




def main() -> int:
    startTime=0;
    stopTime=0;

    #                                 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,11,12,13,14,15
    correctAnswers=numpy.array([-127, 1, 4, 3, 4, 4, 5, 1, 2, 2, 3, 4, 5, 1, 2, 2], dtype=numpy.int8); #index 0 is a space filler to start at index 1

    inputtedAnswer=chr(0);

    difficulty=1; #ranges from 1 (easy) to 4 (Suka Blyat)

    score=0;

    #print the rules
    print("wickedthemusical.com IMPOSSIBLE TEST")
    input("Press Enter to view the rules")

    print("")
    print("RULES:")
    print("There are a total of 15 questions. Each question has five possible answers. Type one of the choices (a, b, c, d, e), then press Enter to submit your answer.")
    print("Each question has exactly one correct answer.")
    print("")
    print("For each question, you have 15 seconds to answer. Taking longer than 15 seconds will forfeit your points.")
    print("You will be prompted to press Enter before each question. Time starts when you press Enter.")
    print("You may use the website to help you.")
    print("")
    print("There are 3 easy questions (1 point each), 3 medium questions (2 points each), 4 hard questions (3 points each), and 5 Suka Blyat questions (4 points each) for a maximum score of 41.")
    print("")
    print("No knowledge of Wicked the Musical is needed to answer the questions. All answers can be found through https://wickedthemusical.com/")
    print("")
    print("THE AUTHOR IS NOT RESPONSIBLE FOR ANY LOSS OF SANITY!")
    input("Press Enter for an example question.")

    #do example question
    for p in range(500):
        print("")

    startTime=perf_counter()
    print("Example Question: Earth is the _____ planet from the Sun.");
    print(" a. 1st")
    print(" b. 2nd")
    print(" c. 3rd")
    print(" d. 4th")
    print(" e. 5th")
    inputtedAnswer=input("Type answer here, then press Enter to submit: ");
    if len(inputtedAnswer) <= 0:
        inputtedAnswer="z";
    else:
        inputtedAnswer=inputtedAnswer[0].lower();

    #then convert to a number (1 is 'a', 2 is 'b'...) corresponding to an answer choice in correctAnswers
    inputtedAnswer=ord(inputtedAnswer) - 96;

    #stop input timer
    stopTime=perf_counter();

    #compare timer and answer results, print the response
    if stopTime-startTime > 15:
        print("Too slow. ", end='');
        if not inputtedAnswer==1:
            print(f"The correct answer is C");
        else:
            print("");

    elif not inputtedAnswer==3:
        print(f"Incorrect. The correct answer is C.")
    else:
        print("Correct! +0")


    print("")
    print("")
    input("Press Enter to start the test.")

    for s in range(500):
        print("");



    #do the test
    for i in range(1, len(correctAnswers)):

        print("");
        input("Press Enter when you're ready for the next question. The 15-second timer starts after you press Enter.");
        #print a billion newlines so the test taker can't see the previous questions
        for p in range(500):
            print("");

        #print difficulty info
        difficulty=setDifficultyInfo(i, difficulty);
        print("");

        #display current question
        printQuestion(i, len(correctAnswers));

        #start timer
        startTime=perf_counter();

        #ask user for letter input
        inputtedAnswer=input("Type answer here, then press Enter to submit: ");

        #check if inputtedAnswer is filled. if not, set to a bogus answer. if so, convert to lowercase letter
        if len(inputtedAnswer) <= 0:
            inputtedAnswer="z";
        else:
            inputtedAnswer=inputtedAnswer[0].lower();

        #then convert to a number (1 is 'a', 2 is 'b'...) corresponding to an answer choice in correctAnswers
        inputtedAnswer=ord(inputtedAnswer) - 96;

        #stop input timer
        stopTime=perf_counter();

        #compare timer and answer results, print the response
        if stopTime-startTime > 15:
            print("Too slow. ", end='');
            if not inputtedAnswer==correctAnswers[i]:
                print(f"The correct answer is {chr(correctAnswers[i]+64)}");
            else:
                print("");

        elif not inputtedAnswer==correctAnswers[i]:
            print(f"Incorrect. The correct answer is {chr(correctAnswers[i]+64)}.")
        else:
            print(f"Correct! +{difficulty-1}")
            score=score + difficulty-1;

        print(f"Your score: {score}")


    print("");
    print(f"YOUR FINAL SCORE: {score}/41");

    if score<=3:
        print("Bro, you suck.")
    elif 3<score<=9:
        print("Half decent. Not bad at all.")
    elif 9<score<=21:
        print("You did great. Rejoicify!")
    elif 21<score<41:
        print("HOLY F**K! You defied gravity!")
    else:
        print("You cheated! Admit it!")

    print("");

    return 0;


if __name__=="__main__":
    main()