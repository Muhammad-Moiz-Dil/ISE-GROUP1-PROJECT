#include "../../logs/include/chatbot.h"
#include "../../logs/include/application.h"
#include "../../logs/include/car.h"
#include "../../logs/include/file_io.h"
#include "../../logs/include/loan_plan.h"
#include "../../logs/include/scooter.h"
#include "../../logs/include/utils.h"
#include <fstream>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::ifstream;
using std::string;

void runChatbot() {
  displayWelcomeHeader();

  string state = "MAIN_MENU";
  string currentArea = "";
  string currentCarMake = "";
  string currentScooterMake = "";

  while (true) {
    // Check for action states that don't need input
    if (state == "SUBMIT_APPLICATION") {
      handleApplicationSubmission(state, currentArea);
      continue;
    } else if (state == "QUERY_APPLICATIONS") {
      handleQueryApplications(state);
      continue;
    } else if (state == "RESUME_APPLICATION") {
      handleResumeApplication(state);
      continue;
    } else if (state == "CHECK_STATUS") {
      handleCheckStatus(state);
      continue;
    }

    // Now get input for interactive states
    string userInput;
    cout << ">> ";
    getline(cin, userInput);

    if (userInput == "X" || userInput == "x")
      break;

    string lowerInput = toLower(userInput);

    if (state == "MAIN_MENU") {
      handleMainMenu(userInput, lowerInput, state);
    } else if (state == "LOAN_CATEGORY") {
      handleLoanCategory(userInput, lowerInput, state);
    } else if (state == "HOME_LOAN_AREA") {
      handleHomeLoanArea(userInput, lowerInput, state, currentArea);
    } else if (state == "CAR_LOAN") {
      handleCarLoan(userInput, lowerInput, state, currentCarMake);
    } else if (state == "SCOOTER_LOAN_AREA") {
      handleScooterLoan(userInput, lowerInput, state, currentScooterMake);
    } else if (state == "VIEW_CAR_MONTHLY_INSTALLMENTS") {
      handleViewCarMonthlyInstallments(userInput, lowerInput, state,
                                       currentCarMake);
    } else if (state == "VIEW_SCOOTER_MONTHLY_INSTALLMENTS") {
      handleViewScooterMonthlyInstallments(userInput, lowerInput, state,
                                           currentScooterMake);
    } else if (state == "VIEW_MONTHLY_INSTALLMENTS") {
      handleViewMonthlyInstallments(userInput, lowerInput, state, currentArea);
    }
  }
  displayGoodbyeFooter();
}

void handleMainMenu(string userInput, string lowerInput, string &state) {
  cout << uttrObj.getResponse(lowerInput) << endl;

  if (userInput == "A" || userInput == "a") {
    state = "LOAN_CATEGORY";
  } else if (userInput == "H" || userInput == "h") {
    state = "HOME_LOAN_AREA";
  } else if (userInput == "C" || userInput == "c") {
    state = "CAR_LOAN";
  } else if (userInput == "S" || userInput == "s") {
    state = "SCOOTER_LOAN_AREA";
  } else if (userInput == "3") {
    state = "SUBMIT_APPLICATION";
  } else if (userInput == "4") {
    state = "QUERY_APPLICATIONS";
  } else if (userInput == "5") {
    state = "RESUME_APPLICATION";
  } else if (userInput == "6") {
    state = "CHECK_STATUS";
  }
}
void handleScooterLoan(string &userInput, string &lowerInput, string &state,
                       string &currentScooterMake) {
  if (userInput == "1") {
    currentScooterMake = "Make 1";
    int planCount = ScooterPlanManagerObj.getPlanCount(currentScooterMake);

    if (planCount > 0) {
      ScooterPlanManagerObj.displayScooterPlan(currentScooterMake);
      cout << "\nWould you like to view monthly installments for any plan?\n";
      cout << "(Enter plan number 1-" << planCount
           << ", or A to return to main menu)\n";
      state = "VIEW_SCOOTER_MONTHLY_INSTALLMENTS";
    } else {
      cout << "No such make found." << endl;
      state = "MAIN_MENU";
    }
  } else if (userInput == "2") {
    currentScooterMake = "Make 2";
    int planCount = CarPlanManagerObj.getPlanCount(currentScooterMake);

    if (planCount > 0) {
      CarPlanManagerObj.displayCarPlan(currentScooterMake);
      cout << "\nWould you like to view monthly installments for any plan?\n";
      cout << "(Enter plan number 1-" << planCount
           << ", or A to return to main menu)\n";
      state = "VIEW_SCOOTER_MONTHLY_INSTALLMENTS";
    } else {
      cout << "No such make found." << endl;
      state = "MAIN_MENU";
    }
  } else {
    bool isNumeric = true;
    for (char c : userInput) {
      if (!isdigit(c)) {
        isNumeric = false;
        break;
      }
    }

    if (isNumeric && userInput.length() > 0) {
      cout << "You probably meant to select from 1-2. Please try again."
           << endl;
    } else {
      cout << uttrObj.getResponse(lowerInput) << endl;
    }
  }
}
void handleLoanCategory(string userInput, string lowerInput, string &state) {
  cout << uttrObj.getResponse(lowerInput) << endl;

  if (userInput == "H" || userInput == "h") {
    state = "HOME_LOAN_AREA";
  } else if (userInput == "C" || userInput == "c") {
    state = "CAR_LOAN";
  } else if (userInput == "S" || userInput == "s") {
    state = "SCOOTER_LOAN_AREA";
  } else if (userInput == "A" || userInput == "a") {
    return;
  }
}

