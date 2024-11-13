/*
Section 1 - 9:00 am
Version: 3
Programmer: Elise Ruterbories
URL: https://github.com/elrute01/Math_Tutor_3/blob/main/MathTutor3
Description: This math tutor is fun and easy. It gives random questions 
to the user and makes sure the answer is correct. If incorrect, the 
correct answer is given and the option to have another question is given.
There are levels and every 3 questions answered correctly the level goes up.
At the end of the game, the user is given a report of the level, question, and 
how many  attempts were used per question. There is also a report of the total
questions, total correct, total incorrect, and the average correct answers.
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <limits> // For numeric_limits
#include <vector>  // Include the vector library

using namespace std;

// Define Math Types (Addition, Subtraction, Multiplication, Division)
enum MathType {
    ADD = 1,
    SUB,
    MULT,
    DIV
};

// Structure to store a question and its correct answer
struct MathQuestion {
    int leftNum;
    int rightNum;
    MathType mathType;
    double correctAnswer;
    char mathSymbol;
};

// Structure to store the question details for the summary
struct QuestionAttempt {
    int level;
    string question;
    int attempts;
    bool correct;  // To track if the question was answered correctly
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
    cout << "       Welcome to Elise's Silly Math Tutor!" << endl;
    cout << "*********************************************************" << endl;
    cout << endl;
}

// Function to create a math question based on the level
MathQuestion createMathQuestion(int level) {
    int leftNum = getRandomNumber(level);  // Get a random number based on the level
    int rightNum = getRandomNumber(level); // Get a random number based on the level
    MathType mathType = static_cast<MathType>(rand() % 4 + 1); // Random math type (1-4)

    MathQuestion question;

    // Switch based on the selected math type (addition, subtraction, etc.)
    switch (mathType) {
        case ADD:
            question.correctAnswer = leftNum + rightNum;
            question.mathSymbol = '+';
            break;
        case SUB:
            if (leftNum < rightNum) swap(leftNum, rightNum); // Ensure no negative answers in subtraction
            question.correctAnswer = leftNum - rightNum;
            question.mathSymbol = '-';
            break;
        case MULT:
            question.correctAnswer = leftNum * rightNum;
            question.mathSymbol = '*';
            break;
        case DIV:
            // Prevent division by zero
            while (rightNum == 0) rightNum = getRandomNumber(level);
            question.correctAnswer = static_cast<double>(leftNum) / rightNum;
            question.mathSymbol = '/';
            break;
        default:
            cerr << "Invalid math type!" << endl;
            return question;  // Return an empty question on error
    }

    question.leftNum = leftNum;
    question.rightNum = rightNum;
    question.mathType = mathType;

    return question;
}

int main() {
    string userName;
    double userAnswer;
    string userInput;
    int correctCount = 0;  // To track number of correct answers for each level
    int incorrectCount = 0;  // To track number of incorrect answers for each level
    int totalQuestions = 0;   // To track total number of questions attempted
    int level = 1;            // Start at level 1

    // Variables to store question details for the summary
    vector<QuestionAttempt> summaryAttempts;

    // To track the total number of correct answers across all levels
    int totalCorrectAnswers = 0;

    srand(static_cast<unsigned int>(time(0)));

    // 2D Vector to store questions for each level (vector<vector<MathQuestion>>)
    vector<vector<MathQuestion>> questions;

    // Print Welcome Message
    printWelcomeMessage();

    // Ask for the user's name
    cout << "Please enter your name: ";
    getline(cin, userName);

    // Main game loop
    do {
        // Display the current level
        cout << "[Level " << level << "]" << endl;

        // Generate a new question based on the current level
        MathQuestion currentQuestion = createMathQuestion(level);

        // Store the question in the 2D vector (for this level, we store in a new row)
        if (questions.size() < level) {
            questions.push_back(vector<MathQuestion>()); // Add a new level (row)
        }
        questions[level - 1].push_back(currentQuestion); // Add the current question to the current level

        // Ask the math question
        cout << "What is " << currentQuestion.leftNum << " " 
             << currentQuestion.mathSymbol << " " 
             << currentQuestion.rightNum << " = ? ";

        int attemptsLeft = 3;  // Max 3 attempts
        int attempts = 0;  // To track attempts for this question
        bool correct = false;  // To track if the user answered correctly

        while (attemptsLeft > 0) {
            while (!(cin >> userAnswer)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number: ";
            }

            // Increment attempt count
            attempts++;

            // Check if the user's answer is correct
            if (userAnswer == currentQuestion.correctAnswer) {
                cout << "You're a genius!!" << endl;
                correct = true;  // The user answered correctly
                correctCount++;  // Increment correct answer count for this level
                totalCorrectAnswers++; // Increment total correct answers across all levels
                totalQuestions++; // Increment total question count

                // Store the question data for summary, including the number of attempts
                summaryAttempts.push_back({
                    level, 
                    to_string(currentQuestion.leftNum) + " " + currentQuestion.mathSymbol + " " + to_string(currentQuestion.rightNum), 
                    attempts, 
                    correct
                });
                break;
            } else {
                attemptsLeft--;
                if (attemptsLeft > 0) {
                    cout << "Sorry, that's incorrect. You have " << attemptsLeft << " attempts left. Try again: ";
                } else {
                    cout << "Sorry, that's incorrect. The correct answer is: " 
                         << currentQuestion.correctAnswer << endl;
                    incorrectCount++;     // Increment incorrect answer count for this level
                    totalQuestions++; // Increment total question count

                    // Store the question data for summary, including the number of attempts
                    summaryAttempts.push_back({
                        level, 
                        to_string(currentQuestion.leftNum) + " " + currentQuestion.mathSymbol + " " + to_string(currentQuestion.rightNum), 
                        attempts, 
                        correct
                    });
                }
            }
        }

        // Check if the user has answered 3 questions correctly, then level up
        if (correctCount >= 3) {
            level++;  // Level up!
            correctCount = 0;  // Reset the correct answer count for next level
            cout << "Congratulations! You've leveled up to Level " << level << "!" << endl;
        }

        // Ask if the user wants another question
        bool validInput = false;
        while (!validInput) {
            getline(cin, userInput);

            // Convert user input to uppercase for consistency
            for (char& c : userInput) c = toupper(c);

            if (userInput == "Y" || userInput == "YES") {
                validInput = true;
            } else if (userInput == "N" || userInput == "NO") {
                validInput = true;
            } else {
                cout << "Do you want to continue? Please enter 'y' for yes or 'n' for no." << endl;
            }
        }

    } while (userInput == "Y" || userInput == "YES");

    // Calculate average correct percentage
    double averageCorrect = 0.0;
    if (totalQuestions > 0) {
        averageCorrect = (static_cast<double>(totalCorrectAnswers) / totalQuestions) * 100;
    }

    // Display the Summary Report
    cout << "======================================" << endl;
    cout << "        Summary Report              " << endl;
    cout << "======================================" << endl;
    cout << "Level       Question        Attempts" << endl;
    cout << "——————————————————————————————————————————————" << endl;

    // Display question details in the summary
    for (const auto& attempt : summaryAttempts) {
        cout << attempt.level << "      ";
        cout << attempt.question;
        // Ensure consistent formatting for number of attempts
        cout << "        " << attempt.attempts << endl;
    }

    // Display total correct, incorrect, and average correct percentage
    cout << "------------------------------------" << endl;
    cout << "Total Questions: " << totalQuestions << endl;
    cout << "Total Correct: " << totalCorrectAnswers << endl;
    cout << "Total Incorrect: " << incorrectCount << endl;
    cout << "Average Correct: " << averageCorrect << "%" << endl;

    cout << "Thanks for using the Silly Math Tutor! Come back soon!" << endl;

    return 0;
}
