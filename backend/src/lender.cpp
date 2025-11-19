#include "../../logs/include/lender.h"
#include "../../logs/include/utils.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::getline;
using std::setw;
using std::left;
using std::stringstream;

// ==================== LenderManager Class Implementation ====================

/**
 * @brief Constructs a LenderManager with specified file path
 */
LenderManager::LenderManager(const string& filePath)
{
    applicationsFilePath = filePath;
}

/**
 * @brief Loads all applications from file
 */
bool LenderManager::loadApplications()
{
    ifstream file(applicationsFilePath);
    if (!file.is_open())
    {
        cout << "Error: Could not open applications file." << endl;
        return false;
    }

    applications.clear();
    string line;
    
    // Skip header line
    getline(file, line);

    // Parse each application line
    while (getline(file, line))
    {
        if (line.empty()) continue;
        
        // Use the existing fromFileFormat method!
        Application app = Application::fromFileFormat(line);
        applications.push_back(app);
    }

    file.close();
    return true;
}

/**
 * @brief Saves all applications back to file
 */
bool LenderManager::saveApplications()
{
    ofstream file(applicationsFilePath);
    if (!file.is_open())
    {
        cout << "Error: Could not save applications." << endl;
        return false;
    }

    // Write header first
    file << "ApplicationID#Status#FullName#FathersName#PostalAddress#Contact#Email#"
         << "CNIC#CNICExpiry#Employment#Marital#Gender#Dependents#AnnualIncome#"
         << "AvgElectricityBill#CurrentElectricityBill#HasExistingLoan#LoanActive#"
         << "LoanTotal#LoanReturned#LoanDue#LoanBank#LoanCategory#"
         << "Referee1Name#Referee1CNIC#Referee1IssueDate#Referee1Phone#Referee1Email#"
         << "Referee2Name#Referee2CNIC#Referee2IssueDate#Referee2Phone#Referee2Email#"
         << "CNICFrontPath#CNICBackPath#ElectricityBillPath#SalarySlipPath#"
         << "SelectedLoanType#SelectedLoanDetails#SubmissionDate\n";

    for (const auto& app : applications)
    {
        file << app.toFileFormat() << endl;  // ✅ Correct function name
    }

    file.close();
    return true;
}

/**
 * @brief Displays all pending applications in a formatted table
 */
void LenderManager::viewAllApplications()
{
    if (applications.empty())
    {
        cout << "\nNo applications found." << endl;
        return;
    }

    cout << "\n============================================================================" << endl;
    cout << "                         ALL LOAN APPLICATIONS" << endl;
    cout << "============================================================================" << endl;
    cout << left << setw(8) << "ID" 
         << setw(25) << "Name" 
         << setw(15) << "Loan Type" 
         << setw(15) << "Status" 
         << setw(15) << "Date" << endl;
    cout << "----------------------------------------------------------------------------" << endl;

    for (const auto& app : applications)
    {
        cout << left << setw(8) << app.getApplicationID()
             << setw(25) << app.getFullName()
             << setw(15) << app.getLoanType()
             << setw(15) << app.getStatus()
             << setw(15) << app.getSubmissionDate() << endl;
    }

    cout << "============================================================================" << endl;
    cout << "Total Applications: " << applications.size() << endl;
}

/**
 * @brief Searches for an application by ID
 */
int LenderManager::searchApplicationByID(const string& appID)
{
    for (int i = 0; i < applications.size(); i++)
    {
        if (applications[i].getApplicationID() == appID)
        {
            return i;
        }
    }
    return -1;
}

/**
 * @brief Displays detailed information for a specific application
 */
void LenderManager::viewApplicationDetails(int index)
{
    if (index < 0 || index >= applications.size())
    {
        cout << "Invalid application index." << endl;
        return;
    }

    const Application& app = applications[index];

    cout << "\n============================================================================" << endl;
    cout << "                    APPLICATION DETAILS" << endl;
    cout << "============================================================================" << endl;
    cout << "Application ID: " << app.getApplicationID() << endl;
    cout << "Status: " << app.getStatus() << endl;
    cout << "Submission Date: " << app.getSubmissionDate() << endl;
    cout << "\nPERSONAL INFORMATION:" << endl;
    cout << "  Full Name: " << app.getFullName() << endl;
    cout << "  Father's Name: " << app.getFathersName() << endl;
    cout << "  CNIC: " << app.getCNIC() << endl;
    cout << "  Contact: " << app.getContact() << endl;
    cout << "  Email: " << app.getEmail() << endl;
    cout << "\nFINANCIAL INFORMATION:" << endl;
    cout << "  Employment: " << app.getEmployment() << endl;
    cout << "  Annual Income: " << app.getAnnualIncome() << " PKR" << endl;
    cout << "  Dependents: " << app.getDependents() << endl;
    cout << "\nLOAN DETAILS:" << endl;
    cout << "  Loan Type: " << app.getLoanType() << endl;
    cout << "  Loan Area: " << app.getLoanArea() << endl;
    cout << "============================================================================" << endl;
}