void handleCarLoan(string &userInput, string &lowerInput, string &state,
                   string &currentCarMake) {
  if (userInput == "1") {
    currentCarMake = "Make 1";
    int planCount = CarPlanManagerObj.getPlanCount(currentCarMake);

    if (planCount > 0) {
      CarPlanManagerObj.displayCarPlan(currentCarMake);
      cout << "\nWould you like to view monthly installments for any plan?\n";
      cout << "(Enter plan number 1-" << planCount
           << ", or A to return to main menu)\n";
      state = "VIEW_CAR_MONTHLY_INSTALLMENTS";
    } else {
      cout << "No such make found." << endl;
      state = "MAIN_MENU";
    }
  } else if (userInput == "2") {
    currentCarMake = "Make 2";
    int planCount = CarPlanManagerObj.getPlanCount(currentCarMake);

    if (planCount > 0) {
      CarPlanManagerObj.displayCarPlan(currentCarMake);
      cout << "\nWould you like to view monthly installments for any plan?\n";
      cout << "(Enter plan number 1-" << planCount
           << ", or A to return to main menu)\n";
      state = "VIEW_CAR_MONTHLY_INSTALLMENTS";
    } else {
      cout << "No such make found." << endl;
      state = "MAIN_MENU";
    }
  } else {
    bool isNumeric = true;
    for (char c : userInput) {
      if (!isdigit(c)) {
        isNumeric = false;
        break;
      }
    }

    if (isNumeric && userInput.length() > 0) {
      cout << "You probably meant to select from 1-2. Please try again."
           << endl;
    } else {
      cout << uttrObj.getResponse(lowerInput) << endl;
    }
  }
}

