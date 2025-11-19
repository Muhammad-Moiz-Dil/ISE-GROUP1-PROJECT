#include "scooter.h"
#include "utils.h"
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

// Global ScooterPlanManager object definition
ScooterPlanManager ScooterPlanManagerObj;

// ==================== ScooterPlan Class Methods ====================

void ScooterPlan::setMake(const string &make)
{
    this->make = make;
}

void ScooterPlan::setModel(const string &model)
{
    this->model = model;
}

void ScooterPlan::setDistancePerChargeKm(string km)
{
    this->distancePerChargeKm = km;
}

void ScooterPlan::setChargingTimeHrs(string hrs)
{
    this->chargingTimeHrs = hrs;
}

void ScooterPlan::setMaxSpeedKmh(string kmh)
{
    this->maxSpeedKmh = kmh;
}

void ScooterPlan::setInstallments(const string &installments)
{
    this->installments = installments;
}

void ScooterPlan::setPrice(const string &price)
{
    this->price = price;
}

void ScooterPlan::setDownPayment(const string &downPayment)
{
    this->downPayment = downPayment;
}

void ScooterPlan::setMonthlyInstallments(int monthlyInstallments)
{
    this->monthlyInstallments = monthlyInstallments;
}

string ScooterPlan::getMake() const
{
    return make;
}

string ScooterPlan::getModel() const
{
    return model;
}

string ScooterPlan::getDistancePerChargeKm() const
{
    return distancePerChargeKm;
}

string ScooterPlan::getChargingTimeHrs() const
{
    return chargingTimeHrs;
}

string ScooterPlan::getMaxSpeedKmh() const
{
    return maxSpeedKmh;
}

string ScooterPlan::getInstallments() const
{
    return installments;
}

string ScooterPlan::getPrice() const
{
    return price;
}

string ScooterPlan::getDownPayment() const
{
    return downPayment;
}

int ScooterPlan::getMonthlyInstallments() const
{
    return monthlyInstallments;
}

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

// ==================== ScooterPlanManager Class Methods ====================

void ScooterPlanManager::setMake(const string &make, ScooterPlan &sp)
{
    table[make].push_back(sp);
}

int ScooterPlanManager::getPlanCount(const string &make) const
{
    if (table.count(make))
    {
        return table.at(make).size();
    }
    return 0;
}

void ScooterPlanManager::displayScooterPlan(const string &make) const
{
    if (table.count(make))
    {
        cout << "\n" << make << " - Available Scooter Plans:" << endl;
        cout << "====================================================================================" << endl;

        for (int i = 0; i < table.at(make).size(); i++)
        {
            cout << "Plan " << (i + 1) << ": ";
            table.at(make)[i].display(false);
        }

        cout << "====================================================================================" << endl;
    }
    else
    {
        cout << "No such scooter make found." << endl;
    }
}

void ScooterPlanManager::displayMonthlyInstallment(const string &make, int planIndex) const
{
    if (table.count(make) && planIndex >= 0 && planIndex < table.at(make).size())
    {
        const ScooterPlan &sp = table.at(make)[planIndex];

        int installmentAmount = sp.getMonthlyInstallments();
        string noOfInstallments = sp.getInstallments();
        string scooterPriceStr = sp.getPrice();
        string dpStr = sp.getDownPayment();

        int n = stoi(noOfInstallments);
        
        scooterPriceStr = trim(scooterPriceStr);
        int price = stoi(scooterPriceStr);

        dpStr = trim(dpStr);
        int dp = stoi(dpStr);

        price -= dp;
        int currentBalance = price;

        cout << "\n--- Monthly Scooter Payment Schedule ---" << endl;
        cout << "Original Scooter Price: " << price << " PKR" << endl;
        cout << "Monthly Installment: " << installmentAmount << " PKR" << endl;
        cout << "Total Installments: " << n << " months" << endl;

        // Table formatting
        cout << fixed << setprecision(2);
        cout << "==========================================================================" << endl;
        cout << left << setw(8) << "MONTH"
             << right << setw(23) << "START BALANCE"
             << right << setw(18) << "PAYMENT"
             << right << setw(23) << "REMAINING BALANCE" << endl;
        cout << "==========================================================================" << endl;

        for (int i = 1; i <= n; ++i)
        {
            int payment = installmentAmount;
            int remainingBalance = currentBalance - payment;

            if (remainingBalance < 0)
            {
                payment = currentBalance;
                remainingBalance = 0;
            }

            cout << left << setw(8) << i
                 << right << setw(18) << currentBalance
                 << right << setw(18) << payment
                 << right << setw(18) << remainingBalance << endl;

            currentBalance = remainingBalance;

            if (currentBalance <= 0)
            {
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
