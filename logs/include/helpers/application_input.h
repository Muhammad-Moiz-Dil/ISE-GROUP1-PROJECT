#ifndef APPLICATION_INPUT_H
#define APPLICATION_INPUT_H

#include "core/application.h"
#include <string>

using std::string;

// ==================== APPLICATION DATA COLLECTION ====================

/**
 * @brief Generic input validation helper with X-to-exit support
 * 
 * Repeatedly prompts user until valid input is received or user exits (X).
 * Automatically trims input and handles exit command.
 * 
 * @param prompt Text to display to user
 * @param validator Function pointer to validation function (returns true if valid)
 * @param errorMsg Error message to show on invalid input
 * @param state Reference to state string (set to "MAIN_MENU" on exit)
 * @param output Reference to store the validated input
 * @return true if input collected successfully, false if user pressed X
 */
bool getValidatedInput(const string& prompt, 
                    bool (*validator)(const string&), 
                    const string& errorMsg,
                    string& state,
                    string& output);

/**
 * @brief Collects personal information from user (10 fields)
 * 
 * Collects: Full Name, Father's Name, Address, Contact, Email, CNIC,
 * CNIC Expiry, Employment Status, Marital Status, Gender.
 * User can press X at any field to exit and return to main menu.
 * All inputs are validated before being stored in Application object.
 * 
 * @param app Reference to Application object to populate
 * @param state Reference to state (set to "MAIN_MENU" if user exits)
 * @return true if all information collected, false if user exited early
 */
bool collectPersonalInformation(Application& app, string& state);

/**
 * @brief Collects financial information including existing loans (4+ fields)
 * 
 * Collects: Dependents, Annual Income, Avg Electricity Bill, Current Bill.
 * If user has existing loan, also collects loan details (status, amounts, bank, category).
 * User can press X at any field to exit and return to main menu.
 * 
 * @param app Reference to Application object to populate
 * @param state Reference to state (set to "MAIN_MENU" if user exits)
 * @return true if all information collected, false if user exited early
 */
bool collectFinancialInformation(Application& app, string& state);

/**
 * @brief Collects information for two referees (10 fields total)
 * 
 * For each referee collects: Name, CNIC, Issue Date, Phone, Email.
 * All inputs are validated before being stored.
 * User can press X at any field to exit and return to main menu.
 * 
 * @param app Reference to Application object to populate
 * @param state Reference to state (set to "MAIN_MENU" if user exits)
 * @return true if all referee information collected, false if user exited early
 */
bool collectReferenceInformation(Application& app, string& state);

/**
 * @brief Collects document file paths (4 documents)
 * 
 * Collects paths for: CNIC Front, CNIC Back, Electricity Bill, Salary Slip.
 * No validation performed on paths (user responsible for correct paths).
 * User can press X at any field to exit and return to main menu.
 * 
 * @param app Reference to Application object to populate
 * @param state Reference to state (set to "MAIN_MENU" if user exits)
 * @return true if all paths collected, false if user exited early
 */
bool collectDocuments(Application& app, string& state);

#endif // APPLICATION_INPUT_H