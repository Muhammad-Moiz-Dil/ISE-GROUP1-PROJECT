#include "models/car.h"
#include "helpers/utils.h"
#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;
using std::string;

// Global CarPlanManager object definition
CarPlanManager CarPlanManagerObj;

// ==================== CAR PLAN CLASS METHODS ====================

void CarPlan::display(bool showMonthly) const
{
    cout << "  Make: " << make << " | ";
    cout << "Model: " << model << " | ";
    cout << "Engine: " << engine << " | ";
    cout << "Year: " << usedManufacturingYear << " | ";
    cout << "Installments: " << installments << " | ";
    cout << "Price: " << price << " | ";
    cout << "Down Payment: " << downPayment;
    
    if (showMonthly)
    {
        cout << " | Monthly: " << monthlyInstallments << " PKR";
    }
    
    cout << endl;
}

// ==================== CAR PLAN MANAGER CLASS METHODS ====================

void CarPlanManager::displayCarPlan(string make) const
{
    if (carTable.count(make))
    {
        cout << "\n" << COLOR_CYAN << make << " - Available Car Plans:" << COLOR_RESET << endl;
        cout << COLOR_CYAN << "====================================================================================" << COLOR_RESET << endl;
        
        for (size_t i = 0; i < carTable.at(make).size(); i++)
        {
            cout << "Plan " << (i + 1) << ": ";
            carTable.at(make)[i].display(false);
        }
        
        cout << COLOR_CYAN << "====================================================================================" << COLOR_RESET << endl;
    }
    else
    {
        printError("No such car make found.");
    }
}

void CarPlanManager::displayMonthlyInstallment(string make, int planIndex) const
{
    if (!carTable.count(make) || planIndex < 0 || planIndex >= static_cast<int>(carTable.at(make).size()))
    {
        printError("Invalid plan selection.");
        return;
    }

    // NOTE: This function is deprecated and kept only for backward compatibility.
    // New code should use getPlan() + displayPaymentSchedule() from ui_display.cpp
    
    const CarPlan& plan = carTable.at(make)[planIndex];
    
    // Extract and parse values
    int installments = std::stoi(trim(plan.getInstallments()));
    int totalPrice = std::stoi(trim(plan.getPrice()));
    int downPayment = std::stoi(trim(plan.getDownPayment()));
    int loanAmount = totalPrice - downPayment;
    int monthlyInstallment = plan.getMonthlyInstallments();
    
    // Display header
    cout << "\n" << COLOR_CYAN << "--- Monthly Car Payment Schedule ---" << COLOR_RESET << endl;
    cout << "Original Car Price: " << loanAmount << " PKR" << endl;
    cout << "Monthly Installment: " << monthlyInstallment << " PKR" << endl;
    cout << "Total Installments: " << installments << " months" << endl;
    
    // Display table
    cout << COLOR_CYAN << "==========================================================================" << COLOR_RESET << endl;
    cout << std::left << std::setw(8) << "MONTH" 
         << std::right << std::setw(23) << "START BALANCE" 
         << std::right << std::setw(18) << "PAYMENT" 
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