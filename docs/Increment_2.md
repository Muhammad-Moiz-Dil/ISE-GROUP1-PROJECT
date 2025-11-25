# Increment 2 Requirements

## 1. Overview

Building upon Increment 1 (monthly installment plan), Increment 2 focuses on **collecting and saving loan seeker information**. The chatbot will gather detailed applicant data and save it to `applications.txt`.

## 2. Data Collection

The chatbot must collect the following information:

### A. Personal Information

- Full Name
- Father’s Name
- Postal Address
- Contact Number
- Email Address
- CNIC Number (without dashes)
- CNIC Expiry Date (DD-MM-YYYY)
- Employment Status (Self-employed, Salaried, Retired, Unemployed)
- Marital Status (Single, Married, Divorced, Widowed)
- Gender
- Number of Dependents

### B. Financial Information

- Annual Income (PKR, numeric only)
- Monthly Average Electricity Bill (last 12 months, PKR, numeric only)
- Current Electricity Bill Amount (PKR, numeric only)
- **Existing Loans Information** (if any):
  - Loan Status (Active/Inactive)
  - Total Loan Amount
  - Amount Returned
  - Amount Still Due
  - Bank Name
  - Loan Category (Car, Home, Bike)

### C. References

Details for **two** referees:

- Name
- CNIC
- CNIC Issue Date
- Phone Number
- Email Address

### D. Documents (Images)

- Picture of Applicant’s CNIC Front
- Picture of Applicant’s CNIC Back
- Picture of Recent Electricity Bill
- Picture of Salary Slip / Bank Statement Page 1

> **Storage**: Save images in `./data/xxxx/` where `xxxx` is a unique 4-digit application ID.

## 3. Application Submission & Storage

- **Confirmation**: Ask the user to confirm submission after collecting all info.
- **Storage Format**:
  - Save data in `applications.txt` as a single row (e.g., `#` separated values).
  - Field order must match the collection order.
  - The last 4 fields should be the **file paths** of the images.
- **Confirmation Message**: Confirm successful submission to the user.

## 4. Application Status & Reporting

- **Status Check**: Users can ask for the count of **submitted**, **approved**, and **rejected** applications against ar
- **Monthly Plan**: For **approved** applications, generate a monthly plan with actual month names (ask user for starting month).
- **Note**: You may need to add status fields to `applications.txt`.

## 5. Lender Interface

- A separate **conventional interface** (not a chatbot) for the lender.
- Functionality:
  - View list of applications.
  - View details of a selected application.
  - **Approve** or **Reject** applications.

## 6. Deliverables & Notes

- **Files**: You can append to `Home.txt`, `Utterances.txt`, `Car.txt`, and `Scooter.txt`.
- **Sprint Deadline**: Wednesday, November 19, 2025.
- **Demo**: November 20, 2025.
- **Process**:
  - Update requirements on Jira.
  - Update code on GitHub.
  - **Effort Tracking**: Record hours spent in the Google Sheet. Accuracy is key for future estimations.
