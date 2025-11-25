#include "core/chatbot.h"
#include "core/state_handlers.h"
#include "core/application.h"
#include "core/file_io.h"
#include "core/chat_corpus.h"
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
    // Action States (No User Input Required)
    if (state == "SUBMIT_APPLICATION") {
      handleApplicationSubmission(state, currentArea);
      continue;
    } else if (state == "RESUME_APPLICATION") {
      handleResumeApplication(state);
      continue;
    } else if (state == "CHECK_STATUS") {
      handleCheckStatus(state);
      continue;
    }

    // Get User Input ONCE 
    string userInput;
    cout << ">> ";
    getline(cin, userInput);

    if (userInput == "X" || userInput == "x")
      break;

    string lowerInput = toLower(userInput);

    // ========================================
    // Global Navigation Shortcuts
    // ========================================
    if (userInput == "A" || userInput == "a") {
      state = "LOAN_CATEGORY";
    } 
    else if (userInput == "H" || userInput == "h") {
      cout << "You are applying for a home loan. Please select area. Options are 1, 2, 3, 4" << endl;
      state = "HOME_LOAN_AREA";
      continue;
    }
    else if (userInput == "C" || userInput == "c") {
      cout << "You are applying for a car loan. Please select car options. Options are 1, 2." << endl;
      state = "CAR_LOAN";
      continue;
    }
    else if (userInput == "E" || userInput == "e") {
      cout << "You are applying for a scooter loan. Please select scooter options. Options are 1, 2." << endl;
      state = "SCOOTER_LOAN_AREA";
      continue;
    }
    else if (userInput == "P" || userInput == "p") {
      cout << "You are applying for a personal loan. Please select options. Options are 1, 2, 3." << endl;
      state = "PERSONAL_LOAN";
      continue;
    }
    else if (userInput == "5") {
      state = "RESUME_APPLICATION";
      continue;
    } 
    else if (userInput == "6") {
      state = "CHECK_STATUS";
      continue;
    }

    // ========================================
    // Route to State Handlers
    // ========================================
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