#include "../../logs/include/file_io.h"
#include "../../logs/include/utils.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <iomanip>
using std::cout;
using std::endl;
using std::find_if;
using std::ifstream;
using std::string;
using std::stringstream;
using std::unordered_map;
using std::vector;
using std:: setprecision;
using std:: fixed;
using std:: left;
using std:: right;
using std:: setw;

// Global object definitions
Utterance uttrObj;
LoanPlanManager LoanPlanManagerObj;

//  === Utterance class methods ===
/*
 * Stores a user input and its corresponding chatbot response.
 * @param userInput: the phrase or keyword the user types.
 * @param response: the bot's reply to that input.
 * @return: void.
 */
void Utterance::setResponse(string userInput, string response)
{
    responseTable[userInput] = response;
}

/*
 * Retrieves the chatbot response for a given user input.
 * @param userInput: the user's typed message.
 * @return: the matching response string, or fallback (*) if not found. "No reply found" as a fallback.
 */
string Utterance::getResponse(string userInput)
{
    if (responseTable.count(userInput))
        return responseTable[userInput];

    // Fallback to "*"
    else if (responseTable.count("*"))
        return responseTable["*"];

    else
        return "[No reply found]";
}

// LoanPlan class methods
void LoanPlan::setprice(string price) { this->price = price; }
void LoanPlan::setSize(string size) { this->size = size; }
void LoanPlan::setInstallments(string installments) { this->installments = installments; }
void LoanPlan::setDownPayment(string downPayment) { this->downPayment = downPayment; }
void LoanPlan::setMonthlyInstallments(int monthlyInstallment) { this->monthlyInstallments = monthlyInstallment; }
string LoanPlan::getprice() { return price; }
string LoanPlan::getSize() { return size; }
string LoanPlan::getInstallments() { return installments; }
string LoanPlan::getDownPayment() { return downPayment; }
int LoanPlan::getMonthlyInstallments() { return monthlyInstallments; }

void LoanPlan::display(bool showMonthly)
{
    cout << " Size: " << size << " | ";
    cout << "Installments: " << installments << " | ";
    cout << "Price: " << price << " | ";
    cout << "Down Payment: " << downPayment;
    
    if (showMonthly)
    {
        cout << " | Monthly: " << monthlyInstallments << " PKR";
    }
    
    cout << endl;
}


// === LoanPlanManager methods ===
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
                 << right << setw(18) << "START BALANCE" 
                 << right << setw(18) << "PAYMENT" 
                 << right << setw(18) << "REMAINING BALANCE" << endl;
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



// === file_io methods ===
bool loadUtterances(string filePath)
{
    ifstream utterancesFile;
    utterancesFile.open(filePath);
    if (!utterancesFile.is_open())
    {
        cout << "File not opened." << endl;
        return false;
    }
    else
    {
        string line;
        while (getline(utterancesFile, line))
        {
            int pos = line.find('#');
            string userInput = line.substr(0, pos);
            string response = line.substr(pos + 1);

            // Convert userInput to lowercase before storing
            for (int i = 0; i < userInput.length(); i++)
            {
                userInput[i] = tolower(userInput[i]);
            }

            uttrObj.setResponse(userInput, response);
        }
    }
    utterancesFile.close();
    return true;
}

bool loadLoanPlans(string filePath)
{
    ifstream homeFile;
    homeFile.open(filePath);
    if (!homeFile.is_open())
    {
        cout << "File not opened." << endl;
        return false;
    }
    else
    {
        string line;
        int i = 0;
        while (getline(homeFile, line))
        {
            stringstream ss(line);
            string area, size, installmentStr, priceStr, downpaymentStr;

            getline(ss, area, '#');
            getline(ss, size, '#');
            getline(ss, installmentStr, '#');
            getline(ss, priceStr, '#');
            getline(ss, downpaymentStr, '#');
            if (i == 0) // ignore the first line of txt file.
            {
                i++;
                continue;
            }

            string inst = trim(installmentStr);
            int installments = stoi(inst);
            int totalPrice = 0;
            int downPayments = 0;
            string actualPrice = "";
            for (int i = 0; i < priceStr.length(); i++)
            {
                if (priceStr[i] != ',')
                {
                    actualPrice = actualPrice + priceStr[i];
                }
            }
            totalPrice = stoi(actualPrice);

            string actualDownPayment = "";
            for (int i = 0; i < downpaymentStr.length(); i++)
            {
                if (downpaymentStr[i] != ',')
                {
                    actualDownPayment = actualDownPayment + downpaymentStr[i];
                }
            }
            downPayments = stoi(actualDownPayment);

            int monthlyInstallment = (totalPrice - downPayments) / installments;
            LoanPlan loanPlanObj;
            loanPlanObj.setSize(size);
            loanPlanObj.setDownPayment(downpaymentStr);
            loanPlanObj.setInstallments(installmentStr);
            loanPlanObj.setprice(priceStr);
            loanPlanObj.setMonthlyInstallments(monthlyInstallment);

            LoanPlanManagerObj.setArea(area, loanPlanObj);
        }
    }

    homeFile.close();
    return true;
}