#ifndef APPLICATION_H
#define APPLICATION_H

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using std::string;
using std::vector;

/**
 * Stores information about an existing loan
 * Used when applicant has taken a previous loan
 */
struct ExistingLoan {
  bool isActive;       // Is the loan currently active?
  long totalAmount;    // Total loan amount borrowed
  long amountReturned; // Amount already paid back
  long amountDue;      // Remaining amount to be paid
  string bankName;     // Name of the lending bank
  string category;     // Type: Car, Home, or Bike
};

/**
 * Stores information about a referee/guarantor
 * Two referees are required per application
 */
struct Referee {
  string name;      // Full name of referee
  string cnic;      // 13-digit CNIC without dashes
  string issueDate; // CNIC issue date (DD-MM-YYYY)
  string phone;     // Contact number (03xxxxxxxxx)
  string email;     // Email address
};

/**
 * Main Application class - stores all loan application data
 * Represents a single loan application with personal, financial, and reference
 * information
 */
class Application {
private:
  string applicationID; // Unique 4-digit ID (e.g., "1001")
  string status;        // "Submitted", "Approved", or "Rejected"

  // Personal Information (10 fields)
  string fullName;
  string fathersName;
  string postalAddress;
  string contact;
  string email;
  string cnic;       // 13 digits, no dashes
  string cnicExpiry; // DD-MM-YYYY format
  string employment; // Self-employed, Salaried, Retired, Unemployed
  string marital;    // Single, Married, Divorced, Widowed
  string gender;     // Male, Female, Other

  // Financial Information (4 fields)
  int dependents;              // Number of dependents
  long annualIncome;           // Annual income in PKR
  long avgElectricityBill;     // 12-month average
  long currentElectricityBill; // Current bill amount

  // Existing Loan Information
  bool hasExistingLoan;      // Does user have existing loan?
  ExistingLoan existingLoan; // Details if yes

  // Reference Information (2 referees)
  Referee referee1;
  Referee referee2;

  // Document Paths (4 files)
  string cnicFrontPath; // Path to CNIC front image
  string cnicBackPath;  // Path to CNIC back image
  string billPath;      // Path to electricity bill
  string salaryPath;    // Path to salary slip/bank statement

  // Loan Selection
  string selectedLoanType;    // Home, Car, or Scooter
  string selectedLoanDetails; // Specific plan details
  string submissionDate;      // Date of submission
  int checkpoint; // 0: Start, 1: Personal Done, 2: Financial Done, 3: Ref Done,
                  // 4: Docs Done (Submitted)

public:
  /**
   * Constructor - initializes with default values
   */
  Application()
      : hasExistingLoan(false), dependents(0), status("Incomplete"),
        checkpoint(0) {}

  // [<-| SETTERS |->]
  void setApplicationID(string id) { applicationID = id; }
  void setStatus(string s) { status = s; }
  void setFullName(string n) { fullName = n; }
  void setFathersName(string n) { fathersName = n; }
  void setPostalAddress(string a) { postalAddress = a; }
  void setContact(string c) { contact = c; }
  void setEmail(string e) { email = e; }
  void setCNIC(string c) { cnic = c; }
  void setCNICExpiry(string e) { cnicExpiry = e; }
  void setEmployment(string e) { employment = e; }
  void setMarital(string m) { marital = m; }
  void setGender(string g) { gender = g; }
  void setDependents(int d) { dependents = d; }
  void setAnnualIncome(long i) { annualIncome = i; }
  void setAvgElectricityBill(long b) { avgElectricityBill = b; }
  void setCurrentElectricityBill(long b) { currentElectricityBill = b; }
  void setExistingLoan(ExistingLoan l) {
    existingLoan = l;
    hasExistingLoan = true;
  }
  void setReferee1(Referee r) { referee1 = r; }
  void setReferee2(Referee r) { referee2 = r; }
  void setDocumentPaths(string cf, string cb, string eb, string ss) {
    cnicFrontPath = cf;
    cnicBackPath = cb;
    billPath = eb;
    salaryPath = ss;
  }
  void setLoanDetails(string type, string details) {
    selectedLoanType = type;
    selectedLoanDetails = details;
  }
  void setSubmissionDate(string d) { submissionDate = d; }
  void setCheckpoint(int c) { checkpoint = c; }

