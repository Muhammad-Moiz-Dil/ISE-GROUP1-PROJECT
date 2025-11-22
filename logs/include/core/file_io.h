#ifndef FILE_IO_H
#define FILE_IO_H

#include <string>
#include <map>

using std::string;
using std::map;

// ==================== UTTERANCE MANAGEMENT ====================

/**
 * @brief Manages chatbot responses based on user input
 * 
 * Stores key-value pairs where keys are user inputs (lowercase)
 * and values are corresponding bot responses. Supports fallback
 * response for unrecognized inputs using "*" key.
 */
class Utterance {
private:
    map<string, string> responseTable;

public:
    /**
     * @brief Sets a response for a given user input
     * @param userInput The user's input text (will be stored as lowercase)
     * @param response The bot's response text
     */
    void setResponse(string userInput, string response);

    /**
     * @brief Gets the response for a given user input
     * @param userInput The user's input text
     * @return Corresponding response, or fallback "*" response if not found
     */
    string getResponse(string userInput);
};

/**
 * @brief Global Utterance manager instance
 */
extern Utterance uttrObj;

// ==================== FILE LOADING FUNCTIONS ====================

/**
 * @brief Loads chatbot utterances from file
 * 
 * File format: userInput#response (one per line)
 * User inputs are automatically converted to lowercase.
 * 
 * @param filePath Path to utterances file (e.g., "input/Utterances.txt")
 * @return true if file loaded successfully, false otherwise
 */
bool loadUtterances(const string &filePath);

/**
 * @brief Loads home loan plans from file
 * 
 * File format (CSV with # delimiter):
 * Area#Size#Installments#Price#DownPayment
 * 
 * @param filePath Path to loan plans file (e.g., "input/Home.txt")
 * @return true if file loaded successfully, false otherwise
 */
bool loadLoanPlans(const string &filePath);

/**
 * @brief Loads car loan plans from file
 * 
 * File format (CSV with # delimiter):
 * Make#Model#Engine#Used#Manufacturing#Installments#Price#DownPayment
 * 
 * @param filePath Path to car plans file (e.g., "input/Car.txt")
 * @return true if file loaded successfully, false otherwise
 */
bool loadCarPlans(const string &filePath);

/**
 * @brief Loads scooter loan plans from file
 * 
 * File format (CSV with # delimiter):
 * Make#Model#DistancePerCharge#ChargingTime#MaxSpeed#Installments#Price#DownPayment
 * 
 * @param filePath Path to scooter plans file (e.g., "input/Scooter.txt")
 * @return true if file loaded successfully, false otherwise
 */
bool loadScooterPlans(const string &filePath);

#endif // FILE_IO_H