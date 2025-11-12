#include "../../logs/include/chatbot.h"
#include "../../logs/include/file_io.h"
#include "../../logs/include/utils.h"
#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::getline;

void runChatbot()
{
    displayWelcomeHeader();

    string state = "MAIN_MENU";
    string currentArea = "";  // Track which area user is viewing

    while (true)
    {
        string userInput;
        cout << ">> ";
        getline(cin, userInput);

        if (userInput == "X" || userInput == "x")
            break;

        string lowerInput = toLower(userInput);

        if (state == "MAIN_MENU")
        {
            handleMainMenu(userInput, lowerInput, state);
        }
        else if (state == "LOAN_CATEGORY")
        {
            handleLoanCategory(userInput, lowerInput, state);
        }
        else if (state == "HOME_LOAN_AREA")
        {
            handleHomeLoanArea(userInput, lowerInput, state, currentArea);
        }
        else if (state == "VIEW_MONTHLY_INSTALLMENTS")
        {
            handleViewMonthlyInstallments(userInput, lowerInput, state, currentArea);
        }
    }

    displayGoodbyeFooter();
}

void handleMainMenu(string userInput, string lowerInput, string &state)
{
    cout << uttrObj.getResponse(lowerInput) << endl;

    if (userInput == "A" || userInput == "a")
    {
        state = "LOAN_CATEGORY";
    }
    else if (userInput == "H" || userInput == "h")
    {
        state = "HOME_LOAN_AREA";
    }
}

void handleLoanCategory(string userInput, string lowerInput, string &state)
{
    cout << uttrObj.getResponse(lowerInput) << endl;

    if (userInput == "H" || userInput == "h")
    {
        state = "HOME_LOAN_AREA";
    }
    else if (userInput == "C" || userInput == "c" ||
             userInput == "S" || userInput == "s" ||
             userInput == "P" || userInput == "p")
    {
        cout << "Coming soon! Let's get you back to the main menu." << endl;
        state = "MAIN_MENU";
    }
    else if (userInput == "A" || userInput == "a")
    {
        return;
    }
}

void handleHomeLoanArea(string userInput, string lowerInput, string &state, string &currentArea)
{
    if (userInput == "1")
    {
        currentArea = "Area 1";
        int planCount = LoanPlanManagerObj.getPlanCount(currentArea);
        
        if (planCount > 0)  // ✅ Check if area exists
        {
            LoanPlanManagerObj.displayLoanPlan(currentArea);
            cout << "\nWould you like to view monthly installments for any plan?\n";
            cout << "(Enter plan number 1-" << planCount << ", or A to return to main menu)\n";
            state = "VIEW_MONTHLY_INSTALLMENTS";
        }
        else
        {
            cout << "No such area found." << endl;
            state = "MAIN_MENU";  // Return to main menu
        }
    }
    else if (userInput == "2")
    {
        currentArea = "Area 2";
        int planCount = LoanPlanManagerObj.getPlanCount(currentArea);
        
        if (planCount > 0)
        {
            LoanPlanManagerObj.displayLoanPlan(currentArea);
            cout << "\nWould you like to view monthly installments for any plan?\n";
            cout << "(Enter plan number 1-" << planCount << ", or A to return to main menu)\n";
            state = "VIEW_MONTHLY_INSTALLMENTS";
        }
        else
        {
            cout << "No such area found." << endl;
            state = "MAIN_MENU";
        }
    }
    else if (userInput == "3")
    {
        currentArea = "Area 3";
        int planCount = LoanPlanManagerObj.getPlanCount(currentArea);
        
        if (planCount > 0)
        {
            LoanPlanManagerObj.displayLoanPlan(currentArea);
            cout << "\nWould you like to view monthly installments for any plan?" << endl;
            cout << "(Enter plan number 1-" << planCount << ", or A to return to main menu)" << endl;
            state = "VIEW_MONTHLY_INSTALLMENTS";
        }
        else
        {
            cout << "No such area found." << endl;
            state = "MAIN_MENU";
        }
    }
    else if (userInput == "4")
    {
        currentArea = "Area 4";
        int planCount = LoanPlanManagerObj.getPlanCount(currentArea);
        
        if (planCount > 0)
        {
            LoanPlanManagerObj.displayLoanPlan(currentArea);
            cout << "\nWould you like to view monthly installments for any plan?" << endl;
            cout << "(Enter plan number 1-" << planCount << ", or A to return to main menu)" << endl;
            state = "VIEW_MONTHLY_INSTALLMENTS";
        }
        else
        {
            cout << "No such area found." << endl;
            state = "MAIN_MENU";
        }
    }
    else
    {
        bool isNumeric = true;
        for (char c : userInput)
        {
            if (!isdigit(c))
            {
                isNumeric = false;
                break;
            }
        }

        if (isNumeric && userInput.length() > 0)
        {
            cout << "You probably meant to select from 1-4. Please try again." << endl;
        }
        else
        {
            cout << uttrObj.getResponse(lowerInput) << endl;
        }
    }
}

void handleViewMonthlyInstallments(string userInput, string lowerInput, string &state, string &currentArea)
{
    int planCount = LoanPlanManagerObj.getPlanCount(currentArea);
    
    if (userInput == "A" || userInput == "a")
    {
        state = "MAIN_MENU";
        cout << uttrObj.getResponse(lowerInput) << endl;
        return;
    }
    
    // Check if input is a valid plan number
    bool isNumeric = true;
    for (char c : userInput)
    {
        if (!isdigit(c))
        {
            isNumeric = false;
            break;
        }
    }
    
    if (isNumeric && userInput.length() > 0)
    {
        int planChoice = stoi(userInput);
        if (planChoice >= 1 && planChoice <= planCount)
        {
            LoanPlanManagerObj.displayMonthlyInstallment(currentArea, planChoice - 1);
            // Ask if they want to see another
            cout << "View another plan? (Enter plan number 1-" << planCount  << ", or A to return to main menu)" << endl;
        }
        else
        {
            cout << "You probably meant to select from 1-" << planCount << ". Please try again." << endl;
        }
    }
    else
    {
        cout << uttrObj.getResponse(lowerInput) << endl;
    }
}


void displayWelcomeHeader()
{
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
}

void displayGoodbyeFooter()
{
    cout << "\n";
    cout << "\033[1;31m" // Bright Red
         << "=============================================\n";
    cout << "          CHATBOT SESSION ENDED!           \n";
    cout << "=============================================\n";
    cout << "\033[0m\n"; // Reset color
}