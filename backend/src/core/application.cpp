#include "core/application.h"
#include "helpers/utils.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

using std::cout;
using std::endl;
using std::left;
using std::setw;
using std::string;
using std::vector;

// Global application manager instance
ApplicationManager appManager;

// ============================================================================
// HELPER FUNCTIONS (Private to this file)
// ============================================================================

namespace {
    /**
     * @brief Helper to get next token from stringstream
     */
    string getNextToken(std::stringstream& ss) {
        string token;
        std::getline(ss, token, '#');
        return token;
    }

    /**
     * @brief Displays a field in formatted manner
     */
    void displayField(const string& label, const string& value) {
        cout << left << setw(25) << label << value << endl;
    }

    void displayField(const string& label, long value) {
        cout << left << setw(25) << label << value << endl;
    }

    void displayField(const string& label, int value) {
        cout << left << setw(25) << label << value << endl;
    }
}

// ============================================================================
// APPLICATION CLASS METHODS
// ============================================================================

string Application::toFileFormat() const {
    std::stringstream ss;

    // Personal Information
    ss << applicationID << "#" << status << "#" << fullName << "#" 
      << fathersName << "#" << postalAddress << "#" << contact << "#" 
      << email << "#" << cnic << "#" << cnicExpiry << "#" << employment << "#" 
      << marital << "#" << gender << "#";

    // Financial Information
    ss << dependents << "#" << annualIncome << "#" << avgElectricityBill << "#" 
      << currentElectricityBill << "#";

    // Existing Loan Information
    if (hasExistingLoan) {
        ss << "Yes#" << (existingLoan.isActive ? "Active" : "Inactive") << "#"
          << existingLoan.totalAmount << "#" << existingLoan.amountReturned << "#"
          << existingLoan.amountDue << "#" << existingLoan.bankName << "#"
          << existingLoan.category << "#";
    } else {
        ss << "No#N/A#0#0#0#N/A#N/A#";
    }

    // Referee Information
    ss << referee1.name << "#" << referee1.cnic << "#" << referee1.issueDate << "#"
      << referee1.phone << "#" << referee1.email << "#"
      << referee2.name << "#" << referee2.cnic << "#" << referee2.issueDate << "#"
      << referee2.phone << "#" << referee2.email << "#";

    // Document Paths
    ss << cnicFrontPath << "#" << cnicBackPath << "#" << billPath << "#" 
      << salaryPath << "#";

    // Loan Selection & Metadata
    ss << selectedLoanType << "#" << selectedLoanDetails << "#" 
      << submissionDate << "#" << checkpoint;

    return ss.str();
}

Application Application::fromFileFormat(const string &line) {
    Application app;
    std::stringstream ss(line);
    
    // Personal Information (12 fields)
    app.applicationID = getNextToken(ss);
    app.status = getNextToken(ss);
    app.fullName = getNextToken(ss);
    app.fathersName = getNextToken(ss);
    app.postalAddress = getNextToken(ss);
    app.contact = getNextToken(ss);
    app.email = getNextToken(ss);
    app.cnic = getNextToken(ss);
    app.cnicExpiry = getNextToken(ss);
    app.employment = getNextToken(ss);
    app.marital = getNextToken(ss);
    app.gender = getNextToken(ss);

    // Financial Information (4 fields)
    app.dependents = std::stoi(getNextToken(ss));
    app.annualIncome = std::stol(getNextToken(ss));
    app.avgElectricityBill = std::stol(getNextToken(ss));
    app.currentElectricityBill = std::stol(getNextToken(ss));

    // Existing Loan (7 fields)
    string hasLoan = getNextToken(ss);
    app.hasExistingLoan = (hasLoan == "Yes");
    
    if (app.hasExistingLoan) {
        app.existingLoan.isActive = (getNextToken(ss) == "Active");
        app.existingLoan.totalAmount = std::stol(getNextToken(ss));
        app.existingLoan.amountReturned = std::stol(getNextToken(ss));
        app.existingLoan.amountDue = std::stol(getNextToken(ss));
        app.existingLoan.bankName = getNextToken(ss);
        app.existingLoan.category = getNextToken(ss);
    } else {
        // Skip placeholder fields
        for (int i = 0; i < 6; i++) getNextToken(ss);
    }

    // Referee Information (10 fields)
    app.referee1.name = getNextToken(ss);
    app.referee1.cnic = getNextToken(ss);
    app.referee1.issueDate = getNextToken(ss);
    app.referee1.phone = getNextToken(ss);
    app.referee1.email = getNextToken(ss);

    app.referee2.name = getNextToken(ss);
    app.referee2.cnic = getNextToken(ss);
    app.referee2.issueDate = getNextToken(ss);
    app.referee2.phone = getNextToken(ss);
    app.referee2.email = getNextToken(ss);

    // Document Paths (4 fields)
    app.cnicFrontPath = getNextToken(ss);
    app.cnicBackPath = getNextToken(ss);
    app.billPath = getNextToken(ss);
    app.salaryPath = getNextToken(ss);

    // Loan Selection & Metadata (3 fields)
    app.selectedLoanType = getNextToken(ss);
    app.selectedLoanDetails = getNextToken(ss);
    app.submissionDate = getNextToken(ss);
    app.checkpoint = std::stoi(getNextToken(ss));

    return app;
}

