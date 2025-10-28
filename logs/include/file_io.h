#ifndef FILE_IO_H
#define FILE_IO_H

#include <vector>
#include <string>
using namespace std;

// Stores a user input phrase and its bot response
class Utterance
{
private:
    string userInput;
    string response;

public:
    string getUserInput()
    {
        return userInput;
    }

    string getResponse()
    {
        return response;
    }

    void setUserInput(string input)
    {
        userInput = input;
    }

    void setResponse(string response)
    {
        this->response = response;
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

// Declare shared data
extern vector<Utterance> utterancesList;
extern vector<LoanPlan> loanPlans;

bool loadUtterances(const string &filePath);
bool loadLoanPlans(const string &filePath);

#endif