void handleHomeLoanArea(string userInput, string lowerInput, string &state,
                        string &currentArea) {
  if (userInput == "1") {
    currentArea = "Area 1";
    int planCount = LoanPlanManagerObj.getPlanCount(currentArea);

    if (planCount > 0) // Check if area exists
    {
      LoanPlanManagerObj.displayLoanPlan(currentArea);
      cout << "\nWould you like to view monthly installments for any plan?\n";
      cout << "(Enter plan number 1-" << planCount
           << ", or A to return to main menu)\n";
      state = "VIEW_MONTHLY_INSTALLMENTS";
    } else {
      cout << "No such area found." << endl;
      state = "MAIN_MENU"; // Return to main menu
    }
  } else if (userInput == "2") {
    currentArea = "Area 2";
    int planCount = LoanPlanManagerObj.getPlanCount(currentArea);

    if (planCount > 0) {
      LoanPlanManagerObj.displayLoanPlan(currentArea);
      cout << "\nWould you like to view monthly installments for any plan?\n";
      cout << "(Enter plan number 1-" << planCount
           << ", or A to return to main menu)\n";
      state = "VIEW_MONTHLY_INSTALLMENTS";
    } else {
      cout << "No such area found." << endl;
      state = "MAIN_MENU";
    }
  } else if (userInput == "3") {
    currentArea = "Area 3";
    int planCount = LoanPlanManagerObj.getPlanCount(currentArea);

    if (planCount > 0) {
      LoanPlanManagerObj.displayLoanPlan(currentArea);
      cout << "\nWould you like to view monthly installments for any plan?"
           << endl;
      cout << "(Enter plan number 1-" << planCount
           << ", or A to return to main menu)" << endl;
      state = "VIEW_MONTHLY_INSTALLMENTS";
    } else {
      cout << "No such area found." << endl;
      state = "MAIN_MENU";
    }
  } else if (userInput == "4") {
    currentArea = "Area 4";
    int planCount = LoanPlanManagerObj.getPlanCount(currentArea);

    if (planCount > 0) {
      LoanPlanManagerObj.displayLoanPlan(currentArea);
      cout << "\nWould you like to view monthly installments for any plan?"
           << endl;
      cout << "(Enter plan number 1-" << planCount
           << ", or A to return to main menu)" << endl;
      state = "VIEW_MONTHLY_INSTALLMENTS";
    } else {
      cout << "No such area found." << endl;
      state = "MAIN_MENU";
    }
  } else {
    bool isNumeric = true;
    for (char c : userInput) {
      if (!isdigit(c)) {
        isNumeric = false;
        break;
      }
    }

    if (isNumeric && userInput.length() > 0) {
      cout << "You probably meant to select from 1-4. Please try again."
           << endl;
    } else {
      cout << uttrObj.getResponse(lowerInput) << endl;
    }
  }
}
void handleViewScooterMonthlyInstallments(string userInput, string lowerInput,
                                          string &state, string &currentMake) {
  userInput = trim(userInput);
  lowerInput = toLower(userInput);

  int planCount = ScooterPlanManagerObj.getPlanCount(currentMake);

  // Check if user wants to return to main menu
  if (userInput == "A" || userInput == "a") {
    state = "MAIN_MENU";
    cout << uttrObj.getResponse(lowerInput) << endl;
    return;
  }

  // Check if user wants to submit application
  if (userInput == "S" || userInput == "s") {
    state = "SUBMIT_APPLICATION";
    return;
  }

  // Check if input is a valid plan number
  bool isNumeric = true;
  bool hasNegativeSign = false;

  // Check for negative sign at start
  if (!userInput.empty() && userInput[0] == '-') {
    hasNegativeSign = true;
  }

  // Check if all characters (after optional negative sign) are digits
  for (int i = (hasNegativeSign ? 1 : 0); i < userInput.length(); i++) {
    if (!isdigit(userInput[i])) {
      isNumeric = false;
      break;
    }
  }

  // If it's a number (positive or negative)
  if (isNumeric && userInput.length() > 0 &&
      (hasNegativeSign || isdigit(userInput[0]))) {
    int planChoice = stoi(userInput);

    if (planChoice >= 1 && planChoice <= planCount) {
      ScooterPlanManagerObj.displayMonthlyInstallment(currentMake,
                                                      planChoice - 1);

      cout << "\nWhat would you like to do next?" << endl;
      cout << " S - Submit loan application" << endl;
      cout << " (Enter plan number 1-" << planCount << " to view another)"
           << endl;
      cout << " A - Return to main menu" << endl;
    } else {
      cout << "You probably meant to select from 1-" << planCount
           << ". Please try again." << endl;
    }
  } else {
    // Non-numeric input
    cout << uttrObj.getResponse(lowerInput) << endl;
  }
}
void handleViewCarMonthlyInstallments(string userInput, string lowerInput,
                                      string &state, string &currentMake) {
  userInput = trim(userInput);
  lowerInput = toLower(userInput);

  int planCount = CarPlanManagerObj.getPlanCount(currentMake);

  // Check if user wants to return to main menu
  if (userInput == "A" || userInput == "a") {
    state = "MAIN_MENU";
    cout << uttrObj.getResponse(lowerInput) << endl;
    return;
  }

  // Check if user wants to submit application
  if (userInput == "S" || userInput == "s") {
    state = "SUBMIT_APPLICATION";
    return;
  }

  // Check if input is a valid plan number
  bool isNumeric = true;
  bool hasNegativeSign = false;

  // Check for negative sign at start
  if (!userInput.empty() && userInput[0] == '-') {
    hasNegativeSign = true;
  }

  // Check if all characters (after optional negative sign) are digits
  for (int i = (hasNegativeSign ? 1 : 0); i < userInput.length(); i++) {
    if (!isdigit(userInput[i])) {
      isNumeric = false;
      break;
    }
  }

  // If it's a number (positive or negative)
  if (isNumeric && userInput.length() > 0 &&
      (hasNegativeSign || isdigit(userInput[0]))) {
    int planChoice = stoi(userInput);

    if (planChoice >= 1 && planChoice <= planCount) {
      CarPlanManagerObj.displayMonthlyInstallment(currentMake, planChoice - 1);

      cout << "\nWhat would you like to do next?" << endl;
      cout << " S - Submit loan application" << endl;
      cout << " (Enter plan number 1-" << planCount << " to view another)"
           << endl;
      cout << " A - Return to main menu" << endl;
    } else {
      cout << "You probably meant to select from 1-" << planCount
           << ". Please try again." << endl;
    }
  } else {
    // Non-numeric input
    cout << uttrObj.getResponse(lowerInput) << endl;
  }
}

