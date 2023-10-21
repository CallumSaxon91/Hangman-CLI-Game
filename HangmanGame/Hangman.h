#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <string>
#include <time.h>

using namespace std;

// function to display a message with optional top and bottom borders
void displayMessage(const string& message, bool showTop = true, bool showBottom = true,
    const string& topStr = " __________________________________",
    const string& bottomStr = " __________________________________") {
    if (showTop) cout << topStr << '\n';
    int leftPadding = (34 - message.length()) / 2;
    cout << '|' << std::string(leftPadding, ' ') << message << std::string(34 - message.length() - leftPadding, ' ') << "|\n";
    if (showBottom) cout << bottomStr << '\n';
}

// function to draw the hangman
void drawHangman(int incorrectGuessCount = 0) {
    if (incorrectGuessCount >= 1) {
        displayMessage("|", false, false);
    }
    else {
        displayMessage("", false, false);
    }
    if (incorrectGuessCount >= 2) {
        displayMessage("|", false, false);
    }
    else {
        displayMessage("", false, false);
    }
    if (incorrectGuessCount >= 3) {
        displayMessage("O", false, false);
    }
    else {
        displayMessage("", false, false);
    }
    if (incorrectGuessCount == 4) {
        displayMessage("/  ", false, false);
    }
    else if (incorrectGuessCount == 5) {
        displayMessage("/| ", false, false);
    }
    else if (incorrectGuessCount >= 6) {
        displayMessage("/|\\", false, false);
    }
    else {
        displayMessage("", false, false);
    }
    if (incorrectGuessCount >= 7) {
        displayMessage("|", false, false);
    }
    else {
        displayMessage("", false, false);
    }
    if (incorrectGuessCount == 8) {
        displayMessage("/", false, false);
    }
    else if (incorrectGuessCount >= 9) {
        displayMessage("/ \\", false, false);
    }
    else {
        displayMessage("", false, false);
    }
    displayMessage("", false, true);
}

// function to display the available letters for guessing
void displayLetters(string input, char from, char to)
{
    // calculate the range of letters to display
    const int range = to - from + 1;
    string s;
    s.reserve(range * 2);
    bitset<256> present;
    // set the bits in the bitset for each letter in the input string
    for (char c : input) present.set(c);
    for (char i = from; i <= to; i++) s += present.test(i) ? "  " : string(1, i) + ' ';
    displayMessage(s, false, false);
}

// function to display the available letters for guessing in three ranges to offer readability
void displayAvailableLetters(string taken)
{
    displayLetters(taken, 'A', 'H');
    displayLetters(taken, 'I', 'Q');
    displayLetters(taken, 'R', 'Z');
}

// this function displays the guessed letters of the word and checks if the player has won
bool displayWordAndCheckWin(const string& word, const string& guessed)
{
    // for each letter in the secret word, add the letter if it has been guessed or add an underscore if it hasn't been guessed
    bool win = true;
    string s;
    for (char c : word)
    {
        if (guessed.find(c) != string::npos)
        {
            s += c;
        }
        else
        {
            s += "_";
            win = false;
        }
        s += " ";
    }
    // display the word with underscores for unguessed letters and spaces between each letter
    displayMessage(s, false);
    // return whether the player has won.
    return win;
}

// this function loads a random secret word from a text file
string loadSecretWord(const string& path) {
    string word;
    vector<string> words;
    ifstream reader(path);
    while (reader >> word) words.push_back(word);
    int randomLine = rand() % words.size();
    word = words.at(randomLine);
        reader.close();// close the file
    // return the randomly chosen secret word
    return word;
}

int triesLeft(const string& word, const string& guessed) {
    int error = 0;
    for (char c : guessed) error += word.find(c) == string::npos;
    return error;
}

// this function displays the losing message when the player has used all their tries
void printLoseMessage(string wordToGuess)
{
    displayMessage("GAME OVER");
    displayMessage("The word was: " + wordToGuess);
}

// this function displays the winning message when the player has correctly guessed the word
void printWinMessage()
{
    displayMessage("CONGRATULATIONS! YOU WON!");
    displayMessage("Press 0 to exit!");
}