#include <iostream>
#include <iomanip>
#include <string>
#include "../../logs/include/application.h"

using namespace std;

void displayMenu() {
    cout << "\n";
    cout << "\033[1;36m" // Cyan for header border (following the same color scheme as in the Chatbot)
     << "=============================================\n";
    cout << "\033[1;32m" // Green for title
         << "           LENDER DASHBOARD\n";
    cout << "\033[1;36m" // Cyan for closing border
         << "=============================================\n";
    cout << "\033[0m\n"; // Reset colors
    
    cout << "1. View All Applications\n";
    cout << "2. View Application Details\n";
    cout << "3. Approve Application\n";
    cout << "4. Reject Application\n";
    cout << "5. Filter by Status\n";
    cout << "6. Exit\n";
    cout << "\nChoose an option: ";
}

void viewAllApplications() {
    auto apps = appManager.getAllApplications();
    
    if (apps.empty()) {
        cout << "\nNo applications found.\n";
        return;
    }
    
    cout << "\n" << string(100, '=') << "\n";
    cout << left << setw(8) << "App ID" 
         << setw(25) << "Name" 
         << setw(15) << "CNIC"
         << setw(15) << "Loan Type"
         << setw(12) << "Status"
         << setw(12) << "Date" << "\n";
    cout << string(100, '-') << "\n";
    
    for (const auto& app : apps) {
        cout << left << setw(8) << app.getApplicationID()
             << setw(25) << app.getFullName()
             << setw(15) << app.getCNIC()
             << setw(15) << app.getLoanType()
             << setw(12) << app.getStatus()
             << setw(12) << app.getSubmissionDate() << "\n";
    }
    
    cout << string(100, '=') << "\n";
    cout << "Total Applications: " << apps.size() << "\n";
}

void viewApplicationDetails() {
    string appID;
    cout << "\nEnter Application ID: ";
    getline(cin, appID);
    
    Application* app = appManager.getApplicationByID(appID);
    
    if (app) {
        app->displayDetails();
    } else {
        cout << "\nApplication not found.\n";
    }
}

void approveApplication() {
    string appID;
    cout << "\nEnter Application ID to approve: ";
    getline(cin, appID);
    
    Application* app = appManager.getApplicationByID(appID);
    
    if (!app) {
        cout << "\nApplication not found.\n";
        return;
    }
    
    cout << "\nApplication Preview:\n";
    cout << "Applicant:      " << app->getFullName() << "\n";
    cout << "CNIC:           " << app->getCNIC() << "\n";
    cout << "Current Status: " << app->getStatus() << "\n";
    
    cout << "\nConfirm approval? (Y/N): ";
    string confirm;
    getline(cin, confirm);
    
    if (toupper(confirm[0]) == 'Y') {
        if (appManager.updateApplicationStatus(appID, "Approved")) {
            cout << "\nSUCCESS! Application #" << appID << " has been APPROVED.\n";
        } else {
            cout << "\nError updating status.\n";
        }
    } else {
        cout << "\nAction cancelled.\n";
    }
}

void rejectApplication() {
    string appID;
    cout << "\nEnter Application ID to reject: ";
    getline(cin, appID);
    
    Application* app = appManager.getApplicationByID(appID);
    
    if (!app) {
        cout << "\nApplication not found.\n";
        return;
    }
    
    cout << "\nApplication Preview:\n";
    cout << "Applicant:      " << app->getFullName() << "\n";
    cout << "CNIC:           " << app->getCNIC() << "\n";
    cout << "Current Status: " << app->getStatus() << "\n";
    
    cout << "\nConfirm rejection? (Y/N): ";
    string confirm;
    getline(cin, confirm);
    
    if (toupper(confirm[0]) == 'Y') {
        if (appManager.updateApplicationStatus(appID, "Rejected")) {
            cout << "\nSUCCESS! Application #" << appID << " has been REJECTED.\n";
        } else {
            cout << "\nError updating status.\n";
        }
    } else {
        cout << "\nAction cancelled.\n";
    }
}

void filterByStatus() {
    cout << "\nFilter by status:\n";
    cout << "1. Submitted\n";
    cout << "2. Approved\n";
    cout << "3. Rejected\n";
    cout << "Choose (1-3): ";
    
    string choice;
    getline(cin, choice);
    
    string status[] = {"Submitted", "Approved", "Rejected"};
    int idx = stoi(choice) - 1;
    
    if (idx < 0 || idx > 2) {
        cout << "\nInvalid choice.\n";
        return;
    }
    
    string selectedStatus = status[idx];
    auto apps = appManager.getAllApplications();
    int count = 0;
    
    cout << "\n" << string(100, '=') << "\n";
    cout << "APPLICATIONS WITH STATUS: " << selectedStatus << "\n";
    cout << string(100, '=') << "\n";
    
    cout << left << setw(8) << "App ID" 
         << setw(25) << "Name" 
         << setw(15) << "CNIC"
         << setw(15) << "Loan Type"
         << setw(12) << "Date" << "\n";
    cout << string(100, '-') << "\n";
    
    for (const auto& app : apps) {
        if (app.getStatus() == selectedStatus) {
            cout << left << setw(8) << app.getApplicationID()
                 << setw(25) << app.getFullName()
                 << setw(15) << app.getCNIC()
                 << setw(15) << app.getLoanType()
                 << setw(12) << app.getSubmissionDate() << "\n";
            count++;
        }
    }
    
    cout << string(100, '=') << "\n";
    cout << "Total: " << count << " applications\n";
}

int main() {
    if (!appManager.loadApplications("output/applications.txt")) {
        cout << "\nWarning: Could not load applications file.\n";
        cout << "File may not exist yet or is empty.\n";
    }
    
    string input;
    bool running = true;
    
    while (running) {
        displayMenu();
        getline(cin, input);
        
        if (input == "1") {
            viewAllApplications();
        } 
        else if (input == "2") {
            viewApplicationDetails();
        } 
        else if (input == "3") {
            approveApplication();
        } 
        else if (input == "4") {
            rejectApplication();
        } 
        else if (input == "5") {
            filterByStatus();
        } 
        else if (input == "6") {
            cout << "\nExiting lender dashboard. Goodbye!\n";
            running = false;
        } 
        else {
            cout << "\nInvalid option. Please try again.\n";
        }
    }
    
    return 0;
}
