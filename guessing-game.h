#pragma once

#include <stdbool.h>

void displayUserInput(char *message);
void displayMainMenu(char *message, bool needToClear);
int obtainNumericUserInput();
void recordGameAnswer(int *answerHistory, int *answerHistoryCount, int answer);
void displayMostGuesses(int *answerHistory, int answerHistoryCount);
void displaySettingsMenu(int *minimumValue, int *maximumValue);
int generateRandomNumber(int minimumNumber, int maximumNumber);
void playGame(int minimumValue, int maximumValue, bool cheatModeOn, int *answerHistory, int *answerHistoryCount);
