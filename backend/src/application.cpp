#include "../../logs/include/application.h"
#include "../../logs/include/utils.h"
#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;
using std::setw;
using std::left;
using std::string;


// Global application manager instance
ApplicationManager appManager;

// ============================================================================
// APPLICATION CLASS METHODS
// ============================================================================

string Application::toFileFormat() const {
    std::stringstream ss;
    
    ss << applicationID << "#" << status << "#" << fullName << "#" 
       << fathersName << "#" << postalAddress << "#" << contact << "#" 
       << email << "#" << cnic << "#" << cnicExpiry << "#" << employment << "#" 
       << marital << "#" << gender << "#" << dependents << "#" 
       << annualIncome << "#" << avgElectricityBill << "#" << currentElectricityBill << "#";
    
    if (hasExistingLoan) {
        ss << "Yes#" << (existingLoan.isActive ? "Active" : "Inactive") << "#"
           << existingLoan.totalAmount << "#" << existingLoan.amountReturned << "#"
           << existingLoan.amountDue << "#" << existingLoan.bankName << "#"
           << existingLoan.category << "#";
    } else {
        ss << "No#N/A#0#0#0#N/A#N/A#";
    }
    
    ss << referee1.name << "#" << referee1.cnic << "#" << referee1.issueDate << "#"
       << referee1.phone << "#" << referee1.email << "#"
       << referee2.name << "#" << referee2.cnic << "#" << referee2.issueDate << "#"
       << referee2.phone << "#" << referee2.email << "#"
       << cnicFrontPath << "#" << cnicBackPath << "#" << billPath << "#"
       << salaryPath << "#" << selectedLoanType << "#" << selectedLoanDetails << "#"
       << submissionDate;
    
    return ss.str();
}

Application Application::fromFileFormat(const string& line) {
    Application app;
    std::stringstream ss(line);
    string token;
    int field = 0;
    
    while (std::getline(ss, token, '#')) {
        switch(field++) {
            case 0: app.applicationID = token; break;
            case 1: app.status = token; break;
            case 2: app.fullName = token; break;
            case 3: app.fathersName = token; break;
            case 4: app.postalAddress = token; break;
            case 5: app.contact = token; break;
            case 6: app.email = token; break;
            case 7: app.cnic = token; break;
            case 8: app.cnicExpiry = token; break;
            case 9: app.employment = token; break;
            case 10: app.marital = token; break;
            case 11: app.gender = token; break;
            case 12: app.dependents = std::stoi(token); break;
            case 13: app.annualIncome = std::stol(token); break;
            case 14: app.avgElectricityBill = std::stol(token); break;
            case 15: app.currentElectricityBill = std::stol(token); break;
            case 16: app.hasExistingLoan = (token == "Yes"); break;
            case 17: if (app.hasExistingLoan) app.existingLoan.isActive = (token == "Active"); break;
            case 18: if (app.hasExistingLoan) app.existingLoan.totalAmount = std::stol(token); break;
            case 19: if (app.hasExistingLoan) app.existingLoan.amountReturned = std::stol(token); break;
            case 20: if (app.hasExistingLoan) app.existingLoan.amountDue = std::stol(token); break;
            case 21: if (app.hasExistingLoan) app.existingLoan.bankName = token; break;
            case 22: if (app.hasExistingLoan) app.existingLoan.category = token; break;
            case 23: app.referee1.name = token; break;
            case 24: app.referee1.cnic = token; break;
            case 25: app.referee1.issueDate = token; break;
            case 26: app.referee1.phone = token; break;
            case 27: app.referee1.email = token; break;
            case 28: app.referee2.name = token; break;
            case 29: app.referee2.cnic = token; break;
            case 30: app.referee2.issueDate = token; break;
            case 31: app.referee2.phone = token; break;
            case 32: app.referee2.email = token; break;
            case 33: app.cnicFrontPath = token; break;
            case 34: app.cnicBackPath = token; break;
            case 35: app.billPath = token; break;
            case 36: app.salaryPath = token; break;
            case 37: app.selectedLoanType = token; break;
            case 38: app.selectedLoanDetails = token; break;
            case 39: app.submissionDate = token; break;
        }
    }
    
    return app;
}

