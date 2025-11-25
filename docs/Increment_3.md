# Increment 3 Requirements

## 1. Overview

- **Validation**: All validation checks from Increment 2 are required (invalid values for amount, date, input choice, etc.).
- **Multi-session Support**:
  - Users can complete applications in multiple sessions.
  - Users can resume by providing **Application ID** and **CNIC**.
  - Only **incomplete** applications can be updated. Completed applications cannot be modified.
  - **Checkpoints**: The application form is divided into 4 categories. Data is saved to `applications.txt` after completing each section.

## 2. Application Sections (Checkpoints)

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

### D. Documents

- Picture of Applicant’s CNIC Front
- Picture of Applicant’s CNIC Back
- Picture of Recent Electricity Bill
- Picture of Salary Slip / Bank Statement Page 1

> **Hint**: Use status codes like `C1`, `C2`, `C3` in `applications.txt` to track progress. Change to `Submitted` upon completion.

## 3. Lender Interface

- A separate conventional interface (not a chatbot) for the lender.
- yan4. General Conversation Mode (Chatbot)
- **Feature**: Chatbot can handle general conversation.
- **Data Source**: `human_chat_corpus.txt`.

  - Format: Interactions on separate lines. `Human 1` (Question) followed by `Human 2` (Response).
- **Matching Algorithm**: **Intersection over Union (IoU)**.

  - `IoU = (Tokens common in User Input & Human 1) / (Unique tokens in both)`
  - Select the `Human 2` response corresponding to the `Human 1` line with the highest IoU.

## 5. Deliverables & Notes

- **New Files**: Create `Personal.txt` (similar to `Home.txt`, `Utterances.txt`, etc.).
- **Sprint Deadline**: Wednesday, November 26, 2025.
- **Demo**: November 27, 2025.
- **Process**:
  - Update requirements on Jira.
  - Update code on GitHub.
  - **Effort Tracking**: Record estimated vs. actual effort in the Google Sheet. Marks are based on data correctness, not the size of the difference.