  // [<-| GETTERS |->]
  string getApplicationID() const { return applicationID; }
  string getStatus() const { return status; }
  int getCheckpoint() const { return checkpoint; }
  string getCNIC() const { return cnic; }
  string getFullName() const { return fullName; }
  string getFathersName() const { return fathersName; }
  string getContact() const { return contact; }
  string getEmail() const { return email; }
  string getSubmissionDate() const { return submissionDate; }
  string getPostalAddress() const { return postalAddress; }

  // Financial Information Getters
  string getEmployment() const { return employment; }
  int getDependents() const { return dependents; }
  long getAnnualIncome() const { return annualIncome; }
  long getAvgElectricityBill() const { return avgElectricityBill; }
  long getCurrentElectricityBill() const { return currentElectricityBill; }

  // Loan Details Getters
  string getLoanType() const { return selectedLoanType; }
  string getLoanArea() const { return selectedLoanDetails; }

  // [<-| FILE OPERATIONS |->]
  /**
   * Converts application to # separated format for file storage
   * @return string in format: field1#field2#field3#...
   */
  string toFileFormat() const;

  /**
   * Creates Application object from file line
   * @param line: # separated string from applications.txt
   * @return Application object with parsed data
   */
  static Application fromFileFormat(const string &line);

  /**
   * Displays complete application details in formatted manner
   * Used by lender to review applications
   */
  void displayDetails() const;
};

/**
 * ApplicationManager class - manages all applications
 * Handles loading, saving, querying, and status updates
 */
class ApplicationManager {
private:
  vector<Application> applications; // All loaded applications
  int nextApplicationID;            // Next ID to assign (starts at 1001)

public:
  /**
   * Constructor - initializes with starting ID 1001
   */
  ApplicationManager() : nextApplicationID(1001) {}

  /**
   * Loads applications from file
   * @param filename: path to applications.txt
   * @return true if successful, false otherwise
   */
  bool loadApplications(const string &filename);

  /**
   * Saves a new application to file (append mode)
   * @param app: Application object to save
   * @return true if successful, false otherwise
   */
  bool saveApplication(const Application &app);

  /**
   * Saves all applications to file (overwrites entire file)
   * Used when updating application status
   * @param filename: path to applications.txt
   * @return true if successful, false otherwise
   */
  bool saveAllApplications(const string &filename);

  /**
   * Generates next unique application ID
   * @return string ID (e.g., "1001", "1002", etc.)
   */
  string generateApplicationID();

  /**
   * Gets all applications for a specific CNIC
   * @param cnic: 13-digit CNIC number
   * @return vector of matching applications
   */
  vector<Application> getApplicationsByCNIC(const string &cnic);

  /**
   * Counts applications by status for a specific CNIC
   * @param cnic: 13-digit CNIC number
   * @param status: "Submitted", "Approved", or "Rejected"
   * @return count of matching applications
   */
  int getCountByStatus(const string &cnic, const string &status);

  /**
   * Finds application by ID
   * @param appID: Application ID to search for
   * @return pointer to Application if found, nullptr otherwise
   */
  Application *getApplicationByID(const string &appID);

  /**
   * Updates status of an application
   * @param appID: Application ID to update
   * @param newStatus: New status ("Approved" or "Rejected")
   * @return true if successful, false if not found
   */
  bool updateApplicationStatus(const string &appID, const string &newStatus);

  /**
   * Gets all applications (for lender dashboard)
   * @return vector of all applications
   */
  vector<Application> getAllApplications() { return applications; }
};

/**
 * Global application manager instance
 * Used by both chatbot and lender programs
 */
extern ApplicationManager appManager;

#endif
