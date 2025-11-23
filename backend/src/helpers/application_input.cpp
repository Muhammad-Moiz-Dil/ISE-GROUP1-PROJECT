#include "helpers/application_input.h"
#include "helpers/error_handling.h"
#include "helpers/utils.h"
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::stoi;
using std::stol;
using std::string;
using std::toupper;

// ==================== GENERIC INPUT HELPER ====================

/**
 * @brief Generic function to collect and validate user input with X-to-exit support
 * @param prompt: Text to display to user
 * @param validator: Validation function pointer (returns true if valid)
 * @param errorMsg: Error message to show on invalid input
 * @param state: Reference to state (for X handling)
 * @param output: Reference to store the validated input
 * @return true if input collected successfully, false if user pressed X
 */
bool getValidatedInput(const string& prompt,  bool (*validator)(const string&),  const string& errorMsg, string& state, string& output)
{
    string input;
    while (true)
    {
        cout << prompt;
        getline(cin, input);
        input = trim(input);
        
        if (input == "X" || input == "x")
        {
            state = "MAIN_MENU";
            return false;
        }
        
        if (validator(input))
        {
            output = input;
            return true;
        }
        
        printError(errorMsg);
    }
}


// ==================== PERSONAL INFORMATION COLLECTION ====================

bool collectPersonalInformation(Application &app, string &state)
{
    printSectionHeader("PERSONAL INFORMATION");
    
    string input;
    
    // Full Name
    if (!getValidatedInput("Full Name: ", isValidName, "Invalid name format.", state, input))
        return false;
    app.setFullName(input);
    
    // Father's Name
    if (!getValidatedInput("Father's Name: ", isValidName, "Invalid name format.", state, input))
        return false;
    app.setFathersName(input);
    
    // Postal Address
    cout << "Postal Address: ";
    getline(cin, input);
    input = trim(input);
    if (input == "X" || input == "x") {
        state = "MAIN_MENU";
        return false;
    }
    app.setPostalAddress(input);
    
    // Contact
    if (!getValidatedInput("Contact Number (03xxxxxxxxx): ", isValidContact, "Invalid contact number.", state, input))
        return false;
    app.setContact(input);
    
    // Email
    if (!getValidatedInput("Email Address: ", isValidEmail, "Invalid email format.", state, input))
        return false;
    app.setEmail(toLower(input));
    
    // CNIC
    if (!getValidatedInput("CNIC (13 digits, no dashes): ", isValidCNIC, "Invalid CNIC.", state, input))
        return false;
    app.setCNIC(input);
    
    // CNIC Expiry
    if (!getValidatedInput("CNIC Expiry Date (DD-MM-YYYY): ", isValidDate, "Invalid date format.", state, input))
        return false;
    app.setCNICExpiry(input);
    
    // Employment - WITH VALIDATION LOOP
    string employment[] = {"Self-employed", "Salaried", "Retired", "Unemployed"};
    while (true)
    {
        cout << "\nEmployment Status:\n1. Self-employed\n2. Salaried\n3. Retired\n4. Unemployed\nChoose (1-4): ";
        getline(cin, input);
        input = trim(input);
        
        if (input == "X" || input == "x") {
            state = "MAIN_MENU";
            return false;
        }
        
        if (isValidMenuChoice(input, 1, 4)) {
            app.setEmployment(employment[stoi(input) - 1]);
            break;
        }
        
        printError("Invalid choice. Please enter a number between 1 and 4.");
    }
    
    // Marital
    string marital[] = {"Single", "Married", "Divorced", "Widowed"};
    while (true)
    {
        cout << "\nMarital Status:\n1. Single\n2. Married\n3. Divorced\n4. Widowed\nChoose (1-4): ";
        getline(cin, input);
        input = trim(input);
        
        if (input == "X" || input == "x") {
            state = "MAIN_MENU";
            return false;
        }
        
        if (isValidMenuChoice(input, 1, 4)) {
            app.setMarital(marital[stoi(input) - 1]);
            break;
        }
        
        printError("Invalid choice. Please enter a number between 1 and 4.");
    }
    
    // Gender
    string gender[] = {"Male", "Female", "Other"};
    while (true)
    {
        cout << "\nGender:\n1. Male\n2. Female\n3. Other\nChoose (1-3): ";
        getline(cin, input);
        input = trim(input);
        
        if (input == "X" || input == "x") {
            state = "MAIN_MENU";
            return false;
        }
        
        if (isValidMenuChoice(input, 1, 3)) {
            app.setGender(gender[stoi(input) - 1]);
            break;
        }
        
        printError("Invalid choice. Please enter a number between 1 and 3.");
    }
    
    return true;
}

// ==================== FINANCIAL INFORMATION COLLECTION ====================