void Application::displayDetails() const {
    cout << "\n" << string(80, '=') << "\n";
    cout << "\033[1;36mAPPLICATION DETAILS\033[0m\n";
    cout << string(80, '=') << "\n";

    cout << left << setw(25) << "Application ID:" << applicationID << endl;
    cout << left << setw(25) << "Status:" << status << endl;
    cout << left << setw(25) << "Full Name:" << fullName << endl;
    cout << left << setw(25) << "Father's Name:" << fathersName << endl;
    cout << left << setw(25) << "Postal Address:" << postalAddress << endl;
    cout << left << setw(25) << "Contact:" << contact << endl;
    cout << left << setw(25) << "Email:" << email << endl;
    cout << left << setw(25) << "CNIC:" << cnic << endl;
    cout << left << setw(25) << "CNIC Expiry:" << cnicExpiry << endl;
    cout << left << setw(25) << "Employment:" << employment << endl;
    cout << left << setw(25) << "Marital Status:" << marital << endl;
    cout << left << setw(25) << "Gender:" << gender << endl;
    cout << left << setw(25) << "Dependents:" << dependents << endl;
    cout << left << setw(25) << "Annual Income:" << annualIncome << endl;
    cout << left << setw(25) << "Avg Electricity Bill:" << avgElectricityBill << endl;
    cout << left << setw(25) << "Current Electricity Bill:" << currentElectricityBill << endl;

    if (hasExistingLoan) {
        cout << left << setw(25) << "Existing Loan:" << "Yes" << endl;
        cout << left << setw(25) << "Loan Status:" << (existingLoan.isActive ? "Active" : "Inactive") << endl;
        cout << left << setw(25) << "Total Amount:" << existingLoan.totalAmount << endl;
        cout << left << setw(25) << "Amount Returned:" << existingLoan.amountReturned << endl;
        cout << left << setw(25) << "Amount Due:" << existingLoan.amountDue << endl;
        cout << left << setw(25) << "Bank Name:" << existingLoan.bankName << endl;
        cout << left << setw(25) << "Category:" << existingLoan.category << endl;
    } else {
        cout << left << setw(25) << "Existing Loan:" << "No" << endl;
    }

    cout << left << setw(25) << "Referee 1:" << referee1.name << " (" << referee1.cnic << ")" << endl;
    cout << left << setw(25) << "Referee 2:" << referee2.name << " (" << referee2.cnic << ")" << endl;

    cout << left << setw(25) << "CNIC Front Path:" << cnicFrontPath << endl;
    cout << left << setw(25) << "CNIC Back Path:" << cnicBackPath << endl;
    cout << left << setw(25) << "Bill Path:" << billPath << endl;
    cout << left << setw(25) << "Salary Path:" << salaryPath << endl;
    cout << left << setw(25) << "Selected Loan Type:" << selectedLoanType << endl;
    cout << left << setw(25) << "Loan Details:" << selectedLoanDetails << endl;
    cout << left << setw(25) << "Submission Date:" << submissionDate << endl;

    cout << string(80, '=') << "\n";
}


// ============================================================================
// APPLICATION MANAGER CLASS METHODS
// ============================================================================

bool ApplicationManager::loadApplications(const string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;
    
    string line;
    std::getline(file, line);  // Skip header
    
    while (std::getline(file, line)) {
        if (!line.empty() && line.find('#') != string::npos) {
            applications.push_back(Application::fromFileFormat(line));
        }
    }
    
    file.close();
    
    if (!applications.empty()) {
        int maxID = 1000;
        for (const auto& app : applications) {
            int id = std::stoi(app.getApplicationID());
            if (id > maxID) maxID = id;
        }
        nextApplicationID = maxID + 1;
    }
    
    return true;
}

bool ApplicationManager::saveApplication(const Application& app) {
    std::ofstream file("output/applications.txt", std::ios::app);
    if (!file.is_open()) {
        std::ofstream newFile("output/applications.txt");
        if (!newFile.is_open()) return false;
        
        newFile << "ApplicationID#Status#FullName#FathersName#PostalAddress#Contact#Email#"
                << "CNIC#CNICExpiry#Employment#Marital#Gender#Dependents#AnnualIncome#"
                << "AvgElectricityBill#CurrentElectricityBill#HasExistingLoan#LoanActive#"
                << "LoanTotal#LoanReturned#LoanDue#LoanBank#LoanCategory#"
                << "Referee1Name#Referee1CNIC#Referee1IssueDate#Referee1Phone#Referee1Email#"
                << "Referee2Name#Referee2CNIC#Referee2IssueDate#Referee2Phone#Referee2Email#"
                << "CNICFrontPath#CNICBackPath#ElectricityBillPath#SalarySlipPath#"
                << "SelectedLoanType#SelectedLoanDetails#SubmissionDate\n";
        
        newFile << app.toFileFormat() << "\n";
        newFile.close();
    } else {
        file << app.toFileFormat() << "\n";
        file.close();
    }
    
    applications.push_back(app);
    return true;
}

bool ApplicationManager::saveAllApplications(const string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) return false;
    
    file << "ApplicationID#Status#FullName#FathersName#PostalAddress#Contact#Email#"
         << "CNIC#CNICExpiry#Employment#Marital#Gender#Dependents#AnnualIncome#"
         << "AvgElectricityBill#CurrentElectricityBill#HasExistingLoan#LoanActive#"
         << "LoanTotal#LoanReturned#LoanDue#LoanBank#LoanCategory#"
         << "Referee1Name#Referee1CNIC#Referee1IssueDate#Referee1Phone#Referee1Email#"
         << "Referee2Name#Referee2CNIC#Referee2IssueDate#Referee2Phone#Referee2Email#"
         << "CNICFrontPath#CNICBackPath#ElectricityBillPath#SalarySlipPath#"
         << "SelectedLoanType#SelectedLoanDetails#SubmissionDate\n";
    
    for (const auto& app : applications) {
        file << app.toFileFormat() << "\n";
    }
    
    file.close();
    return true;
}

string ApplicationManager::generateApplicationID() {
    return std::to_string(nextApplicationID++);
}

vector<Application> ApplicationManager::getApplicationsByCNIC(const string& cnic) {
    vector<Application> result;
    for (const auto& app : applications) {
        if (app.getCNIC() == cnic) {
            result.push_back(app);
        }
    }
    return result;
}

int ApplicationManager::getCountByStatus(const string& cnic, const string& status) {
    int count = 0;
    for (const auto& app : applications) {
        if (app.getCNIC() == cnic && app.getStatus() == status) {
            count++;
        }
    }
    return count;
}

Application* ApplicationManager::getApplicationByID(const string& appID) {
    for (auto& app : applications) {
        if (app.getApplicationID() == appID) {
            return &app;
        }
    }
    return nullptr;
}

bool ApplicationManager::updateApplicationStatus(const string& appID, const string& newStatus) {
    for (auto& app : applications) {
        if (app.getApplicationID() == appID) {
            app.setStatus(newStatus);
            return saveAllApplications("output/applications.txt");
        }
    }
    return false;
}
