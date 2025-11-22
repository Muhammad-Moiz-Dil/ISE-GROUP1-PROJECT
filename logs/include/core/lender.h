#ifndef LENDER_H
#define LENDER_H

#include "core/application.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

// ==================== LENDER MANAGER CLASS ====================

/**
 * @brief Manages loan applications from lender's perspective
 * 
 * Provides functionality for lenders to:
 * - View all applications in a table format
 * - Search for specific applications by ID
 * - View detailed application information
 * - Approve or reject applications
 * - Save status updates to file
 * 
 * This class is separate from ApplicationManager (which is for customers)
 * to maintain clear separation between customer and lender operations.
 */
class LenderManager
{
private:
    vector<Application> applications;  ///< All loaded applications
    string applicationsFilePath;       ///< Path to applications.txt file

public:
    /**
     * @brief Constructor - initializes with file path
     * @param filePath Path to applications.txt (e.g., "output/applications.txt")
     */
    LenderManager(const string& filePath);

    /**
     * @brief Loads all applications from file into memory
     * 
     * Reads applications.txt and parses each line using Application::fromFileFormat().
     * Clears any previously loaded applications before loading.
     * 
     * @return true if file loaded successfully, false if file not found or error
     */
    bool loadApplications();

    /**
     * @brief Saves all applications back to file
     * 
     * Overwrites entire applications.txt file with current state.
     * Used after approving/rejecting applications to persist changes.
     * 
     * @return true if saved successfully, false on file error
     */
    bool saveApplications();

    /**
     * @brief Displays all applications in a formatted table
     * 
     * Shows: Application ID, Full Name, Loan Type, Status, Submission Date
     * Organized in a clean table format with headers and borders.
     * Shows total count at the bottom.
     */
    void displayAllApplications() const;

    /**
     * @brief Searches for an application by its ID
     * 
     * Performs linear search through loaded applications.
     * Case-sensitive exact match.
     * 
     * @param appID Application ID to search for (e.g., "1001")
     * @return Index of application in vector (0-based), or -1 if not found
     */
    int findApplicationByID(const string& appID) const;

    /**
     * @brief Displays detailed information for a specific application
     * 
     * Shows all fields organized into sections:
     * - Metadata (ID, Status, Date)
     * - Personal Information (Name, CNIC, Contact, etc.)
     * - Financial Information (Income, Employment, etc.)
     * - Loan Details (Type, Area/Make)
     * 
     * Uses color-coded section headers for better readability.
     * 
     * @param index Index of application in vector (from findApplicationByID)
     */
    void displayApplicationDetails(int index) const;

    /**
     * @brief Updates status of an application and saves to file
     * 
     * Changes application status to "Approved" or "Rejected"
     * and immediately persists changes to file.
     * 
     * @param index Index of application in vector
     * @param newStatus New status ("Approved" or "Rejected")
     * @return true if updated and saved successfully, false otherwise
     */
    bool updateApplicationStatus(int index, const string& newStatus);

    /**
     * @brief Gets total number of loaded applications
     * @return Count of applications in memory
     */
    int getApplicationCount() const;
};

// ==================== LENDER PORTAL INTERFACE FUNCTIONS ====================

/**
 * @brief Displays lender portal welcome header with branding
 * 
 * Shows colorful header with title "LENDER PORTAL - LOAN MANAGEMENT"
 * Uses green color scheme to differentiate from customer interface.
 */
void displayLenderHeader();

/**
 * @brief Displays main menu options for lender portal
 * 
 * Menu options:
 * 1. View All Applications
 * 2. Search Application by ID
 * 3. Approve/Reject Application
 * 4. Exit
 * 
 * Prompts user to enter choice (1-4 or X to exit).
 */
void displayLenderMenu();

/**
 * @brief Handles "View All Applications" menu option
 * 
 * Displays table of all applications with key information.
 * 
 * @param manager Reference to LenderManager instance
 */
void handleViewAllApplications(LenderManager& manager);

/**
 * @brief Handles "Search Application by ID" menu option
 * 
 * Prompts for Application ID, searches, and displays details if found.
 * Shows error message if application not found.
 * 
 * @param manager Reference to LenderManager instance
 */
void handleSearchApplication(LenderManager& manager);

/**
 * @brief Handles "Approve/Reject Application" menu option
 * 
 * Flow:
 * 1. Prompt for Application ID
 * 2. Display application details
 * 3. Show action menu (Approve/Reject/Cancel)
 * 4. Update status and save if approved/rejected
 * 
 * Shows success/error messages after action.
 * 
 * @param manager Reference to LenderManager instance
 */
void handleApproveReject(LenderManager& manager);

/**
 * @brief Main entry point for lender portal
 * 
 * Complete flow:
 * 1. Display welcome header
 * 2. Load applications from file
 * 3. Enter menu loop
 * 4. Route user choices to appropriate handlers
 * 5. Exit when user selects X or option 4
 * 
 * @param manager Reference to LenderManager instance
 */
void runLenderPortal(LenderManager& manager);

#endif // LENDER_H