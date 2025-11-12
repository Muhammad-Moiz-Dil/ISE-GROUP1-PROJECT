#ifndef FILE_IO_H
#define FILE_IO_H

#include <vector>
#include <string>
#include <unordered_map>

using std::string;
using std::vector;
using std::unordered_map;

/**
 * Stores user input phrases and their corresponding bot responses for quick lookup.
 * Uses an unordered_map for fast retrieval based on user input strings.
 * Provides fallback response (*) when no match is found.
 */
class Utterance
{
private:
    string userInput;
    string response;
    unordered_map<string, string> responseTable;

public:
    /**
     * Stores a user input and its corresponding chatbot response.
     * @param userInput: the phrase or keyword the user types
     * @param response: the bot's reply to that input
     * @return void
     */
    void setResponse(string userInput, string response);

    /**
     * Retrieves the chatbot response for a given user input.
     * @param userInput: the user's typed message
     * @return the matching response string, or fallback (*) if not found
     */
    string getResponse(string userInput);
};

/**
 * Represents a single loan plan with details like size, installments, price, and down payment.
 * Used to store and display loan information for different property areas.
 */
class LoanPlan
{
private:
    string size;
    string installments;
    string price;
    string downPayment;
    int monthlyInstallments;

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
     * Displays all loan plan details to the console. Control whether to show monthly installments or not.
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
    string area;
    unordered_map<string, vector<LoanPlan>> loanTable;

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
     * Displays monthly installment for a specific plan in an area.
     * @param area: the area identifier
     * @param planIndex: the plan number (0-indexed)
     * @return void
     */
    void displayMonthlyInstallment(string area, int planIndex);

};

/**
 * Loads chatbot utterances from a text file into memory.
 * @param filePath: path to the Utterances.txt file
 * @return true if file loaded successfully, false otherwise
 */
bool loadUtterances(string filePath);

/**
 * Loads loan plan data from a text file into memory.
 * @param filePath: path to the Home.txt (or loan data) file
 * @return true if file loaded successfully, false otherwise
 */
bool loadLoanPlans(string filePath);

// Global object declarations
extern Utterance uttrObj;
extern LoanPlanManager LoanPlanManagerObj;

#endif
