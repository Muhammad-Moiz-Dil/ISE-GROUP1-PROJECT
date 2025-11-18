#include "file_io.h"
#include "loan_plan.h"  // Need this to populate LoanPlanManager
#include "car.h"
#include "utils.h"       // for trim() function
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::stringstream;

// Global Utterance object definition
Utterance uttrObj;
// ==================== Utterance Class Methods ====================

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

// ==================== File Loading Functions ====================

bool loadUtterances(const string &filePath)
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

bool loadLoanPlans(const string &filePath)
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

bool loadCarPlans(const string &filePath)
{
    ifstream carFile;
    carFile.open(filePath);
    if (!carFile.is_open())
    {
        cout << "File not opened." << endl;
        return false;
    }
    else
    {
        string line;
        int i = 0;
        while (getline(carFile, line))
        {
            stringstream ss(line);
            string make, modal, Engine, Used, Manufacturing, installments,Price,DownPayment;

            getline(ss, make, '#');
            getline(ss, modal, '#');
            getline(ss, Engine, '#');
            getline(ss, Used, '#');
            getline(ss, Manufacturing, '#');
            getline(ss, installments, '#');
            getline(ss, Price, '#');
            getline(ss, DownPayment, '#');
            if (i == 0) // ignore the first line of txt file.
            {
                i++;
                continue;
            }

            string inst = trim(installments);
            int Installments = stoi(inst);
            int totalPrice = 0;
            int downPayments = 0;
            string actualPrice = "";
            for (int i = 0; i < Price.length(); i++)
            {
                if (Price[i] != ',')
                {
                    actualPrice = actualPrice + Price[i];
                }
            }
            totalPrice = stoi(actualPrice);

            string actualDownPayment = "";
            for (int i = 0; i < DownPayment.length(); i++)
            {
                if (DownPayment[i] != ',')
                {
                    actualDownPayment = actualDownPayment + DownPayment[i];
                }
            }
            downPayments = stoi(actualDownPayment);

            int monthlyInstallment = (totalPrice - downPayments) / Installments;
            CarPlan carPlanObj;
            carPlanObj.setModel(modal);
            carPlanObj.setDownPayment(DownPayment);
            carPlanObj.setInstallments(installments);
            carPlanObj.setPrice(Price);
            carPlanObj.setMonthlyInstallments(monthlyInstallment);
            carPlanObj.setEngine(Engine);
            carPlanObj.setUsed(Used);
            carPlanObj.setUsedManufacturingYear(Manufacturing);


            CarPlanManagerObj.setMake(make, carPlanObj);
        }
    }
    carFile.close();
    return true;
}