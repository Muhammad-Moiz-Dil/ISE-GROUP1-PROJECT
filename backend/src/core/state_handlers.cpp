#include "core/state_handlers.h"
#include "core/chat_corpus.h"
#include "core/application.h"
#include "core/file_io.h"
#include "helpers/application_input.h"
#include "helpers/utils.h"
#include "helpers/ui_display.h"
#include "helpers/error_handling.h"
#include "models/car.h"
#include "models/scooter.h"
#include "models/home_loan.h"
#include "models/personal_loan.h"

#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::stoi;
using std::string;
using std::vector;

// External global objects (defined in their respective cpp files)
extern ApplicationManager appManager;
extern HomeLoanManager HomeLoanManagerObj;
extern CarPlanManager CarPlanManagerObj;
extern ScooterPlanManager ScooterPlanManagerObj;
extern PersonalLoanManager PersonalLoanManagerObj;
extern Utterance uttrObj;

// ==================== MAIN MENU HANDLER ====================

void handleMainMenu(string userInput, string lowerInput, string &state)
{
    cout << uttrObj.getResponse(lowerInput) << endl;
    if(uttrObj.getResponse(lowerInput) == "")
    {
        state = "GENERAL_CONVERSATION";
    }
    if (userInput == "A" || userInput == "a")
    {
        state = "LOAN_CATEGORY";
    }
    else if (userInput == "3")
    {
        state = "SUBMIT_APPLICATION";
    }
    else if (userInput == "4")
    {
        state = "QUERY_APPLICATIONS";
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
    else if (userInput == "S" || userInput == "s")
    {
        state = "SCOOTER_LOAN_AREA";
    }
    else if (userInput == "P" || userInput == "p")
    {
        state = "PERSONAL_LOAN";
    }  
    else if (userInput == "A" || userInput == "a")
    {
        return;
    }
}

// ==================== HOME LOAN HANDLER ====================

void handleHomeLoanArea(string userInput, string lowerInput, string &state, string &currentArea)
{
    // Validate input is 1, 2, 3, or 4
    if (userInput == "1" || userInput == "2" || userInput == "3" || userInput == "4")
    {
        currentArea = "Area " + userInput;
        int planCount = HomeLoanManagerObj.getPlanCount(currentArea);

        if (planCount > 0)
        {
            HomeLoanManagerObj.displayHomeLoanPlan(currentArea);
            cout << "\nWould you like to view monthly installments for any plan?\n";
            cout << "(Enter plan number 1-" << planCount << ", or A to return to main menu)\n";
            state = "VIEW_MONTHLY_INSTALLMENTS";
        }
        else
        {
            printError("No such area found.");
            state = "MAIN_MENU";
        }
    }
    else if (isValidPositiveInteger(userInput))
    {
        // Numeric but out of range
        printError("You probably meant to select from 1-4. Please try again.");
    }
    else
    {
        // Non-numeric input
        cout << uttrObj.getResponse(lowerInput) << endl;
    }
}

// ==================== CAR LOAN HANDLER ====================

void handleCarLoan(string &userInput, string &lowerInput, string &state, string &currentCarMake)
{
    // Validate input is 1 or 2
    if (userInput == "1" || userInput == "2")
    {
        currentCarMake = "Make " + userInput;
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
            printError("No such make found.");
            state = "MAIN_MENU";
        }
    }
    else if (isValidPositiveInteger(userInput))
    {
        // Numeric but out of range
        printError("You probably meant to select from 1-2. Please try again.");
    }
    else
    {
        // Non-numeric input
        cout << uttrObj.getResponse(lowerInput) << endl;
    }
}

// ==================== SCOOTER LOAN HANDLER ====================

void handleScooterLoan(string &userInput, string &lowerInput, string &state, string &currentScooterMake)
{
    // Validate input is 1 or 2
    if (userInput == "1" || userInput == "2")
    {
        currentScooterMake = "Make " + userInput;
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
            printError("No such make found.");
            state = "MAIN_MENU";
        }
    }
    else if (isValidPositiveInteger(userInput))
    {
        // Numeric but out of range
        printError("You probably meant to select from 1-2. Please try again.");
    }
    else
    {
        // Non-numeric input
        cout << uttrObj.getResponse(lowerInput) << endl;
    }
}

