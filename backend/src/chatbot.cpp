#include "../../logs/include/chatbot.h"
#include "../../logs/include/file_io.h"
#include "../../logs/include/loan_plan.h"
#include "../../logs/include/car.h"
#include "../../logs/include/utils.h"
#include "../../logs/include/application.h"  
#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::getline;

string currentMake = "";
void runChatbot()
{
    displayWelcomeHeader();

    string state = "MAIN_MENU";
    string currentArea = "";

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
        else if(state == "CAR_LOAN_AREA")
        {
            handleCarLoan(userInput, lowerInput,state, currentArea);
        }
        else if(state == "SCOOTER_LOAN_AREA")
        {

        }
        else if(state == "VIEW_CAR_MONTHLY_INSTALLMENTS")
        {
            handleViewCarMonthlyInstallments(userInput, lowerInput, state, currentMake);
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
    else if (userInput == "3")  
    {
        state = "SUBMIT_APPLICATION";
    }
    else if (userInput == "4")  
    {
        state = "QUERY_APPLICATION";
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
        state = "CAR_LOAN_AREA";
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
string getInput()
{
    string userInput;
    getline(cin, userInput);
    return userInput;
}
 void handleCarLoan(string userInput, string lowerInput,string  &state, string& currentArea)
 {
    cout<<"Select options 1 2"<<endl;
    userInput = getInput();
    if(userInput == "1")
    {
        currentMake = "Make 1";
        int planCount = CarPlanManagerObj.getPlanCount(currentMake);
        if (planCount > 0)  // Check if area exists
        {
            CarPlanManagerObj.displayCarPlan(currentMake);
            cout << "\nWould you like to view monthly installments for any plan?\n";
            cout << "(Enter plan number 1-" << planCount << ", or A to return to main menu)\n";
            state = "VIEW_CAR_MONTHLY_INSTALLMENTS";
        }
        else
        {
            cout << "No such modal found." << endl;
            state = "MAIN_MENU";  // Return to main menu
        }
    }
    else if(userInput == "2")
    {
        currentMake = "Make 2";
        int planCount = CarPlanManagerObj.getPlanCount(currentMake);
        if (planCount > 0)  // Check if area exists
        {
            CarPlanManagerObj.displayCarPlan(currentMake);
            cout << "\nWould you like to view monthly installments for any plan?\n";
            cout << "(Enter plan number 1-" << planCount << ", or A to return to main menu)\n";
            state = "VIEW_CAR_MONTHLY_INSTALLMENTS";
        }
        else
        {
            cout << "No such modal found." << endl;
            state = "MAIN_MENU";  // Return to main menu
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
void handleHomeLoanArea(string userInput, string lowerInput, string &state, string &currentArea)
{
    if (userInput == "1")
    {
        currentArea = "Area 1";
        int planCount = LoanPlanManagerObj.getPlanCount(currentArea);
        
        if (planCount > 0)  // Check if area exists
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
void handleViewCarMonthlyInstallments(string userInput, string lowerInput, string &state, string &currentMake)
{
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

// ============================================================================
// NEW FUNCTIONS FOR INCREMENT 2
// ============================================================================

void handleApplicationSubmission(string &state, string &currentArea)
{
    Application newApp;
    string input;
    
    cout << "\n\033[1;33m";  // Yellow color
    cout << "=============================================\n";
    cout << "\n=============================================" << endl;
    cout << "       LOAN APPLICATION FORM" << endl;
    cout << "=============================================" << endl;
    cout << "You are applying for: " << currentArea << " Loan" << endl;
    cout << "=============================================" << endl;
    
    Application app;
    app.setLoanDetails(currentArea, "");

    cout << "=============================================\n";
    cout << "\033[0m\n";  // Reset color
    
    // SECTION 1: Personal Information
    cout << "\033[1;36mPERSONAL INFORMATION:\033[0m\n\n";
    
    cout << "Full Name: ";
    getline(cin, input);
    newApp.setFullName(trim(input));
    
    cout << "Father's Name: ";
    getline(cin, input);
    newApp.setFathersName(trim(input));
    
    cout << "Postal Address: ";
    getline(cin, input);
    newApp.setPostalAddress(trim(input));
    
    cout << "Contact Number (03xxxxxxxxx): ";
    getline(cin, input);
    newApp.setContact(trim(input));
    
    cout << "Email Address: ";
    getline(cin, input);
    newApp.setEmail(trim(input));
    
    cout << "CNIC (13 digits, no dashes): ";
    getline(cin, input);
    newApp.setCNIC(trim(input));
    
    cout << "CNIC Expiry Date (DD-MM-YYYY): ";
    getline(cin, input);
    newApp.setCNICExpiry(trim(input));
    
    // Employment Status
    cout << "\nEmployment Status:\n";
    cout << "1. Self-employed\n";
    cout << "2. Salaried\n";
    cout << "3. Retired\n";
    cout << "4. Unemployed\n";
    cout << "Choose (1-4): ";
    getline(cin, input);
    string employment[] = {"Self-employed", "Salaried", "Retired", "Unemployed"};
    int empChoice = stoi(input);
    newApp.setEmployment(employment[empChoice - 1]);
    
    // Marital Status
    cout << "\nMarital Status:\n";
    cout << "1. Single\n";
    cout << "2. Married\n";
    cout << "3. Divorced\n";
    cout << "4. Widowed\n";
    cout << "Choose (1-4): ";
    getline(cin, input);
    string marital[] = {"Single", "Married", "Divorced", "Widowed"};
    int marChoice = stoi(input);
    newApp.setMarital(marital[marChoice - 1]);
    
    // Gender
    cout << "\nGender:\n";
    cout << "1. Male\n";
    cout << "2. Female\n";
    cout << "3. Other\n";
    cout << "Choose (1-3): ";
    getline(cin, input);
    string gender[] = {"Male", "Female", "Other"};
    int genChoice = stoi(input);
    newApp.setGender(gender[genChoice - 1]);
    
    // SECTION 2: Financial Information
    cout << "\n\033[1;36mFINANCIAL INFORMATION:\033[0m\n\n";
    
    cout << "Number of Dependents: ";
    getline(cin, input);
    newApp.setDependents(stoi(input));
    
    cout << "Annual Income (PKR): ";
    getline(cin, input);
    newApp.setAnnualIncome(stol(input));
    
    cout << "Average Monthly Electricity Bill (PKR): ";
    getline(cin, input);
    newApp.setAvgElectricityBill(stol(input));
    
    cout << "Current Electricity Bill (PKR): ";
    getline(cin, input);
    newApp.setCurrentElectricityBill(stol(input));
    
    // SECTION 3: Existing Loan
    cout << "\nDo you have any existing loans? (Y/N): ";
    getline(cin, input);
    
    if (toupper(input[0]) == 'Y')
    {
        ExistingLoan loan;
        
        cout << "Is the loan active? (Y/N): ";
        getline(cin, input);
        loan.isActive = (toupper(input[0]) == 'Y');
        
        cout << "Total Loan Amount (PKR): ";
        getline(cin, input);
        loan.totalAmount = stol(input);
        
        cout << "Amount Returned (PKR): ";
        getline(cin, input);
        loan.amountReturned = stol(input);
        
        cout << "Amount Still Due (PKR): ";
        getline(cin, input);
        loan.amountDue = stol(input);
        
        cout << "Bank Name: ";
        getline(cin, input);
        loan.bankName = trim(input);
        
        cout << "Loan Category (Car/Home/Bike): ";
        getline(cin, input);
        loan.category = trim(input);
        
        newApp.setExistingLoan(loan);
    }
    
    // SECTION 4: References
    cout << "\n\033[1;36mREFERENCE INFORMATION:\033[0m\n\n";
    
    Referee ref1;
    cout << "REFEREE 1:\n";
    cout << "Name: ";
    getline(cin, input);
    ref1.name = trim(input);
    
    cout << "CNIC (13 digits): ";
    getline(cin, input);
    ref1.cnic = trim(input);
    
    cout << "CNIC Issue Date (DD-MM-YYYY): ";
    getline(cin, input);
    ref1.issueDate = trim(input);
    
    cout << "Phone Number (03xxxxxxxxx): ";
    getline(cin, input);
    ref1.phone = trim(input);
    
    cout << "Email: ";
    getline(cin, input);
    ref1.email = trim(input);
    
    newApp.setReferee1(ref1);
    
    Referee ref2;
    cout << "\nREFEREE 2:\n";
    cout << "Name: ";
    getline(cin, input);
    ref2.name = trim(input);
    
    cout << "CNIC (13 digits): ";
    getline(cin, input);
    ref2.cnic = trim(input);
    
    cout << "CNIC Issue Date (DD-MM-YYYY): ";
    getline(cin, input);
    ref2.issueDate = trim(input);
    
    cout << "Phone Number (03xxxxxxxxx): ";
    getline(cin, input);
    ref2.phone = trim(input);
    
    cout << "Email: ";
    getline(cin, input);
    ref2.email = trim(input);
    
    newApp.setReferee2(ref2);
    
    // SECTION 5: Document Paths
    cout << "\n\033[1;36mDOCUMENT PATHS:\033[0m\n\n";
    string cnicFront, cnicBack, billPath, salaryPath;
    
    cout << "Path to CNIC Front Image: ";
    getline(cin, cnicFront);
    
    cout << "Path to CNIC Back Image: ";
    getline(cin, cnicBack);
    
    cout << "Path to Electricity Bill: ";
    getline(cin, billPath);
    
    cout << "Path to Salary Slip: ";
    getline(cin, salaryPath);
    
    newApp.setDocumentPaths(cnicFront, cnicBack, billPath, salaryPath);
    
    // Set metadata
    newApp.setApplicationID(appManager.generateApplicationID());
    newApp.setSubmissionDate("2025-11-17");
    newApp.setLoanDetails("Home", "Area 1 - 5 Marla");
    
    // Confirmation
    cout << "\n\033[1;33m⚠  Review and confirm submission? (Y/N): \033[0m";
    getline(cin, input);

    if (!input.empty() && toupper(input[0]) == 'Y')
    {
        if (appManager.saveApplication(newApp))
        {
            cout << "\n\033[1;32m✔ Application saved successfully!\033[0m\n";
        }
        else
        {
            cout << "\n\033[1;31m❌ Failed to save application.\033[0m\n";
        }
    }
    else
    {
        cout << "\n\033[1;34mℹ Submission canceled.\033[0m\n";
    }
    state = "MAIN_MENU";
}

void handleQueryApplications(string &state) {
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