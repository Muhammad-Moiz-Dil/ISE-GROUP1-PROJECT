#ifndef UI_DISPLAY_H
#define UI_DISPLAY_H

#include <string>
using std::string;

/**
 * @brief Displays the main welcome header/banner
 */
void displayWelcomeHeader();

/**
 * @brief Displays goodbye message when exiting
 */
void displayGoodbyeFooter();

/**
 * @brief Displays a generic payment schedule for any loan type
 * @param loanType: "Car", "Scooter", "Home", etc.
 * @param totalPrice: Full price of item/property
 * @param downPayment: Initial payment amount
 * @param installments: Number of monthly payments
 */
void displayPaymentSchedule(const string& loanType, int totalPrice, int downPayment, int installments);

/**
 * @brief Displays application status with color coding
 * @param status: Status string ("Approved", "Rejected", "Submitted", etc.)
 */
void displayApplicationStatus(const string& status);


#endif // UI_DISPLAY_H