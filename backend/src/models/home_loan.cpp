#include "models/home_loan.h"
#include "helpers/utils.h"
#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;
using std::string;
using std::stoi;

// Global HomeLoanManager object definition
HomeLoanManager HomeLoanManagerObj;

// ==================== HOME LOAN PLAN CLASS METHODS ====================

void HomeLoanPlan::display(bool showMonthly) const
{
    cout << "  Size: " << size << " | ";
    cout << "Installments: " << installments << " | ";
    cout << "Price: " << price << " | ";
    cout << "Down Payment: " << downPayment;
    
    if (showMonthly)
    {
        cout << " | Monthly: " << monthlyInstallments << " PKR";
    }
    
    cout << endl;
}

// ==================== HOME LOAN PLAN MANAGER CLASS METHODS ====================

void HomeLoanManager::displayHomeLoanPlan(string area) const
{
    if (loanTable.count(area))
    {
        cout << "\n" << COLOR_CYAN << area << " - Available Home Loan Plans:" << COLOR_RESET << endl;
        cout << COLOR_CYAN << "====================================================================================" << COLOR_RESET << endl;
        
        for (size_t i = 0; i < loanTable.at(area).size(); i++)
        {
            cout << "Plan " << (i + 1) << ": ";
            loanTable.at(area)[i].display(false);
        }
        
        cout << COLOR_CYAN << "====================================================================================" << COLOR_RESET << endl;
    }
    else
    {
        printError("No such area found.");
    }
}

void HomeLoanManager::displayMonthlyInstallment(string area, int planIndex) const
{
    if (!loanTable.count(area) || planIndex < 0 || planIndex >= static_cast<int>(loanTable.at(area).size()))
    {
        printError("Invalid plan selection.");
        return;
    }

    // NOTE: This function is deprecated and kept only for backward compatibility.
    // New code should use getPlan() + displayPaymentSchedule() from ui_display.cpp
    
    const HomeLoanPlan& plan = loanTable.at(area)[planIndex];
    
    // Extract and parse values
    int installments = stoi(trim(plan.getInstallments()));
    int totalPrice = stoi(trim(plan.getPrice()));
    int downPayment = stoi(trim(plan.getDownPayment()));
    int loanAmount = totalPrice - downPayment;
    int monthlyInstallment = plan.getMonthlyInstallments();
    
    // Display header
    cout << "\n" << COLOR_CYAN << "--- Monthly Home Loan Payment Schedule ---" << COLOR_RESET << endl;
    cout << "Original Loan Amount (Principal): " << loanAmount << " PKR" << endl;
    cout << "Monthly Installment: " << monthlyInstallment << " PKR" << endl;
    cout << "Total Installments: " << installments << " months" << endl;
    
    // Display table
    cout << std::fixed << std::setprecision(2);
    cout << COLOR_CYAN << "==========================================================================" << COLOR_RESET << endl;
    cout << std::left << std::setw(8) << "MONTH" 
        << std::right << std::setw(23) << "START BALANCE" 
        << std::right << std::setw(14) << "PAYMENT" 
        << std::right << std::setw(23) << "REMAINING BALANCE" << endl;
    cout << COLOR_CYAN << "==========================================================================" << COLOR_RESET << endl;
    
    int currentBalance = loanAmount;
    for (int i = 1; i <= installments; ++i)
    {
        int payment = (currentBalance >= monthlyInstallment) ? monthlyInstallment : currentBalance;
        int remainingBalance = currentBalance - payment;
        
        cout << std::left << std::setw(8) << i 
            << std::right << std::setw(18) << currentBalance 
            << std::right << std::setw(18) << payment
            << std::right << std::setw(18) << remainingBalance << endl;
        
        currentBalance = remainingBalance;
        
        if (currentBalance <= 0) break;
    }
    
    cout << COLOR_CYAN << "==========================================================================" << COLOR_RESET << endl;
}