#ifndef LENDER_H
#define LENDER_H

#include <string>
#include <vector>
#include "application.h"

using std::string;
using std::vector;

/**
 * @brief Manages lender operations for viewing and processing loan applications
 * 
 * This class provides functionality for lenders to:
 * - View all pending applications
 * - Search applications by ID
 * - Approve or reject applications
 */
class LenderManager
{
private:
    vector<Application> applications;
    string applicationsFilePath;

public:
    /**
     * @brief Constructs a LenderManager with specified file path
     * @param filePath Path to applications.txt file
     */
    LenderManager(const string& filePath);

    /**
     * @brief Loads all applications from file
     * @return true if load successful, false otherwise
     */
    bool loadApplications();

    /**
     * @brief Saves all applications back to file
     * @return true if save successful, false otherwise
     */
    bool saveApplications();

    /**
     * @brief Displays all pending applications in a formatted table
     */
    void viewAllApplications();

    /**
     * @brief Searches for an application by ID
     * @param appID Application ID to search for
     * @return Index of application if found, -1 otherwise
     */
    int searchApplicationByID(const string& appID);

    /**
     * @brief Displays detailed information for a specific application
     * @param index Index of application in vector
     */
    void viewApplicationDetails(int index);

    /**
     * @brief Approves an application
     * @param index Index of application in vector
     * @return true if approval successful, false otherwise
     */
    bool approveApplication(int index);

    /**
     * @brief Rejects an application
     * @param index Index of application in vector
     * @return true if rejection successful, false otherwise
     */
    bool rejectApplication(int index);

    /**
     * @brief Gets total count of applications
     * @return Number of applications loaded
     */
    int getApplicationCount() const;
};

/**
 * @brief Displays the lender portal welcome header
 */
void displayLenderHeader();

/**
 * @brief Displays the lender portal main menu
 */
void displayLenderMenu();

/**
 * @brief Runs the main lender portal loop
 * @param manager Reference to LenderManager object
 */
void runLenderPortal(LenderManager& manager);

#endif
