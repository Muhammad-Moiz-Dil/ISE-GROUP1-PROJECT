#ifndef STATE_HANDLERS_H
#define STATE_HANDLERS_H

#include <string>

using std::string;

// ==================== STATE HANDLER FUNCTION DECLARATIONS ====================

/**
 * Handles user input in the MAIN_MENU state.
 * @param userInput: the original user input (case-sensitive for state
 * transitions)
 * @param lowerInput: lowercase version for utterance lookups
 * @param state: reference to current state string (modified by this function)
 * @return void
 */
void handleMainMenu(string userInput, string lowerInput, string &state);

/**
 * Handles user input in the LOAN_CATEGORY state.
 * @param userInput: the original user input
 * @param lowerInput: lowercase version for utterance lookups
 * @param state: reference to current state string (modified by this function)
 * @return void
 */
void handleLoanCategory(string userInput, string lowerInput, string &state);

/**
 * Handles user input in the HOME_LOAN_AREA state.
 * User selects area 1-4 to view loan plans, then transitions to monthly
 * installment view.
 * @param userInput: the original user input
 * @param lowerInput: lowercase version for utterance lookups
 * @param state: reference to current state string (modified by this function)
 * @param currentArea: reference to track which area the user is viewing
 * (modified by this function)
 * @return void
 */
void handleHomeLoanArea(string userInput, string lowerInput, string &state, string &currentArea);

/**
 * Handles user input in the CAR_LOAN state.
 * User selects make 1-2 to view car loan plans, then transitions to monthly
 * installment view.
 * @param userInput: the original user input
 * @param lowerInput: lowercase version for utterance lookups
 * @param state: reference to current state string (modified by this function)
 * @param currentCarMake: reference to track which car make the user is viewing
 * (modified by this function)
 * @return void
 */
void handleCarLoan(string &userInput, string &lowerInput, string &state, string &currentCarMake);

/**
 * Handles user input in the SCOOTER_LOAN state.
 * User selects make 1-2 to view scooter loan plans, then transitions to monthly
 * installment view.
 * @param userInput: the original user input
 * @param lowerInput: lowercase version for utterance lookups
 * @param state: reference to current state string (modified by this function)
 * @param currentScooterMake: reference to track which scooter make the user is viewing
 * (modified by this function)
 * @return void
 */
void handleScooterLoan(string &userInput, string &lowerInput, string &state, string &currentScooterMake);

/**
 * Handles user input in the VIEW_CAR_MONTHLY_INSTALLMENTS state.
 * User can select a specific plan number to view its monthly installment
 * details. Allows viewing multiple plans or returning to main menu.
 * @param userInput: the original user input (plan number or A to return)
 * @param lowerInput: lowercase version for utterance lookups
 * @param state: reference to current state string (modified by this function)
 * @param currentCarMake: reference to the car make being viewed (used to fetch correct
 * plans)
 * @return void
 */
void handleViewCarMonthlyInstallments(string userInput, string lowerInput, string &state, string &currentCarMake);

/**
 * Handles user input in the VIEW_SCOOTER_MONTHLY_INSTALLMENTS state.
 * User can select a specific plan number to view its monthly installment
 * details. Allows viewing multiple plans or returning to main menu.
 * @param userInput: the original user input (plan number or A to return)
 * @param lowerInput: lowercase version for utterance lookups
 * @param state: reference to current state string (modified by this function)
 * @param currentScooterMake: reference to the scooter make being viewed (used to fetch correct
 * plans)
 * @return void
 */
void handleViewScooterMonthlyInstallments(string userInput, string lowerInput, string &state, string &currentScooterMake);

/**
 * Handles user input in the VIEW_MONTHLY_INSTALLMENTS state.
 * User can select a specific plan number to view its monthly installment
 * details. Allows viewing multiple plans or returning to main menu.
 * @param userInput: the original user input (plan number or A to return)
 * @param lowerInput: lowercase version for utterance lookups
 * @param state: reference to current state string (modified by this function)
 * @param currentArea: reference to the area being viewed (used to fetch correct
 * plans)
 * @return void
 */
void handleViewMonthlyInstallments(string userInput, string lowerInput, string &state, string &currentArea);

/**
 * Handles user input in the CHECK_STATUS state.
 * @param state: reference to current state string (modified by this function)
 * @return void
 */
void handleCheckStatus(string &state);

/**
 * Handles user input in the RESUME_APPLICATION state.
 * @param state: reference to current state string (modified by this function)
 * @return void
 */
void handleResumeApplication(string &state);

/**
 * Handles user input in the SUBMIT_APPLICATION state.
 * @param state: reference to current state string (modified by this function)
 * @param currentArea: reference to the area being viewed (used to fetch correct
 * plans)
 * @return void
 */
void handleApplicationSubmission(string &state, string &currentArea);

