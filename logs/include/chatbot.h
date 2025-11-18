#ifndef CHATBOT_H
#define CHATBOT_H

#include <string>
using std::string; 

/**
 * Displays a welcome header for the chatbot session.
 * @return void
 */
void displayWelcomeHeader();

/**
 * Displays a goodbye footer when the chatbot session ends.
 * @return void
 */
void displayGoodbyeFooter();

/**
 * Main chatbot loop that handles user interaction and state management.
 * Manages conversation flow through MAIN_MENU, LOAN_CATEGORY, and HOME_LOAN_AREA states.
 * @return void
 */
void runChatbot();

/**
 * Handles user input in the MAIN_MENU state.
 * @param userInput: the original user input (case-sensitive for state transitions)
 * @param lowerInput: lowercase version for utterance lookups
 * @param state: reference to current state string (modified by this function)
 * @return void
 */
void handleMainMenu(std::string userInput, std::string lowerInput, std::string &state);

/**
 * Handles user input in the LOAN_CATEGORY state.
 * @param userInput: the original user input
 * @param lowerInput: lowercase version for utterance lookups
 * @param state: reference to current state string (modified by this function)
 * @return void
 */
void handleLoanCategory(std::string userInput, std::string lowerInput, std::string &state);

/**
 * Handles user input in the HOME_LOAN_AREA state.
 * User selects area 1-4 to view loan plans, then transitions to monthly installment view.
 * @param userInput: the original user input
 * @param lowerInput: lowercase version for utterance lookups
 * @param state: reference to current state string (modified by this function)
 * @param currentArea: reference to track which area the user is viewing (modified by this function)
 * @return void
 */
void handleHomeLoanArea(std::string userInput, std::string lowerInput, std::string &state, std::string &currentArea);

/**
 * Handles user input in the VIEW_MONTHLY_INSTALLMENTS state.
 * User can select a specific plan number to view its monthly installment details.
 * Allows viewing multiple plans or returning to main menu.
 * @param userInput: the original user input (plan number or A to return)
 * @param lowerInput: lowercase version for utterance lookups
 * @param state: reference to current state string (modified by this function)
 * @param currentArea: reference to the area being viewed (used to fetch correct plans)
 * @return void
 */
void handleViewMonthlyInstallments(std::string userInput, std::string lowerInput, std::string &state, std::string &currentArea);

// [Increment - 2]
/**
 * Handles application submission flow - collects all required fields from user
 * @param state: reference to current state string (modified to return to MAIN_MENU)
 * @return void
 */
void handleApplicationSubmission(string &state, string &currentArea);

/**
 * Handles querying applications by CNIC number
 * @param state: reference to current state string (modified to return to MAIN_MENU)
 * @return void
 */
void handleQueryApplications(std::string &state);

void handleCarLoan(string userInput, string lowerInput, string &state, string &currentMake);
void handleViewCarMonthlyInstallments(string userInput, string lowerInput, string &state, string &currentMake);

#endif