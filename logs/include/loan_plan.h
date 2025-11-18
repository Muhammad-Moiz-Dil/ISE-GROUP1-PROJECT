#ifndef LOAN_PLAN_H
#define LOAN_PLAN_H

#include <string>
#include <vector>
#include <unordered_map>

using std::string;
using std::vector;
using std::unordered_map;

/**
 * Represents a single loan plan with details like size, installments, price, and down payment.
 * Used to store and display loan information for different property areas.
 */
class LoanPlan
{
private:
    string size;              // Property size (e.g., "5 Marla", "10 Marla")
    string installments;      // Number of installments as string
    string price;             // Total loan price (with commas)
    string downPayment;       // Down payment amount (with commas)
    int monthlyInstallments;  // Calculated monthly installment amount

public:
    /**
     * Sets the total price of the loan plan.
     * @param price: the loan plan price as a string
     * @return void
     */
    void setprice(string price);

    /**
     * Sets the property size for the loan plan.
     * @param size: the size of the property (e.g., "5 Marla")
     * @return void
     */
    void setSize(string size);

    /**
     * Sets the number of installments for the loan plan.
     * @param installments: the installment count as a string
     * @return void
     */
    void setInstallments(string installments);

    /**
     * Sets the down payment amount for the loan plan.
     * @param downPayment: the down payment amount as a string
     * @return void
     */
    void setDownPayment(string downPayment);

    /**
     * Sets the calculated monthly installment amount.
     * @param monthlyInstallments: the monthly payment amount as an integer
     * @return void
     */
    void setMonthlyInstallments(int monthlyInstallments);

    /**
     * Gets the total price of the loan plan.
     * @return the price as a string
     */
    string getprice();

    /**
     * Gets the property size.
     * @return the size as a string
     */
    string getSize();

    /**
     * Gets the number of installments.
     * @return the installments as a string
     */
    string getInstallments();

    /**
     * Gets the down payment amount.
     * @return the down payment as a string
     */
    string getDownPayment();

    /**
     * Gets the monthly installment amount.
     * @return the monthly payment as an integer
     */
    int getMonthlyInstallments();

    /**
     * Displays all loan plan details to the console.
     * @param showMonthly: if true, displays monthly installment amount
     * @return void
     */
    void display(bool showMonthly);
};

/**
 * Manages multiple loan plans organized by area using an unordered_map.
 * Allows storage and retrieval of loan plans for specific areas.
 */
class LoanPlanManager
{
private:
    string area;                                           // Current area name
    unordered_map<string, vector<LoanPlan>> loanTable;    // Map: area name -> list of plans

public:
    /**
     * Adds a loan plan to the manager under a specific area.
     * @param area: the area identifier (e.g., "Area 1", "Area 2")
     * @param lp: reference to the LoanPlan object to store
     * @return void
     */
    void setArea(string area, LoanPlan &lp);

    /**
     * Gets the number of plans available for an area.
     * @param area: the area identifier
     * @return: number of plans, or 0 if area doesn't exist
     */
    int getPlanCount(string area);

    /**
     * Displays all loan plans stored for a given area.
     * @param area: the area identifier to look up
     * @return void
     */
    void displayLoanPlan(string area);

    /**
     * Displays detailed monthly installment schedule for a specific plan in an area.
     * Shows amortization table with month-by-month breakdown.
     * @param area: the area identifier
     * @param planIndex: the plan number (0-indexed)
     * @return void
     */
    void displayMonthlyInstallment(string area, int planIndex);
};

// Global LoanPlanManager object declaration
extern LoanPlanManager LoanPlanManagerObj;

#endif // LOAN_PLAN_H