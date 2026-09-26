#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "guessing-game.h"

#define CLEAR_SCREEN() printf("\033[H\033[J");
#define NUM_MOST_GUESSES 10

void displayUserInput(char *message)
{
    int messageLength = strlen(message);

    printf("──────────────────────────────────────────────────────────────────────\n");
    printf("%s", message);
    printf("──────────────────────────────────────────────────────────────────────\n");
    printf("\033[2A");
    printf("\033[%dC", messageLength);
    fflush(stdout);
}

void displayMainMenu(char *message, bool needToClear)
{
    if (needToClear)
    {
        CLEAR_SCREEN();
    }

    printf("======================================================================\n");
    printf("☆                    Welcome to the Guessing Game!                   ☆\n");
    printf("======================================================================\n\n");
    printf("\t1. Play\n");
    printf("\t2. Settings\n");
    printf("\t3. Most Guesses\n");
    printf("\t4. Exit\n\n");

    if (message != NULL && strcmp(message, "") != 0)
    {
        printf("\n");
        printf("\033[33m");
        printf("%s", message);
        printf("\033[0m");
        displayUserInput("Please select menu option typing its number:\n");
    }
    else
    {
        displayUserInput("Please select menu option typing its number:\n");
    }
}

int obtainNumericUserInput()
{
    int inputStatus, tempValue, selection;

    do
    {
        inputStatus = scanf("%d", &selection);
    } while (inputStatus != 1 && (tempValue = getchar()) != EOF && tempValue != '\n');

    if (inputStatus != 1)
    {
        printf("\nGoodbye!\n");
        exit(0);
    }

    while ((tempValue = getchar()) != '\n' && tempValue != EOF)
        ;

    return selection;
}

void recordGameAnswer(int *answerHistory, int *answerHistoryCount, int answer)
{
    int entriesToShift = (*answerHistoryCount < NUM_MOST_GUESSES) ? *answerHistoryCount : NUM_MOST_GUESSES - 1;

    for (int i = entriesToShift; i > 0; i--)
    {
        answerHistory[i] = answerHistory[i - 1];
    }

    answerHistory[0] = answer;

    if (*answerHistoryCount < NUM_MOST_GUESSES)
    {
        (*answerHistoryCount)++;
    }
}

void displayMostGuesses(int *answerHistory, int answerHistoryCount)
{
    printf("Most Guesses Table (most recent game's answer first)\n\n");

    if (answerHistoryCount == 0)
    {
        printf("No games have been played yet.\n");
    }
    else
    {
        for (int i = 0; i < answerHistoryCount; i++)
        {
            printf("%d. %d\n", i + 1, answerHistory[i]);
        }
    }

    int selection;

    do
    {
        printf("\nTo return to the main menu enter 0: ");
        selection = obtainNumericUserInput();
    } while (selection != 0);
}

void displaySettingsMenu(int *minimumValue, int *maximumValue)
{
    int selection, backToMainMenu = 0;

    while (backToMainMenu == 0)
    {
        printf("\nGuessing Game Settings\n\n");
        printf("1. Set Minimum Value (current value: %d)\n", *minimumValue);
        printf("2. Set Maximum Value (current value: %d)\n", *maximumValue);
        printf("3. Back to Main Menu\n\n");
        displayUserInput("Please enter your selection and hit ENTER (please select 1 to 3):\n");

        selection = obtainNumericUserInput();

        switch (selection)
        {
        case 1:
            printf("\nPlease specify the minimum possible value that can be guessed: ");
            int newMinimumValue = obtainNumericUserInput();

            if (newMinimumValue < *maximumValue && newMinimumValue > 0)
            {
                *minimumValue = newMinimumValue;
            }
            else
            {
                printf("\033[33m");
                printf("Value is invalid - the value must be larger than zero and lower than the current maximum value (%d).\n", *maximumValue);
                printf("\033[0m");
            }
            break;

        case 2:
            printf("\nPlease specify the maximum possible value that can be guessed: ");
            int newMaximumValue = obtainNumericUserInput();

            if (newMaximumValue > *minimumValue)
            {
                *maximumValue = newMaximumValue;
            }
            else
            {
                printf("\033[33m");
                printf("Value is invalid - the maximum value must be larger than the current minimum value (%d).\n", *minimumValue);
                printf("\033[0m");
            }
            break;

        case 3:
            backToMainMenu = 1;
            displayMainMenu("", true);
            break;

        default:
            break;
        }
    }
}

