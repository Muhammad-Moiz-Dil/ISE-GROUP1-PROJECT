#include "core/file_io.h"
#include "models/home_loan.h"
#include "models/car.h"
#include "models/scooter.h"
#include "models/personal_loan.h"
#include "helpers/utils.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::stringstream;
using std::stoi;

// Global Utterance object definition
Utterance uttrObj;

// ==================== UTTERANCE CLASS METHODS ====================

void Utterance::setResponse(string userInput, string response)
{
    responseTable[userInput] = response;
}

string Utterance::getResponse(string userInput)
{
    // Convert input to lowercase for case-insensitive matching
    userInput = toLower(userInput);

    // Check if exact match exists
    if (responseTable.count(userInput))
    {
        return responseTable[userInput];
    }

    // Return fallback response if no match found
    return responseTable["*"];
}

// ==================== HELPER FUNCTIONS ====================

namespace {
    /**
     * @brief Calculates monthly installment amount
     * @param price Total price
     * @param downPayment Down payment amount
     * @param installments Number of months
     * @return Monthly installment amount
     */
    int calculateMonthlyInstallment(int price, int downPayment, int installments)
    {
        return (price - downPayment) / installments;
    }
}

// ==================== FILE LOADING FUNCTIONS ====================

bool loadUtterances(const string &filePath)
{
    ifstream file(filePath);
    if (!file.is_open())
    {
        cout << "Error: Could not open utterances file: " << filePath << endl;
        return false;
    }

    string line;
    while (getline(file, line))
    {
        int pos = line.find('#');
        if (pos == string::npos) continue;

        string userInput = toLower(line.substr(0, pos));
        string response = line.substr(pos + 1);

        uttrObj.setResponse(userInput, response);
    }

    file.close();
    return true;
}

bool loadLoanPlans(const string &filePath)
{
    ifstream file(filePath);
    if (!file.is_open())
    {
        cout << "Error: Could not open loan plans file: " << filePath << endl;
        return false;
    }

    string line;
    getline(file, line); // Skip header row

    while (getline(file, line))
    {
        stringstream ss(line);
        string area, size, installmentStr, priceStr, downPaymentStr;

        getline(ss, area, '#');
        getline(ss, size, '#');
        getline(ss, installmentStr, '#');
        getline(ss, priceStr, '#');
        getline(ss, downPaymentStr, '#');

        // Parse values
        int installments = stoi(trim(installmentStr));
        int totalPrice = parseNumberWithCommas(priceStr);
        int downPayment = parseNumberWithCommas(downPaymentStr);
        int monthlyInstallment = calculateMonthlyInstallment(totalPrice, downPayment, installments);

        // Create and populate loan plan
        HomeLoanPlan HomeLoanObj;
        HomeLoanObj.setSize(size);
        HomeLoanObj.setDownPayment(downPaymentStr);
        HomeLoanObj.setInstallments(installmentStr);
        HomeLoanObj.setPrice(priceStr);
        HomeLoanObj.setMonthlyInstallments(monthlyInstallment);

        HomeLoanManagerObj.setArea(area, HomeLoanObj);
    }

    file.close();
    return true;
}

bool loadCarPlans(const string &filePath)
{
    ifstream file(filePath);
    if (!file.is_open())
    {
        cout << "Error: Could not open car plans file: " << filePath << endl;
        return false;
    }

    string line;
    getline(file, line); // Skip header row

    while (getline(file, line))
    {
        stringstream ss(line);
        string make, model, engine, used, manufacturing, installmentStr, priceStr, downPaymentStr;

        getline(ss, make, '#');
        getline(ss, model, '#');
        getline(ss, engine, '#');
        getline(ss, used, '#');
        getline(ss, manufacturing, '#');
        getline(ss, installmentStr, '#');
        getline(ss, priceStr, '#');
        getline(ss, downPaymentStr, '#');

        // Parse values
        int installments = stoi(trim(installmentStr));
        int totalPrice = parseNumberWithCommas(priceStr);
        int downPayment = parseNumberWithCommas(downPaymentStr);
        int monthlyInstallment = calculateMonthlyInstallment(totalPrice, downPayment, installments);

        // Create and populate car plan
        CarPlan carPlanObj;
        carPlanObj.setMake(make);
        carPlanObj.setModel(model);
        carPlanObj.setEngine(engine);
        carPlanObj.setUsed(used);
        carPlanObj.setUsedManufacturingYear(manufacturing);
        carPlanObj.setInstallments(installmentStr);
        carPlanObj.setPrice(priceStr);
        carPlanObj.setDownPayment(downPaymentStr);
        carPlanObj.setMonthlyInstallments(monthlyInstallment);

        CarPlanManagerObj.setMake(make, carPlanObj);
    }

    file.close();
    return true;
}

