#pragma once

#include <stdbool.h>

void displayUserInput(char *message);
void displayMainMenu(char *message, bool needToClear);
int obtainNumericUserInput();
int *getMostGuessesList(int numberOfGuesses);
void displayMostGuesses();
void displaySettingsMenu(int *minimumValue, int *maximumValue);
int generateRandomNumber(int minimumNumber, int maximumNumber);
void playGame(int minimumValue, int maximumValue, bool cheatModeOn);
