#include "../../logs/include/chatbot.h"
#include "../../logs/include/file_io.h"
#include "../../logs/include/loan_plan.h"
#include "../../logs/include/car.h"
#include "../../logs/include/utils.h"
#include "../../logs/include/application.h"
#include "../../logs/include/scooter.h"
#include <iostream>
#include <string>
#include <fstream>

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::ifstream;
using std::string;

void runChatbot()
{
    displayWelcomeHeader();

    string state = "MAIN_MENU";
    string currentArea = "";
    string currentCarMake = "";
    string currentScooterMake = "";

    while (true)
    {
        // Check for action states that don't need input
        if (state == "SUBMIT_APPLICATION")
        {
            handleApplicationSubmission(state, currentArea);
            continue;
        }
        else if (state == "QUERY_APPLICATIONS")
        {
            handleQueryApplications(state);
            continue;
        }

        // Now get input for interactive states
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
        else if (state == "CAR_LOAN")
        {
            handleCarLoan(userInput, lowerInput, state, currentCarMake);
        }
        else if (state == "SCOOTER_LOAN_AREA")
        {
            handleScooterLoan(userInput, lowerInput, state, currentScooterMake);
        }
        else if (state == "VIEW_CAR_MONTHLY_INSTALLMENTS")
        {
            handleViewCarMonthlyInstallments(userInput, lowerInput, state, currentCarMake);
        }
        else if(state == "VIEW_SCOOTER_MONTHLY_INSTALLMENTS")
        {
            handleViewScooterMonthlyInstallments(userInput, lowerInput, state, currentScooterMake);
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
    else if (userInput == "C" || userInput == "c")
    {
        state = "CAR_LOAN";
    }
    else if (userInput == "S" || userInput == "s")
    {
        state = "SCOOTER_LOAN_AREA";
    }
    else if (userInput == "3")
    {
        state = "SUBMIT_APPLICATION";
    }
    else if (userInput == "4")
    {
        state = "QUERY_APPLICATION";
    }
}
void handleScooterLoan(string &userInput, string &lowerInput, string &state,string &currentScooterMake)
{
    if (userInput == "1")
    {
        currentScooterMake = "Make 1";
        int planCount = ScooterPlanManagerObj.getPlanCount(currentScooterMake);
        
        if (planCount > 0)
        {
            ScooterPlanManagerObj.displayScooterPlan(currentScooterMake);
            cout << "\nWould you like to view monthly installments for any plan?\n";
            cout << "(Enter plan number 1-" << planCount << ", or A to return to main menu)\n";
            state = "VIEW_SCOOTER_MONTHLY_INSTALLMENTS";
        }
        else
        {
            cout << "No such make found." << endl;
            state = "MAIN_MENU";
        }
    }
    else if (userInput == "2")
    {
        currentScooterMake = "Make 2";
        int planCount = CarPlanManagerObj.getPlanCount(currentScooterMake);
        
        if (planCount > 0)
        {
            CarPlanManagerObj.displayCarPlan(currentScooterMake);
            cout << "\nWould you like to view monthly installments for any plan?\n";
            cout << "(Enter plan number 1-" << planCount << ", or A to return to main menu)\n";
            state = "VIEW_SCOOTER_MONTHLY_INSTALLMENTS";
        }
        else
        {
            cout << "No such make found." << endl;
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
            cout << "You probably meant to select from 1-2. Please try again." << endl;
        }
        else
        {
            cout << uttrObj.getResponse(lowerInput) << endl;
        }
    }
}
void handleLoanCategory(string userInput, string lowerInput, string &state)
{
    cout << uttrObj.getResponse(lowerInput) << endl;

    if (userInput == "H" || userInput == "h")
    {
        state = "HOME_LOAN_AREA";
    }
    else if (userInput == "C" || userInput == "c")
    {
        state = "CAR_LOAN";
    }
    else if(userInput == "S" || userInput == "s")
    {
        state = "SCOOTER_LOAN_AREA";
    }
    else if (userInput == "A" || userInput == "a")
    {
        return;
    }
}

void handleCarLoan(string &userInput, string &lowerInput, string &state, string &currentCarMake)
{    
    if (userInput == "1")
    {
        currentCarMake = "Make 1";
        int planCount = CarPlanManagerObj.getPlanCount(currentCarMake);
        
        if (planCount > 0)
        {
            CarPlanManagerObj.displayCarPlan(currentCarMake);
            cout << "\nWould you like to view monthly installments for any plan?\n";
            cout << "(Enter plan number 1-" << planCount << ", or A to return to main menu)\n";
            state = "VIEW_CAR_MONTHLY_INSTALLMENTS";
        }
        else
        {
            cout << "No such make found." << endl;
            state = "MAIN_MENU";
        }
    }
    else if (userInput == "2")
    {
        currentCarMake = "Make 2";
        int planCount = CarPlanManagerObj.getPlanCount(currentCarMake);
        
        if (planCount > 0)
        {
            CarPlanManagerObj.displayCarPlan(currentCarMake);
            cout << "\nWould you like to view monthly installments for any plan?\n";
            cout << "(Enter plan number 1-" << planCount << ", or A to return to main menu)\n";
            state = "VIEW_CAR_MONTHLY_INSTALLMENTS";
        }
        else
        {
            cout << "No such make found." << endl;
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
            cout << "You probably meant to select from 1-2. Please try again." << endl;
        }
        else
        {
            cout << uttrObj.getResponse(lowerInput) << endl;
        }
    }
}

void handleHomeLoanArea(string userInput, string lowerInput, string &state, string &currentArea)
{
    if (userInput == "1")
    {
        currentArea = "Area 1";
        int planCount = LoanPlanManagerObj.getPlanCount(currentArea);

        if (planCount > 0) // Check if area exists
        {
            LoanPlanManagerObj.displayLoanPlan(currentArea);
            cout << "\nWould you like to view monthly installments for any plan?\n";
            cout << "(Enter plan number 1-" << planCount << ", or A to return to main menu)\n";
            state = "VIEW_MONTHLY_INSTALLMENTS";
        }
        else
        {
            cout << "No such area found." << endl;
            state = "MAIN_MENU"; // Return to main menu
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
void handleViewScooterMonthlyInstallments(string userInput, string  lowerInput, string &state,string &currentMake)
{
    userInput = trim(userInput); 
    lowerInput = toLower(userInput); 
    
    int planCount = ScooterPlanManagerObj.getPlanCount(currentMake);

    // Check if user wants to return to main menu
    if (userInput == "A" || userInput == "a")
    {
        state = "MAIN_MENU";
        cout << uttrObj.getResponse(lowerInput) << endl;
        return;
    }

    // Check if user wants to submit application
    if (userInput == "S" || userInput == "s")
    {
        state = "SUBMIT_APPLICATION";
        return;
    }

    // Check if input is a valid plan number
    bool isNumeric = true;
    bool hasNegativeSign = false;

    // Check for negative sign at start
    if (!userInput.empty() && userInput[0] == '-')
    {
        hasNegativeSign = true;
    }

    // Check if all characters (after optional negative sign) are digits
    for (int i = (hasNegativeSign ? 1 : 0); i < userInput.length(); i++)
    {
        if (!isdigit(userInput[i]))
        {
            isNumeric = false;
            break;
        }
    }

    // If it's a number (positive or negative)
    if (isNumeric && userInput.length() > 0 && (hasNegativeSign || isdigit(userInput[0])))
    {
        int planChoice = stoi(userInput);

        if (planChoice >= 1 && planChoice <= planCount)
        {
            ScooterPlanManagerObj.displayMonthlyInstallment(currentMake, planChoice - 1);

            cout << "\nWhat would you like to do next?" << endl;
            cout << " S - Submit loan application" << endl;
            cout << " (Enter plan number 1-" << planCount << " to view another)" << endl;
            cout << " A - Return to main menu" << endl;
        }
        else
        {
            cout << "You probably meant to select from 1-" << planCount << ". Please try again." << endl;
        }
    }
    else
    {
        // Non-numeric input
        cout << uttrObj.getResponse(lowerInput) << endl;
    }
}
void handleViewCarMonthlyInstallments(string userInput, string lowerInput, string &state, string &currentMake)
{
    userInput = trim(userInput); 
    lowerInput = toLower(userInput); 
    
    int planCount = CarPlanManagerObj.getPlanCount(currentMake);

    // Check if user wants to return to main menu
    if (userInput == "A" || userInput == "a")
    {
        state = "MAIN_MENU";
        cout << uttrObj.getResponse(lowerInput) << endl;
        return;
    }

    // Check if user wants to submit application
    if (userInput == "S" || userInput == "s")
    {
        state = "SUBMIT_APPLICATION";
        return;
    }

    // Check if input is a valid plan number
    bool isNumeric = true;
    bool hasNegativeSign = false;

    // Check for negative sign at start
    if (!userInput.empty() && userInput[0] == '-')
    {
        hasNegativeSign = true;
    }

    // Check if all characters (after optional negative sign) are digits
    for (int i = (hasNegativeSign ? 1 : 0); i < userInput.length(); i++)
    {
        if (!isdigit(userInput[i]))
        {
            isNumeric = false;
            break;
        }
    }

    // If it's a number (positive or negative)
    if (isNumeric && userInput.length() > 0 && (hasNegativeSign || isdigit(userInput[0])))
    {
        int planChoice = stoi(userInput);

        if (planChoice >= 1 && planChoice <= planCount)
        {
            CarPlanManagerObj.displayMonthlyInstallment(currentMake, planChoice - 1);

            cout << "\nWhat would you like to do next?" << endl;
            cout << " S - Submit loan application" << endl;
            cout << " (Enter plan number 1-" << planCount << " to view another)" << endl;
            cout << " A - Return to main menu" << endl;
        }
        else
        {
            cout << "You probably meant to select from 1-" << planCount << ". Please try again." << endl;
        }
    }
    else
    {
        // Non-numeric input
        cout << uttrObj.getResponse(lowerInput) << endl;
    }
}

void handleViewMonthlyInstallments(string userInput, string lowerInput, string &state, string &currentArea)
{
    userInput = trim(userInput);
    lowerInput = toLower(userInput); // Recalculate lowerInput after trim
    int planCount = LoanPlanManagerObj.getPlanCount(currentArea);

    // Check if user wants to return to main menu
    if (userInput == "A" || userInput == "a")
    {
        state = "MAIN_MENU";
        cout << uttrObj.getResponse(lowerInput) << endl;
        return;
    }

    // Check if user wants to submit application
    if (userInput == "S" || userInput == "s")
    {
        state = "SUBMIT_APPLICATION";
        return;
    }

    // Check if input is a valid plan number
    bool isNumeric = true;
    bool hasNegativeSign = false;

    // Check for negative sign at start
    if (!userInput.empty() && userInput[0] == '-')
    {
        hasNegativeSign = true;
    }

    // Check if all characters (after optional negative sign) are digits
    for (int i = (hasNegativeSign ? 1 : 0); i < userInput.length(); i++)
    {
        if (!isdigit(userInput[i]))
        {
            isNumeric = false;
            break;
        }
    }

    // If it's a number (positive or negative)
    if (isNumeric && userInput.length() > 0 && (hasNegativeSign || isdigit(userInput[0])))
    {
        int planChoice = stoi(userInput);

        if (planChoice >= 1 && planChoice <= planCount)
        {
            LoanPlanManagerObj.displayMonthlyInstallment(currentArea, planChoice - 1);

            cout << "\nWhat would you like to do next?" << endl;
            cout << " S - Submit loan application" << endl;
            cout << " (Enter plan number 1-" << planCount << " to view another)" << endl;
            cout << " A - Return to main menu" << endl;
        }
        else
        {
            cout << "You probably meant to select from 1-" << planCount << ". Please try again." << endl;
        }
    }
    else
    {
        // Non-numeric input
        cout << uttrObj.getResponse(lowerInput) << endl;
    }
}

void displayWelcomeHeader()
{
    cout << "\033[1;36m" // Cyan for header border
         << "=============================================\n";
    cout << "\033[1;32m" // Green for title
         << "           WELCOME TO THE CHATBOT!        \n";
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

// ============================================================================
// NEW FUNCTIONS FOR INCREMENT 2
// ============================================================================

void handleApplicationSubmission(string &state, string &currentArea)
{
    Application newApp;
    string input;

    cout << "\n\033[1;33m";
    cout << "=============================================\n";
    cout << "       LOAN APPLICATION FORM" << endl;
    cout << "=============================================\n";
    cout << "You are applying for: " << currentArea << " Loan" << endl;
    cout << "=============================================\n";
    cout << "Type 'X' at any time to cancel and return to main menu\n\n";
    cout << "IMPORTANT: Before starting, prepare your documents:\n";
    cout << "1. Save files in: output/application_documents/\n";
    cout << "2. Use naming format: YourCNIC_FileType.extension\n";
    cout << "   Example: 3520212345678_CNIC_FRONT.jpg\n";
    cout << "=============================================\n";
    cout << "\033[0m\n";

    // SECTION 1: Personal Information
    cout << "\033[1;36mPERSONAL INFORMATION:\033[0m\n\n";

    // CNIC
    while (true)
    {
        cout << "Full Name: ";
        getline(cin, input);
        input = trim(input);

        if (input == "X" || input == "x")
        {
            cout << "\nApplication canceled. Returning to main menu.\n";
            state = "MAIN_MENU";
            return;
        }

        if (input.empty())
        {
            cout << "Error: Name cannot be empty. Please enter your full name.\n";
            continue;
        }

        if (!isValidName(input))
        {
            bool allDigits = true;
            for (char c : input)
            {
                if (!isdigit(c) && !isspace(c))
                {
                    allDigits = false;
                    break;
                }
            }

            if (allDigits)
            {
                cout << "Error: Name cannot contain only numbers. Please enter a valid name.\n";
            }
            else
            {
                cout << "Error: Name contains invalid characters. Please use only letters, spaces, hyphens, and apostrophes.\n";
            }
            continue;
        }

        newApp.setFullName(input);
        break;
    }

    // Father's Name
    while (true)
    {
        cout << "Father's Name: ";
        getline(cin, input);
        input = trim(input);

        if (input == "X" || input == "x")
        {
            cout << "\nApplication canceled. Returning to main menu.\n";
            state = "MAIN_MENU";
            return;
        }

        if (input.empty())
        {
            cout << "Error: Father's name cannot be empty.\n";
            continue;
        }

        if (!isValidName(input))
        {
            cout << "Error: Invalid name format.\n";
            continue;
        }

        newApp.setFathersName(input);
        break;
    }

    // Postal Address
    while (true)
    {
        cout << "Postal Address: ";
        getline(cin, input);
        input = trim(input);

        if (input == "X" || input == "x")
        {
            cout << "\nApplication canceled. Returning to main menu.\n";
            state = "MAIN_MENU";
            return;
        }

        if (input.empty())
        {
            cout << "Error: Address cannot be empty.\n";
            continue;
        }

        newApp.setPostalAddress(input);
        break;
    }

    // Contact Number
    while (true)
    {
        cout << "Contact Number (03xxxxxxxxx): ";
        getline(cin, input);
        input = trim(input);

        if (input == "X" || input == "x")
        {
            cout << "\nApplication canceled. Returning to main menu.\n";
            state = "MAIN_MENU";
            return;
        }

        if (!isValidContact(input))
        {
            if (input.length() != 11)
            {
                cout << "Error: Contact must be 11 digits. Please try again.\n";
            }
            else if (input[0] != '0' || input[1] != '3')
            {
                cout << "Error: Contact must start with 03. Please try again.\n";
            }
            else
            {
                cout << "Error: Contact must contain only numbers. Please try again.\n";
            }
            continue;
        }

        newApp.setContact(input);
        break;
    }

    // Email Address
    while (true)
    {
        cout << "Email Address: ";
        getline(cin, input);
        input = trim(input);

        if (input == "X" || input == "x")
        {
            cout << "\nApplication canceled. Returning to main menu.\n";
            state = "MAIN_MENU";
            return;
        }

        if (!isValidEmail(input))
        {
            if (input.find('@') == string::npos)
            {
                cout << "Error: Email must contain '@'. Please enter a valid email.\n";
            }
            else if (input.find(' ') != string::npos)
            {
                cout << "Error: Email cannot contain spaces. Please try again.\n";
            }
            else
            {
                cout << "Error: Email must have a domain (e.g., @gmail.com). Please try again.\n";
            }
            continue;
        }

        input = toLower(input);
        newApp.setEmail(input);
        break;
    }

    // CNIC
    while (true)
    {
        cout << "CNIC (13 digits, no dashes): ";
        getline(cin, input);
        input = trim(input);

        if (input == "X" || input == "x")
        {
            cout << "\nApplication canceled. Returning to main menu.\n";
            state = "MAIN_MENU";
            return;
        }

        // Check for dashes or spaces FIRST
        if (input.find('-') != string::npos || input.find(' ') != string::npos)
        {
            cout << "Error: CNIC must be 13 digits without dashes or spaces.\n";
            continue;
        }

        // Then check if it's valid
        if (!isValidCNIC(input))
        {
            if (input.length() != 13)
            {
                cout << "Error: CNIC must be exactly 13 digits. Please try again.\n";
            }
            else
            {
                cout << "Error: CNIC must contain only numbers. Please try again.\n";
            }
            continue;
        }

        newApp.setCNIC(input);
        break;
    }

    // CNIC Expiry Date
    while (true)
    {
        cout << "CNIC Expiry Date (DD-MM-YYYY): ";
        getline(cin, input);
        input = trim(input);

        if (input == "X" || input == "x")
        {
            cout << "\nApplication canceled. Returning to main menu.\n";
            state = "MAIN_MENU";
            return;
        }

        // Check for slashes instead of dashes
        if (input.find('/') != string::npos)
        {
            cout << "Error: Please use dashes (-) not slashes (/). Format: DD-MM-YYYY\n";
            continue;
        }

        // Check length first
        if (input.length() != 10)
        {
            cout << "Error: Date must be in DD-MM-YYYY format. Please try again.\n";
            continue;
        }

        // Check dash positions
        if (input[2] != '-' || input[5] != '-')
        {
            cout << "Error: Date must be in DD-MM-YYYY format. Please try again.\n";
            continue;
        }

        // Extract components
        string dayStr = input.substr(0, 2);
        string monthStr = input.substr(3, 2);
        string yearStr = input.substr(6, 4);

        // Check if all parts are numeric
        bool allNumeric = true;
        for (char c : dayStr)
            if (!isdigit(c))
                allNumeric = false;
        for (char c : monthStr)
            if (!isdigit(c))
                allNumeric = false;
        for (char c : yearStr)
            if (!isdigit(c))
                allNumeric = false;

        if (!allNumeric)
        {
            cout << "Error: Date must contain only numbers. Please try again.\n";
            continue;
        }

        // Validate day
        int day = stoi(dayStr);
        if (day < 1 || day > 31)
        {
            cout << "Error: Invalid day. Day must be between 01-31. Please try again.\n";
            continue;
        }

        // Validate month
        int month = stoi(monthStr);
        if (month < 1 || month > 12)
        {
            cout << "Error: Invalid month. Month must be between 01-12. Please try again.\n";
            continue;
        }

        // Validate year (reasonable range)
        int year = stoi(yearStr);
        if (year < 2025)
        {
            cout << "Error: Your CNIC has expired. Please get a new one and apply again.\n";
            continue;
        }

        if (year > 2100)
        {
            cout << "Error: Invalid year. Please enter a valid year.\n";
            continue;
        }

        newApp.setCNICExpiry(input);
        break;
    }

    // Employment Status
    string employment[] = {"Self-employed", "Salaried", "Retired", "Unemployed"};
    while (true)
    {
        cout << "\nEmployment Status:\n";
        cout << "1. Self-employed\n";
        cout << "2. Salaried\n";
        cout << "3. Retired\n";
        cout << "4. Unemployed\n";
        cout << "Choose (1-4): ";
        getline(cin, input);
        input = trim(input);

        if (input == "X" || input == "x")
        {
            cout << "\nApplication canceled. Returning to main menu.\n";
            state = "MAIN_MENU";
            return;
        }

        if (!isValidMenuChoice(input, 1, 4))
        {
            cout << "Error: Please choose between 1-4.\n";
            continue;
        }

        int empChoice = stoi(input);
        newApp.setEmployment(employment[empChoice - 1]);
        break;
    }

    // Marital Status
    string marital[] = {"Single", "Married", "Divorced", "Widowed"};
    while (true)
    {
        cout << "\nMarital Status:\n";
        cout << "1. Single\n";
        cout << "2. Married\n";
        cout << "3. Divorced\n";
        cout << "4. Widowed\n";
        cout << "Choose (1-4): ";
        getline(cin, input);
        input = trim(input);

        if (input == "X" || input == "x")
        {
            cout << "\nApplication canceled. Returning to main menu.\n";
            state = "MAIN_MENU";
            return;
        }

        if (!isValidMenuChoice(input, 1, 4))
        {
            cout << "Error: Please choose between 1-4.\n";
            continue;
        }

        int marChoice = stoi(input);
        newApp.setMarital(marital[marChoice - 1]);
        break;
    }

    // Gender
    string gender[] = {"Male", "Female", "Other"};
    while (true)
    {
        cout << "\nGender:\n";
        cout << "1. Male\n";
        cout << "2. Female\n";
        cout << "3. Other\n";
        cout << "Choose (1-3): ";
        getline(cin, input);
        input = trim(input);

        if (input == "X" || input == "x")
        {
            cout << "\nApplication canceled. Returning to main menu.\n";
            state = "MAIN_MENU";
            return;
        }

        if (!isValidMenuChoice(input, 1, 3))
        {
            cout << "Error: Please choose between 1-3.\n";
            continue;
        }

        int genChoice = stoi(input);
        newApp.setGender(gender[genChoice - 1]);
        break;
    }

    // SECTION 2: Financial Information
    cout << "\n\033[1;36mFINANCIAL INFORMATION:\033[0m\n\n";

    // Number of Dependents
    while (true)
    {
        cout << "Number of Dependents: ";
        getline(cin, input);
        input = trim(input);

        if (input == "X" || input == "x")
        {
            cout << "\nApplication canceled. Returning to main menu.\n";
            state = "MAIN_MENU";
            return;
        }

        if (!isValidPositiveInteger(input))
        {
            cout << "Error: Please enter a valid number (0 or greater).\n";
            continue;
        }

        int deps = stoi(input);
        if (deps < 0)
        {
            cout << "Error: Dependents cannot be negative.\n";
            continue;
        }

        newApp.setDependents(deps);
        break;
    }

    // Annual Income
    while (true)
    {
        cout << "Annual Income (PKR): ";
        getline(cin, input);
        input = trim(input);

        if (input == "X" || input == "x")
        {
            cout << "\nApplication canceled. Returning to main menu.\n";
            state = "MAIN_MENU";
            return;
        }

        if (!isValidPositiveAmount(input))
        {
            if (!isValidPositiveInteger(input))
            {
                cout << "Error: Please enter a valid number.\n";
            }
            else
            {
                cout << "Error: Income must be greater than zero.\n";
            }
            continue;
        }

        newApp.setAnnualIncome(stol(input));
        break;
    }

    // Average Electricity Bill
    while (true)
    {
        cout << "Average Monthly Electricity Bill (PKR): ";
        getline(cin, input);
        input = trim(input);

        if (input == "X" || input == "x")
        {
            cout << "\nApplication canceled. Returning to main menu.\n";
            state = "MAIN_MENU";
            return;
        }

        if (!isValidPositiveInteger(input))
        {
            cout << "Error: Please enter a valid number.\n";
            continue;
        }

        newApp.setAvgElectricityBill(stol(input));
        break;
    }

    // Current Electricity Bill
    while (true)
    {
        cout << "Current Electricity Bill (PKR): ";
        getline(cin, input);
        input = trim(input);

        if (input == "X" || input == "x")
        {
            cout << "\nApplication canceled. Returning to main menu.\n";
            state = "MAIN_MENU";
            return;
        }

        if (!isValidPositiveInteger(input))
        {
            cout << "Error: Please enter a valid number.\n";
            continue;
        }

        newApp.setCurrentElectricityBill(stol(input));
        break;
    }

    // SECTION 3: Existing Loan
    while (true)
    {
        cout << "\nDo you have any existing loans? (Y/N): ";
        getline(cin, input);
        input = trim(input);

        if (input == "X" || input == "x")
        {
            cout << "\nApplication canceled. Returning to main menu.\n";
            state = "MAIN_MENU";
            return;
        }

        if (input.empty() || (toupper(input[0]) != 'Y' && toupper(input[0]) != 'N'))
        {
            cout << "Error: Please enter Y or N.\n";
            continue;
        }

        if (toupper(input[0]) == 'Y')
        {
            ExistingLoan loan;

            // Is loan active?
            while (true)
            {
                cout << "Is the loan active? (Y/N): ";
                getline(cin, input);
                input = trim(input);

                if (input == "X" || input == "x")
                {
                    cout << "\nApplication canceled. Returning to main menu.\n";
                    state = "MAIN_MENU";
                    return;
                }

                if (input.empty() || (toupper(input[0]) != 'Y' && toupper(input[0]) != 'N'))
                {
                    cout << "Error: Please enter Y or N.\n";
                    continue;
                }

                loan.isActive = (toupper(input[0]) == 'Y');
                break;
            }

            // Total Loan Amount
            while (true)
            {
                cout << "Total Loan Amount (PKR): ";
                getline(cin, input);
                input = trim(input);

                if (input == "X" || input == "x")
                {
                    cout << "\nApplication canceled. Returning to main menu.\n";
                    state = "MAIN_MENU";
                    return;
                }

                if (!isValidPositiveInteger(input))
                {
                    cout << "Error: Please enter a valid number.\n";
                    continue;
                }

                // Check if the number is too large for stol
                try
                {
                    long amount = stol(input);

                    // Additional check: must be greater than 0
                    if (amount <= 0)
                    {
                        cout << "Error: Loan amount must be greater than zero.\n";
                        continue;
                    }

                    loan.totalAmount = amount;
                    break;
                }
                catch (const std::out_of_range &)
                {
                    cout << "Error: Amount is too large. Please enter a reasonable value.\n";
                }
                catch (const std::invalid_argument &)
                {
                    cout << "Error: Please enter a valid number.\n";
                }
            }

            // Amount Returned
            while (true)
            {
                cout << "Amount Returned (PKR): ";
                getline(cin, input);
                input = trim(input);

                if (input == "X" || input == "x")
                {
                    cout << "\nApplication canceled. Returning to main menu.\n";
                    state = "MAIN_MENU";
                    return;
                }

                if (!isValidPositiveInteger(input))
                {
                    cout << "Error: Please enter a valid number (0 or greater).\n";
                    continue;
                }

                try
                {
                    long returned = stol(input);

                    // Business logic validation: returned cannot exceed total
                    if (returned > loan.totalAmount)
                    {
                        cout << "Error: Amount returned cannot be greater than total loan amount ("
                             << loan.totalAmount << " PKR).\n";
                        continue;
                    }

                    loan.amountReturned = returned;
                    break;
                }
                catch (const std::out_of_range &)
                {
                    cout << "Error: Amount is too large. Please enter a reasonable value.\n";
                }
            }

            // Amount Still Due
            while (true)
            {
                cout << "Amount Still Due (PKR): ";
                getline(cin, input);
                input = trim(input);

                if (input == "X" || input == "x")
                {
                    cout << "\nApplication canceled. Returning to main menu.\n";
                    state = "MAIN_MENU";
                    return;
                }

                if (!isValidPositiveInteger(input))
                {
                    cout << "Error: Please enter a valid number (0 or greater).\n";
                    continue;
                }

                try
                {
                    loan.amountDue = stol(input);
                    break;
                }
                catch (const std::out_of_range &)
                {
                    cout << "Error: Amount is too large. Please enter a reasonable value.\n";
                }
            }

            // Bank Name
            while (true)
            {
                cout << "Bank Name: ";
                getline(cin, input);
                input = trim(input);

                if (input == "X" || input == "x")
                {
                    cout << "\nApplication canceled. Returning to main menu.\n";
                    state = "MAIN_MENU";
                    return;
                }

                if (input.empty())
                {
                    cout << "Error: Bank name cannot be empty.\n";
                    continue;
                }

                loan.bankName = input;
                break;
            }

            // Loan Category
            while (true)
            {
                cout << "Loan Category (Car/Home/Bike): ";
                getline(cin, input);
                input = trim(input);

                if (input == "X" || input == "x")
                {
                    cout << "\nApplication canceled. Returning to main menu.\n";
                    state = "MAIN_MENU";
                    return;
                }

                string lowerInput = toLower(input);
                if (lowerInput != "car" && lowerInput != "home" && lowerInput != "bike")
                {
                    cout << "Error: Please enter Car, Home, or Bike.\n";
                    continue;
                }

                loan.category = input;
                break;
            }

            newApp.setExistingLoan(loan);
        }

        break; // Exit the outer while loop
    }

    // SECTION 4: References
    cout << "\n\033[1;36mREFERENCE INFORMATION:\033[0m\n\n";

    Referee ref1;
    cout << "REFEREE 1:\n";

    // Referee 1 Name
    while (true)
    {
        cout << "Name: ";
        getline(cin, input);
        input = trim(input);

        if (input == "X" || input == "x")
        {
            cout << "\nApplication canceled. Returning to main menu.\n";
            state = "MAIN_MENU";
            return;
        }

        if (input.empty())
        {
            cout << "Error: Referee name cannot be empty.\n";
            continue;
        }

        if (!isValidName(input))
        {
            cout << "Error: Invalid name format.\n";
            continue;
        }

        ref1.name = input;
        break;
    }

    // Referee 1 CNIC
    while (true)
    {
        cout << "CNIC (13 digits): ";
        getline(cin, input);
        input = trim(input);

        if (input == "X" || input == "x")
        {
            cout << "\nApplication canceled. Returning to main menu.\n";
            state = "MAIN_MENU";
            return;
        }

        if (input.find('-') != string::npos || input.find(' ') != string::npos)
        {
            cout << "Error: CNIC must be 13 digits without dashes or spaces.\n";
            continue;
        }

        if (!isValidCNIC(input))
        {
            if (input.length() != 13)
            {
                cout << "Error: CNIC must be exactly 13 digits.\n";
            }
            else
            {
                cout << "Error: CNIC must contain only numbers.\n";
            }
            continue;
        }

        ref1.cnic = input;
        break;
    }

    // Referee 1 Issue Date
    while (true)
    {
        cout << "CNIC Issue Date (DD-MM-YYYY): ";
        getline(cin, input);
        input = trim(input);

        if (input == "X" || input == "x")
        {
            cout << "\nApplication canceled. Returning to main menu.\n";
            state = "MAIN_MENU";
            return;
        }

        if (input.find('/') != string::npos)
        {
            cout << "Error: Please use dashes (-) not slashes (/). Format: DD-MM-YYYY\n";
            continue;
        }

        if (input.length() != 10 || input[2] != '-' || input[5] != '-')
        {
            cout << "Error: Date must be in DD-MM-YYYY format.\n";
            continue;
        }

        if (!isValidDate(input))
        {
            cout << "Error: Invalid date. Please check day and month.\n";
            continue;
        }

        ref1.issueDate = input;
        break;
    }

    // Referee 1 Phone
    while (true)
    {
        cout << "Phone Number (03xxxxxxxxx): ";
        getline(cin, input);
        input = trim(input);

        if (input == "X" || input == "x")
        {
            cout << "\nApplication canceled. Returning to main menu.\n";
            state = "MAIN_MENU";
            return;
        }

        if (!isValidContact(input))
        {
            if (input.length() != 11)
            {
                cout << "Error: Contact must be 11 digits.\n";
            }
            else if (input[0] != '0' || input[1] != '3')
            {
                cout << "Error: Contact must start with 03.\n";
            }
            else
            {
                cout << "Error: Contact must contain only numbers.\n";
            }
            continue;
        }

        ref1.phone = input;
        break;
    }

    // Referee 1 Email
    while (true)
    {
        cout << "Email: ";
        getline(cin, input);
        input = trim(input);

        if (input == "X" || input == "x")
        {
            cout << "\nApplication canceled. Returning to main menu.\n";
            state = "MAIN_MENU";
            return;
        }

        if (!isValidEmail(input))
        {
            if (input.find('@') == string::npos)
            {
                cout << "Error: Email must contain '@'.\n";
            }
            else
            {
                cout << "Error: Invalid email format.\n";
            }
            continue;
        }

        input = toLower(input);
        ref1.email = input;
        break;
    }

    newApp.setReferee1(ref1);

    // REFEREE 2 (Same validation as Referee 1)
    Referee ref2;
    cout << "\nREFEREE 2:\n";

    // Referee 2 Name
    while (true)
    {
        cout << "Name: ";
        getline(cin, input);
        input = trim(input);

        if (input == "X" || input == "x")
        {
            cout << "\nApplication canceled. Returning to main menu.\n";
            state = "MAIN_MENU";
            return;
        }

        if (input.empty() || !isValidName(input))
        {
            cout << "Error: Invalid name format.\n";
            continue;
        }

        ref2.name = input;
        break;
    }

    // Referee 2 CNIC
    while (true)
    {
        cout << "CNIC (13 digits): ";
        getline(cin, input);
        input = trim(input);

        if (input == "X" || input == "x")
        {
            cout << "\nApplication canceled. Returning to main menu.\n";
            state = "MAIN_MENU";
            return;
        }

        if (input.find('-') != string::npos || input.find(' ') != string::npos)
        {
            cout << "Error: CNIC must be 13 digits without dashes or spaces.\n";
            continue;
        }

        if (!isValidCNIC(input))
        {
            cout << "Error: CNIC must be exactly 13 digits.\n";
            continue;
        }

        ref2.cnic = input;
        break;
    }

    // Referee 2 Issue Date
    while (true)
    {
        cout << "CNIC Issue Date (DD-MM-YYYY): ";
        getline(cin, input);
        input = trim(input);

        if (input == "X" || input == "x")
        {
            cout << "\nApplication canceled. Returning to main menu.\n";
            state = "MAIN_MENU";
            return;
        }

        if (input.length() != 10 || input[2] != '-' || input[5] != '-' || !isValidDate(input))
        {
            cout << "Error: Invalid date format. Use DD-MM-YYYY.\n";
            continue;
        }

        ref2.issueDate = input;
        break;
    }

    // Referee 2 Phone
    while (true)
    {
        cout << "Phone Number (03xxxxxxxxx): ";
        getline(cin, input);
        input = trim(input);

        if (input == "X" || input == "x")
        {
            cout << "\nApplication canceled. Returning to main menu.\n";
            state = "MAIN_MENU";
            return;
        }

        if (!isValidContact(input))
        {
            cout << "Error: Invalid contact number.\n";
            continue;
        }

        ref2.phone = input;
        break;
    }

    // Referee 2 Email
    while (true)
    {
        cout << "Email: ";
        getline(cin, input);
        input = trim(input);

        if (input == "X" || input == "x")
        {
            cout << "\nApplication canceled. Returning to main menu.\n";
            state = "MAIN_MENU";
            return;
        }

        if (!isValidEmail(input))
        {
            cout << "Error: Invalid email format.\n";
            continue;
        }

        input = toLower(input);
        ref2.email = input;
        break;
    }

    newApp.setReferee2(ref2);

    // SECTION 5: Document Paths
    cout << "\n\033[1;36mDOCUMENT PATHS:\033[0m\n\n";
    cout << "Please save your documents in: output/application_documents/\n";
    cout << "Naming convention: CNIC_FileType.extension\n";
    cout << "Example: 3520212345678_CNIC_FRONT.jpg\n\n";

    string cnicFront, cnicBack, billPath, salaryPath;

    // CNIC Front Image
    while (true)
    {
        cout << "Path to CNIC Front Image: ";
        getline(cin, cnicFront);
        cnicFront = trim(cnicFront);

        if (cnicFront == "X" || cnicFront == "x")
        {
            cout << "\nApplication canceled. Returning to main menu.\n";
            state = "MAIN_MENU";
            return;
        }

        if (cnicFront.empty())
        {
            cout << "Error: Path cannot be empty.\n";
            continue;
        }

        // Check if file exists
        ifstream fileCheck(cnicFront);
        if (!fileCheck.good())
        {
            cout << "Error: File not found at the specified path. Please check and try again.\n";
            continue;
        }
        fileCheck.close();

        break;
    }

    // CNIC Back Image
    while (true)
    {
        cout << "Path to CNIC Back Image: ";
        getline(cin, cnicBack);
        cnicBack = trim(cnicBack);

        if (cnicBack == "X" || cnicBack == "x")
        {
            cout << "\nApplication canceled. Returning to main menu.\n";
            state = "MAIN_MENU";
            return;
        }

        if (cnicBack.empty())
        {
            cout << "Error: Path cannot be empty.\n";
            continue;
        }

        ifstream fileCheck(cnicBack);
        if (!fileCheck.good())
        {
            cout << "Error: File not found at the specified path. Please check and try again.\n";
            continue;
        }
        fileCheck.close();

        break;
    }

    // Electricity Bill
    while (true)
    {
        cout << "Path to Electricity Bill: ";
        getline(cin, billPath);
        billPath = trim(billPath);

        if (billPath == "X" || billPath == "x")
        {
            cout << "\nApplication canceled. Returning to main menu.\n";
            state = "MAIN_MENU";
            return;
        }

        if (billPath.empty())
        {
            cout << "Error: Path cannot be empty.\n";
            continue;
        }

        ifstream fileCheck(billPath);
        if (!fileCheck.good())
        {
            cout << "Error: File not found at the specified path. Please check and try again.\n";
            continue;
        }
        fileCheck.close();

        break;
    }

    // Salary Slip
    while (true)
    {
        cout << "Path to Salary Slip: ";
        getline(cin, salaryPath);
        salaryPath = trim(salaryPath);

        if (salaryPath == "X" || salaryPath == "x")
        {
            cout << "\nApplication canceled. Returning to main menu.\n";
            state = "MAIN_MENU";
            return;
        }

        if (salaryPath.empty())
        {
            cout << "Error: Path cannot be empty.\n";
            continue;
        }

        ifstream fileCheck(salaryPath);
        if (!fileCheck.good())
        {
            cout << "Error: File not found at the specified path. Please check and try again.\n";
            continue;
        }
        fileCheck.close();

        break;
    }

    newApp.setDocumentPaths(cnicFront, cnicBack, billPath, salaryPath);

    // Set metadata
    newApp.setApplicationID(appManager.generateApplicationID());
    newApp.setSubmissionDate("2025-11-18");
    newApp.setLoanDetails("Home", currentArea + " Loan");

    // Confirmation
    while (true)
    {
        cout << "\nReview and confirm submission? (Y/N): ";
        getline(cin, input);
        input = trim(input);

        if (input == "X" || input == "x")
        {
            cout << "\nApplication canceled.\n";
            state = "MAIN_MENU";
            return;
        }

        if (input.empty() || (toupper(input[0]) != 'Y' && toupper(input[0]) != 'N'))
        {
            cout << "Error: Please enter Y or N.\n";
            continue;
        }

        if (toupper(input[0]) == 'Y')
        {
            if (appManager.saveApplication(newApp))
            {
                cout << "\nApplication saved successfully!\n";
                cout << "Your Application ID: " << newApp.getApplicationID() << "\n";
            }
            else
            {
                cout << "\nFailed to save application.\n";
            }
        }
        else
        {
            cout << "\nSubmission canceled.\n";
        }

        break;
    }

    state = "MAIN_MENU";
}

void handleQueryApplications(string &state)
{
    string cnic;
    cout << "\nEnter CNIC to query (13 digits): ";
    getline(cin, cnic);
    cnic = trim(cnic);

    int submitted = appManager.getCountByStatus(cnic, "Submitted");
    int approved = appManager.getCountByStatus(cnic, "Approved");
    int rejected = appManager.getCountByStatus(cnic, "Rejected");

    cout << "\n";
    cout << "=============================================\n";
    cout << "  APPLICATION STATUS FOR CNIC: " << cnic << "\n";
    cout << "=============================================\n";
    cout << "Submitted:  " << submitted << "\n";
    cout << "Approved:   " << approved << "\n";
    cout << "Rejected:   " << rejected << "\n";
    cout << "=============================================\n";

    state = "MAIN_MENU";
}