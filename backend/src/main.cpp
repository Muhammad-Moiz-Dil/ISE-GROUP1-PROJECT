#include <iostream>
#include "../../logs/include/file_io.h"

using namespace std;

// Build Command (run while in src): g++ -I../../logs/include main.cpp file_io.cpp -o main.exe; if ($?) { .\main.exe }

int main()
{
    // Load the utterances file into utterancesList at the very start
    if (!loadUtterances("output/Utterances.txt"))
    {
        cout << "Chatbot could not load utterances. Exiting." << endl;
        return 1;
    }
    if (!loadLoanPlans("output/Home.txt"))
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
    
    string state = "MAIN_MENU";  // Track current state
    
    while (true) {
        string userInput;
        cout << "=> ";
        getline(cin, userInput);
        
        // Exit check
        if (userInput == "X" || userInput == "x") break;
        
        // Handle based on current state
        if (state == "MAIN_MENU") {
            cout << uttrObj.getResponse(userInput) << endl;
            
            if (userInput == "A") {
                state = "LOAN_CATEGORY";  // Move to next state
            }
            else if (userInput == "H")
            {
                state = "HOME_LOAN_AREA";
            }
        }
        if (state == "LOAN_CATEGORY") {
            if (userInput == "H") {
                cout << uttrObj.getResponse(userInput) << endl;
                state = "HOME_LOAN_AREA";
            }
            else if (userInput == "C" || userInput == "S" || userInput == "P") {
                cout << "Coming soon!" << endl;
                state = "MAIN_MENU";
            }
            else {
                cout << "Invalid input. Please press H, C, S, or P." << endl;
            }
        }
        if (state == "HOME_LOAN_AREA") 
        {
            //cout <<"Moiz";
            string options;
            getline(cin, options);
            if(options == "1")
            {
                userInput = "Area 1";
            }
            else if(options == "2")
            {
                userInput = "Area 2";
            }
             else if(options == "3")
            {
                userInput = "Area 3";
            }
             else if(options == "4")
            {
                userInput = "Area 4";
            }
            else
            {
                cout << "Not a valid Input."<<endl;
                state = "MAIN_MENU";
                continue;
            }
            LoanPlanManagerObj.displayLoanPlan(userInput);
            state = "MAIN_MENU";  // Go back to start
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
