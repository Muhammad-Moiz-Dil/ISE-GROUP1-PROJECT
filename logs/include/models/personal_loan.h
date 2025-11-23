#ifndef PERSONAL_LOAN_H
#define PERSONAL_LOAN_H

#include <string>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;

class PersonalLoanPlan {
    string planName;
    string installments;
    string totalAmount;
    string downPayment;
    int monthlyInstallments;

public:
    PersonalLoanPlan() : monthlyInstallments(0) {}

    void setPlanName(string n) { planName = n; }
    void setInstallments(string i) { installments = i; }
    void setTotalAmount(string t) { totalAmount = t; }
    void setDownPayment(string d) { downPayment = d; }
    void setMonthlyInstallments(int m) { monthlyInstallments = m; }

    string getPlanName() const { return planName; }
    string getInstallments() const { return installments; }
    string getTotalAmount() const { return totalAmount; }
    string getDownPayment() const { return downPayment; }
    int getMonthlyInstallments() const { return monthlyInstallments; }

    void display(bool showMonthly) const;
};

class PersonalLoanManager {
    map<string, vector<PersonalLoanPlan>> loanTable;

public:
    void setCategory(string category, PersonalLoanPlan plan) { loanTable[category].push_back(plan); }
    
    int getPlanCount(string category) const { 
        return loanTable.count(category) ? loanTable.at(category).size() : 0; 
    }
    
    void displayPersonalLoanPlan(string category) const;
    
    PersonalLoanPlan getPlan(string category, int index) const { 
        if (loanTable.count(category) && index >= 0 && index < loanTable.at(category).size()) {
            return loanTable.at(category)[index];
        }
        return PersonalLoanPlan();
    }
};

extern PersonalLoanManager PersonalLoanManagerObj;

#endif