/**
 * @brief Approves an application
 */
bool LenderManager::approveApplication(int index)
{
    if (index < 0 || index >= applications.size())
    {
        return false;
    }

    applications[index].setStatus("Approved");
    return saveApplications();
}

/**
 * @brief Rejects an application
 */
bool LenderManager::rejectApplication(int index)
{
    if (index < 0 || index >= applications.size())
    {
        return false;
    }

    applications[index].setStatus("Rejected");
    return saveApplications();
}

/**
 * @brief Gets total count of applications
 */
int LenderManager::getApplicationCount() const
{
    return applications.size();
}

// ==================== Helper Functions ====================

/**
 * @brief Displays the lender portal welcome header
 */
void displayLenderHeader()
{
    cout << "\n=============================================" << endl;
    cout << "       LENDER PORTAL - LOAN MANAGEMENT" << endl;
    cout << "---------------------------------------------" << endl;
}

/**
 * @brief Displays the lender portal main menu
 */
void displayLenderMenu()
{
    cout << "\n1. View All Applications" << endl;
    cout << "2. Search Application by ID" << endl;
    cout << "3. Approve/Reject Application" << endl;
    cout << "4. Exit" << endl;
    cout << "\nEnter your choice (or X to exit): ";
}

/**
 * @brief Runs the main lender portal loop
 */
void runLenderPortal(LenderManager& manager)
{
    displayLenderHeader();

    if (!manager.loadApplications())
    {
        cout << "Failed to load applications. Exiting." << endl;
        return;
    }

    cout << "Loaded " << manager.getApplicationCount() << " applications." << endl;

    string choice;
    while (true)
    {
        displayLenderMenu();
        getline(cin, choice);
        choice = trim(choice);

        // ✅ Add X/x support for exit
        if (choice == "X" || choice == "x")
        {
            cout << "\nExiting Lender Portal. Goodbye!" << endl;
            break;
        }

        if (choice == "1")
        {
            manager.viewAllApplications();
        }
        else if (choice == "2")
        {
            cout << "\nEnter Application ID: ";
            string appID;
            getline(cin, appID);
            appID = trim(appID);

            int index = manager.searchApplicationByID(appID);
            if (index != -1)
            {
                manager.viewApplicationDetails(index);
            }
            else
            {
                cout << "\nI couldn't find that application. Please check the ID and try again." << endl;
            }
        }
        else if (choice == "3")
        {
            cout << "\nEnter Application ID: ";
            string appID;
            getline(cin, appID);
            appID = trim(appID);

            int index = manager.searchApplicationByID(appID);
            if (index != -1)
            {
                manager.viewApplicationDetails(index);

                cout << "\n1. Approve" << endl;
                cout << "2. Reject" << endl;
                cout << "3. Cancel" << endl;
                cout << "Enter choice: ";

                string action;
                getline(cin, action);
                action = trim(action);

                if (action == "1")
                {
                    if (manager.approveApplication(index))
                    {
                        cout << "\nApplication approved successfully!" << endl;
                    }
                    else
                    {
                        cout << "\nSorry, I couldn't approve the application. Please try again." << endl;
                    }
                }
                else if (action == "2")
                {
                    if (manager.rejectApplication(index))
                    {
                        cout << "\nApplication rejected successfully!" << endl;
                    }
                    else
                    {
                        cout << "\nSorry, I couldn't reject the application. Please try again." << endl;
                    }
                }
                else if (action == "3")
                {
                    cout << "\nOperation canceled." << endl;
                }
                else
                {
                    cout << "\nI didn't understand that. Let's return to the main menu." << endl;
                }
            }
            else
            {
                cout << "\nI couldn't find that application. Please check the ID and try again." << endl;
            }
        }
        else if (choice == "4")
        {
            cout << "\nExiting Lender Portal. Goodbye!" << endl;
            break;
        }
        else
        {
            // ✅ More natural error message
            cout << "\nHmm, that's not a valid option. Please choose 1-4, or press X to exit." << endl;
        }
    }
}