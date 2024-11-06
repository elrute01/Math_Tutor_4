#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <vector>   // Initializing vector

using namespace std;

const int numAttempts = 3;
const int maxCorrect = 3; // Number of correct answers to level up

// Enum for math operations
enum MathOperation {
    Addition = 1,
    Subtraction,
    Multiplication,
    Division,
};

// Structure to store each question's details
struct Question {
    string questionText;   // The question (e.g., "What is 3 + 5?")
    int correctAnswer;     // The correct answer to the question
    int userAnswer;        // The user's answer
    bool isCorrect;        // Whether the user got the answer correct
};

// Function to ask a question and check answers
void askQuestion(int randomNumL, int randomNumR, char mathSymbol, int cAnswer, int& correct, int& incorrect, int& mathLevel, const string& userName, vector<Question>& questionHistory) {
    int answer = 0;
    bool answeredCorrectly = false;

    // Try to get a valid answer
    for (int i = 0; i < numAttempts; i++) {
        cout << "[Level " << mathLevel << "] " << userName << ", what does " << randomNumL << " " << mathSymbol << " " << randomNumR << " = ";

        // Input validation for numeric input
        while (!(cin >> answer)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number: ";
        }

        if (answer == cAnswer) {
            correct++;
            cout << "Correct!" << endl;
            answeredCorrectly = true;
            break;
        } else {
            cout << "Wrong! ";
            if (i < numAttempts - 1) {
                cout << "You have " << numAttempts - 1 - i << " attempts left." << endl;
            } else {
                cout << "The correct answer was: " << cAnswer << endl;
                incorrect++;
                mathLevel = max(1, mathLevel - 1); // Ensures mathLevel doesn't go below 1
            }
        }
    }

    // Save the question, user's answer, and correctness to the history
    Question q;
    q.questionText = to_string(randomNumL) + " " + mathSymbol + " " + to_string(randomNumR);
    q.correctAnswer = cAnswer;
    q.userAnswer = answer;
    q.isCorrect = answeredCorrectly;
    questionHistory.push_back(q);  // Add to the question history
}

// Function to print a summary of all questions asked
void printSummary(const vector<Question>& questionHistory) {
    cout << "*** Summary of your math quiz ***" << endl;;
    for (const auto& q : questionHistory) {
        cout << q.questionText << " = " << q.correctAnswer;
        cout << "Your answer: " << q.userAnswer << endl;
        cout << (q.isCorrect ? " (Correct)" : " (Incorrect)") << endl;
    }
}

int main() {
    string userName;
    int cAnswer = 0;
    int tempNum = 0;
    char mathSymbol = '?';
    int correct = 0;
    int incorrect = 0;
    string userInput;
    int mathLevel = 1; // Start at level 1

    // Vector to store all questions and answers
    vector<Question> questionHistory;

    // ASCII art for welcome screen
    cout << "*********************************************************" << endl;
    cout << "     __  __       _   _       _____      _ " << endl;
    cout << "    |  \\/  | __ _| |_| |__   |_   _|   _| |_ ___  _ __ " << endl;
    cout << "    | |\\/| |/ _` | __| '_ \\    | || | | | __/ _ \\| '__|" << endl;
    cout << "    | |  | | (_| | |_| | | |   | || |_| | || (_) | |" << endl;
    cout << "    |_|  |_|\\__,_|\\__|_| |_|   |_| \\__,_|\\__\\___/|_|" << endl;
    cout << endl;
    cout << "*********************************************************" << endl;
    cout << "*      Welcome to the Silly Simple Math Tutor           *" << endl;
    cout << "*********************************************************" << endl;

    cout << "Fun math facts: " << endl;
    cout << "    *Math teachers have problems." << endl;
    cout << "    *Math is the only subject that counts" << endl;
    cout << "    *If it seems easy, you're doing it wrong" << endl;
    cout << "    *It's all fun and games until someone divides by zero" << endl;
    cout << "*********************************************************" << endl;

    // Gets user name
    cout << "Please enter your name: ";
    getline(cin, userName);
    cout << "Hello " << userName << "!" << endl;
    cout << "Let's do some math!" << endl;

    // Main loop for the game
    do {
        // Used to get a random number depending on time
        srand(time(NULL));

        // Left random number 1-10
        int randomNumL = rand() % (10 * mathLevel) + 1;

        // Right random number 1-10
        int randomNumR = rand() % (10 * mathLevel) + 1;

        // Decides if add, sub, multi, divide
        MathOperation mathType = static_cast<MathOperation>(rand() % 4 + 1);

        // Switch based on math type
        switch (mathType) {
            case Addition:
                cAnswer = randomNumL + randomNumR;
                mathSymbol = '+';
                break;
            case Subtraction:
                if (randomNumL < randomNumR) {
                    tempNum = randomNumL;
                    randomNumL = randomNumR;
                    randomNumR = tempNum;
                }
                cAnswer = randomNumL - randomNumR;
                mathSymbol = '-';
                break;
            case Multiplication:
                cAnswer = randomNumL * randomNumR;
                mathSymbol = '*';
                break;
            case Division:
                randomNumR = rand() % 9 + 1; // randomNumR can be from 1 to 9
                randomNumL = randomNumR * (rand() % 10 + 1); // randomNumL is a multiple of randomNumR
                cAnswer = randomNumL / randomNumR;
                mathSymbol = '/';
                break;
            default:
                cout << "Error -1! Contact Ellie Ruterbories or Trey Miller" << endl;
                return -1;
        }

        // Ask the question
        askQuestion(randomNumL, randomNumR, mathSymbol, cAnswer, correct, incorrect, mathLevel, userName, questionHistory);

        // Level up or down logic
        if (correct >= maxCorrect) {
            mathLevel++;
            cout << "Congratulations! You've leveled up to Level " << mathLevel << "!" << endl;
            correct = 0;  // Reset correct answers count when leveling up
        }

        // Ask if the user wants to continue
        cin.ignore(); // Clear the input buffer
        cout << "Do you want to continue? (y/n): ";
        getline(cin, userInput);
        for (char& c : userInput) c = tolower(c);

    } while (userInput == "yes" || userInput == "y");

    // Print the summary of all questions
    printSummary(questionHistory);

    // Fun outro messages
    cout << endl << endl;
    cout << "Since this was the best tutor ever, feel free to stick around for the free trial!" << endl;
    cout << endl;
    cout << "If you are interested, go to www.mysillymathtutor.com" << endl;
    cout << endl;
    cout << " or call 1-800-(SILMATH) for more information." << endl;
    cout << endl;
    cout << "Thank you for using my program" << endl; 

  return 0;
}
