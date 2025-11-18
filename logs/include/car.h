#ifndef CAR_H
#define CAR_H

#include <string>
#include <vector>
#include <unordered_map>

using std::string;
using std::vector;
using std::unordered_map;

/**
 * Represents a single car plan with details like make, model, engine,
 * manufacturing year, installments, price, down payment, and monthly installments.
 */
class CarPlan
{
private:
    string make;                 // Car make (e.g., "Toyota")
    string model;                // Car model (e.g., "Corolla")
    string engine;               // Engine type or capacity (e.g., "1.6L")
    string usedManufacturingYear;   // Year of manufacture
    string installments;         // Number of installments as string
    string price;                // Total price (with commas)
    string downPayment;          // Down payment amount (with commas)
    int monthlyInstallments;     // Calculated monthly installment amount
    string used;

public:
    // Setters
    void setMake(string make);
    void setModel(string model);
    void setEngine(string engine);
    void setUsed(string u);
    void setInstallments(string installments);
    void setPrice(string price);
    void setDownPayment(string downPayment);
    void setMonthlyInstallments(int monthlyInstallments);
    void setUsedManufacturingYear(string year);

    // Getters
    string getMake();
    string getModel();
    string getEngine();
    string getUsedManufacturingYear();
    string getInstallments();
    string getPrice();
    string getDownPayment();
    int getMonthlyInstallments();

    /**
     * Displays all car plan details to the console.
     * @param showMonthly: if true, displays monthly installment amount
     */
    void display(bool showMonthly);
};

/**
 * Manages multiple car plans organized by brand using an unordered_map.
 * Allows storage and retrieval of car plans for specific makes.
 */
class CarPlanManager
{
private:
    string make;                                   // Current car make
    unordered_map<string, vector<CarPlan>> carTable; // Map: car make -> list of car plans

public:
    /**
     * Adds a car plan to the manager under a specific make.
     * @param make: the car make (e.g., "Toyota")
     * @param cp: reference to the CarPlan object to store
     */
    void setMake(string make, CarPlan &cp);

    /**
     * Gets the number of plans available for a make.
     * @param make: the car make
     * @return: number of plans, or 0 if make doesn't exist
     */
    int getPlanCount(string make);

    /**
     * Displays all car plans stored for a given make.
     * @param make: the car make to look up
     */
    void displayCarPlan(string make);

    /**
     * Displays detailed monthly installment schedule for a specific car plan.
     * @param make: the car make
     * @param planIndex: the plan number (0-indexed)
     */
    void displayMonthlyInstallment(string make, int planIndex);
};

// Global CarPlanManager object declaration
extern CarPlanManager CarPlanManagerObj;
#endif