// ==================== VIEW CAR MONTHLY INSTALLMENTS ====================

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

    // Validate numeric input
    bool isNumeric = true;
    for (char c : userInput)
    {
        if (!isdigit(c))
        {
            isNumeric = false;
            break;
        }
    }

    if (isNumeric && !userInput.empty())
    {
        int planChoice = stoi(userInput);

        if (planChoice >= 1 && planChoice <= planCount)
        {
            // Get plan data from Manager
            CarPlan plan = CarPlanManagerObj.getPlan(currentMake, planChoice - 1);

            // Extract values (trim and convert)
            int price = stoi(trim(plan.getPrice()));
            int downPayment = stoi(trim(plan.getDownPayment()));
            int installments = stoi(trim(plan.getInstallments()));

            // Display using ui_display function
            displayPaymentSchedule("Car", price, downPayment, installments);

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
        cout << uttrObj.getResponse(lowerInput) << endl;
    }
}

// ==================== VIEW SCOOTER MONTHLY INSTALLMENTS ====================

void handleViewScooterMonthlyInstallments(string userInput, string lowerInput, string &state, string &currentMake)
{
    userInput = trim(userInput);
    lowerInput = toLower(userInput);
    int planCount = ScooterPlanManagerObj.getPlanCount(currentMake);

    if (userInput == "A" || userInput == "a")
    {
        state = "MAIN_MENU";
        cout << uttrObj.getResponse(lowerInput) << endl;
        return;
    }

    if (userInput == "S" || userInput == "s")
    {
        state = "SUBMIT_APPLICATION";
        return;
    }

    bool isNumeric = true;
    for (char c : userInput)
    {
        if (!isdigit(c))
        {
            isNumeric = false;
            break;
        }
    }

    if (isNumeric && !userInput.empty())
    {
        int planChoice = stoi(userInput);

        if (planChoice >= 1 && planChoice <= planCount)
        {
            // Get plan data from Manager
            ScooterPlan plan = ScooterPlanManagerObj.getPlan(currentMake, planChoice - 1);

            // Extract values
            int price = stoi(trim(plan.getPrice()));
            int downPayment = stoi(trim(plan.getDownPayment()));
            int installments = stoi(trim(plan.getInstallments()));

            // Display using ui_display function
            displayPaymentSchedule("Scooter", price, downPayment, installments);

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
        cout << uttrObj.getResponse(lowerInput) << endl;
    }
}

// ==================== VIEW HOME MONTHLY INSTALLMENTS ====================

void handleViewMonthlyInstallments(string userInput, string lowerInput, string &state, string &currentArea)
{
    userInput = trim(userInput);
    lowerInput = toLower(userInput);
    int planCount = HomeLoanManagerObj.getPlanCount(currentArea);

    if (userInput == "A" || userInput == "a")
    {
        state = "MAIN_MENU";
        cout << uttrObj.getResponse(lowerInput) << endl;
        return;
    }

    if (userInput == "S" || userInput == "s")
    {
        state = "SUBMIT_APPLICATION";
        return;
    }

    bool isNumeric = true;
    for (char c : userInput)
    {
        if (!isdigit(c))
        {
            isNumeric = false;
            break;
        }
    }

    if (isNumeric && !userInput.empty())
    {
        int planChoice = stoi(userInput);

        if (planChoice >= 1 && planChoice <= planCount)
        {
            // Get plan data from Manager
            HomeLoanPlan plan = HomeLoanManagerObj.getPlan(currentArea, planChoice - 1);

            // Extract values
            int price = stoi(trim(plan.getPrice()));
            int downPayment = stoi(trim(plan.getDownPayment()));
            int installments = stoi(trim(plan.getInstallments()));

            // Display using ui_display function
            displayPaymentSchedule("Home", price, downPayment, installments);

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
        cout << uttrObj.getResponse(lowerInput) << endl;
    }
}

// ==================== PERSONAL LOAN HANDLER ====================

void handlePersonalLoan(string &userInput, string &lowerInput, string &state, string &currentCategory, string &personalLoanSubState)
{
    // Initial Entry
    if (personalLoanSubState.empty())
    {
        cout << "\n" << COLOR_CYAN << "--- PERSONAL LOAN MENU ---" << COLOR_RESET << endl;
        cout << "1. Wedding Loan" << endl;
        cout << "2. Education Loan" << endl;
        cout << "3. Business Loan" << endl;
        cout << "4. View All Categories" << endl;
        cout << "5. Resume Application" << endl;
        cout << "6. Check Status" << endl;
        cout << "A. Apply (General)" << endl;
        cout << "X. Exit" << endl;
        
        personalLoanSubState = "MENU";
        return; // Return to let main loop capture input
    }

    // Handle Menu Selection
    if (personalLoanSubState == "MENU")
    {
        if (lowerInput == "a") {
            personalLoanSubState = "CATEGORY";
            cout << "\nPlease select category (1-Wedding, 2-Education, 3-Business): ";
            return;
        }
        else if (userInput == "1") currentCategory = "Wedding";
        else if (userInput == "2") currentCategory = "Education";
        else if (userInput == "3") currentCategory = "Business";
        else if (userInput == "4") {
            printInfo("Available Categories: Wedding, Education, Business");
            return;
        }
        else if (userInput == "5") { state = "RESUME_APPLICATION"; return; }
        else if (userInput == "6") { state = "CHECK_STATUS"; return; }
        else if (lowerInput == "x") { state = "MAIN_MENU"; return; }
        else {
            printError("Invalid option. Please choose 1-6, A, or X.");
            return;
        }

        // If we got here, a category was selected (1, 2, or 3)
        int planCount = PersonalLoanManagerObj.getPlanCount(currentCategory);
        
        if (planCount > 0) {
            PersonalLoanManagerObj.displayPersonalLoanPlan(currentCategory);
            cout << "\nWhat would you like to do?" << endl;
            cout << "Enter plan number (1-" << planCount << ") to view installments" << endl;
            cout << "S - Submit Application" << endl;
            cout << "A - Return to Main Menu" << endl;
            
            state = "VIEW_PERSONAL_INSTALLMENTS";
            personalLoanSubState = ""; // Reset sub-state
        } else {
            printError("No plans available for " + currentCategory);
            state = "MAIN_MENU";
        }
    }
    // Handle Category Selection Sub-state
    else if (personalLoanSubState == "CATEGORY")
    {
        if (userInput == "1") currentCategory = "Wedding";
        else if (userInput == "2") currentCategory = "Education";
        else if (userInput == "3") currentCategory = "Business";
        else {
            printError("Invalid category. Please choose 1, 2, or 3.");
            return;
        }
        
        // Same display logic as above...
        int planCount = PersonalLoanManagerObj.getPlanCount(currentCategory);
        PersonalLoanManagerObj.displayPersonalLoanPlan(currentCategory);
        // ... (display prompt)
        state = "VIEW_PERSONAL_INSTALLMENTS";
        personalLoanSubState = "";
    }
}

// ==================== VIEW PERSONAL MONTHLY INSTALLMENTS ====================

void handleViewPersonalInstallments(string userInput, string lowerInput, string &state, string &currentCategory)
{
    userInput = trim(userInput);
    lowerInput = toLower(userInput);
    int planCount = PersonalLoanManagerObj.getPlanCount(currentCategory);

    // Return to main menu
    if (userInput == "A" || userInput == "a")
    {
        state = "MAIN_MENU";
        return;
    }

    // Submit application
    if (userInput == "S" || userInput == "s")
    {
        state = "SUBMIT_APPLICATION";
        return;
    }

    // Use helper function instead of manual loop
    if (isValidPositiveAmount(userInput))
    {
        int planChoice = stoi(userInput);

        if (planChoice >= 1 && planChoice <= planCount)
        {
            // Get plan data
            PersonalLoanPlan plan = PersonalLoanManagerObj.getPlan(currentCategory, planChoice - 1);

            // Parse with helper (already correct in your snippet)
            int amount = parseNumberWithCommas(plan.getTotalAmount());
            int downPayment = parseNumberWithCommas(plan.getDownPayment());
            int installments = stoi(trim(plan.getInstallments()));

            // Display using standard UI helper
            displayPaymentSchedule("Personal", amount, downPayment, installments);

            cout << "\nWhat would you like to do next?" << endl;
            cout << "S - Submit loan application" << endl;
            cout << "(Enter plan number 1-" << planCount << " to view another plan)" << endl;
            cout << "A - Return to main menu" << endl;
        }
        else
        {
            // Use standard error printer
            printError("You probably meant to select from 1-" + std::to_string(planCount) + ". Please try again.");
        }
    }
    else
    {
        cout << uttrObj.getResponse(lowerInput) << endl;
    }
}


// ==================== CHECK STATUS HANDLER ====================

void handleCheckStatus(string &state)
{
    printSectionHeader("CHECK APPLICATION STATUS");

    cout << "Enter your CNIC (without dashes) or Application ID:\n>> ";
    string input;
    getline(cin, input);
    input = trim(input);

    if (input == "X" || input == "x")
    {
        state = "MAIN_MENU";
        return;
    }

    // Try to find by ID first
    Application *app = appManager.getApplicationByID(input);

    if (app != nullptr)
    {
        // Found by ID
        cout << "\nApplication Found:\n";
        cout << "ID: " << app->getApplicationID() << endl;
        cout << "Name: " << app->getFullName() << endl;
        displayApplicationStatus(app->getStatus());
    }
    else
    {
        // Try by CNIC
        vector<Application> apps = appManager.getApplicationsByCNIC(input);

        if (apps.empty())
        {
            printError("No application found with this ID or CNIC.");
        }
        else
        {
            cout << "\nFound " << apps.size() << " application(s):\n";
            for (const auto &a : apps)
            {
                cout << "--------------------------------\n";
                cout << "ID: " << a.getApplicationID() << endl;
                cout << "Loan Type: " << a.getLoanType() << endl;
                displayApplicationStatus(a.getStatus());
            }
        }
    }

    cout << "\nPress Enter to return to main menu...";
    getline(cin, input);
    state = "MAIN_MENU";
}

// ==================== RESUME APPLICATION HANDLER ====================

void handleResumeApplication(string &state)
{
    printSectionHeader("RESUME APPLICATION");

    cout << "Enter Application ID: ";
    string id;
    getline(cin, id);
    id = trim(id);

    if (id == "X" || id == "x")
    {
        state = "MAIN_MENU";
        return;
    }

    cout << "Enter CNIC: ";
    string cnic;
    getline(cin, cnic);
    cnic = trim(cnic);

    if (cnic == "X" || cnic == "x")
    {
        state = "MAIN_MENU";
        return;
    }

    Application *app = appManager.getApplicationByID(id);

    // Validate application exists and CNIC matches
    if (app == nullptr || app->getCNIC() != cnic)
    {
        printError("Invalid Application ID or CNIC.");
        cout << "Press Enter to return...";
        getline(cin, id);
        state = "MAIN_MENU";
        return;
    }

    // Check if already completed
    if (app->getStatus() == "Submitted" || app->getStatus() == "Approved" || app->getStatus() == "Rejected")
    {
        printWarning("This application is already completed/submitted.");
        cout << "Status: " << app->getStatus() << endl;
        cout << "Press Enter to return...";
        getline(cin, id);
        state = "MAIN_MENU";
        return;
    }

    // Resume flow based on checkpoint
    printSuccess("Resuming application from Checkpoint " + std::to_string(app->getCheckpoint()) + "...");

    if (app->getCheckpoint() < 1)
    {
        if (!collectPersonalInformation(*app, state))
            return;
        app->setCheckpoint(1);
        appManager.saveApplication(*app);
    }

    if (app->getCheckpoint() < 2)
    {
        if (!collectFinancialInformation(*app, state))
            return;
        app->setCheckpoint(2);
        appManager.saveApplication(*app);
    }

    if (app->getCheckpoint() < 3)
    {
        if (!collectReferenceInformation(*app, state))
            return;
        app->setCheckpoint(3);
        appManager.saveApplication(*app);
    }

    if (!collectDocuments(*app, state))
        return;

    // Finalize submission
    app->setStatus("Submitted");
    app->setCheckpoint(4);
    appManager.saveApplication(*app);

    printSuccess("Application Submitted Successfully!");
    cout << "Your Application ID is: " << app->getApplicationID() << endl;
    cout << "Press Enter to return to main menu...";
    getline(cin, id);
    state = "MAIN_MENU";
}

// ==================== APPLICATION SUBMISSION HANDLER ====================

void handleApplicationSubmission(string &state, string &currentArea)
{
    Application newApp;
    newApp.setApplicationID(appManager.generateApplicationID());
    newApp.setLoanDetails(currentArea, "Standard Plan");

    // Display application header
    cout << "\n"
        << COLOR_YELLOW << "=============================================" << endl;
    cout << "       LOAN APPLICATION FORM" << endl;
    cout << "=============================================" << endl;
    cout << "You are applying for: " << currentArea << endl;
    cout << "Application ID: " << newApp.getApplicationID() << endl;
    cout << "=============================================" << endl;
    cout << "Type 'X' at any time to save and exit (Resume later)\n"
        << COLOR_RESET << endl;

    // Collect information with checkpoints
    if (!collectPersonalInformation(newApp, state))
        return;
    newApp.setCheckpoint(1);
    appManager.saveApplication(newApp);

    if (!collectFinancialInformation(newApp, state))
        return;
    newApp.setCheckpoint(2);
    appManager.saveApplication(newApp);

    if (!collectReferenceInformation(newApp, state))
        return;
    newApp.setCheckpoint(3);
    appManager.saveApplication(newApp);

    if (!collectDocuments(newApp, state))
        return;

    // Finalize submission
    newApp.setStatus("Submitted");
    newApp.setCheckpoint(4);
    appManager.saveApplication(newApp);

    printSuccess("Application Submitted Successfully!");
    cout << "Your Application ID is: " << newApp.getApplicationID() << endl;
    cout << "Press Enter to return to main menu...";

    string dummy;
    getline(cin, dummy);
    state = "MAIN_MENU";
}

// ==================== QUERY APPLICATIONS HANDLER ====================

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