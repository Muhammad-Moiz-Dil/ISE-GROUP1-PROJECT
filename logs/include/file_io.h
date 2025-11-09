#ifndef FILE_IO_H
#define FILE_IO_H

#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
using namespace std;

// Stores a user input phrase and its bot response
class Utterance
{
private:
    string userInput;
    string response;
    unordered_map<string, string> responseTable;

public:
    void setResponse(string userInput, string response)
    {
        responseTable[userInput] = response;
    }

    string getResponse(string userInput)
    {
        if (responseTable.count(userInput))
        {
            return responseTable[userInput];
        }
        else // if  no user input then standard  reply is given.
        {
            userInput = "*";
            return responseTable[userInput];
        }
    }
};

// Stores a loan plan (for later)
class LoanPlan
{
private:
    string size, installments, price, downPayment;

public:
    void setprice(string price)
    {
        this->price = price;
    }
    void setSize(string size)
    {
        this->size = size;
    }
    void setInstallments(string installments)
    {
        this->installments = installments;
    }
    void setDownPayment(string downPayment)
    {
        this->downPayment = downPayment;
    }

    string getprice()
    {
        return this->price;
    }
    string getSize()
    {
        return this->size;
    }
    string getInstallments()
    {
        return this->installments;
    }
    string getDownPayment()
    {
        return this->downPayment;
    }
    void display()
    {
        cout << "Size: " << this->size << " ";
        cout << "Installments: " << this->installments << " ";
        cout << "Price: " << this->price << " ";
        cout << "DownPayment: " << this->downPayment << " ";
        cout << endl;
    }
};
class LoanPlanManager
{
private:
    string area;
    unordered_map<string, vector<LoanPlan>> loanTable;

public:
    void setArea(string area, LoanPlan &lp)
    {
        loanTable[area].push_back(lp);
    }
    void displayLoanPlan(string area)
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
            cout <<"No such area found."<<endl;
        }
    }
};
bool loadUtterances(string filePath);
bool loadLoanPlans(string filePath);
extern Utterance uttrObj;
extern LoanPlanManager LoanPlanManagerObj;

#endif
