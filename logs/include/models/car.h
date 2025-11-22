#ifndef CAR_H
#define CAR_H

#include <string>
#include <map>
#include <vector>

using std::string;
using std::map;
using std::vector;

// ==================== CAR PLAN CLASS ====================

/**
 * @brief Represents a single car loan plan
 * 
 * Stores all details about a specific car financing option including
 * vehicle specifications (make, model, engine) and loan terms
 * (installments, price, down payment, monthly payment).
 */
class CarPlan
{
private:
    string make;                  ///< Car manufacturer (e.g., "Make 1", "Make 2")
    string model;                 ///< Car model name
    string engine;                ///< Engine specifications (e.g., "1300cc", "1600cc")
    string used;                  ///< Used/New status
    string usedManufacturingYear; ///< Manufacturing year
    string installments;          ///< Number of months (as string, e.g., "36", "48")
    string price;                 ///< Total car price with commas (e.g., "2,500,000")
    string downPayment;           ///< Down payment with commas (e.g., "500,000")
    int monthlyInstallments;      ///< Calculated monthly payment amount (PKR)

public:
    /**
     * @brief Default constructor
     */
    CarPlan() : monthlyInstallments(0) {}

    // ==================== SETTERS ====================
    
    void setMake(string m) { make = m; }
    void setModel(string m) { model = m; }
    void setEngine(string e) { engine = e; }
    void setUsed(string u) { used = u; }
    void setUsedManufacturingYear(string y) { usedManufacturingYear = y; }
    void setInstallments(string i) { installments = i; }
    void setPrice(string p) { price = p; }
    void setDownPayment(string dp) { downPayment = dp; }
    void setMonthlyInstallments(int mi) { monthlyInstallments = mi; }

    // ==================== GETTERS ====================
    
    string getMake() const { return make; }
    string getModel() const { return model; }
    string getEngine() const { return engine; }
    string getUsed() const { return used; }
    string getUsedManufacturingYear() const { return usedManufacturingYear; }
    string getInstallments() const { return installments; }
    string getPrice() const { return price; }
    string getDownPayment() const { return downPayment; }
    int getMonthlyInstallments() const { return monthlyInstallments; }

    /**
     * @brief Displays car plan information in a single line
     * @param showMonthly If true, also shows monthly installment amount
     */
    void display(bool showMonthly = false) const;
};

// ==================== CAR PLAN MANAGER CLASS ====================

/**
 * @brief Manages all car loan plans organized by make
 * 
 * Stores car plans in a map where:
 * - Key: Car make (e.g., "Make 1", "Make 2")
 * - Value: Vector of CarPlan objects for that make
 * 
 * Provides functionality to:
 * - Add plans by make
 * - Display all plans for a specific make
 * - Get plan count for a make
 * - Retrieve specific plan by make and index
 */
class CarPlanManager
{
private:
    map<string, vector<CarPlan>> carTable; ///< Make -> Plans mapping

public:
    /**
     * @brief Adds a car plan to a specific make
     * @param make Car manufacturer name
     * @param plan CarPlan object to add
     */
    void setMake(string make, CarPlan plan)
    {
        carTable[make].push_back(plan);
    }

    /**
     * @brief Displays all available plans for a car make
     * 
     * Shows plans in a formatted table with plan numbers.
     * Displays error if make not found.
     * 
     * @param make Car manufacturer name to display plans for
     */
    void displayCarPlan(string make) const;

    /**
     * @brief Gets the number of plans available for a make
     * @param make Car manufacturer name
     * @return Number of plans, or 0 if make not found
     */
    int getPlanCount(string make) const
    {
        if (carTable.count(make))
        {
            return carTable.at(make).size();
        }
        return 0;
    }

    /**
     * @brief Retrieves a specific car plan by make and index
     * @param make Car manufacturer name
     * @param planIndex Zero-based index of plan
     * @return CarPlan object if found, empty CarPlan otherwise
     */
    CarPlan getPlan(const string& make, int planIndex) const
    {
        if (carTable.count(make) && planIndex >= 0 && planIndex < carTable.at(make).size())
        {
            return carTable.at(make)[planIndex];
        }
        return CarPlan(); // Return empty plan if not found
    }

    /**
     * @brief DEPRECATED - Use displayPaymentSchedule() from ui_display instead
     * 
     * This function is kept for backward compatibility but will be removed.
     * New code should extract plan data using getPlan() and use
     * displayPaymentSchedule() from ui_display.cpp for rendering.
     * 
     * @param make Car manufacturer name
     * @param planIndex Zero-based index of plan
     */
    void displayMonthlyInstallment(string make, int planIndex) const;
};

/**
 * @brief Global car plan manager instance
 * 
 * Loaded from input/Car.txt during program initialization.
 * Available throughout the program for accessing car loan plans.
 */
extern CarPlanManager CarPlanManagerObj;

#endif // CAR_H