bool loadScooterPlans(const string &filePath)
{
    ifstream file(filePath);
    if (!file.is_open())
    {
        cout << "Error: Could not open scooter plans file: " << filePath << endl;
        return false;
    }

    string line;
    getline(file, line); // Skip header row

    while (getline(file, line))
    {
        stringstream ss(line);
        string make, model, distancePerCharge, chargingTime, maxSpeed, installmentStr, priceStr, downPaymentStr;

        getline(ss, make, '#');
        getline(ss, model, '#');
        getline(ss, distancePerCharge, '#');
        getline(ss, chargingTime, '#');
        getline(ss, maxSpeed, '#');
        getline(ss, installmentStr, '#');
        getline(ss, priceStr, '#');
        getline(ss, downPaymentStr, '#');

        // Parse values
        int installments = stoi(trim(installmentStr));
        int totalPrice = parseNumberWithCommas(priceStr);
        int downPayment = parseNumberWithCommas(downPaymentStr);
        int monthlyInstallment = calculateMonthlyInstallment(totalPrice, downPayment, installments);

        // Create and populate scooter plan
        ScooterPlan scooterPlanObj;
        scooterPlanObj.setMake(make);
        scooterPlanObj.setModel(model);
        scooterPlanObj.setDistancePerChargeKm(distancePerCharge);
        scooterPlanObj.setChargingTimeHrs(chargingTime);
        scooterPlanObj.setMaxSpeedKmh(maxSpeed);
        scooterPlanObj.setInstallments(installmentStr);
        scooterPlanObj.setPrice(priceStr);
        scooterPlanObj.setDownPayment(downPaymentStr);
        scooterPlanObj.setMonthlyInstallments(monthlyInstallment);

        ScooterPlanManagerObj.setMake(make, scooterPlanObj);
    }

    file.close();
    return true;
}

bool loadPersonalPlans(const string &filePath)
{
    ifstream file(filePath);
    if (!file.is_open())
    {
        cout << "Error: Could not open personal plans file: " << filePath << endl;
        return false;
    }

    string line;
    getline(file, line); // Skip header row

    while (getline(file, line))
    {
        stringstream ss(line);
        string category, planName, installmentStr, amountStr, downPaymentStr;

        getline(ss, category, '#');
        getline(ss, planName, '#');
        getline(ss, installmentStr, '#');
        getline(ss, amountStr, '#');
        getline(ss, downPaymentStr, '#');

        // Parse values
        int installments = stoi(trim(installmentStr));
        int totalAmount = parseNumberWithCommas(amountStr);
        int downPayment = parseNumberWithCommas(downPaymentStr);
        int monthlyInstallment = calculateMonthlyInstallment(totalAmount, downPayment, installments);

        // Create and populate personal loan plan
        PersonalLoanPlan personalPlanObj;
        personalPlanObj.setPlanName(planName);
        personalPlanObj.setInstallments(installmentStr);
        personalPlanObj.setTotalAmount(amountStr);
        personalPlanObj.setDownPayment(downPaymentStr);
        personalPlanObj.setMonthlyInstallments(monthlyInstallment);

        PersonalLoanManagerObj.setCategory(category, personalPlanObj);
    }

    file.close();
    return true;
}