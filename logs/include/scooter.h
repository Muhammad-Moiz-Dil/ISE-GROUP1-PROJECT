#ifndef SCOOTER_H
#define SCOOTER_H

#include <string>
#include <vector>
#include <unordered_map>

using std::string;
using std::vector;
using std::unordered_map;

/**
 * Represents a single scooter plan with details like make, model,
 * distance per charge (km), charging time (hrs), max speed (km/h),
 * installments, price, down payment, and monthly installment amount.
 */
class ScooterPlan
{
private:
    string make;                 // Scooter make (e.g., "Make 1")
    string model;                // Scooter model (e.g., "Model PQR")
    string distancePerChargeKm;  // Distance per full charge in KM (e.g., 250)
    string chargingTimeHrs;      // Charging time in hours (e.g., 3)
    string maxSpeedKmh;          // Max speed km/h (e.g., 75)
    string installments;         // Number of installments as string (e.g., "60")
    string price;                // Price (with commas allowed) (e.g., "250,000")
    string downPayment;          // Down payment (with commas) (e.g., "50,000")
    int monthlyInstallments;     // Calculated monthly installment amount

public:
    // Setters
    void setMake(const string &make);
    void setModel(const string &model);
    void setDistancePerChargeKm(string km);
    void setChargingTimeHrs(string hrs);
    void setMaxSpeedKmh(string kmh);
    void setInstallments(const string &installments);
    void setPrice(const string &price);
    void setDownPayment(const string &downPayment);
    void setMonthlyInstallments(int monthlyInstallments);

    // Getters
    string getMake() const;
    string getModel() const;
    string getDistancePerChargeKm() const;
    string getChargingTimeHrs() const;
    string getMaxSpeedKmh() const;
    string getInstallments() const;
    string getPrice() const;
    string getDownPayment() const;
    int getMonthlyInstallments() const;

    /**
     * Displays all scooter plan details to the console.
     * @param showMonthly: if true, prints the monthly installment amount
     */
    void display(bool showMonthly) const;
};

/**
 * Manages multiple scooter plans organized by brand using an unordered_map.
 * Allows storage and retrieval of scooter plans for specific makes.
 */
class ScooterPlanManager
{
private:
    string make;                                        // Current scooter make
    unordered_map<string, vector<ScooterPlan>> table;   // Map: make -> list of plans

public:
    /**
     * Adds a scooter plan to the manager under a specific make.
     * @param make: the scooter make (e.g., "Make 1")
     * @param sp: reference to the ScooterPlan object to store
     */
    void setMake(const string &make, ScooterPlan &sp);

    /**
     * Gets the number of plans available for a make.
     * @param make: the scooter make
     * @return: number of plans, or 0 if make doesn't exist
     */
    int getPlanCount(const string &make) const;

    /**
     * Displays all scooter plans stored for a given make.
     * @param make: the scooter make to look up
     */
    void displayScooterPlan(const string &make) const;

    /**
     * Displays detailed monthly installment schedule for a specific scooter plan.
     * @param make: the scooter make
     * @param planIndex: the plan number (0-indexed)
     */
    void displayMonthlyInstallment(const string &make, int planIndex) const;
};

// Global ScooterPlanManager object declaration
extern ScooterPlanManager ScooterPlanManagerObj;

#endif