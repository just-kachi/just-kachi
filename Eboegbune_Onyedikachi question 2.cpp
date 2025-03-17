#include <iostream>
#include <string>
#include <random>
#include <cstdlib>
using namespace std;

string scramble(const string& word) {
    string scrambled = word;
    for (int i = 0; i < scrambled.length(); i++) {
        int j = rand() % scrambled.length();
        char temp = scrambled[i];
        scrambled[i] = scrambled[j];
        scrambled[j] = temp;
    }
    return scrambled;
}

// Function to get a random correct letter for the "get correct letter" option
char getRandomCorrectLetter(const string& word, const string& revealedLetters) {
    // Reveal a letter that has not been revealed before
    while (true) {
        char letter = word[rand() % word.length()];
        if (revealedLetters.find(letter) == string::npos) {
            return letter;
        }
    }
}

int main() {
    string ch;
    string words[] = {"apple", "watermelon", "terrible", "beginning", "hatred", "time", "petrol", "excuse", "sport", "rust"};
    int score = 0;
    int getCorrectLetterAttempts = 5;
    
    while (true) {
        cout << "Press 'S' to start or 'E' to exit: ";
        getline(cin, ch);

        if (ch == "e" || ch == "E") {
            cout << "Exiting the game." << endl;
            break;
        } else if (ch == "s" || ch == "S") {
            // Loop through each word in the list
            bool skippedWords[10] = {false};  // Track if a word was skipped
            string previousAnswers[10];  // Store previous answers for skipped words

            for (int i = 0; i < 10; i++) {
                string scrambled = scramble(words[i]);
                string userGuess;
                bool wordGuessedCorrectly = false;
                string revealedLetters = "";  // Track which letters have been revealed

                cout << "Scrambled word: " << scrambled << endl;

                while (!wordGuessedCorrectly) {
                    // If the word was skipped previously, allow them to answer again
                    if (skippedWords[i]) {
                        cout << "Your previous answer was: " << previousAnswers[i] << endl;
                    }

                    cout << "Your Guess (or type 'skip' to skip, 'hint' for a hint, 'get correct letter' for help): ";
                    getline(cin, userGuess);

                    // Convert user input to lowercase for case-insensitivity
                    for (auto & c: userGuess) c = tolower(c);

                    if (userGuess == words[i]) {
                        cout << "Correct! You spelt the word correctly." << endl;
                        score++;  // Increase score for correct answer
                        getCorrectLetterAttempts++;  // Increase "GET CORRECT LETTER" attempts
                        wordGuessedCorrectly = true;
                        skippedWords[i] = false;  // Reset skipped status
                    } else if (userGuess == "skip" || userGuess == "SKIP") {
                        // Mark word as skipped, but do not show the correct word yet
                        skippedWords[i] = true;
                        wordGuessedCorrectly = true; // Skip to next word without showing the correct answer
                    } else if (userGuess == "hint") {
                        cout << "Hint: The word has " << words[i].length() << " letters." << endl;
                    } else if (userGuess == "get correct letter" && getCorrectLetterAttempts > 0) {
                        // Reveal a correct letter if attempts are available
                        char revealedLetter = getRandomCorrectLetter(words[i], revealedLetters);
                        revealedLetters += revealedLetter;  // Add to revealed letters
                        cout << "Revealed letter: " << revealedLetter << endl;
                        getCorrectLetterAttempts--;  // Reduce remaining attempts
                    } else if (userGuess == "get correct letter" && getCorrectLetterAttempts == 0) {
                        cout << "You have no 'GET CORRECT LETTER' attempts left." << endl;
                    } else {
                        cout << "Your answer is incorrect. Try again." << endl;
                    }

                    // If attempts for "GET CORRECT LETTER" are exhausted
                    if (getCorrectLetterAttempts == 0) {
                        cout << "You have no 'GET CORRECT LETTER' attempts left." << endl;
                    }
                }

                if (i == 9) {
                    cout << "This is the last word!" << endl;
                }

                // Display the correct answer for skipped words after submission
                if (skippedWords[i]) {
                    cout << "The correct word was: " << words[i] << endl;
                }
            }

            cout << "Game Over. Your final score: " << score << endl;
            
            cout << "Do you want to play again? (Y/N): ";
            getline(cin, ch);
            if (ch == "n" || ch == "N") {
                cout << "Exiting the game." << endl;
                break;
            }
            else if (ch != "y" && ch != "Y") {
                cout << "Invalid input. Exiting the game." << endl;
                break;
            }
        } else {
            cout << "Wrong character entered. Please enter 'S' to start or 'E' to exit." << endl;
        }
    }

    return 0;
}
