#ifndef FILE_IO_H
#define FILE_IO_H

#include <vector>
#include <string>
#include <unordered_map>
using std::string;
using std::vector;
using std::unordered_map;

/*
 * Stores user input phrases and their corresponding bot responses for quick lookup.
 * Uses an unordered_map for fast retrieval based on user input strings.
 * Provides fallback response (*) when no match is found.
*/
class Utterance
{
private:
    string userInput;
    string response;
    unordered_map<string, string> responseTable;

public:
    void setResponse(string userInput, string response);
    string getResponse(string userInput);
};

/*
 * Represents a single loan plan with details like size, installments, price, and down payment.
 * Used to store and display loan information for different property areas.
*/
class LoanPlan
{
private:
    string size;
    string installments;
    string price;
    string downPayment;
    int monthlyInstallments;

public:
    void setprice(string price);
    void setSize(string size);
    void setInstallments(string installments);
    void setDownPayment(string downPayment);
    void setMonthlyInstallments(int monthlyInstallments);
    string getprice();
    string getSize();
    string getInstallments();
    string getDownPayment();
    int getMonthlyInstallments();
    void display();
};

/*
 * Manages multiple loan plans organized by area using an unordered_map.
 * Allows storage and retrieval of loan plans for specific areas.
*/
class LoanPlanManager
{
private:
    string area;
    unordered_map<string, vector<LoanPlan>> loanTable;

public:
    void setArea(string area, LoanPlan &lp);
    void displayLoanPlan(string area);
    string getLoanPlanDetails(string area);
};

bool loadUtterances(string filePath);
bool loadLoanPlans(string filePath);

extern Utterance uttrObj;
extern LoanPlanManager LoanPlanManagerObj;

#endif