bool collectFinancialInformation(Application &app, string &state)
{
    printSectionHeader("FINANCIAL INFORMATION");
    
    string input;
    
    // Dependents (0-20 reasonable range)
    while (true)
    {
        cout << "Number of Dependents (0-20): ";
        getline(cin, input);
        input = trim(input);
        
        if (input == "X" || input == "x") {
            state = "MAIN_MENU";
            return false;
        }
        
        if (isValidIntegerInRange(input, 0, 20)) {
            app.setDependents(stoi(input));
            break;
        }
        
        printError("Invalid number. Please enter a value between 0 and 20.");
    }
    
    // Annual Income (minimum 100,000 PKR)
    while (true)
    {
        cout << "Annual Income (PKR, minimum 100,000): ";
        getline(cin, input);
        input = trim(input);
        
        if (input == "X" || input == "x") {
            state = "MAIN_MENU";
            return false;
        }
        
        if (isValidReasonableAmount(input)) {
            long income = stol(input);
            if (income >= 100000) {
                app.setAnnualIncome(income);
                break;
            }
        }
        
        printError("Invalid amount. Please enter at least 100,000 PKR.");
    }
    
    // Average Monthly Electricity Bill (0-100,000 PKR)
    while (true)
    {
        cout << "Average Monthly Electricity Bill (PKR, 0-100,000): ";
        getline(cin, input);
        input = trim(input);
        
        if (input == "X" || input == "x") {
            state = "MAIN_MENU";
            return false;
        }
        
        if (isValidIntegerInRange(input, 0, 100000)) {
            app.setAvgElectricityBill(stol(input));
            break;
        }
        
        printError("Invalid amount. Please enter between 0 and 100,000 PKR.");
    }
    
    // Current Electricity Bill (0-100,000 PKR)
    while (true)
    {
        cout << "Current Electricity Bill (PKR, 0-100,000): ";
        getline(cin, input);
        input = trim(input);
        
        if (input == "X" || input == "x") {
            state = "MAIN_MENU";
            return false;
        }
        
        if (isValidIntegerInRange(input, 0, 100000)) {
            app.setCurrentElectricityBill(stol(input));
            break;
        }
        
        printError("Invalid amount. Please enter between 0 and 100,000 PKR.");
    }
    
    // Existing Loan
    cout << "\nDo you have any existing loans? (Y/N): ";
    getline(cin, input);
    input = trim(input);
    if (input == "X" || input == "x") {
        state = "MAIN_MENU";
        return false;
    }
    
    if (toupper(input[0]) == 'Y')
    {
        ExistingLoan loan;
        
        // Active?
        cout << "Is the loan active? (Y/N): ";
        getline(cin, input);
        if (input == "X" || input == "x") {
            state = "MAIN_MENU";
            return false;
        }
        loan.isActive = (toupper(input[0]) == 'Y');
        
        // Total Loan Amount (with reasonable limit)
        while (true)
        {
            cout << "Total Loan Amount (PKR): ";
            getline(cin, input);
            input = trim(input);
            
            if (input == "X" || input == "x") {
                state = "MAIN_MENU";
                return false;
            }
            
            if (isValidReasonableAmount(input)) {
                loan.totalAmount = stol(input);
                break;
            }
            
            printError("Invalid amount. Please enter a valid amount.");
        }
        
        // Amount Returned
        while (true)
        {
            cout << "Amount Returned (PKR): ";
            getline(cin, input);
            input = trim(input);
            
            if (input == "X" || input == "x") {
                state = "MAIN_MENU";
                return false;
            }
            
            if (isValidReasonableAmount(input)) {
                long returned = stol(input);
                if (returned <= loan.totalAmount) {
                    loan.amountReturned = returned;
                    break;
                }
                printError("Amount returned cannot exceed total loan amount.");
            } else {
                printError("Invalid amount. Please enter a valid amount.");
            }
        }
        
        // Amount Due
        while (true)
        {
            cout << "Amount Due (PKR): ";
            getline(cin, input);
            input = trim(input);
            
            if (input == "X" || input == "x") {
                state = "MAIN_MENU";
                return false;
            }
            
            if (isValidReasonableAmount(input)) {
                long due = stol(input);
                // Verify: totalAmount - returned should equal due
                long expectedDue = loan.totalAmount - loan.amountReturned;
                if (due == expectedDue) {
                    loan.amountDue = due;
                    break;
                }
                printError("Amount due should equal Total - Returned = " + std::to_string(expectedDue) + " PKR");
            } else {
                printError("Invalid amount. Please enter a valid amount.");
            }
        }
        
        // Bank Name
        while (true)
        {
            cout << "Bank Name: ";
            getline(cin, input);
            input = trim(input);
            
            if (input == "X" || input == "x") {
                state = "MAIN_MENU";
                return false;
            }
            
            if (!input.empty()) {
                loan.bankName = input;
                break;
            }
            
            printError("Bank name cannot be empty.");
        }
        
        // Category
        while (true)
        {
            cout << "Category (Car/Home/Bike/Personal): ";
            getline(cin, input);
            input = trim(input);
            
            if (input == "X" || input == "x") {
                state = "MAIN_MENU";
                return false;
            }
            
            string lowerCategory = toLower(input);
            if (lowerCategory == "car" || lowerCategory == "home" || lowerCategory == "bike" || lowerCategory == "personal") {
                loan.category = input;
                break;
            }
            
            printError("Invalid category. Please enter Car, Home, or Bike.");
        }
        
        app.setExistingLoan(loan);
    }
    
    return true;
}

