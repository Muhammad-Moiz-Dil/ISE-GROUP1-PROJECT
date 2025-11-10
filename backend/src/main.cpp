#include <iostream>
#include "../../logs/include/file_io.h"

using namespace std;

// Build Command: g++ -I../../logs/include main.cpp file_io.cpp -o main.exe; if ($?) { .\main.exe }

int main()
{
    // Load the utterances file into utterancesList at the very start
    if (!loadUtterances("C:/Users/Rafay Dil/Desktop/ISE Project/backend/src/output/Utterances.txt"))
    {
        cout << "Chatbot could not load utterances. Exiting." << endl;
        return 1;
    }
    if (!loadLoanPlans("C:/Users/Rafay Dil/Desktop/ISE Project/backend/src/output/Home.txt"))
    {
        cout << "Chatbot could not load home plans. Exiting." << endl;
        return 1;
    }

    cout << "\033[1;36m" // Cyan for header border
         << "=============================================\n";
    cout << "\033[1;32m" // Green for title
         << "           WELCOME TO SMART CHATBOT!        \n";
    cout << "\033[1;36m" // Cyan again for separator
         << "---------------------------------------------\n";
    cout << "\033[1;33m" // Yellow for message line
         << "    Type your message below (X to exit):\n";
    cout << "\033[1;36m" // Cyan for closing border
         << "=============================================\n";
    cout << "\033[0m\n"; // Reset colors

    // Main Chat Loop
    while (true)
    {
        string userInput;
        getline(cin, userInput);

        // Exit condition
        if (userInput == "X" || userInput == "x")
        {
            break;
        }

        // Find a matching response
        cout << uttrObj.getResponse(userInput) << endl;
        getline(cin, userInput);
        //  if users enters x in between selecting the loan type so it exits.
        if (userInput == "X" || userInput == "x")
        {
            break;
        }
        if (userInput == "A") // No use of the small case letter check as in txt files Upper case letters are defined only.
        {
            cout << uttrObj.getResponse(userInput) << endl;
            //  cin.ignore();
            getline(cin, userInput);
            if (userInput == "X" || userInput == "x")
            {
                break;
            }
            if (userInput == "H")
            {
                cout << uttrObj.getResponse(userInput) << endl;
                getline(cin, userInput);
                if (userInput == "X" || userInput == "x")
                {
                    break;
                }
                LoanPlanManagerObj.displayLoanPlan(userInput);
            }
            else if (userInput == "C")
            {
                // Increament from Sir will be expected from sir in near Future.
            }
            else if (userInput == "S")
            {
                // Increament from Sir will be expected from sir in near Future.
            }
            else if (userInput == "P")
            {
                // Increament from Sir will be expected from sir in near Future.
            }
            else
            {
                cout << "Invalid Input." << endl;
            }
        }
    }

    cout << "\n";
    cout << "\033[1;31m" // Bright Red
         << "=============================================\n";
    cout << "          CHATBOT SESSION ENDED!           \n";
    cout << "=============================================\n";
    cout << "\033[0m\n"; // Reset color

    return 0;
}
