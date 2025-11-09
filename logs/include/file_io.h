#ifndef FILE_IO_H
#define FILE_IO_H

#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

// Stores a user input phrase and its bot response
class Utterance
{
private:
    string userInput;
    string response;
    unordered_map<string,string> responseTable;
public:
    void setResponse(string userInput,  string response)
    {
        responseTable[userInput]  = response;
    }

    string getResponse(string userInput)
    {
        if(responseTable.count(userInput))
        {
            return responseTable[userInput];
        }
        else      //if  no user input then standard  reply is given.
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
    string area, type, amount, terms;
public:
    string getArea()
    {
        return area;
    }

    string getType()
    {
        return type;
    }

    string getAmount()
    {
        return amount;
    }

    string getTerms()
    {
        return terms;
    }

    void setArea(string area)
    {
        this->area = area;
    }

    void setType(string type)
    {
        this->type = type;
    }

    void setAmount(string amount)
    {
        this->amount = amount;
    }

    void setTerms(string terms)
    {
        this->terms = terms;
    }
};
bool loadUtterances(const string &filePath);
bool loadLoanPlans(const string &filePath);

#endif
