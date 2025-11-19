#include "Car.h"
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

// Global CarPlanManager object definition
CarPlanManager CarPlanManagerObj;

// ==================== CarPlan Class Methods ====================

void CarPlan::setMake(string make) 
{ 
    this->make = make; 
}

void CarPlan::setModel(string model) 
{ 
    this->model = model; 
}

void CarPlan::setEngine(string engine) 
{ 
    this->engine = engine; 
}

void CarPlan::setUsed(string year) 
{ 
    this->usedManufacturingYear = year; 
}

void CarPlan::setInstallments(string installments) 
{ 
    this->installments = installments; 
}
void CarPlan::setUsedManufacturingYear(string year)
{
    this->usedManufacturingYear = year;
}

void CarPlan::setPrice(string price) 
{ 
    this->price = price; 
}

void CarPlan::setDownPayment(string downPayment) 
{ 
    this->downPayment = downPayment; 
}

void CarPlan::setMonthlyInstallments(int monthlyInstallments) 
{ 
    this->monthlyInstallments = monthlyInstallments; 
}

string CarPlan::getMake() 
{ 
    return make; 
}

string CarPlan::getModel() 
{ 
    return model; 
}

string CarPlan::getEngine() 
{ 
    return engine; 
}

string CarPlan::getUsedManufacturingYear() 
{ 
    return usedManufacturingYear; 
}

string CarPlan::getInstallments() 
{ 
    return installments; 
}

string CarPlan::getPrice() 
{ 
    return price; 
}

string CarPlan::getDownPayment() 
{ 
    return downPayment; 
}

int CarPlan::getMonthlyInstallments() 
{ 
    return monthlyInstallments; 
}

void CarPlan::display(bool showMonthly)
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

// ==================== CarPlanManager Class Methods ====================

void CarPlanManager::setMake(string make, CarPlan &cp)
{
    carTable[make].push_back(cp);
}

int CarPlanManager::getPlanCount(string make)
{
    if (carTable.count(make))
    {
        return carTable[make].size();
    }
    return 0;
}

void CarPlanManager::displayCarPlan(string make)
{
    if (carTable.count(make))
    {
        cout << "\n" << make << " - Available Car Plans:" << endl;
        cout << "====================================================================================" << endl;
        
        for (int i = 0; i < carTable[make].size(); i++)
        {
            cout << "Plan " << (i + 1) << ": ";
            carTable[make][i].display(false);
        }
        
        cout << "====================================================================================" << endl;
    }
    else
    {
        cout << "No such car make found." << endl;
    }
}

void CarPlanManager::displayMonthlyInstallment(string make, int planIndex)
{
    if (carTable.count(make) && planIndex >= 0 && planIndex < carTable[make].size())
    {
        int installmentAmount = carTable[make][planIndex].getMonthlyInstallments();
        string noOfInstallments = carTable[make][planIndex].getInstallments();
        string carPrice = carTable[make][planIndex].getPrice();
        string dp = carTable[make][planIndex].getDownPayment();

        int n = stoi(noOfInstallments);
        carPrice = trim(carPrice);
        int price = stoi(carPrice);
        //cout << price <<endl;
        dp = trim(dp);
        int Dp = stoi(dp);
       // cout << dp<<endl;
        price -= Dp;

        int currentBalance = price;

        cout << "\n--- Monthly Car Payment Schedule ---" << endl;
        cout << "Original Car Price: " << price << " PKR" << endl;
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

            if (remainingBalance < 0 && i == n) {
                payment = currentBalance;
                remainingBalance = 0;
            } else if (remainingBalance < 0 && i < n) {
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

        cout << "==========================================================================" << endl;
    }
    else
    {
        cout << "Invalid plan selection." << endl;
    }
}
