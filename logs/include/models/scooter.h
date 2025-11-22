#ifndef SCOOTER_H
#define SCOOTER_H

#include <string>
#include <map>
#include <vector>

using std::string;
using std::map;
using std::vector;

// ==================== SCOOTER PLAN CLASS ====================

/**
 * @brief Represents a single electric scooter loan plan
 * 
 * Stores all details about an electric scooter financing option including
 * vehicle specifications (make, model, battery specs) and loan terms
 * (installments, price, down payment, monthly payment).
 */
class ScooterPlan
{
private:
    string make;                  ///< Scooter manufacturer (e.g., "Make 1", "Make 2")
    string model;                 ///< Scooter model name
    string distancePerChargeKm;   ///< Range per full charge in kilometers
    string chargingTimeHrs;       ///< Time to fully charge in hours
    string maxSpeedKmh;           ///< Maximum speed in km/h
    string installments;          ///< Number of months (as string, e.g., "24", "36")
    string price;                 ///< Total scooter price with commas (e.g., "150,000")
    string downPayment;           ///< Down payment with commas (e.g., "30,000")
    int monthlyInstallments;      ///< Calculated monthly payment amount (PKR)

public:
    /**
     * @brief Default constructor
     */
    ScooterPlan() : monthlyInstallments(0) {}

    // ==================== SETTERS ====================
    
    void setMake(string m) { make = m; }
    void setModel(string m) { model = m; }
    void setDistancePerChargeKm(string d) { distancePerChargeKm = d; }
    void setChargingTimeHrs(string c) { chargingTimeHrs = c; }
    void setMaxSpeedKmh(string s) { maxSpeedKmh = s; }
    void setInstallments(string i) { installments = i; }
    void setPrice(string p) { price = p; }
    void setDownPayment(string dp) { downPayment = dp; }
    void setMonthlyInstallments(int mi) { monthlyInstallments = mi; }

    // ==================== GETTERS ====================
    
    string getMake() const { return make; }
    string getModel() const { return model; }
    string getDistancePerChargeKm() const { return distancePerChargeKm; }
    string getChargingTimeHrs() const { return chargingTimeHrs; }
    string getMaxSpeedKmh() const { return maxSpeedKmh; }
    string getInstallments() const { return installments; }
    string getPrice() const { return price; }
    string getDownPayment() const { return downPayment; }
    int getMonthlyInstallments() const { return monthlyInstallments; }

    /**
     * @brief Displays scooter plan information in a single line
     * @param showMonthly If true, also shows monthly installment amount
     */
    void display(bool showMonthly = false) const;
};

// ==================== SCOOTER PLAN MANAGER CLASS ====================

/**
 * @brief Manages all electric scooter loan plans organized by make
 * 
 * Stores scooter plans in a map where:
 * - Key: Scooter make (e.g., "Make 1", "Make 2")
 * - Value: Vector of ScooterPlan objects for that make
 * 
 * Provides functionality to:
 * - Add plans by make
 * - Display all plans for a specific make
 * - Get plan count for a make
 * - Retrieve specific plan by make and index
 */
class ScooterPlanManager
{
private:
    map<string, vector<ScooterPlan>> table; ///< Make -> Plans mapping

public:
    /**
     * @brief Adds a scooter plan to a specific make
     * @param make Scooter manufacturer name
     * @param plan ScooterPlan object to add
     */
    void setMake(string make, ScooterPlan plan)
    {
        table[make].push_back(plan);
    }

    /**
     * @brief Displays all available plans for a scooter make
     * 
     * Shows plans in a formatted table with plan numbers.
     * Displays error if make not found.
     * 
     * @param make Scooter manufacturer name to display plans for
     */
    void displayScooterPlan(const string &make) const;

    /**
     * @brief Gets the number of plans available for a make
     * @param make Scooter manufacturer name
     * @return Number of plans, or 0 if make not found
     */
    int getPlanCount(const string &make) const
    {
        if (table.count(make))
        {
            return table.at(make).size();
        }
        return 0;
    }

    /**
     * @brief Retrieves a specific scooter plan by make and index
     * @param make Scooter manufacturer name
     * @param planIndex Zero-based index of plan
     * @return ScooterPlan object if found, empty ScooterPlan otherwise
     */
    ScooterPlan getPlan(const string& make, int planIndex) const
    {
        if (table.count(make) && planIndex >= 0 && planIndex < table.at(make).size())
        {
            return table.at(make)[planIndex];
        }
        return ScooterPlan(); // Return empty plan if not found
    }

    /**
     * @brief DEPRECATED - Use displayPaymentSchedule() from ui_display instead
     * 
     * This function is kept for backward compatibility but will be removed.
     * New code should extract plan data using getPlan() and use
     * displayPaymentSchedule() from ui_display.cpp for rendering.
     * 
     * @param make Scooter manufacturer name
     * @param planIndex Zero-based index of plan
     */
    void displayMonthlyInstallment(const string &make, int planIndex) const;
};

/**
 * @brief Global scooter plan manager instance
 * 
 * Loaded from input/Scooter.txt during program initialization.
 * Available throughout the program for accessing scooter loan plans.
 */
extern ScooterPlanManager ScooterPlanManagerObj;

#endif // SCOOTER_H