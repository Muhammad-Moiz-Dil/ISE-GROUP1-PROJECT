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
#include <ctime>

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

void handleUnexpectedInput(string &lowerInput) {
    printError("Invalid input. Please follow the on-screen instructions.");
}

void handleMainMenu(string userInput, string lowerInput, string &state)
{
    // Check Utterances.txt first
    string response = uttrObj.getResponse(lowerInput);

    // If we found a specific match (response is NOT empty)
    if (!response.empty())
    {
        cout << response << endl;
    }
    else
    {
        handleGeneralConversation(userInput, lowerInput, state);
    }
}

void handleLoanCategory(string userInput, string lowerInput, string &state, string &currentLoanType)
{
    cout << uttrObj.getResponse(lowerInput) << endl;

    if (userInput == "H" || userInput == "h")
    {
        state = "HOME_LOAN_AREA";
        currentLoanType = "Home";
    }
    else if (userInput == "C" || userInput == "c")
    {
        state = "CAR_LOAN";
        currentLoanType = "Car";
    }
    else if (userInput == "E" || userInput == "e")
    {
        state = "SCOOTER_LOAN_AREA";
        currentLoanType = "Scooter";
    }
    else if (userInput == "P" || userInput == "p")
    {
        state = "PERSONAL_LOAN";
        currentLoanType = "Personal";
    }
    else if (userInput == "A" || userInput == "a")
    {
        state = "MAIN_MENU";
        return;
    }
    else
    {
        handleUnexpectedInput(lowerInput);
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
        handleUnexpectedInput(lowerInput);
    }
}

// ==================== GENERAL CONVERSATION HANDLER =================
void handleGeneralConversation(string userInput, string lowerInput, string &state)
{
    // Skip empty input
    if (userInput.empty()) return;

    // Use IoU logic from Chat Corpus
    string response = chatCorpusObj.getResponse(userInput);

    // Print the response
    cout << COLOR_GREEN << "Bot: " << COLOR_RESET << response << endl;
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
        handleUnexpectedInput(lowerInput);
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
        handleUnexpectedInput(lowerInput);
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
        handleUnexpectedInput(lowerInput);
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
        handleUnexpectedInput(lowerInput);
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
        handleUnexpectedInput(lowerInput);
    }
}

// ==================== PERSONAL LOAN HANDLER ====================

void handlePersonalLoan(string &userInput, string &lowerInput, string &state, string &currentCategory, string &personalLoanSubState)
{

    if (userInput == "1") currentCategory = "Wedding";
    else if (userInput == "2") currentCategory = "Education";
    else if (userInput == "3") currentCategory = "Business";
    
    else if (userInput == "A" || userInput == "a") { state = "MAIN_MENU"; return; }
    
    else {
        // Check if numeric but out of range
        if (isValidPositiveInteger(userInput)) {
            printError("You probably meant to select from 1-3. Please try again.");
            return;
        }
        // Fallback to utterances (e.g., "hi")
        handleUnexpectedInput(lowerInput);
        return;
    }

    // 4. If valid category selected, show plans
    int planCount = PersonalLoanManagerObj.getPlanCount(currentCategory);

    if (planCount > 0)
    {
        PersonalLoanManagerObj.displayPersonalLoanPlan(currentCategory);
        
        cout << "\nWould you like to view monthly installments for any plan?" << endl;
        cout << "(Enter plan number 1-" << planCount << ", or A to return to main menu)" << endl;
        
        state = "VIEW_PERSONAL_INSTALLMENTS";
    }
    else
    {
        printError("No plans available for " + currentCategory);
        // Stay in current state or go back?
        // usually we stay so they can pick another category
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
        handleUnexpectedInput(lowerInput);
    }
}

// ==================== CHECK STATUS HANDLER ====================

