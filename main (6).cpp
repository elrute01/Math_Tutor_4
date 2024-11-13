/*
Section 1 - 9:00 am
Version: 3
Programmer: Elise Ruterbories
URL: https://github.com/elrute01/Math_Tutor_3/blob/main/MathTutor3
Description: This math tutor is fun and easy. It gives random questions 
to the user and makes sure the answer is correct. If incorrect, the 
correct answer is given and the option to have another question is given.
There are levels and every 3 questions answered correctly the level goes up.
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <limits> // For numeric_limits

using namespace std;

// Define Math Types (Addition, Subtraction, Multiplication, Division)
enum MathType {
    ADD = 1,
    SUB,
    MULT,
    DIV
};

// Function to generate random numbers based on the current level
int getRandomNumber(int level) {
    // Difficulty increases as the level increases
    switch (level) {
        case 1: return rand() % 10 + 1;  // Level 1: Range 1-10
        case 2: return rand() % 20 + 1;  // Level 2: Range 1-20
        case 3: return rand() % 30 + 1;  // Level 3: Range 1-30
        case 4: return rand() % 50 + 1;  // Level 4: Range 1-50
        default: return rand() % 50 + 1; // For any level greater than 4
    }
}

void printWelcomeMessage() {
    cout << "*********************************************************" << endl;
    cout << "   __  __       _   _       _____      _   " << endl;
    cout << "  |  \\/  | __ _| |_| |__   |_   _|   _| |_ ___  _ __" << endl;
    cout << "  | |\\/| |/ _` | __| '_ \\    | || | | | __/ _ \\| '__|" << endl;
    cout << "  | |  | | (_| | |_| | | |     | || |_| | || (_) | |" << endl;
    cout << "  |_|  |_|\\__,_|\\__|_| |_|   |_| \\__,_|\\__\\___/|_|" << endl;
    cout << "*********************************************************" << endl;
    cout << "       Welcome to Elise & Jacob's Silly Math Tutor!" << endl;
    cout << "*********************************************************" << endl;
    cout << endl;
}

int main() {
    string userName;
    int leftNum, rightNum;
    MathType mathType;
    char mathSymbol;
    double correctAnswer, userAnswer;
    string userInput;
    int correctCount = 0;  // To track number of correct answers
    int level = 1;         // Start at level 1
    int incorrectAttempts = 0;  // To track incorrect attempts

    srand(static_cast<unsigned int>(time(0)));

    // Print Welcome Message
    printWelcomeMessage();

    // Ask for the user's name
    cout << "Please enter your name: ";
    getline(cin, userName);

    // Main game loop
    do {
        // Display the current level
        cout << "[Level " << level << "]" << endl;

        // Get random numbers based on the current level
        leftNum = getRandomNumber(level);  // Get a random number based on the level
        rightNum = getRandomNumber(level); // Get a random number based on the level

        mathType = static_cast<MathType>(rand() % 4 + 1); // Random math type (1-4)

        // Switch based on the selected math type (addition, subtraction, etc.)
        switch (mathType) {
            case ADD:
                correctAnswer = leftNum + rightNum;
                mathSymbol = '+';
                break;
            case SUB:
                if (leftNum < rightNum) swap(leftNum, rightNum); // Ensure no negative answers in subtraction
                correctAnswer = leftNum - rightNum;
                mathSymbol = '-';
                break;
            case MULT:
                correctAnswer = leftNum * rightNum;
                mathSymbol = '*';
                break;
            case DIV:
                // Prevent division by zero
                while (rightNum == 0) rightNum = getRandomNumber(level);
                correctAnswer = static_cast<double>(leftNum) / rightNum;
                mathSymbol = '/';
                break;
            default:
                cerr << "Invalid math type!" << endl;
                return -1;
        }

        // Ask the math question
        cout << "What is " << leftNum << " " << mathSymbol << " " << rightNum << " = ? ";
        int attemptsLeft = 3;  // Max 3 attempts
        bool correct = false;

        while (attemptsLeft > 0) {       
            while (!(cin >> userAnswer)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number: ";
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Add this line to clear the newline character

            if (userAnswer == correctAnswer) {
                cout << "You're a genius!!" << endl;
                correct = true;
                correctCount++;  // Increment correct answer count
                break;
            } else {
                attemptsLeft--;
                if (attemptsLeft > 0) {
                    cout << "Sorry, that's incorrect. You have " << attemptsLeft << " attempts left. Try again: ";
                } else {
                    cout << "Sorry, that's incorrect. The correct answer is: " << correctAnswer << endl;
                    incorrectAttempts++;  // Increment incorrect attempts
                }
            }
        }

        // Check if the user has answered 3 questions correctly, then level up
        if (correctCount >= 3) {
            level++;  // Level up!
            correctCount = 0;  // Reset the correct answer count
            cout << "Congratulations! You've leveled up to Level " << level << "!" << endl;
        }
        // Check if the user has been incorrect 3 times, then level down
        if (incorrectAttempts >= 3) {
            level--;  // Level down!
            incorrectAttempts = 0;  // Reset incorrect attempts
            cout << "Oops! You've been answering incorrectly. You've leveled down to Level " << level << "!" << endl;
        }

        // Ask if the user wants another question
        bool validInput = false;
        while (!validInput) {
            cout << "Do you want to keep testing your skills? (y-yes | n-no): ";
            getline(cin, userInput);

            // Convert user input to uppercase for consistency
            for (char& c : userInput) c = toupper(c);

            if (userInput == "Y" || userInput == "YES") {
                validInput = true;
            } else if (userInput == "N" || userInput == "NO") {
                validInput = true;
            } else {
                cout << "Invalid input. Please enter 'y' for yes or 'n' for no." << endl;
            }
        }

    } while (userInput == "Y" || userInput == "YES");

    cout << "Thanks for using the Silly Math Tutor! Come back soon!" << endl;

    return 0;
}
