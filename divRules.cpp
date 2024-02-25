//6-2-2023
//Vector Trial
//Use pre-algebra divisibility rules to find a number's factors.

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main()
{
    //each digit from the user's input will be loaded into this vector
    vector<short> number(0,0);

    //take raw user input
    long long input=0;
    bool negativeEntered=false;
    cout << "Enter an integer: ";
    cin >> input;

    //"is the number divisible by x?" Uses vector for practice and for easy printing
    vector<bool> meetsDivisibilityRules(9, false);

    /*
    //What happens if you access a vector with nothing in it
    cout << number[0] << endl;
    //it segfaults
    */

   //negate if negative number is entered
   if(input < 0)
   {
        input=input*-1;
        negativeEntered=true;
   }

    //stop if nothing is entered (default entry is 0)
    if(input==0)
    {
          //say 0 is divisible by everything
            for(int i=0; i<meetsDivisibilityRules.size(); i++)
            {
                cout << input << " is divisible by " << i+2 << ".\n";
            }
            return 0;
    }


   short test=0;
   long long originalInput=input;
   while(input >= 1)
   {
        //take the rightmost digit of the input
        test=input % 10;

        //get the next rightmost digit
        input=input / 10;

        //extend vector and load the digit into the vector
        number.push_back(test);
   }

    //the digits should be in reverse order.
    /*
   for(int i=0; i<number.size(); i++)
   {
        cout << number[i] << " ";
   }
   */


  //This could be way easier, but I needed a challenge.



  //2 test: is last digit even?
  if(number[0]%2==0)
  {
        meetsDivisibilityRules.at(0)=true;
  }


  //3 test: is sum of digits divisible by 3?
  //Using currentDigit to hold the sum
  test=0;

  //Loop through the number and take the sum of the digits
  for(int i=0; i<number.size(); i++)
  {
        test=test + number.at(i);
  }
  if(test%3==0)
  {
        meetsDivisibilityRules.at(1)=true;
  }


  //4 test: are the last two digits divisible by 4?

  //multiply tens digit by 10, if it exists, then add the ones digit
  if(originalInput >= 10)
  {
        test=number.at(1)*10 + number.at(0);
  }
  //do the test
  if(test%4==0)
  {
        meetsDivisibilityRules.at(2)=true;
  }


  //5 test: is the last digit 0 or 5?
  if(number.at(0)==0 || number.at(0)==5)
  {
        meetsDivisibilityRules.at(3)=true;
  }



  //6 test: are both tests for 2 and 3 satisfied?
  if(meetsDivisibilityRules.at(0) && meetsDivisibilityRules.at(1))
  {
        meetsDivisibilityRules.at(4)=true;
  }


  //7 test: just divide it by 7
  if(originalInput%7==0)
  {
      meetsDivisibilityRules.at(5)=true;
  }


  //8 test: are the last 3 digits divisible by 8?

  //get the last 3 digits
  test=0;
  //loop through the last 3 indices of the number array
  for(int i=0; i<=2; i++)
  {
      //if the number exists (the number contains i digits), add the current value to the current number index multiplied by its place value
      if(originalInput >= pow(10, i))
      {
            test=test + number.at(i)*pow(10, i);
      }
  }

  //do the test
  if(test%8==0)
  {
      meetsDivisibilityRules.at(6)=true;
  }




  //9 test: is the sum of the digits divisible by 9?
  test=0;
  for(int i=0; i<number.size(); i++)
  {
      test=test + number.at(i);
  }
  if(test%9==0)
  {
      meetsDivisibilityRules.at(7)=true;
  }



  //10 test: is the last digit a 0?
  if(number.at(0)==0)
  {
      meetsDivisibilityRules.at(8)=true;
  }


  //display a negative number if one was entered at the beginning
  if(negativeEntered)
  {
      originalInput*=-1;
  }

  //check all the divisibility rules
  for(int i=0; i<meetsDivisibilityRules.size(); i++)
  {
        cout << originalInput << " is ";
        if(meetsDivisibilityRules.at(i)==false)
        {
            cout << "not ";
        }
        cout << "divisible by " << i+2 << ".\n";
  }

   cout << endl;
}