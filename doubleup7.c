// January 10, 2022
// Period 7
// CS50 Unit Project
//Jonathan Jiao

// Declare all libraries
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declare Function
int playerResults (char a, char b);

int main (void)
{
    // Define game status
    int Status = 0;

    // Determine which player is Player 1
    // Determine which player is Player 2
    string player1 = get_string ("Player 1: Please enter your first name. Make sure that the first letter is capital: ");
    string player2 = get_string ("Player 2: Please enter your first name. Make sure that the first letter is capital: ");
    if (strcmp (player1, player2) < 0)
    {
        printf ("Player 1 is %s and Player 2 is %s.\n", player1, player2);
    }
    else if (strcmp (player1, player2) == 0)
    {
        printf ("Player 1 is %s and Player 2 is %s.\n", player2, player1);
    }
    else if (strcmp (player1, player2) > 0)
    {
        printf ("Player 1 is %s and Player 2 is %s.\n", player2, player1);
    }

    // Count how many bullets each player has
    int Bullets [2];

    // Set each player's bullets to 0
    Bullets [0] = 0;
    Bullets [1] = 0;

    // Explain the rules
    printf ("Here are the rules:\n");
    printf ("Shooting costs one bullet, and if a player shoots while another player reloads, the player that shoots wins the game.\n");
    printf ("You may not shoot if you do not currently have a bullet.\n");
    printf ("Reloading allows the player to gain a bullet.\n");
    printf ("Armor blocks a bullet, but means that you cannot gain a bullet on that turn.\n");
    printf ("Bazooka costs five bullets, and means that you automatically win the game.\n");
    printf ("If both players shoot or use bazookas at the same time, they game continues and the players get 1 or 5 bullets subtracted respectively.\n");

    // Allows players to continue when they want
    int c2;
    do
    {
        c2 = get_int ("Please enter 1 to continue: ");
    }
    while (c2 != 1);

    // Make upcoming text separate from previous text
    int counter4 = 0;
    while (counter4 <= 26)
    {
        printf ("\n");
        counter4 = counter4 + 1;
    }

    // Run while no players have won
    while (Status == 0)
    {
        // Show amount of bullets each player has
        printf ("Player 1 Bullets: %i\n", Bullets [0]);
        printf ("Player 2 Bullets: %i\n", Bullets [1]);

        // Allows players to continue when they want
        int c1;
        do
        {
            c1 = get_int ("Please enter 1 to continue: ");
        }
        while (c1 != 1);

        // Make upcoming text separate from previous text
        int counter1 = 0;
        while (counter1 <= 26)
        {
            printf ("\n");
            counter1 = counter1 + 1;
        }

        // Ask for Player 1's action
        char p1 = get_char ("Player 1, enter s for shoot, r for reload, a for armor, or b for bazooka.\n");

        // Make upcoming text separate from previous text
        int counter2 = 0;
        while (counter2 <= 26)
        {
        printf ("\n");
        counter2 = counter2 + 1;
        }

        // Ask for Player 2's Action
        char p2 = get_char ("Player 2, enter s for shoot, r for reload, a for armor, or b for bazooka.\n");

        // If players do the same action, call on the function below
        if (p1 == p2)
        {
            int results = playerResults (p1, p2);
            if (results == 1)
            {
                printf ("Keep going! Each player loses a bullet.\n");
                Bullets [0] = Bullets [0] - 1;
                Bullets [1] = Bullets [1] - 1;
            }
            // Run through all scenarios
            else if (results == 2)
            {
                printf ("Keep going! Each player gains a bullet.\n");
                Bullets [0] = Bullets [0] + 1;
                Bullets [1] = Bullets [1] + 1;
            }
            else if (results == 3)
            {
                printf ("Keep going! Neither player gains or loses a bullet.\n");
            }
            else if (results == 4)
            {
                printf ("Wow, both players tried to blow each other up. Keep going! Each player loses 5 bullets.\n");
                Bullets [0] = Bullets [0] - 5;
                Bullets [1] = Bullets [1] - 5;
            }
        }
        else if ((p1 == 'b') && (Bullets [0] >= 5))
        {
            printf ("Player 1 Wins!\n");
            Status = Status + 1;
        }
        else if ((p2 == 'b') && (Bullets [1] >= 5))
        {
            printf ("Player 2 Wins!\n");
            Status = Status + 1;
        }
        else if ((Bullets [0] >= 1) && (p1 == 's') && (p2 == 'r'))
        {
            printf ("Player 1 Wins!\n");
            Status = Status + 1;
        }
        else if ((Bullets [1] >= 1) && (p2 == 's') && (p1 == 'r'))
        {
            printf ("Player 2 Wins!\n");
            Status = Status + 1;
        }
        else if ((Bullets [0] >= 1) && (p1 == 's') && (p2 == 'a'))
        {
            printf ("Keep Going! Player 2 has blocked Player 1's shot.\n");
            Bullets [0] = Bullets [0] - 1;
        }
        else if ((Bullets [0] >= 1) && (p2 == 's') && (p1 == 'a'))
        {
            printf ("Keep Going! Player 2 has blocked Player 3's shot.\n");
            Bullets [1] = Bullets [1] - 1;
        }
        else if ((p1 == 'r') && (p2 == 'a'))
        {
            printf ("Keep Going! Player 1 gains a bullet.\n");
            Bullets [0] = Bullets [0] + 1;
        }
        else if ((p2 == 'r') && (p1 == 'a'))
        {
            printf ("Keep Going! Player 2 gains a bullet.\n");
            Bullets [1] = Bullets [1] + 1;
        }
        else if ((p1 == 's') && (Bullets [0] < 1) && (p2 == 'r'))
        {
            printf ("Player 1: Please read the rules carefully. You can't take a shot if you don't have a bullet. Because of that, you have wasted your turn.\n");
            printf ("Player 2 gains a bullet.\n");
            Bullets [1] = Bullets [1] + 1;
        }
        else if ((p1 == 's') && (Bullets [0] < 1) && (p2 == 's') && (Bullets [1] >= 1))
        {
            printf ("Player 2 Wins!\n");
            Status = Status + 1;
        }
        else if ((p1 == 'b') && (Bullets [0] < 5) && (p2 == 'r'))
        {
            printf ("Player 1: Please read the rules carefully. You can't fire a bazooka if you don't have a bullet. Because of that, you have wasted your turn.\n");
            printf ("Player 2 gains a bullet.\n");
            Bullets [1] = Bullets [1] + 1;
        }
        else if ((p1 == 'b') && (Bullets [0] < 5) && (p2 =='s') && (Bullets [1] >= 1))
        {
            printf ("Player 2 Wins!\n");
            Status = Status + 1;
        }
        else if ((p1 == 'b') && (Bullets [0] < 5) && (p2 == 'b') && (Bullets [1] >= 5))
        {
            printf ("Player 2 Wins!\n");
            Status = Status + 1;
        }
               else if ((p2 == 's') && (Bullets [1] < 1) && (p1 == 'r'))
        {
            printf ("Player 2: Please read the rules carefully. You can't take a shot if you don't have a bullet. Because of that, you have wasted your turn.\n");
            printf ("Player 1 gains a bullet.\n");
            Bullets [0] = Bullets [0] + 1;
        }
        else if ((p2 == 's') && (Bullets [1] < 1) && (p1 == 's') && (Bullets [0] >= 1))
        {
            printf ("Player 1 Wins!\n");
            Status = Status + 1;
        }
        else if ((p2 == 'b') && (Bullets [1] < 5) && (p1 == 'r'))
        {
            printf ("Player 2: Please read the rules carefully. You can't fire a bazooka if you don't have a bullet. Because of that, you have wasted your turn.\n");
            printf ("Player 1 gains a bullet.\n");
            Bullets [0] = Bullets [0] + 1;
        }
        else if ((p2 == 'b') && (Bullets [1] < 5) && (p1 =='s') && (Bullets [0] >= 1))
        {
            printf ("Player 1 Wins!\n");
            Status = Status + 1;
        }
        else if ((p2 == 'b') && (Bullets [1] < 5) && (p1 == 'b') && (Bullets [0] >= 5))
        {
            printf ("Player 1 Wins!\n");
            Status = Status + 1;
        }
        else if ((p1 == 's') && (Bullets [0] < 1) && (p2 == 's') && (Bullets [1] < 1))
        {
            printf ("Please read the rules carefully. Both players have wasted their turns.\n");
        }
        else if ((p1 == 's') && (Bullets [0] < 1) && (p2 == 'b') && (Bullets [1] < 5))
        {
            printf ("Please read the rules carefully. Both players have wasted their turns.\n");
        }
        else if ((p2 == 's') && (Bullets [1] < 1) && (p1 == 's') && (Bullets [0] < 1))
        {
            printf ("Please read the rules carefully. Both players have wasted their turns.\n");
        }
        else if ((p2 == 's') && (Bullets [1] < 1) && (p1 == 'b') && (Bullets [0] < 5))
        {
            printf ("Please read the rules carefully. Both players have wasted their turns.\n");
        }
        else if ((p1 == 'b') && (Bullets [0] < 5) && (p2 == 'b') && (Bullets [1] < 5))
        {
            printf ("Please read the rules carefully. Both players have wasted their turns.\n");
        }

        // Allow players to continue when they want
        int c3;
        do
        {
            c3 = get_int ("Please enter 1 to continue: ");
        }
        while (c3 != 1);

        // Make upcoming text separate from previous text only if game is not over
        if (Status == 0)
        {
            int counter3 = 0;
            while (counter3 <= 26)
            {
                printf ("\n");
                counter3 = counter3 + 1;
            }
        }
     }
 }

// Define Function
int playerResults (char a, char b)
{
    // Run through all scenarios
    int outcomes = 0;
    if ((a == 's') && (b == 's'))
    {
        outcomes = outcomes + 1;
    }
    else if ((a == 'r') && (b == 'r'))
    {
        outcomes = outcomes + 2;
    }
    else if ((a == 'a') && (b == 'a'))
    {
        outcomes = outcomes + 3;
    }
    else if ((a == 'b') && (b == 'b'))
    {
        outcomes = outcomes + 4;
    }
    return outcomes;
}
