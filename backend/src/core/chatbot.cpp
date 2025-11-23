// Core includes
#include "core/chatbot.h"
#include "core/state_handlers.h"
#include "core/application.h"

// Helper includes
#include "helpers/utils.h"
#include "helpers/ui_display.h"

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::string;

void runChatbot() {
  displayWelcomeHeader();

  string state = "MAIN_MENU";
  string currentArea = "";
  string currentCarMake = "";
  string currentScooterMake = "";
  string currentCategory = "";
  string personalLoanSubState = ""; 


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

    // Get user input for interactive states
    string userInput;
    cout << ">> ";
    getline(cin, userInput);

    if (userInput == "X" || userInput == "x")
      break;

    string lowerInput = toLower(userInput);

    // Route to appropriate state handler
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
    } else if (state == "PERSONAL_LOAN") {
    handlePersonalLoan(userInput, lowerInput, state, currentCategory, personalLoanSubState);
    } else if (state == "VIEW_CAR_MONTHLY_INSTALLMENTS") {
      handleViewCarMonthlyInstallments(userInput, lowerInput, state, currentCarMake);
    } else if (state == "VIEW_SCOOTER_MONTHLY_INSTALLMENTS") {
      handleViewScooterMonthlyInstallments(userInput, lowerInput, state, currentScooterMake);
    } else if (state == "VIEW_MONTHLY_INSTALLMENTS") {
      handleViewMonthlyInstallments(userInput, lowerInput, state, currentArea);
    } else if (state == "VIEW_PERSONAL_INSTALLMENTS") {
      handleViewPersonalInstallments(userInput, lowerInput, state, currentCategory);
    }
  }

  displayGoodbyeFooter();
}