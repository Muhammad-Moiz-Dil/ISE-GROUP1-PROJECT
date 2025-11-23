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


string state = "MAIN_MENU";
void runChatbot()
{
  displayWelcomeHeader();

  string currentArea = "";
  string currentCarMake = "";
  string currentScooterMake = "";
  string currentCategory = "";
  string personalLoanSubState = "";

  while (true)
  {
    if (state == "GENERAL_CONVERSATION")
    {
      startGeneralConversation();
    }
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
    else if (state == "RESUME_APPLICATION")
    {
      handleResumeApplication(state);
      continue;
    }
    else if (state == "CHECK_STATUS")
    {
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
    else if (state == "PERSONAL_LOAN")
    {
      handlePersonalLoan(userInput, lowerInput, state, currentCategory, personalLoanSubState);
    }
    else if (state == "VIEW_CAR_MONTHLY_INSTALLMENTS")
    {
      handleViewCarMonthlyInstallments(userInput, lowerInput, state, currentCarMake);
    }
    else if (state == "VIEW_SCOOTER_MONTHLY_INSTALLMENTS")
    {
      handleViewScooterMonthlyInstallments(userInput, lowerInput, state, currentScooterMake);
    }
    else if (state == "VIEW_MONTHLY_INSTALLMENTS")
    {
      handleViewMonthlyInstallments(userInput, lowerInput, state, currentArea);
    }
    else if (state == "VIEW_PERSONAL_INSTALLMENTS")
    {
      handleViewPersonalInstallments(userInput, lowerInput, state, currentCategory);
    }
  }

  displayGoodbyeFooter();
}
void startGeneralConversation()
{
  ChatCorpus &corpus = getChatCorpus();

  // Use your colored styling
  cout << "\n"
       << COLOR_GREEN;
  cout << "=============================================" << endl;
  cout << "   General Conversation Mode Active        " << endl;
  cout << "=============================================" << COLOR_RESET << endl;
  cout << COLOR_YELLOW << "Chat naturally with me!" << COLOR_RESET << endl;
  cout << COLOR_YELLOW << "Type 'back' or 'B' to return to main menu." << COLOR_RESET << endl;
  cout << COLOR_GREEN << "=============================================" << COLOR_RESET << endl;
  cout << endl;

  string userInput;

  while (true)
  {
    cout << COLOR_CYAN << "You: " << COLOR_RESET;
    getline(cin, userInput);

    if (userInput == "A" || userInput == "a")
    {
        state = "LOAN_CATEGORY";
        break;
    }
    else if (userInput == "3")
    {
      state = "SUBMIT_APPLICATION";
      break;
    }
    else if (userInput == "4")
    {
      state = "QUERY_APPLICATIONS";
       break;
    }
    else if (userInput == "H" || userInput == "h")
    {
      state = "HOME_LOAN_AREA";
       break;
    }
    else if (userInput == "C" || userInput == "c")
    {
      state = "CAR_LOAN";
       break;
    }
    else if (userInput == "S" || userInput == "s")
    {
      state = "SCOOTER_LOAN_AREA";
       break;
    }
    else if (userInput == "P" || userInput == "p")
    {
      state = "PERSONAL_LOAN";
       break;
    }
    else if (userInput == "X" || userInput == "x")
    {
       displayGoodbyeFooter();
       exit(0);
    }
    else
    {
      // Exit conditions
      string lowerInput = toLower(userInput);
      if (lowerInput == "back" || lowerInput == "b" ||
          lowerInput == "exit" || lowerInput == "quit")
      {
        cout << COLOR_YELLOW << "\nReturning to main menu...\n"
             << COLOR_RESET << endl;
        break;
      }

      // Skip empty input
      if (userInput.empty())
      {
        continue;
      }

      // Get response from corpus using IoU matching
      string response = corpus.getResponse(userInput);
      cout << COLOR_GREEN << "Bot: " << COLOR_RESET << response << "\n"
           << endl;
    }
  }
}