#ifndef HOME_LOAN_H
#define HOME_LOAN_H

#include <string>
#include <map>
#include <vector>

using std::string;
using std::map;
using std::vector;

// ==================== HOME LOAN PLAN CLASS ====================

/**
 * @brief Represents a single home loan plan
 * 
 * Stores all details about a home financing option including
 * property size and loan terms (installments, price, down payment, monthly payment).
 */
class HomeLoanPlan
{
private:
    string size;              ///< Property size (e.g., "3 Marla", "5 Marla", "10 Marla")
    string installments;      ///< Number of months (as string, e.g., "36", "60")
    string price;             ///< Total property price with commas (e.g., "5,000,000")
    string downPayment;       ///< Down payment with commas (e.g., "1,000,000")
    int monthlyInstallments;  ///< Calculated monthly payment amount (PKR)

public:
    /**
     * @brief Default constructor
     */
    HomeLoanPlan() : monthlyInstallments(0) {}

    // ==================== SETTERS ====================
    
    void setSize(string s) { size = s; }
    void setInstallments(string i) { installments = i; }
    void setPrice(string p) { price = p; }
    void setDownPayment(string dp) { downPayment = dp; }
    void setMonthlyInstallments(int mi) { monthlyInstallments = mi; }

    // ==================== GETTERS ====================
    
    string getSize() const { return size; }
    string getInstallments() const { return installments; }
    string getPrice() const { return price; }
    string getDownPayment() const { return downPayment; }
    int getMonthlyInstallments() const { return monthlyInstallments; }

    /**
     * @brief Displays home loan plan information in a single line
     * @param showMonthly If true, also shows monthly installment amount
     */
    void display(bool showMonthly = false) const;
};

// ==================== HOME LOAN PLAN MANAGER CLASS ====================

/**
 * @brief Manages all home loan plans organized by area
 * 
 * Stores home loan plans in a map where:
 * - Key: Area name (e.g., "Area 1", "Area 2", "Area 3", "Area 4")
 * - Value: Vector of HomeLoanPlan objects for that area
 * 
 * Provides functionality to:
 * - Add plans by area
 * - Display all plans for a specific area
 * - Get plan count for an area
 * - Retrieve specific plan by area and index
 */
class HomeLoanManager
{
private:
    map<string, vector<HomeLoanPlan>> loanTable; ///< Area -> Plans mapping

public:
    /**
     * @brief Adds a home loan plan to a specific area
     * @param area Area name (e.g., "Area 1")
     * @param plan HomeLoanPlan object to add
     */
    void setArea(string area, HomeLoanPlan plan)
    {
        loanTable[area].push_back(plan);
    }

    /**
     * @brief Displays all available home loan plans for an area
     * 
     * Shows plans in a formatted table with plan numbers.
     * Displays error if area not found.
     * 
     * @param area Area name to display plans for
     */
    void displayHomeLoanPlan(string area) const;

    /**
     * @brief Gets the number of plans available for an area
     * @param area Area name
     * @return Number of plans, or 0 if area not found
     */
    int getPlanCount(string area) const
    {
        if (loanTable.count(area))
        {
            return loanTable.at(area).size();
        }
        return 0;
    }

    /**
     * @brief Retrieves a specific home loan plan by area and index
     * @param area Area name
     * @param planIndex Zero-based index of plan
     * @return HomeLoanPlan object if found, empty HomeLoanPlan otherwise
     */
    HomeLoanPlan getPlan(const string& area, int planIndex) const
    {
        if (loanTable.count(area) && planIndex >= 0 && planIndex < loanTable.at(area).size())
        {
            return loanTable.at(area)[planIndex];
        }
        return HomeLoanPlan(); // Return empty plan if not found
    }

    /**
     * @brief DEPRECATED - Use displayPaymentSchedule() from ui_display instead
     * 
     * This function is kept for backward compatibility but will be removed.
     * New code should extract plan data using getPlan() and use
     * displayPaymentSchedule() from ui_display.cpp for rendering.
     * 
     * @param area Area name
     * @param planIndex Zero-based index of plan
     */
    void displayMonthlyInstallment(string area, int planIndex) const;
};

/**
 * @brief Global home loan plan manager instance
 * 
 * Loaded from input/Home.txt during program initialization.
 * Available throughout the program for accessing home loan plans.
 */
extern HomeLoanManager HomeLoanManagerObj;

#endif // HOME_LOAN_H