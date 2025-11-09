using namespace std;
#ifndef FILE_IO_H
#define FILE_IO_H

#include <vector>
#include <string>

// classes for loaded data
class Utterance 
{ 
    string userInput; string response; 
};
class LoanPlan 
{ 
    string area, type, amount, terms ; 
};
// Global vectors to share in multiple modules
extern vector<Utterance> utterancesList;
extern vector<LoanPlan> loanPlans;

// Loads utterances from text file into utterancesList vector
bool loadUtterances(const string& filePath);

// Loads loan plan data (such as from Home.txt) into loanPlans vector
bool loadLoanPlans(const string& filePath);



#endif // FILE_IO_H
