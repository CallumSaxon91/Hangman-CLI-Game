#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <time.h>
#include <bitset>
#include "Hangman.h"

int main() {
    srand(time(0));
    string guesses, wordToGuess = loadSecretWord("words.txt");
    int tries = 0;
    bool win = false;

    while (tries < 10) {
        system("cls");
        displayMessage("Welcome to Hangman!");
        drawHangman(tries);
        displayAvailableLetters(guesses);
        displayMessage("Guess the secret word");
        win = displayWordAndCheckWin(wordToGuess, guesses);
        displayMessage("Press 0 to exit!");

        if (win)
            break;

        char x;
        bool validInput;

        do {
            cout << ">";
            cin >> x;

            cin.ignore(1000, '\n'); // this will ignore additional characters input after the first

            if (!isalpha(x)) {
                validInput = false;
                displayMessage("Please enter a valid character!");
            }
            else {
                validInput = true;
            }

            if (isupper(x)) {
                x = tolower(x);
            }

        } while (!validInput || guesses.find(x) != string::npos && (cout << "Letter already guessed, please try again!" << endl));

        guesses += x;
        tries = triesLeft(wordToGuess, guesses);
    }

    if (win)
        printWinMessage();
    else
        printLoseMessage(wordToGuess);

    cin.ignore();
    cin.get();
    return 0;
}