void handleViewMonthlyInstallments(string userInput, string lowerInput,
                                   string &state, string &currentArea) {
  userInput = trim(userInput);
  lowerInput = toLower(userInput); // Recalculate lowerInput after trim
  int planCount = LoanPlanManagerObj.getPlanCount(currentArea);

  // Check if user wants to return to main menu
  if (userInput == "A" || userInput == "a") {
    state = "MAIN_MENU";
    cout << uttrObj.getResponse(lowerInput) << endl;
    return;
  }

  // Check if user wants to submit application
  if (userInput == "S" || userInput == "s") {
    state = "SUBMIT_APPLICATION";
    return;
  }

  // Check if input is a valid plan number
  bool isNumeric = true;
  bool hasNegativeSign = false;

  // Check for negative sign at start
  if (!userInput.empty() && userInput[0] == '-') {
    hasNegativeSign = true;
  }

  // Check if all characters (after optional negative sign) are digits
  for (int i = (hasNegativeSign ? 1 : 0); i < userInput.length(); i++) {
    if (!isdigit(userInput[i])) {
      isNumeric = false;
      break;
    }
  }

  // If it's a number (positive or negative)
  if (isNumeric && userInput.length() > 0 &&
      (hasNegativeSign || isdigit(userInput[0]))) {
    int planChoice = stoi(userInput);

    if (planChoice >= 1 && planChoice <= planCount) {
      LoanPlanManagerObj.displayMonthlyInstallment(currentArea, planChoice - 1);

      cout << "\nWhat would you like to do next?" << endl;
      cout << " S - Submit loan application" << endl;
      cout << " (Enter plan number 1-" << planCount << " to view another)"
           << endl;
      cout << " A - Return to main menu" << endl;
    } else {
      cout << "You probably meant to select from 1-" << planCount
           << ". Please try again." << endl;
    }
  } else {
    // Non-numeric input
    cout << uttrObj.getResponse(lowerInput) << endl;
  }
}

