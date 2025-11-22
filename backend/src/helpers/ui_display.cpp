#include "helpers/ui_display.h"
#include "helpers/utils.h"
#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;
using std::left;
using std::right;
using std::setw;
using std::fixed;
using std::setprecision;

void displayWelcomeHeader() {
    cout << COLOR_CYAN << "=============================================" << COLOR_RESET << endl;
    cout << COLOR_CYAN << "           WELCOME TO THE CHATBOT!        " << COLOR_RESET << endl;
    cout << COLOR_CYAN << "---------------------------------------------" << COLOR_RESET << endl;
    cout << COLOR_CYAN << "    Type your message below (X to exit):" << COLOR_RESET << endl;
    cout << COLOR_CYAN << "=============================================" << COLOR_RESET << endl;
    cout << endl;
}

void displayGoodbyeFooter() {
    cout << "\n" << COLOR_RED
        << "=============================================" << endl
        << "          CHATBOT SESSION ENDED!           " << endl
        << "=============================================" 
    << COLOR_RESET << endl;
}

void displayApplicationStatus(const string& status) {
    cout << "Status: ";
    if (status == "Approved") {
        cout << COLOR_GREEN << "Approved" << COLOR_RESET;
    } else if (status == "Rejected") {
        cout << COLOR_RED << "Rejected" << COLOR_RESET;
    } else {
        cout << COLOR_YELLOW << status << COLOR_RESET;
    }
    cout << endl;
}

void displayPaymentSchedule(const string& loanType, int totalPrice, int downPayment, int installments) {
    // Calculate loan amount
    int loanAmount = totalPrice - downPayment;
    int monthlyInstallment = loanAmount / installments;
    int currentBalance = loanAmount;
    
    // Header
    cout << "\n--- Monthly " << loanType << " Payment Schedule ---" << endl;
    cout << "Original " << loanType << " Price: " << (totalPrice) << " PKR" << endl;
    cout << "Down Payment: " << downPayment << " PKR" << endl;
    cout << "Loan Amount (Principal): " << loanAmount << " PKR" << endl;
    cout << "Monthly Installment: " << monthlyInstallment << " PKR" << endl;
    cout << "Total Installments: " << installments << " months" << endl;
    
    // Table formatting
    cout << fixed << setprecision(2);
    cout << COLOR_CYAN << "==========================================================================" << COLOR_RESET << endl;
    cout << left << setw(8) << "MONTH"
        << right << setw(23) << "START BALANCE"
        << right << setw(18) << "PAYMENT"
        << right << setw(23) << "REMAINING BALANCE" << endl;
    cout << COLOR_CYAN << "==========================================================================" << COLOR_RESET << endl;
    
    // Payment schedule loop
    for (int i = 1; i <= installments; ++i) {
        int payment = monthlyInstallment;
        int remainingBalance = currentBalance - payment;
        
        // Handle final payment adjustment
        if (remainingBalance < 0) {
            payment = currentBalance;
            remainingBalance = 0;
        }
        
        cout << left << setw(8) << i
            << right << setw(18) << currentBalance
            << right << setw(18) << payment
            << right << setw(18) << remainingBalance << endl;
        
        currentBalance = remainingBalance;
        
        if (currentBalance <= 0) {
            break;
        }
    }
    
    cout << COLOR_CYAN << "==========================================================================" << COLOR_RESET << endl;
}