#include "../../logs/include/file_io.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cctype>
using std::cout;
using std::endl;
using std::find_if;
using std::ifstream;
using std::string;
using std::stringstream;
using std::unordered_map;
using std::vector;

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

void LoanPlan::display()
{
    cout << "Size: " << size << " ";
    cout << "Installments: " << installments << " ";
    cout << "Price: " << price << " ";
    cout << "DownPayment: " << downPayment << " ";
    cout << "Monthly Installments: " << monthlyInstallments << " ";
    cout << endl;
}

// === LoanPlanManager methods ===
/*
 * Adds a loan plan to the manager under a specific area.
 * @param area: the area identifier (e.g., "1", "2").
 * @param lp: reference to the LoanPlan object to store.
 * @return: void.
 */
void LoanPlanManager::setArea(string area, LoanPlan &lp)
{
    loanTable[area].push_back(lp);
}

/*
 * Displays all loan plans stored for a given area.
 * @param area: the area identifier to look up.
 * @return: void.
 */
void LoanPlanManager::displayLoanPlan(string area)
{
    if (loanTable.count(area))
    {
        for (int i = 0; i < loanTable[area].size(); i++)
        {
            cout << "Area: " << area << " ";
            loanTable[area][i].display();
        }
    }
    else
    {
        cout << "No such area found." << endl;
    }
}

// === file_io methods ===
/*
 * Loads chatbot utterances from a text file into memory.
 * @param filePath: path to the Utterances.txt file.
 * @return: true if file loaded successfully, false otherwise.
 */
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

            uttrObj.setResponse(userInput, response);
        }
    }
    utterancesFile.close();
    return true;
}

string trim(const string &s)
{
    string result = s;
    // remove leading spaces and carriage returns
    result.erase(result.begin(), std::find_if(result.begin(), result.end(),
                                              [](unsigned char ch)
                                              { return !std::isspace(ch) && ch != '\r'; }));
    // remove trailing spaces and carriage returns
    result.erase(std::find_if(result.rbegin(), result.rend(),
                              [](unsigned char ch)
                              { return !std::isspace(ch) && ch != '\r'; })
                     .base(),
                 result.end());
    return result;
}
/*
 * Loads loan plan data from a text file into memory.
 * @param filePath: path to the Home.txt (or loan data) file.
 * @return: true if file loaded successfully, false otherwise.
 */
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
            for(int i =0; i<priceStr.length(); i++)
            {
                if(priceStr[i] != ',')
                {
                    actualPrice = actualPrice + priceStr[i];
                }
            }
            totalPrice = stoi(actualPrice);

            string actualDownPayment = "";
             for(int i =0; i<downpaymentStr.length(); i++)
            {
                if(downpaymentStr[i] != ',')
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