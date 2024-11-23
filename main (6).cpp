#include <cstdlib> //for srand and rand
#include <ctime> //for time seedin
#include <iomanip> //for report column alignment
#include <iostream> //for cout and cin
#include <string> //for string
#include <vector> //for vector

using namespace std;


void DisplayGameIntro(){
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

    return;
}

string GetUserName(){
    string userName = "?";
    
    //get the user's name, so we can call them by name later
    cout << "Please enter your name: ";
    getline([&]cin, [&]userName); //handle for spaces in a person's name
    cout << "Welcome " << userName << "!" << endl;

    return userName;
}
        
// this loops until the user enters a valid numeric value and then returns the value
int GetNumericValue(){
    int userAnswer = 0;
    // loop until the user enters numeric data
    while (!(cin >> userAnswer)) {
        cin.clear(); // clear the error flag on cin
        // need to include the limits library to use numeric_limits
        cin.ignore (n:numberic_linits<streamsize>::max(),
                        delim:'\n'); // ignore the last input
        cout << "Invalid input! Please enter a number: ";
    } // end of get userAnswer while loop
    return userAnswer;
}

string AskToPlayAgain (string userName){
    string userInput = "?";
    while (true) {
            cout << "Do you want to play again? (y=yes, n=no): ";
            getline(&cin, &userInput);

            // to lower case the user's input
            for (int i = 0; i < userInput.size(); i++){
                userInput.at(i) = tolower(userInput.at(i));
        } // end of for loop to lower case user's input

        if (userInput == "y"|| userInput == "yes" || userInput == "n" || userInput == "no"){
            break;
        }
        else {
            cout << "Invalid input! Please try again." << endl;
            cout << endl;
        } // end of if (y,yes,n,no)
    } // end of inner while loop to validate user's input

    return userInput;
}

void DisplaySummaryReport (vector<vector<int>> & questions) {
    int mathLevel = 1;
    int leftNum = 0;
    char mathSymbol = '?';
    int rightNum = 0;
    int correctAnswer = 0;
    int attempts = 0;


    int totalCorrect = 0;
    int totalIncorrect = 0;
    
    
    // display summary report
    cout << endl;
    cout << "=================================================" << endl;
    cout << "            Math Tutor Summary Report            " << endl;
    cout << "=================================================" << endl;
    cout << " Level            Question            Attempts" << endl;
    cout << "-------------------------------------------------" << endl;

    totalCorrect = 0;
    totalIncorrect = 0;

    //loop through the 2D vector and display the summary report
    for (int i = 0; i < questions.size(); i++)
        // pull the current rows data
        mathLevel = questions.at(i).at(0);
        leftNum = questions.at(i).at(1);
        mathSymbol = static_cast<char>(questions.at(i).at(2));
        rightNum = questions.at(i).at(3);
        correctAnswer = questions.at(i).at(4);
        attempts = questions.at(i).at(5);

        //display the question
        cout << "    " << setw(2) << right << mathSymbol << " "
             << setw(3) << right << leftNum << " "
             << mathSymbol << " "
             << setw(3) << left << rightNum << " = "
             << setw(5) << right << correctAnswer << " ";

        // display the attempts
        if (attempts == 0) {
            totalIncorrect++;
            cout << "Incorrect" << endl;
        }
        else {
            totalCorrect++;
            cout << "        " << attempts << endl;
        }
    }

    // display the summary stats
    cout << endl;
    cout << "Total Questions: " << setw(4) << right << questions.size() << endl;
    cout << "Total Correct: " << setw(4) << totalCorrect << endl;
    cout << "Total Incorrect: " << setw(4) << totalIncorrect << endl;
    // have to multiply by 100 to get the percentage
    cout << "Average Correct: " << setw(4) << totalCorrect * 100 / questions.size() << "%" << endl;

    return;
}
int main()

//max number of attempts per question before displaying the answer
const int MAX_ATTEMPTS = 3;
//how much to increase or decrease the random number range per level
const int LEVEL_RANGE_CHANGE = 10;

enum MathType {MT_ADD=1, MT_SUB=2, MT_MULT=3, MT_DIV=4};

