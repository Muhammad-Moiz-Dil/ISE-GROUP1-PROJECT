#include "models/scooter.h"
#include "helpers/utils.h"
#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;
using std::string;
using std::stoi;

// Global ScooterPlanManager object definition
ScooterPlanManager ScooterPlanManagerObj;

// ==================== SCOOTER PLAN CLASS METHODS ====================

void ScooterPlan::display(bool showMonthly) const
{
    cout << "  Make: " << make << " | ";
    cout << "Model: " << model << " | ";
    cout << "Distance/Charge: " << distancePerChargeKm << " KM | ";
    cout << "Charging Time: " << chargingTimeHrs << " Hrs | ";
    cout << "Max Speed: " << maxSpeedKmh << " KM/H | ";
    cout << "Installments: " << installments << " | ";
    cout << "Price: " << price << " | ";
    cout << "Down Payment: " << downPayment;

    if (showMonthly)
    {
        cout << " | Monthly: " << monthlyInstallments << " PKR";
    }

    cout << endl;
}

// ==================== SCOOTER PLAN MANAGER CLASS METHODS ====================

void ScooterPlanManager::displayScooterPlan(const string &make) const
{
    if (table.count(make))
    {
        cout << "\n" << COLOR_CYAN << make << " - Available Scooter Plans:" << COLOR_RESET << endl;
        cout << COLOR_CYAN << "====================================================================================" << COLOR_RESET << endl;

        for (size_t i = 0; i < table.at(make).size(); i++)
        {
            cout << "Plan " << (i + 1) << ": ";
            table.at(make)[i].display(false);
        }

        cout << COLOR_CYAN << "====================================================================================" << COLOR_RESET << endl;
    }
    else
    {
        printError("No such scooter make found.");
    }
}

void ScooterPlanManager::displayMonthlyInstallment(const string &make, int planIndex) const
{
    if (!table.count(make) || planIndex < 0 || planIndex >= static_cast<int>(table.at(make).size()))
    {
        printError("Invalid plan selection.");
        return;
    }

    // NOTE: This function is deprecated and kept only for backward compatibility.
    // New code should use getPlan() + displayPaymentSchedule() from ui_display.cpp

    const ScooterPlan &plan = table.at(make)[planIndex];

    // Extract and parse values
    int installments = stoi(trim(plan.getInstallments()));
    int totalPrice = stoi(trim(plan.getPrice()));
    int downPayment = stoi(trim(plan.getDownPayment()));
    int loanAmount = totalPrice - downPayment;
    int monthlyInstallment = plan.getMonthlyInstallments();

    // Display header
    cout << "\n" << COLOR_CYAN << "--- Monthly Scooter Payment Schedule ---" << COLOR_RESET << endl;
    cout << "Original Scooter Price: " << loanAmount << " PKR" << endl;
    cout << "Monthly Installment: " << monthlyInstallment << " PKR" << endl;
    cout << "Total Installments: " << installments << " months" << endl;

    // Display table
    cout << std::fixed << std::setprecision(2);
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