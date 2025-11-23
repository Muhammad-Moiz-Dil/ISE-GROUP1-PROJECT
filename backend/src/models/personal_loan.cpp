#include "models/personal_loan.h"
#include "helpers/utils.h"
#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;
using std::string;

// Global Manager Instance
PersonalLoanManager PersonalLoanManagerObj;

// ==================== PERSONAL LOAN PLAN METHODS ====================

void PersonalLoanPlan::display(bool showMonthly) const {
    cout << "  Plan: " << planName << " | ";
    cout << "Amount: " << totalAmount << " | ";
    cout << "Installments: " << installments << " months | ";
    cout << "Down Payment: " << downPayment;

    if (showMonthly) {
        cout << " | Monthly: " << monthlyInstallments << " PKR";
    }
    cout << endl;
}

// ==================== MANAGER METHODS ====================

void PersonalLoanManager::displayPersonalLoanPlan(string category) const {
    if (loanTable.count(category)) {
        cout << "\n" << COLOR_CYAN << category << " - Available Plans:" << COLOR_RESET << endl;
        cout << COLOR_CYAN << "====================================================================================" << COLOR_RESET << endl;

        const vector<PersonalLoanPlan>& plans = loanTable.at(category);
        for (size_t i = 0; i < plans.size(); i++) {
            cout << "Plan " << (i + 1) << ": ";
            plans[i].display(false);
        }

        cout << COLOR_CYAN << "====================================================================================" << COLOR_RESET << endl;
    } else {
        printError("No plans found for category: " + category);
    }
}