void handleCheckStatus(string &state)
{
    printSectionHeader("CHECK APPLICATION STATUS");

    
    if (!appManager.loadApplications("output/applications.txt")) 
    {
        printError("Warning: Could not refresh data. Showing cached status.");
    }

    cout << "Enter your CNIC (without dashes) >> ";
    string input;
    getline(cin, input);
    input = trim(input);

    if (input == "X" || input == "x")
    {
        state = "MAIN_MENU";
        return;
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

    if (id == "X" || id == "x") { state = "MAIN_MENU"; return; }

    cout << "Enter CNIC: ";
    string cnic;
    getline(cin, cnic);
    cnic = trim(cnic);

    if (cnic == "X" || cnic == "x") { state = "MAIN_MENU"; return; }

    Application *app = appManager.getApplicationByID(id);

    if (app == nullptr || app->getCNIC() != cnic)
    {
        printError("Invalid Application ID or CNIC.");
        cout << "Press Enter to return...";
        getline(cin, id);
        state = "MAIN_MENU";
        return;
    }

    if (app->getStatus() == "Submitted" || app->getStatus() == "Approved" || app->getStatus() == "Rejected")
    {
        printWarning("This application is already completed/submitted.");
        cout << "Status: " << app->getStatus() << endl;
        cout << "Press Enter to return...";
        getline(cin, id);
        state = "MAIN_MENU";
        return;
    }

    printSuccess("Resuming application from Checkpoint " + std::to_string(app->getCheckpoint()) + "...");

    // Checkpoint 1: Personal Info
    if (app->getCheckpoint() < 1)
    {
        if (!collectPersonalInformation(*app, state)) {
            // User pressed X
            cout << "\n" << COLOR_GREEN << ">> Progress saved as draft (ID: " << app->getApplicationID() << ")" << COLOR_RESET << endl;
            return;
        }
        app->setCheckpoint(1);
        appManager.saveApplication(*app);
        cout << ">> Personal Information saved." << endl;
    }

    // Checkpoint 2: Financial Info
    if (app->getCheckpoint() < 2)
    {
        if (!collectFinancialInformation(*app, state)) {
            cout << "\n" << COLOR_GREEN << ">> Progress saved at Checkpoint 1 (ID: " << app->getApplicationID() << ")" << COLOR_RESET << endl;
            return;
        }
        app->setCheckpoint(2);
        appManager.saveApplication(*app);
        cout << ">> Financial Information saved." << endl;
    }

    // Checkpoint 3: Reference Info
    if (app->getCheckpoint() < 3)
    {
        if (!collectReferenceInformation(*app, state)) {
            cout << "\n" << COLOR_GREEN << ">> Progress saved at Checkpoint 2 (ID: " << app->getApplicationID() << ")" << COLOR_RESET << endl;
            return;
        }
        app->setCheckpoint(3);
        appManager.saveApplication(*app);
        cout << ">> Reference Information saved." << endl;
    }

    // Checkpoint 4: Documents
    if (!collectDocuments(*app, state)) {
        cout << "\n" << COLOR_GREEN << ">> Progress saved at Checkpoint 3 (ID: " << app->getApplicationID() << ")" << COLOR_RESET << endl;
        return;
    }

    // Finalize
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

void handleApplicationSubmission(string &state, string &currentArea, string &currentLoanType, string &currentCarMake, string &currentScooterMake, string &currentCategory)
{
    Application newApp;
    newApp.setApplicationID(appManager.generateApplicationID());

    string finalDetails = "Standard Plan";
    
    if (currentLoanType == "Home") {
        finalDetails = currentArea;
    } else if (currentLoanType == "Car") {
        finalDetails = currentCarMake;
    } else if (currentLoanType == "Scooter") {
        finalDetails = currentScooterMake;
    } else if (currentLoanType == "Personal") {
        finalDetails = currentCategory;
    }

    newApp.setLoanDetails(currentLoanType, finalDetails);

    cout << "\n" << COLOR_YELLOW << "=============================================" << endl;
    cout << "       LOAN APPLICATION FORM" << endl;
    cout << "=============================================" << endl;
    cout << "You are applying for: " << currentLoanType << " Loan (" << finalDetails << ")" << endl;
    cout << "Application ID: " << newApp.getApplicationID() << endl;
    cout << "=============================================" << endl;
    cout << "Type 'X' at any time to save and exit (Resume later)\n" << COLOR_RESET << endl;

    // We save immediately to reserve the ID
    appManager.saveApplication(newApp);

    // Checkpoint 1: Personal Info
    if (!collectPersonalInformation(newApp, state)) {
        // User pressed X
        cout << "\n" << COLOR_GREEN << ">> Application saved as draft (ID: " << newApp.getApplicationID() << ")" << COLOR_RESET << endl;
        return;
    }
    newApp.setCheckpoint(1);
    appManager.saveApplication(newApp);
    cout << ">> Personal Information saved." << endl;

    // Checkpoint 2: Financial Info
    if (!collectFinancialInformation(newApp, state)) {
        cout << "\n" << COLOR_GREEN << ">> Progress saved at Checkpoint 1 (ID: " << newApp.getApplicationID() << ")" << COLOR_RESET << endl;
        return;
    }
    newApp.setCheckpoint(2);
    appManager.saveApplication(newApp);
    cout << ">> Financial Information saved." << endl;

    // Checkpoint 3: Reference Info
    if (!collectReferenceInformation(newApp, state)) {
        cout << "\n" << COLOR_GREEN << ">> Progress saved at Checkpoint 2 (ID: " << newApp.getApplicationID() << ")" << COLOR_RESET << endl;
        return;
    }
    newApp.setCheckpoint(3);
    appManager.saveApplication(newApp);
    cout << ">> Reference Information saved." << endl;

    // Checkpoint 4: Documents
    if (!collectDocuments(newApp, state)) {
        cout << "\n" << COLOR_GREEN << ">> Progress saved at Checkpoint 3 (ID: " << newApp.getApplicationID() << ")" << COLOR_RESET << endl;
        return;
    }

    // Finalize submission
    newApp.setStatus("Submitted");
    newApp.setCheckpoint(4);
    
    // Calculate todays date to save as "submissionDate"
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[20];
    // Format: DD-MM-YYYY
    sprintf(buffer, "%02d-%02d-%04d", ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year);
    newApp.setSubmissionDate(string(buffer));

    appManager.saveApplication(newApp);

    printSuccess("Application Submitted Successfully!");
    cout << "Your Application ID is: " << newApp.getApplicationID() << endl;
    cout << "Press Enter to return to main menu...";

    string dummy;
    getline(cin, dummy);
    state = "MAIN_MENU";
}