vector<vector<int>>
    questions; //vector to store the questions and answers

int temp = 0; // uses to swap two values

int leftNum = 0; // first random number between 1 and 10
int rightNum = 0; // second random number between 1 and 10

MathType mathtype = MT_ADD; // default to addition
char mathSymbol = '?'; //[+,-,*,/]

int userAnswer = 0; // user's answer to the question
int correctAnswer = 0; // correct answer to the question

int attempts = 0;
int totalCorrect = 0;
int totalIncorrect = 0;
int mathLevel = 1;
int levelRange = 10;

srand(Seed:time(0)); //seed the random method with the current time

DisplayGameIntro();

userName = GetUserName();

GetNumericValue 

do {
    cout << endl;

    //generate the first random number between 1 and 10
    leftNum = rand() % levelRange + 1;
    rightNum = rand() % levelRange + 1;

    //1=MT_ADD, 2=MT_SUB, 3=MT_MULT, 4=MT_DIV
    mathtype = static_cast<MathType>(rand() % 4 + 1);

    //make sure the left number is greater than the right
    if (leftNum < rightNum){
        temp = leftNum;
        leftNum = rightNum;
        rightNum = temp;
    }
//switch to calculate the correct answer and wich math operator to display
    switch (mathType){
        case MT_ADD:
            correctAnswer = leftNum + rightNum;
            mathSymbol = '+';
            break;
        case MT_SUB:
            correctAnswer = leftNum - rightNum;
            mathSymbol = '-';
            break;
        case MT_MULT:
            correctAnswer = leftNum * rightNum;
            mathSymbol = '*';
            break;
        case MT_DIV:
            correctAnswer = leftNum;
            leftNum *= rightNum;
            mathSymbol = '/';
            break;
        default:
            cout << "Invalid question type: " << mathType << endl;
            cout << "Program ended with an error -1" << endl;
            cout << "Please report this error to Elise Ruterbories" << endl;
            return -1;
    }

    vector<int>row = {mathLevel, leftNum, mathSymbol, rightNum, correctAnswer};

    // for loop to give the user 3 attempts
    for (int i = 1; i <= MAX_ATTEMPTS; i++)
        //prompt the user to answer a math question and get the user's answer
        cout << "[Level #" << mathLevel << "] " << userName << ", what does " << leftNum << mathSymbol << rightNum << "= ";


        userAnswer = GetNumericValue();
    
    // if userAnswer is correct then add to the correct counrter, display correct message and break out of the for loop
    if (userAnswer == correctAnswer) {
        totalCorrect++;
        row.push_back(i);
        cout << "That answer is correct!" << endl;
        break;
    }
        else {
            //if the user is out of attempts
            if (i==3){
                totalIncorrect++;
                row.push_back(0);
                cout << "Sorry, you are out of attempts." << endl;
                cout << "The correct answer is " << correctAnswer << endl;
            }
            else {
                cout << "Sorry, that answer is incorrect." << endl;
                cout << "You have " << MAX_ATTEMPTS - i << " attempts left." << endl;
                        << endl;
                } // end if last attempt
            } // end if correct answer
        } // end of for loop
        cout << endl;

        questions.push_back(row);

        if (totalCorrect ==3) {
            mathLevel++;
            totalCorrect = 0;
            totalIncorrect = 0;
            levelRange += LEVEL_RANGE_CHANGE;
            cout << "Congratulations! You leveled up to Level " << mathLevel << endl;
            cout << "You now have " << levelRange << " numbers to work with." << endl;
            cout << endl;
        }
        else if (totalIncorrect == 3 && mathLevel > 1){
            mathLevel--;
            totalCorrect = 0;
            totalIncorrect = 0;
            levelRange -= LEVEL_RANGE_CHANGE;
            cout << "Sorry :( You are leveled down to Level " << mathLevel << endl;
            cout << "You now have " << levelRange << " numbers to work with." << endl;
            cout << endl;
        }

        getline(&cin, &userInput); // clearing the newline from the input buffer

userInput = AskToPlayAgain(userName);

} while (userInput == "y" || userInput == "yes");

DisplaySummaryReport(&questions);

return 0;
}