/**
 * Handles user input in the QUERY_APPLICATIONS state.
 * @param state: reference to current state string (modified by this function)
#ifndef STATE_HANDLERS_H
#define STATE_HANDLERS_H

#include <string>

using std::string;

// ==================== STATE HANDLER FUNCTION DECLARATIONS ====================

/**
 * Handles user input in the MAIN_MENU state.
 * @param userInput: the original user input (case-sensitive for state
 * transitions)
 * @param lowerInput: lowercase version for utterance lookups
 * @param state: reference to current state string (modified by this function)
 * @return void
 */
void handleMainMenu(string userInput, string lowerInput, string &state);

/**
 * Handles user input in the LOAN_CATEGORY state.
 * @param userInput: the original user input
 * @param lowerInput: lowercase version for utterance lookups
 * @param state: reference to current state string (modified by this function)
 * @return void
 */
void handleLoanCategory(string userInput, string lowerInput, string &state);

/**
 * Handles user input in the HOME_LOAN_AREA state.
 * User selects area 1-4 to view loan plans, then transitions to monthly
 * installment view.
 * @param userInput: the original user input
 * @param lowerInput: lowercase version for utterance lookups
 * @param state: reference to current state string (modified by this function)
 * @param currentArea: reference to track which area the user is viewing
 * (modified by this function)
 * @return void
 */
void handleHomeLoanArea(string userInput, string lowerInput, string &state, string &currentArea);

/**
 * Handles user input in the CAR_LOAN state.
 * User selects make 1-2 to view car loan plans, then transitions to monthly
 * installment view.
 * @param userInput: the original user input
 * @param lowerInput: lowercase version for utterance lookups
 * @param state: reference to current state string (modified by this function)
 * @param currentCarMake: reference to track which car make the user is viewing
 * (modified by this function)
 * @return void
 */
void handleCarLoan(string &userInput, string &lowerInput, string &state, string &currentCarMake);

/**
 * Handles user input in the SCOOTER_LOAN state.
 * User selects make 1-2 to view scooter loan plans, then transitions to monthly
 * installment view.
 * @param userInput: the original user input
 * @param lowerInput: lowercase version for utterance lookups
 * @param state: reference to current state string (modified by this function)
 * @param currentScooterMake: reference to track which scooter make the user is viewing
 * (modified by this function)
 * @return void
 */
void handleScooterLoan(string &userInput, string &lowerInput, string &state, string &currentScooterMake);

/**
 * Handles user input in the VIEW_CAR_MONTHLY_INSTALLMENTS state.
 * User can select a specific plan number to view its monthly installment
 * details. Allows viewing multiple plans or returning to main menu.
 * @param userInput: the original user input (plan number or A to return)
 * @param lowerInput: lowercase version for utterance lookups
 * @param state: reference to current state string (modified by this function)
 * @param currentCarMake: reference to the car make being viewed (used to fetch correct
 * plans)
 * @return void
 */
void handleViewCarMonthlyInstallments(string userInput, string lowerInput, string &state, string &currentCarMake);

/**
 * Handles user input in the VIEW_SCOOTER_MONTHLY_INSTALLMENTS state.
 * User can select a specific plan number to view its monthly installment
 * details. Allows viewing multiple plans or returning to main menu.
 * @param userInput: the original user input (plan number or A to return)
 * @param lowerInput: lowercase version for utterance lookups
 * @param state: reference to current state string (modified by this function)
 * @param currentScooterMake: reference to the scooter make being viewed (used to fetch correct
 * plans)
 * @return void
 */
void handleViewScooterMonthlyInstallments(string userInput, string lowerInput, string &state, string &currentScooterMake);

/**
 * Handles user input in the VIEW_MONTHLY_INSTALLMENTS state.
 * User can select a specific plan number to view its monthly installment
 * details. Allows viewing multiple plans or returning to main menu.
 * @param userInput: the original user input (plan number or A to return)
 * @param lowerInput: lowercase version for utterance lookups
 * @param state: reference to current state string (modified by this function)
 * @param currentArea: reference to the area being viewed (used to fetch correct
 * plans)
 * @return void
 */
void handleViewMonthlyInstallments(string userInput, string lowerInput, string &state, string &currentArea);

/**
 * Handles user input in the CHECK_STATUS state.
 * @param state: reference to current state string (modified by this function)
 * @return void
 */
void handleCheckStatus(string &state);

/**
 * Handles user input in the RESUME_APPLICATION state.
 * @param state: reference to current state string (modified by this function)
 * @return void
 */
void handleResumeApplication(string &state);

/**
 * Handles user input in the SUBMIT_APPLICATION state.
 * @param state: reference to current state string (modified by this function)
 * @param currentArea: reference to the area being viewed (used to fetch correct
 * plans)
 * @return void
 */
void handleApplicationSubmission(string &state, string &currentArea);

/**
 * Handles user input in the QUERY_APPLICATIONS state.
 * @param state: reference to current state string (modified by this function)
 * @return void
 */
void handleQueryApplications(string &state);

void handlePersonalLoan(string &userInput, string &lowerInput, string &state, string &currentCategory, string &personalLoanSubState);

void handleViewPersonalInstallments(string userInput, string lowerInput, string &state, string &currentCategory);

void handleGeneralConversation(string userInput, string lowerInput, string &state);

#endif // STATE_HANDLERS_H