int generateRandomNumber(int minimumNumber, int maximumNumber)
{
    return rand() % (maximumNumber - minimumNumber + 1) + minimumNumber;
}

void playGame(int minimumValue, int maximumValue, bool cheatModeOn, int *answerHistory, int *answerHistoryCount)
{
    int maximumNumberOfGuessesAllowed = 3;
    int playerNumberOfGuesses = 0;
    int currentPlayerAnswer = 0;
    int closeGuessRange = 5;
    int gameWon = 0;
    int correctAnswer = generateRandomNumber(minimumValue, maximumValue);

    recordGameAnswer(answerHistory, answerHistoryCount, correctAnswer);

    for (int i = 0; i < maximumNumberOfGuessesAllowed; i++)
    {
        if (cheatModeOn)
        {
            printf("\033[34m");
            printf("\nCheat mode is enabled - the correct answer is %d.\n", correctAnswer);
            printf("\033[0m");
        }

        printf("\nTry to guess the number! This is attempt %d of %d.\n\n", (playerNumberOfGuesses + 1), maximumNumberOfGuessesAllowed);
        displayUserInput("Please enter your guess:\n");
        currentPlayerAnswer = obtainNumericUserInput();
        playerNumberOfGuesses++;

        if (currentPlayerAnswer == correctAnswer)
        {
            gameWon = 1;
            break;
        }
        else if (currentPlayerAnswer >= (correctAnswer - closeGuessRange) && currentPlayerAnswer <= (correctAnswer + closeGuessRange))
        {
            printf("\nSorry, wrong guess, but you're pretty warm!\n\n");
        }
        else
        {
            printf("\nSorry, that's just wrong!\n\n");
        }
    }

    if (gameWon)
    {
        printf("\nCongratulations, you're an amazing guesser!\n");
        printf("\nYou won the game after %d attempt(s).\n", playerNumberOfGuesses);
    }
    else
    {
        printf("\nBad luck, you lost. Better luck next time!\n");
    }
}

int main(void)
{
    int selection;
    bool exitFlag = false;
    bool cheatModeEnabled = false;
    int minimumValue = 1, maximumValue = 30;
    int answerHistory[NUM_MOST_GUESSES];
    int answerHistoryCount = 0;

    displayMainMenu("", true);

    while (!exitFlag)
    {
        selection = obtainNumericUserInput();
        switch (selection)
        {
        case 0:
            displayMainMenu("", true);
            break;
        case 1:
            playGame(minimumValue, maximumValue, cheatModeEnabled, answerHistory, &answerHistoryCount);
            break;
        case 2:
            displaySettingsMenu(&minimumValue, &maximumValue);
            break;

        case 3:
            CLEAR_SCREEN();
            displayMostGuesses(answerHistory, answerHistoryCount);
            displayMainMenu("", true);
            break;
        case 4:
            exitFlag = true;
            CLEAR_SCREEN();
            printf("You can come back anytime! Good luck!\n");
            break;
        case 999:
            cheatModeEnabled = !cheatModeEnabled;
            displayMainMenu(cheatModeEnabled ? "Cheat mode enabled.\n" : "Cheat mode disabled.\n", true);
            break;
        default:
            displayMainMenu("Hm... I guess that you need ... to enter correct menu option!\n", true);
            break;
        }
    }

    return 0;
}
