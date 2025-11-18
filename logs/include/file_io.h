#ifndef FILE_IO_H
#define FILE_IO_H

#include <string>
#include <unordered_map>

using std::string;
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
 * Loads chatbot utterances from a file into the Utterance object.
 * File format: each line contains "user_input | bot_response"
 * @param filePath: path to the Utterances.txt file
 * @return true if loaded successfully, false otherwise
 */
bool loadUtterances(const string& filePath);

/**
 * Loads loan plans from a file into the LoanPlanManager object.
 * File format: each line contains "size,installments,price,downPayment"
 * First line of each section specifies the area name.
 * @param filePath: path to the loan data file (e.g., Home.txt, Car.txt)
 * @return true if loaded successfully, false otherwise
 */
bool loadLoanPlans(const string& filePath);

// Global Utterance object declaration
extern Utterance uttrObj;

#endif // FILE_IO_H