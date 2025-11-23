#ifndef PERSONAL_LOAN_H
#define PERSONAL_LOAN_H

#include <string>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;

// ==================== PERSONAL LOAN PLAN CLASS ====================

/**
 * @brief Represents a single personal loan plan (Wedding, Education, Business)
 */
class PersonalLoanPlan {
private:
    string planName;            ///< Name of the plan (e.g., "Standard", "Premium")
    string installments;        ///< Number of months (e.g., "12", "24")
    string totalAmount;         ///< Total loan amount with commas (e.g., "500,000")
    string downPayment;         ///< Down payment amount
    int monthlyInstallments;    ///< Calculated monthly payment (PKR)

public:
    PersonalLoanPlan() : monthlyInstallments(0) {}

    // ==================== SETTERS ====================
    void setPlanName(string n) { planName = n; }
    void setInstallments(string i) { installments = i; }
    void setTotalAmount(string t) { totalAmount = t; }
    void setDownPayment(string d) { downPayment = d; }
    void setMonthlyInstallments(int m) { monthlyInstallments = m; }

    // ==================== GETTERS ====================
    string getPlanName() const { return planName; }
    string getInstallments() const { return installments; }
    string getTotalAmount() const { return totalAmount; }
    string getDownPayment() const { return downPayment; }
    int getMonthlyInstallments() const { return monthlyInstallments; }

    /**
     * @brief Displays plan details in a single line
     * @param showMonthly If true, includes monthly payment amount
     */
    void display(bool showMonthly = false) const;
};

// ==================== PERSONAL LOAN MANAGER CLASS ====================

/**
 * @brief Manages personal loan plans organized by category
 */
class PersonalLoanManager {
private:
    map<string, vector<PersonalLoanPlan>> loanTable; ///< Category -> Plans mapping

public:
    /**
     * @brief Adds a plan to a specific category
     * @param category Category name (Wedding, Education, Business)
     * @param plan Plan object to add
     */
    void setCategory(string category, PersonalLoanPlan plan) {
        loanTable[category].push_back(plan);
    }
    
    /**
     * @brief Gets number of plans in a category
     * @param category Category name
     * @return Count of plans
     */
    int getPlanCount(string category) const { 
        return loanTable.count(category) ? loanTable.at(category).size() : 0; 
    }
    
    /**
     * @brief Displays all plans for a category
     * @param category Category name to display
     */
    void displayPersonalLoanPlan(string category) const;
    
    /**
     * @brief Retrieves a specific plan
     * @param category Category name
     * @param index Plan index (0-based)
     * @return PersonalLoanPlan object
     */
    PersonalLoanPlan getPlan(string category, int index) const { 
        if (loanTable.count(category) && index >= 0 && index < loanTable.at(category).size()) {
            return loanTable.at(category)[index];
        }
        return PersonalLoanPlan();
    }
};

extern PersonalLoanManager PersonalLoanManagerObj;

#endif // PERSONAL_LOAN_H