// ==================== REFERENCE INFORMATION COLLECTION ====================

bool collectReferenceInformation(Application &app, string &state)
{
    printSectionHeader("REFERENCE INFORMATION");
    
    string input;
    Referee ref1, ref2;
    
    // Referee 1
    cout << "REFEREE 1:\n";
    if (!getValidatedInput("Name: ", isValidName, "Invalid name.", state, input))
        return false;
    ref1.name = input;
    
    if (!getValidatedInput("CNIC: ", isValidCNIC, "Invalid CNIC.", state, input))
        return false;
    ref1.cnic = input;
    
    if (!getValidatedInput("Issue Date (DD-MM-YYYY): ", isValidDate, "Invalid date.", state, input))
        return false;
    ref1.issueDate = input;
    
    if (!getValidatedInput("Phone: ", isValidContact, "Invalid phone.", state, input))
        return false;
    ref1.phone = input;
    
    if (!getValidatedInput("Email: ", isValidEmail, "Invalid email.", state, input))
        return false;
    ref1.email = input;
    
    app.setReferee1(ref1);
    
    // Referee 2
    cout << "\nREFEREE 2:\n";
    if (!getValidatedInput("Name: ", isValidName, "Invalid name.", state, input))
        return false;
    ref2.name = input;
    
    if (!getValidatedInput("CNIC: ", isValidCNIC, "Invalid CNIC.", state, input))
        return false;
    ref2.cnic = input;
    
    if (!getValidatedInput("Issue Date (DD-MM-YYYY): ", isValidDate, "Invalid date.", state, input))
        return false;
    ref2.issueDate = input;
    
    if (!getValidatedInput("Phone: ", isValidContact, "Invalid phone.", state, input))
        return false;
    ref2.phone = input;
    
    if (!getValidatedInput("Email: ", isValidEmail, "Invalid email.", state, input))
        return false;
    ref2.email = input;
    
    app.setReferee2(ref2);
    
    return true;
}

// ==================== DOCUMENT PATHS COLLECTION ====================

bool collectDocuments(Application &app, string &state)
{
    printSectionHeader("DOCUMENT UPLOAD");
    cout << "Please provide the full path to the SOURCE file (e.g., C:\\Images\\cnic.jpg).\n";
    cout << "Accepted formats: JPG, JPEG, PNG\n";
    cout << "Files will be copied to output/application_documents/\n\n";
    
    const string DOC_DIR = "output/application_documents/";
    string cnicF, cnicB, bill, salary;
    
    // Helper lambda to process document upload
    auto processDocument = [&](const string& docName, const string& suffix, string& outputPath) -> bool
    {
        while (true)
        {
            cout << docName << " (Source Path): ";
            string inputPath;
            getline(cin, inputPath);
            inputPath = trim(inputPath);
            
            // Check for exit
            if (inputPath == "X" || inputPath == "x")
            {
                state = "MAIN_MENU";
                return false;
            }
            
            // Validate file exists
            if (!isValidFilePath(inputPath))
            {
                printError("File not found: " + inputPath);
                cout << "Please check the path and try again.\n";
                continue;
            }
            
            // Validate file is an image
            if (!isValidImageFile(inputPath))
            {
                printError("Invalid file format. Please provide a JPG or PNG image.");
                continue;
            }
            
            // Generate new filename: CNIC_SUFFIX.ext
            string ext = getFileExtension(inputPath);
            string newFilename = app.getCNIC() + "_" + suffix + ext;
            string destPath = DOC_DIR + newFilename;
            
            // Copy file to application_documents folder
            if (copyFile(inputPath, destPath))
            {
                outputPath = destPath;
                printSuccess("File uploaded: " + newFilename);
                return true;
            }
            else
            {
                printError("Failed to copy file. Please check permissions and try again.");
            }
        }
    };
    
    // Collect all 4 documents
    if (!processDocument("CNIC Front", "CNIC_FRONT", cnicF)) return false;
    if (!processDocument("CNIC Back", "CNIC_BACK", cnicB)) return false;
    if (!processDocument("Electricity Bill", "BILL", bill)) return false;
    if (!processDocument("Salary Slip", "SALARY", salary)) return false;
    
    // Set document paths in application
    app.setDocumentPaths(cnicF, cnicB, bill, salary);
    
    printSuccess("\nAll documents uploaded successfully!");
    return true;
}