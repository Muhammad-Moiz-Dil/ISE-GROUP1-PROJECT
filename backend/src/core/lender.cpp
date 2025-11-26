#include "core/lender.h"
#include "helpers/utils.h"
#include "helpers/ui_display.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::getline;
using std::setw;
using std::left;

// ==================== LENDER MANAGER IMPLEMENTATION ====================

LenderManager::LenderManager(const string& filePath)
    : applicationsFilePath(filePath)
{
}

bool LenderManager::loadApplications()
{
    ifstream file(applicationsFilePath);
    if (!file.is_open())
    {
        printError("Could not open applications file: " + applicationsFilePath);
        return false;
    }

    applications.clear();
    string line;

    // Skip header line
    getline(file, line);

    // Parse each application
    while (getline(file, line))
    {
        if (line.empty()) continue;
        applications.push_back(Application::fromFileFormat(line));
    }

    file.close();
    return true;
}

bool LenderManager::saveApplications()
{
    ofstream file(applicationsFilePath);
    if (!file.is_open())
    {
        printError("Could not save applications to file.");
        return false;
    }

    // Write header
    file << "ApplicationID#Status#FullName#FathersName#PostalAddress#Contact#Email#"
         << "CNIC#CNICExpiry#Employment#Marital#Gender#Dependents#AnnualIncome#"
         << "AvgElectricityBill#CurrentElectricityBill#HasExistingLoan#LoanActive#"
         << "LoanTotal#LoanReturned#LoanDue#LoanBank#LoanCategory#"
         << "Referee1Name#Referee1CNIC#Referee1IssueDate#Referee1Phone#Referee1Email#"
         << "Referee2Name#Referee2CNIC#Referee2IssueDate#Referee2Phone#Referee2Email#"
         << "CNICFrontPath#CNICBackPath#ElectricityBillPath#SalarySlipPath#"
         << "SelectedLoanType#SelectedLoanDetails#SubmissionDate#Checkpoint\n";

    // Write all applications
    for (const auto& app : applications)
    {
        file << app.toFileFormat() << endl;
    }

    file.flush();
    file.close();
    return true;
}

void LenderManager::displayAllApplications() const
{
    if (applications.empty())
    {
        printWarning("No applications found.");
        return;
    }

    // Header
    cout << "\n" << COLOR_CYAN << string(80, '=') << COLOR_RESET << endl;
    cout << COLOR_CYAN << "                    ALL LOAN APPLICATIONS" << COLOR_RESET << endl;
    cout << COLOR_CYAN << string(80, '=') << COLOR_RESET << endl;

    // Table header
    cout << left << setw(8) << "ID" 
         << setw(25) << "Name" 
         << setw(15) << "Loan Type" 
         << setw(15) << "Status" 
         << setw(15) << "Date" << endl;
    cout << string(80, '-') << endl;

    // Table rows
    for (const auto& app : applications)
    {
        if (app.getStatus() == "Submitted")
        {
            cout << left << setw(8) << app.getApplicationID()
                 << setw(25) << app.getFullName()
                 << setw(15) << app.getLoanType()
                 << setw(15) << app.getStatus()
                 << setw(15) << app.getSubmissionDate() << endl;
        }
    }

    // Footer
    cout << COLOR_CYAN << string(80, '=') << COLOR_RESET << endl;
    cout << "Total Applications: " << applications.size() << endl;
}

int LenderManager::findApplicationByID(const string& appID) const
{
    for (size_t i = 0; i < applications.size(); i++)
    {
        if (applications[i].getApplicationID() == appID && applications[i].getStatus() == "Submitted")
        {
            return static_cast<int>(i);
        }
    }
    return -1; // if not found
}

void LenderManager::displayApplicationDetails(int index) const
{
    if (index < 0 || index >= static_cast<int>(applications.size()))
    {
        printError("Invalid application index.");
        return;
    }

    const Application& app = applications[index];

    // Header
    cout << "\n" << COLOR_CYAN << string(80, '=') << COLOR_RESET << endl;
    cout << COLOR_CYAN << "                 APPLICATION DETAILS" << COLOR_RESET << endl;
    cout << COLOR_CYAN << string(80, '=') << COLOR_RESET << endl;

    // Metadata
    cout << "\n" << COLOR_YELLOW << "METADATA:" << COLOR_RESET << endl;
    cout << "  Application ID: " << app.getApplicationID() << endl;
    cout << "  Status: " << app.getStatus() << endl;
    cout << "  Submission Date: " << app.getSubmissionDate() << endl;

    // Personal Information
    cout << "\n" << COLOR_YELLOW << "PERSONAL INFORMATION:" << COLOR_RESET << endl;
    cout << "  Full Name: " << app.getFullName() << endl;
    cout << "  Father's Name: " << app.getFathersName() << endl;
    cout << "  CNIC: " << app.getCNIC() << endl;
    cout << "  Contact: " << app.getContact() << endl;
    cout << "  Email: " << app.getEmail() << endl;
    cout << "  Address: " << app.getPostalAddress() << endl;

    // Financial Information
    cout << "\n" << COLOR_YELLOW << "FINANCIAL INFORMATION:" << COLOR_RESET << endl;
    cout << "  Employment: " << app.getEmployment() << endl;
    cout << "  Annual Income: " << app.getAnnualIncome() << " PKR" << endl;
    cout << "  Dependents: " << app.getDependents() << endl;
    cout << "  Avg. Electricity Bill: " << app.getAvgElectricityBill() << " PKR" << endl;
    cout << "  Current Bill: " << app.getCurrentElectricityBill() << " PKR" << endl;

    // Documents
    cout << "\n" << COLOR_YELLOW << "DOCUMENTS:" << COLOR_RESET << endl;
    cout << "  CNIC Front: " << app.getCNICFrontPath() << endl;
    cout << "  CNIC Back: " << app.getCNICBackPath() << endl;
    cout << "  Electricity Bill: " << app.getBillPath() << endl;
    cout << "  Salary Slip: " << app.getSalaryPath() << endl;

    // Loan Details
    cout << "\n" << COLOR_YELLOW << "LOAN DETAILS:" << COLOR_RESET << endl;
    cout << "  Loan Type: " << app.getLoanType() << endl;
    cout << "  Loan Area/Make: " << app.getLoanArea() << endl;

    cout << COLOR_CYAN << string(80, '=') << COLOR_RESET << endl;
}