void Application::displayDetails() const {
    cout << "\n" << COLOR_CYAN << string(80, '=') << COLOR_RESET << "\n";
    cout << COLOR_CYAN << "APPLICATION DETAILS" << COLOR_RESET << "\n";
    cout << COLOR_CYAN << string(80, '=') << COLOR_RESET << "\n\n";

    // Personal Information
    cout << COLOR_YELLOW << "PERSONAL INFORMATION:" << COLOR_RESET << "\n";
    displayField("Application ID:", applicationID);
    displayField("Status:", status);
    displayField("Full Name:", fullName);
    displayField("Father's Name:", fathersName);
    displayField("Postal Address:", postalAddress);
    displayField("Contact:", contact);
    displayField("Email:", email);
    displayField("CNIC:", cnic);
    displayField("CNIC Expiry:", cnicExpiry);
    displayField("Employment:", employment);
    displayField("Marital Status:", marital);
    displayField("Gender:", gender);

    // Financial Information
    cout << "\n" << COLOR_YELLOW << "FINANCIAL INFORMATION:" << COLOR_RESET << "\n";
    displayField("Dependents:", dependents);
    displayField("Annual Income:", annualIncome);
    displayField("Avg Electricity Bill:", avgElectricityBill);
    displayField("Current Bill:", currentElectricityBill);

    // Existing Loan
    cout << "\n" << COLOR_YELLOW << "EXISTING LOAN:" << COLOR_RESET << "\n";
    if (hasExistingLoan) {
        displayField("Has Loan:", "Yes");
        displayField("Loan Status:", existingLoan.isActive ? "Active" : "Inactive");
        displayField("Total Amount:", existingLoan.totalAmount);
        displayField("Amount Returned:", existingLoan.amountReturned);
        displayField("Amount Due:", existingLoan.amountDue);
        displayField("Bank Name:", existingLoan.bankName);
        displayField("Category:", existingLoan.category);
    } else {
        displayField("Has Loan:", "No");
    }

    // References
    cout << "\n" << COLOR_YELLOW << "REFERENCES:" << COLOR_RESET << "\n";
    displayField("Referee 1:", referee1.name + " (" + referee1.cnic + ")");
    displayField("Referee 2:", referee2.name + " (" + referee2.cnic + ")");

    // Documents
    cout << "\n" << COLOR_YELLOW << "DOCUMENTS:" << COLOR_RESET << "\n";
    displayField("CNIC Front:", cnicFrontPath);
    displayField("CNIC Back:", cnicBackPath);
    displayField("Electricity Bill:", billPath);
    displayField("Salary Slip:", salaryPath);

    // Loan Selection
    cout << "\n" << COLOR_YELLOW << "LOAN DETAILS:" << COLOR_RESET << "\n";
    displayField("Loan Type:", selectedLoanType);
    displayField("Loan Details:", selectedLoanDetails);
    displayField("Submission Date:", submissionDate);

    cout << COLOR_CYAN << string(80, '=') << COLOR_RESET << "\n";
}

// ============================================================================
// APPLICATION MANAGER CLASS METHODS
// ============================================================================

bool ApplicationManager::loadApplications(const string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    string line;
    std::getline(file, line); // Skip header

    while (std::getline(file, line)) {
        if (!line.empty() && line.find('#') != string::npos) {
            applications.push_back(Application::fromFileFormat(line));
        }
    }

    file.close();

    // Update next ID based on existing applications
    if (!applications.empty()) {
        int maxID = 1000;
        for (const auto &app : applications) {
            int id = std::stoi(app.getApplicationID());
            if (id > maxID) maxID = id;
        }
        nextApplicationID = maxID + 1;
    }

    return true;
}

bool ApplicationManager::saveApplication(const Application &app) {
    // Update existing or add new
    bool found = false;
    for (auto &existingApp : applications) {
        if (existingApp.getApplicationID() == app.getApplicationID()) {
            existingApp = app;
            found = true;
            break;
        }
    }

    if (!found) {
        applications.push_back(app);
    }

    return saveAllApplications("output/applications.txt");
}

bool ApplicationManager::saveAllApplications(const string &filename) {
    std::ofstream file(filename);
    if (!file.is_open()) return false;

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
    for (const auto &app : applications) {
        file << app.toFileFormat() << "\n";
    }

    file.close();
    return true;
}

string ApplicationManager::generateApplicationID() {
    return std::to_string(nextApplicationID++);
}

vector<Application> ApplicationManager::getApplicationsByCNIC(const string &cnic) {
    vector<Application> result;
    for (const auto &app : applications) {
        if (app.getCNIC() == cnic) {
            result.push_back(app);
        }
    }
    return result;
}

int ApplicationManager::getCountByStatus(const string &cnic, const string &status) {
    int count = 0;
    for (const auto &app : applications) {
        if (app.getCNIC() == cnic && app.getStatus() == status) {
            count++;
        }
    }
    return count;
}

Application *ApplicationManager::getApplicationByID(const string &appID) {
    for (auto &app : applications) {
        if (app.getApplicationID() == appID) {
            return &app;
        }
    }
    return nullptr;
}

bool ApplicationManager::updateApplicationStatus(const string &appID, const string &newStatus) {
    for (auto &app : applications) {
        if (app.getApplicationID() == appID) {
            app.setStatus(newStatus);
            return saveAllApplications("output/applications.txt");
        }
    }
    return false;
}