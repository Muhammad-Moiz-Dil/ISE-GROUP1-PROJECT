#include "models/personal_loan.h"
#include "helpers/utils.h"
#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;
using std::string;
using std::stoi;

// Global PersonalLoanManager object definition
PersonalLoanManager PersonalLoanManagerObj;

// ==================== PERSONAL LOAN PLAN CLASS METHODS ====================

void PersonalLoanPlan::display(bool showMonthly) const
{
    cout << "  Plan: " << planName << " | ";
    cout << "Installments: " << installments << " | ";
    cout << "Amount: " << totalAmount << " | ";
    cout << "Down Payment: " << downPayment;
    
    if (showMonthly)
    {
        cout << " | Monthly: " << monthlyInstallments << " PKR";
    }
    
    cout << endl;
}

// ==================== PERSONAL LOAN MANAGER CLASS METHODS ====================

void PersonalLoanManager::displayPersonalLoanPlan(string category) const
{
    if (loanTable.count(category))
    {
        cout << "\n" << COLOR_CYAN << category << " - Available Personal Loan Plans:" << COLOR_RESET << endl;
        cout << COLOR_CYAN << "====================================================================================" << COLOR_RESET << endl;
        
        for (size_t i = 0; i < loanTable.at(category).size(); i++)
        {
            cout << "Plan " << (i + 1) << ": ";
            loanTable.at(category)[i].display(false);
        }
        
        cout << COLOR_CYAN << "====================================================================================" << COLOR_RESET << endl;
    }
    else
    {
        printError("No such category found.");
    }
}