void displayWelcomeHeader() {
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

void displayGoodbyeFooter() {
  cout << "\n";
  cout << "\033[1;31m" // Bright Red
       << "=============================================\n";
  cout << "          CHATBOT SESSION ENDED!           \n";
  cout << "=============================================\n";
  cout << "\033[0m\n"; // Reset color
}


// ============================================================================
// NEW FUNCTIONS FOR INCREMENT 2 & 3
// ============================================================================

void handleCheckStatus(string &state) {
  string input;
  cout << "\n\033[1;36mCHECK APPLICATION STATUS\033[0m\n";
  cout << "Enter your CNIC (without dashes) or Application ID:\n";
  cout << ">> ";
  getline(cin, input);
  input = trim(input);

  if (input == "X" || input == "x") {
    state = "MAIN_MENU";
    return;
  }

  // Try to find by ID first
  Application *app = appManager.getApplicationByID(input);
  if (app != nullptr) {
    cout << "\nApplication Found:\n";
    cout << "ID: " << app->getApplicationID() << endl;
    cout << "Name: " << app->getFullName() << endl;
    cout << "Status: ";
    if (app->getStatus() == "Approved")
      cout << "\033[1;32mApproved\033[0m";
    else if (app->getStatus() == "Rejected")
      cout << "\033[1;31mRejected\033[0m";
    else
      cout << "\033[1;33m" << app->getStatus() << "\033[0m";
    cout << endl;
  } else {
    // Try by CNIC
    vector<Application> apps = appManager.getApplicationsByCNIC(input);
    if (apps.empty()) {
      cout << "\n\033[1;31mNo application found with this ID or CNIC.\033[0m\n";
    } else {
      cout << "\nFound " << apps.size() << " application(s):\n";
      for (const auto &a : apps) {
        cout << "--------------------------------\n";
        cout << "ID: " << a.getApplicationID() << endl;
        cout << "Loan Type: " << a.getLoanType() << endl;
        cout << "Status: ";
        if (a.getStatus() == "Approved")
          cout << "\033[1;32mApproved\033[0m";
        else if (a.getStatus() == "Rejected")
          cout << "\033[1;31mRejected\033[0m";
        else
          cout << "\033[1;33m" << a.getStatus() << "\033[0m";
        cout << endl;
      }
    }
  }

  cout << "\nPress Enter to return to main menu...";
  getline(cin, input);
  state = "MAIN_MENU";
}

void handleResumeApplication(string &state) {
  string id, cnic;
  cout << "\n\033[1;36mRESUME APPLICATION\033[0m\n";

  cout << "Enter Application ID: ";
  getline(cin, id);
  id = trim(id);
  if (id == "X" || id == "x") {
    state = "MAIN_MENU";
    return;
  }

  cout << "Enter CNIC: ";
  getline(cin, cnic);
  cnic = trim(cnic);
  if (cnic == "X" || cnic == "x") {
    state = "MAIN_MENU";
    return;
  }

  Application *app = appManager.getApplicationByID(id);
  if (app != nullptr && app->getCNIC() == cnic) {
    if (app->getStatus() == "Submitted" || app->getStatus() == "Approved" ||
        app->getStatus() == "Rejected") {
      cout << "\n\033[1;33mThis application is already "
              "completed/submitted.\033[0m\n";
      cout << "Status: " << app->getStatus() << endl;
      cout << "Press Enter to return...";
      getline(cin, id);
      state = "MAIN_MENU";
      return;
    }

    // Resume flow
    cout << "\n\033[1;32mResuming application from Checkpoint "
         << app->getCheckpoint() << "...\033[0m\n";

    if (app->getCheckpoint() < 1) {
      if (!collectPersonalInformation(*app, state))
        return;
      app->setCheckpoint(1);
      appManager.saveApplication(*app);
    }

    if (app->getCheckpoint() < 2) {
      if (!collectFinancialInformation(*app, state))
        return;
      app->setCheckpoint(2);
      appManager.saveApplication(*app);
    }

    if (app->getCheckpoint() < 3) {
      if (!collectReferenceInformation(*app, state))
        return;
      app->setCheckpoint(3);
      appManager.saveApplication(*app);
    }

    if (!collectDocuments(*app, state))
      return;

    // Finalize
    app->setStatus("Submitted");
    app->setCheckpoint(4); // Completed
    appManager.saveApplication(*app);

    cout << "\n\033[1;32mApplication Submitted Successfully!\033[0m\n";
    cout << "Your Application ID is: " << app->getApplicationID() << endl;
    cout << "Press Enter to return to main menu...";
    getline(cin, id);
    state = "MAIN_MENU";
  } else {
    cout << "\n\033[1;31mInvalid Application ID or CNIC.\033[0m\n";
    cout << "Press Enter to return...";
    getline(cin, id);
    state = "MAIN_MENU";
  }
}

void handleApplicationSubmission(string &state, string &currentArea) {
  Application newApp;
  newApp.setApplicationID(appManager.generateApplicationID());
  newApp.setLoanDetails(currentArea, "Standard Plan");

  cout << "\n\033[1;33m";
  cout << "=============================================\n";
  cout << "       LOAN APPLICATION FORM" << endl;
  cout << "=============================================\n";
  cout << "You are applying for: " << currentArea << endl;
  cout << "Application ID: " << newApp.getApplicationID() << endl;
  cout << "=============================================\n";
  cout << "Type 'X' at any time to save and exit (Resume later)\n\n";
  cout << "\033[0m\n";

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

  newApp.setStatus("Submitted");
  newApp.setCheckpoint(4);
  appManager.saveApplication(newApp);

  cout << "\n\033[1;32mApplication Submitted Successfully!\033[0m\n";
  cout << "Your Application ID is: " << newApp.getApplicationID() << endl;
  cout << "Press Enter to return to main menu...";
  string dummy;
  getline(cin, dummy);
  state = "MAIN_MENU";
}

bool collectPersonalInformation(Application &app, string &state) {
  string input;
  cout << "\033[1;36mPERSONAL INFORMATION:\033[0m\n\n";

  // Full Name
  while (true) {
    cout << "Full Name: ";
    getline(cin, input);
    input = trim(input);
    if (input == "X" || input == "x") {
      state = "MAIN_MENU";
      return false;
    }
    if (input.empty()) {
      cout << "\033[1;31mError: Name cannot be empty.\033[0m\n";
      continue;
    }
    if (!isValidName(input)) {
      cout << "\033[1;31mError: Invalid name format.\033[0m\n";
      continue;
    }
    app.setFullName(input);
    break;
  }

  // Father's Name
  while (true) {
    cout << "Father's Name: ";
    getline(cin, input);
    input = trim(input);
    if (input == "X" || input == "x") {
      state = "MAIN_MENU";
      return false;
    }
    if (input.empty()) {
      cout << "\033[1;31mError: Name cannot be empty.\033[0m\n";
      continue;
    }
    if (!isValidName(input)) {
      cout << "\033[1;31mError: Invalid name format.\033[0m\n";
      continue;
    }
    app.setFathersName(input);
    break;
  }

  // Postal Address
  while (true) {
    cout << "Postal Address: ";
    getline(cin, input);
    input = trim(input);
    if (input == "X" || input == "x") {
      state = "MAIN_MENU";
      return false;
    }
    if (input.empty()) {
      cout << "\033[1;31mError: Address cannot be empty.\033[0m\n";
      continue;
    }
    app.setPostalAddress(input);
    break;
  }

  // Contact
  while (true) {
    cout << "Contact Number (03xxxxxxxxx): ";
    getline(cin, input);
    input = trim(input);
    if (input == "X" || input == "x") {
      state = "MAIN_MENU";
      return false;
    }
    if (!isValidContact(input)) {
      cout << "\033[1;31mError: Invalid contact number.\033[0m\n";
      continue;
    }
    app.setContact(input);
    break;
  }

  // Email
  while (true) {
    cout << "Email Address: ";
    getline(cin, input);
    input = trim(input);
    if (input == "X" || input == "x") {
      state = "MAIN_MENU";
      return false;
    }
    if (!isValidEmail(input)) {
      cout << "\033[1;31mError: Invalid email address.\033[0m\n";
      continue;
    }
    app.setEmail(toLower(input));
    break;
  }

  // CNIC
  while (true) {
    cout << "CNIC (13 digits, no dashes): ";
    getline(cin, input);
    input = trim(input);
    if (input == "X" || input == "x") {
      state = "MAIN_MENU";
      return false;
    }
    if (!isValidCNIC(input)) {
      cout << "\033[1;31mError: Invalid CNIC.\033[0m\n";
      continue;
    }
    app.setCNIC(input);
    break;
  }

  // CNIC Expiry
  while (true) {
    cout << "CNIC Expiry Date (DD-MM-YYYY): ";
    getline(cin, input);
    input = trim(input);
    if (input == "X" || input == "x") {
      state = "MAIN_MENU";
      return false;
    }
    if (!isValidDate(input)) {
      cout << "\033[1;31mError: Invalid date format.\033[0m\n";
      continue;
    }
    app.setCNICExpiry(input);
    break;
  }

  // Employment
  string employment[] = {"Self-employed", "Salaried", "Retired", "Unemployed"};
  while (true) {
    cout << "\nEmployment Status:\n1. Self-employed\n2. Salaried\n3. "
            "Retired\n4. Unemployed\nChoose (1-4): ";
    getline(cin, input);
    input = trim(input);
    if (input == "X" || input == "x") {
      state = "MAIN_MENU";
      return false;
    }
    if (!isValidMenuChoice(input, 1, 4)) {
      cout << "\033[1;31mError: Invalid choice.\033[0m\n";
      continue;
    }
    app.setEmployment(employment[stoi(input) - 1]);
    break;
  }

  // Marital
  string marital[] = {"Single", "Married", "Divorced", "Widowed"};
  while (true) {
    cout << "\nMarital Status:\n1. Single\n2. Married\n3. Divorced\n4. "
            "Widowed\nChoose (1-4): ";
    getline(cin, input);
    input = trim(input);
    if (input == "X" || input == "x") {
      state = "MAIN_MENU";
      return false;
    }
    if (!isValidMenuChoice(input, 1, 4)) {
      cout << "\033[1;31mError: Invalid choice.\033[0m\n";
      continue;
    }
    app.setMarital(marital[stoi(input) - 1]);
    break;
  }

  // Gender
  string gender[] = {"Male", "Female", "Other"};
  while (true) {
    cout << "\nGender:\n1. Male\n2. Female\n3. Other\nChoose (1-3): ";
    getline(cin, input);
    input = trim(input);
    if (input == "X" || input == "x") {
      state = "MAIN_MENU";
      return false;
    }
    if (!isValidMenuChoice(input, 1, 3)) {
      cout << "\033[1;31mError: Invalid choice.\033[0m\n";
      continue;
    }
    app.setGender(gender[stoi(input) - 1]);
    break;
  }

  return true;
}

bool collectFinancialInformation(Application &app, string &state) {
  string input;
  cout << "\n\033[1;36mFINANCIAL INFORMATION:\033[0m\n\n";

  // Dependents
  while (true) {
    cout << "Number of Dependents: ";
    getline(cin, input);
    input = trim(input);
    if (input == "X" || input == "x") {
      state = "MAIN_MENU";
      return false;
    }
    if (!isValidPositiveInteger(input)) {
      cout << "\033[1;31mError: Invalid number.\033[0m\n";
      continue;
    }
    app.setDependents(stoi(input));
    break;
  }

  // Annual Income
  while (true) {
    cout << "Annual Income (PKR): ";
    getline(cin, input);
    input = trim(input);
    if (input == "X" || input == "x") {
      state = "MAIN_MENU";
      return false;
    }
    if (!isValidPositiveAmount(input)) {
      cout << "\033[1;31mError: Invalid amount.\033[0m\n";
      continue;
    }
    app.setAnnualIncome(stol(input));
    break;
  }

  // Avg Bill
  while (true) {
    cout << "Average Monthly Electricity Bill (PKR): ";
    getline(cin, input);
    input = trim(input);
    if (input == "X" || input == "x") {
      state = "MAIN_MENU";
      return false;
    }
    if (!isValidPositiveInteger(input)) {
      cout << "\033[1;31mError: Invalid amount.\033[0m\n";
      continue;
    }
    app.setAvgElectricityBill(stol(input));
    break;
  }

  // Current Bill
  while (true) {
    cout << "Current Electricity Bill (PKR): ";
    getline(cin, input);
    input = trim(input);
    if (input == "X" || input == "x") {
      state = "MAIN_MENU";
      return false;
    }
    if (!isValidPositiveInteger(input)) {
      cout << "\033[1;31mError: Invalid amount.\033[0m\n";
      continue;
    }
    app.setCurrentElectricityBill(stol(input));
    break;
  }

  // Existing Loan
  while (true) {
    cout << "\nDo you have any existing loans? (Y/N): ";
    getline(cin, input);
    input = trim(input);
    if (input == "X" || input == "x") {
      state = "MAIN_MENU";
      return false;
    }
    if (input.empty() ||
        (toupper(input[0]) != 'Y' && toupper(input[0]) != 'N')) {
      cout << "\033[1;31mError: Enter Y or N.\033[0m\n";
      continue;
    }

    if (toupper(input[0]) == 'Y') {
      ExistingLoan loan;
      // Active?
      while (true) {
        cout << "Is the loan active? (Y/N): ";
        getline(cin, input);
        if (input == "X" || input == "x") {
          state = "MAIN_MENU";
          return false;
        }
        if (toupper(input[0]) == 'Y') {
          loan.isActive = true;
          break;
        }
        if (toupper(input[0]) == 'N') {
          loan.isActive = false;
          break;
        }
      }
      // Total Amount
      while (true) {
        cout << "Total Loan Amount: ";
        getline(cin, input);
        if (input == "X" || input == "x") {
          state = "MAIN_MENU";
          return false;
        }
        if (isValidPositiveAmount(input)) {
          loan.totalAmount = stol(input);
          break;
        }
      }
      // Returned
      while (true) {
        cout << "Amount Returned: ";
        getline(cin, input);
        if (input == "X" || input == "x") {
          state = "MAIN_MENU";
          return false;
        }
        if (isValidPositiveInteger(input)) {
          loan.amountReturned = stol(input);
          break;
        }
      }
      // Due
      while (true) {
        cout << "Amount Due: ";
        getline(cin, input);
        if (input == "X" || input == "x") {
          state = "MAIN_MENU";
          return false;
        }
        if (isValidPositiveInteger(input)) {
          loan.amountDue = stol(input);
          break;
        }
      }
      // Bank
      while (true) {
        cout << "Bank Name: ";
        getline(cin, input);
        if (input == "X" || input == "x") {
          state = "MAIN_MENU";
          return false;
        }
        if (!input.empty()) {
          loan.bankName = input;
          break;
        }
      }
      // Category
      while (true) {
        cout << "Category (Car/Home/Bike): ";
        getline(cin, input);
        if (input == "X" || input == "x") {
          state = "MAIN_MENU";
          return false;
        }
        if (!input.empty()) {
          loan.category = input;
          break;
        }
      }
      app.setExistingLoan(loan);
    }
    break;
  }
  return true;
}

bool collectReferenceInformation(Application &app, string &state) {
  string input;
  cout << "\n\033[1;36mREFERENCE INFORMATION:\033[0m\n\n";

  Referee ref1, ref2;

  // Referee 1
  cout << "REFEREE 1:\n";
  while (true) {
    cout << "Name: ";
    getline(cin, input);
    if (input == "X" || input == "x") {
      state = "MAIN_MENU";
      return false;
    }
    if (isValidName(input)) {
      ref1.name = input;
      break;
    }
  }
  while (true) {
    cout << "CNIC: ";
    getline(cin, input);
    if (input == "X" || input == "x") {
      state = "MAIN_MENU";
      return false;
    }
    if (isValidCNIC(input)) {
      ref1.cnic = input;
      break;
    }
  }
  while (true) {
    cout << "Issue Date (DD-MM-YYYY): ";
    getline(cin, input);
    if (input == "X" || input == "x") {
      state = "MAIN_MENU";
      return false;
    }
    if (isValidDate(input)) {
      ref1.issueDate = input;
      break;
    }
  }
  while (true) {
    cout << "Phone: ";
    getline(cin, input);
    if (input == "X" || input == "x") {
      state = "MAIN_MENU";
      return false;
    }
    if (isValidContact(input)) {
      ref1.phone = input;
      break;
    }
  }
  while (true) {
    cout << "Email: ";
    getline(cin, input);
    if (input == "X" || input == "x") {
      state = "MAIN_MENU";
      return false;
    }
    if (isValidEmail(input)) {
      ref1.email = input;
      break;
    }
  }
  app.setReferee1(ref1);

  // Referee 2
  cout << "\nREFEREE 2:\n";
  while (true) {
    cout << "Name: ";
    getline(cin, input);
    if (input == "X" || input == "x") {
      state = "MAIN_MENU";
      return false;
    }
    if (isValidName(input)) {
      ref2.name = input;
      break;
    }
  }
  while (true) {
    cout << "CNIC: ";
    getline(cin, input);
    if (input == "X" || input == "x") {
      state = "MAIN_MENU";
      return false;
    }
    if (isValidCNIC(input)) {
      ref2.cnic = input;
      break;
    }
  }
  while (true) {
    cout << "Issue Date (DD-MM-YYYY): ";
    getline(cin, input);
    if (input == "X" || input == "x") {
      state = "MAIN_MENU";
      return false;
    }
    if (isValidDate(input)) {
      ref2.issueDate = input;
      break;
    }
  }
  while (true) {
    cout << "Phone: ";
    getline(cin, input);
    if (input == "X" || input == "x") {
      state = "MAIN_MENU";
      return false;
    }
    if (isValidContact(input)) {
      ref2.phone = input;
      break;
    }
  }
  while (true) {
    cout << "Email: ";
    getline(cin, input);
    if (input == "X" || input == "x") {
      state = "MAIN_MENU";
      return false;
    }
    if (isValidEmail(input)) {
      ref2.email = input;
      break;
    }
  }
  app.setReferee2(ref2);

  return true;
}

bool collectDocuments(Application &app, string &state) {
  string input;
  cout << "\n\033[1;36mDOCUMENT UPLOAD (Paths):\033[0m\n";
  cout << "Enter the full path or filename for the following documents:\n";

  string cnicF, cnicB, bill, salary;

  cout << "CNIC Front: ";
  getline(cin, cnicF);
  if (cnicF == "X" || cnicF == "x") {
    state = "MAIN_MENU";
    return false;
  }
  cout << "CNIC Back: ";
  getline(cin, cnicB);
  if (cnicB == "X" || cnicB == "x") {
    state = "MAIN_MENU";
    return false;
  }
  cout << "Electricity Bill: ";
  getline(cin, bill);
  if (bill == "X" || bill == "x") {
    state = "MAIN_MENU";
    return false;
  }
  cout << "Salary Slip: ";
  getline(cin, salary);
  if (salary == "X" || salary == "x") {
    state = "MAIN_MENU";
    return false;
  }

  app.setDocumentPaths(cnicF, cnicB, bill, salary);
  return true;
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