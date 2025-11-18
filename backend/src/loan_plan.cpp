#include "loan_plan.h"
#include "utils.h"   // for trim() function
#include <iostream>
#include <iomanip>
#include <string>

using std::cout;
using std::endl;
using std::string;
using std::stoi;
using std::setprecision;
using std::fixed;
using std::left;
using std::right;
using std::setw;

// Global LoanPlanManager object definition
LoanPlanManager LoanPlanManagerObj;

// ==================== LoanPlan Class Methods ====================

void LoanPlan::setprice(string price) 
{ 
    this->price = price; 
}

void LoanPlan::setSize(string size) 
{ 
    this->size = size; 
}

void LoanPlan::setInstallments(string installments) 
{ 
    this->installments = installments; 
}

void LoanPlan::setDownPayment(string downPayment) 
{ 
    this->downPayment = downPayment; 
}

void LoanPlan::setMonthlyInstallments(int monthlyInstallments) 
{ 
    this->monthlyInstallments = monthlyInstallments; 
}

string LoanPlan::getprice() 
{ 
    return price; 
}

string LoanPlan::getSize() 
{ 
    return size; 
}

string LoanPlan::getInstallments() 
{ 
    return installments; 
}

string LoanPlan::getDownPayment() 
{ 
    return downPayment; 
}

int LoanPlan::getMonthlyInstallments() 
{ 
    return monthlyInstallments; 
}

void LoanPlan::display(bool showMonthly)
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

// ==================== LoanPlanManager Class Methods ====================

void LoanPlanManager::setArea(string area, LoanPlan &lp)
{
    loanTable[area].push_back(lp);
}

int LoanPlanManager::getPlanCount(string area)
{
    if (loanTable.count(area))
    {
        return loanTable[area].size();
    }
    return 0;
}

void LoanPlanManager::displayLoanPlan(string area)
{
    if (loanTable.count(area))
    {
        cout << "\n" << area << " - Available Loan Plans:" << endl;
        cout << "====================================================================================" << endl;
        
        for (int i = 0; i < loanTable[area].size(); i++)
        {
            cout << "Plan " << (i + 1) << ": ";
            loanTable[area][i].display(false);
        }
        
        cout << "====================================================================================" << endl;
    }
    else
    {
        cout << "No such area found." << endl;
    }
}

void LoanPlanManager::displayMonthlyInstallment(string area, int planIndex)
{
    if (loanTable.count(area) && planIndex >= 0 && planIndex < loanTable[area].size())
    {
        cout << "\nMonthly Installment for Plan " << (planIndex + 1) << ": ";
        cout << loanTable[area][planIndex].getMonthlyInstallments() << " PKR" << endl;

        int installmentAmount =  loanTable[area][planIndex].getMonthlyInstallments();
        string noOfInstallments =  loanTable[area][planIndex].getInstallments() ;
        string loan =  loanTable[area][planIndex].getprice();
        string dp =  loanTable[area][planIndex].getDownPayment();

        int n = stoi(noOfInstallments);
        loan  = trim(loan);
        dp = trim(dp);
        int price = stoi(loan);
        int Dp = stoi(dp);
        price = price - Dp;

         int currentBalance = price;
            
            cout << "\n--- Monthly Loan Amortization Schedule ---" << endl;
            cout << "Original Loan Amount (Principal): " << price << " PKR" << endl;
            cout << "Monthly Installment: " << installmentAmount << " PKR" << endl;
            cout << "Total Installments: " << n << " months" << endl;

            // Set up table formatting
            cout << fixed << setprecision(2);
            cout << "==========================================================================" << endl;
            cout << left << setw(8) << "MONTH" 
                 << right << setw(23) << "START BALANCE" 
                 << right << setw(18) << "PAYMENT" 
                 << right << setw(23) << "REMAINING BALANCE" << endl;
            cout << "==========================================================================" << endl;

            for (int i = 1; i <= n; ++i) {
                int payment = installmentAmount;
                int remainingBalance = currentBalance - payment;
                
                // If this is the final payment and the remaining balance is less than the installment, 
                // adjust the payment amount to fully pay off the loan.
                if (remainingBalance < 0 && i == n) {
                    payment = currentBalance;
                    remainingBalance = 0;
                } else if (remainingBalance < 0 && i < n) {
                    // This scenario shouldn't happen if the calculation is correct 
                    // (i.e., installment * n >= price), but we handle it just in case.
                    payment = currentBalance;
                    remainingBalance = 0;
                }

                cout << left << setw(8) << i 
                     << right << setw(18) << currentBalance 
                     << right << setw(18) << payment
                     << right << setw(18) << remainingBalance << endl;

                // Update the balance for the next month
                currentBalance = remainingBalance;

                // Stop if the loan is fully paid off early
                if (currentBalance <= 0) {
                    break;
                }
            }
        
        cout << "==========================================================================" << endl;
    }
    else
    {
        cout << "Invalid plan selection." << endl;
    }
}