bool LenderManager::updateApplicationStatus(int index, const string& newStatus)
{
    if (index < 0 || index >= static_cast<int>(applications.size()))
    {
        return false;
    }

    applications[index].setStatus(newStatus);
    return saveApplications();
}

int LenderManager::getApplicationCount() const
{
    return static_cast<int>(applications.size());
}

// ==================== LENDER PORTAL INTERFACE ====================

void displayLenderHeader()
{
    cout << "\n" << COLOR_GREEN << string(80, '=') << COLOR_RESET << endl;
    cout << COLOR_GREEN << "              LENDER PORTAL - LOAN MANAGEMENT" << COLOR_RESET << endl;
    cout << COLOR_GREEN << string(80, '=') << COLOR_RESET << endl;
}

void displayLenderMenu()
{
    cout << "\n" << COLOR_CYAN << "MAIN MENU:" << COLOR_RESET << endl;
    cout << "  1. View All Applications" << endl;
    cout << "  2. Search Application by ID" << endl;
    cout << "  3. Approve/Reject Application" << endl;
    cout << "  4. Exit" << endl;
    cout << "\nEnter your choice (1-4 or X to exit): ";

    if (!appManager.loadApplications("output/applications.txt")) 
    {
        printError("Failed to refresh data.");
    }
}

void handleViewAllApplications(LenderManager& manager)
{
    manager.displayAllApplications();
}

void handleSearchApplication(LenderManager& manager)
{
    cout << "\nEnter Application ID: ";
    string appID;
    getline(cin, appID);
    appID = trim(appID);

    int index = manager.findApplicationByID(appID);
    if (index != -1)
    {
        manager.displayApplicationDetails(index);
    }
    else
    {
        printError("Application not found. Please check the ID and try again.");
    }
}

void handleApproveReject(LenderManager& manager)
{
    cout << "\nEnter Application ID: ";
    string appID;
    getline(cin, appID);
    appID = trim(appID);

    int index = manager.findApplicationByID(appID);
    if (index == -1)
    {
        printError("Application not found. Please check the ID and try again.");
        return;
    }

    // Display application details
    manager.displayApplicationDetails(index);

    // Show action menu
    cout << "\n" << COLOR_YELLOW << "ACTION MENU:" << COLOR_RESET << endl;
    cout << "  1. Approve" << endl;
    cout << "  2. Reject" << endl;
    cout << "  3. Cancel" << endl;
    cout << "Enter choice (1-3): ";

    string action;
    getline(cin, action);
    action = trim(action);

    if (action == "1")
    {
        if (manager.updateApplicationStatus(index, "Approved"))
        {
            printSuccess("Application approved successfully!");
        }
        else
        {
            printError("Failed to approve application. Please try again.");
        }
    }
    else if (action == "2")
    {
        if (manager.updateApplicationStatus(index, "Rejected"))
        {
            printSuccess("Application rejected successfully!");
        }
        else
        {
            printError("Failed to reject application. Please try again.");
        }
    }
    else if (action == "3")
    {
        printInfo("Operation canceled.");
    }
    else
    {
        printWarning("Invalid choice. Operation canceled.");
    }
}

void runLenderPortal(LenderManager& manager)
{
    displayLenderHeader();

    // Initial Load
    if (!manager.loadApplications())
    {
        printError("Failed to load applications. Exiting.");
        return;
    }

    printSuccess("Loaded " + std::to_string(manager.getApplicationCount()) + " applications.");

    // Main menu loop
    string choice;
    while (true)
    {
        if (!manager.loadApplications()) {
            printError("Failed to load applications. Exiting.");
            return;
        }

        displayLenderMenu(); // Just print the menu options
        
        getline(cin, choice);
        choice = trim(choice);

        // Exit commands
        if (choice == "X" || choice == "x" || choice == "4")
        {
            cout << "\n" << COLOR_GREEN << "Exiting Lender Portal. Goodbye!" << COLOR_RESET << endl;
            break;
        }

        // Route to handlers
        if (choice == "1")
        {
            handleViewAllApplications(manager);
        }
        else if (choice == "2")
        {
            handleSearchApplication(manager);
        }
        else if (choice == "3")
        {
            handleApproveReject(manager);
        }
        else
        {
            printError("Invalid option. Please choose 1-4, or press X to exit.");
        }
    }
}