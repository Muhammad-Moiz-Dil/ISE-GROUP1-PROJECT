# ISE Project - Structure Documentation

## Overview

Loan Application Management System built in C++ with separate interfaces for customers (chatbot) and lenders (portal). The system handles home, car, and scooter loan applications with comprehensive validation and document management.

---

## Directory Tree

```
ISE-Project/
├── backend/
│   └── src/
│       ├── main.cpp                    # User application entry point
│       ├── lender_main.cpp             # Lender portal entry point
│       │
│       ├── core/                       # Core application logic
│       │   ├── chatbot.cpp/.h          # Main chatbot loop and routing
│       │   ├── state_handlers.cpp/.h   # State-specific handler functions
│       │   ├── application.cpp/.h      # Application data model and management
│       │   ├── file_io.cpp/.h          # File loading utilities
│       │   └── lender.cpp/.h           # Lender portal management
│       │
│       ├── helpers/                    # Reusable utility functions
│       │   ├── utils.cpp/.h            # String manipulation and display helpers
│       │   ├── error_handling.cpp/.h   # Input validation functions
│       │   ├── ui_display.cpp/.h       # UI formatting and display
│       │   └── application_input.cpp/.h # Form data collection
│       │
│       ├── models/                     # Data models for loan types
│       │   ├── home_loan.cpp/.h        # Home loan plan model
│       │   ├── car.cpp/.h              # Car loan plan model
│       │   └── scooter.cpp/.h          # Scooter loan plan model
│       │
│       └── output/                     # Data files and documents
│           ├── Utterances.txt          # Chatbot responses
│           ├── Home.txt                # Home loan plans data
│           ├── Car.txt                 # Car loan plans data
│           ├── Scooter.txt             # Scooter loan plans data
│           ├── applications.txt        # Submitted applications
│           └── application_documents/  # Uploaded user documents
│
└── logs/
    └── include/                        # Header files directory
```

---

## Build Instructions

### Compilation Commands

**User Chatbot:**

```bash
cd backend/src
g++ -I../../logs/include main.cpp core/chatbot.cpp core/state_handlers.cpp core/file_io.cpp core/application.cpp helpers/utils.cpp helpers/error_handling.cpp helpers/ui_display.cpp helpers/application_input.cpp models/home_loan.cpp models/car.cpp models/scooter.cpp -o chatbot
```

**Lender Portal:**

```bash
cd backend/src
g++ -I../../logs/include lender_main.cpp core/lender.cpp core/application.cpp helpers/utils.cpp helpers/error_handling.cpp helpers/ui_display.cpp -o lender
```

### Run

```bash
./chatbot    # User application
./lender     # Lender portal
```

---

## Module Documentation

### Core Module (core/)

#### chatbot.cpp/h

**Purpose:** Main chatbot orchestration and user interaction loop

**Key Functions:**

- `runChatbot()` - Main chatbot loop, handles user input and state routing

**Dependencies:** state_handlers, file_io, application

**Lines:** ~80

---

#### state_handlers.cpp/h

**Purpose:** Individual state handler functions for different chatbot states

**Key Functions:**

- `handleMainMenu(string, string, string&)` - Processes main menu choices
- `handleLoanCategory(string, string, string&)` - Routes to specific loan types
- `handleHomeLoanArea(string, string, string&, string&)` - Home loan area selection
- `handleCarLoan(string&, string&, string&, string&)` - Car loan make selection
- `handleScooterLoan(string&, string&, string&, string&)` - Scooter loan make selection
- `handleViewCarMonthlyInstallments()` - Displays car payment schedule
- `handleViewScooterMonthlyInstallments()` - Displays scooter payment schedule
- `handleViewMonthlyInstallments()` - Displays home loan payment schedule
- `handleCheckStatus(string&)` - Checks application status
- `handleResumeApplication(string&)` - Resumes incomplete applications
- `handleApplicationSubmission()` - Manages new application submission
- `handleQueryApplications(string&)` - Queries applications by CNIC

**Dependencies:** application, ui_display, error_handling, all model classes

**Lines:** ~500

---

#### application.cpp/h

**Purpose:** Application data model and management system

**Key Classes:**

- `Application` - Stores complete loan application data (40+ fields)
- `ApplicationManager` - Manages all applications

**Structures:**

- `ExistingLoan` - Stores existing loan details
- `Referee` - Stores referee/guarantor information

**Application Class:**

- `toFileFormat()` - Converts to file format
- `fromFileFormat()` - Parses from file line
- `displayDetails()` - Displays application with color coding
- Getters/Setters for all fields

**ApplicationManager:**

- `loadApplications()` - Loads from file
- `saveApplication()` - Saves/updates single app
- `generateApplicationID()` - Generates unique IDs (starts at 1001)
- `getApplicationByID()` - Finds by ID
- `getApplicationsByCNIC()` - Finds all apps for CNIC
- `updateApplicationStatus()` - Updates status

**Dependencies:** utils, file I/O

**Lines:** ~250

---

#### file_io.cpp/h

**Purpose:** File loading and parsing

**Classes:**

- `Utterance` - Chatbot response mappings

**Functions:**

- `loadUtterances()` - Loads chatbot responses
- `loadLoanPlans()` - Loads home loan plans
- `loadCarPlans()` - Loads car plans
- `loadScooterPlans()` - Loads scooter plans

**Helpers:**

- `parseNumberWithCommas()` - Removes commas
- `calculateMonthlyInstallment()` - Calculates monthly payment

**Dependencies:** models, utils

**Lines:** ~210

---

#### lender.cpp/h

**Purpose:** Lender portal for reviewing applications

**Classes:**

- `LenderManager` - Manages lender operations

**Functions:**

- `loadApplications()` - Loads for review
- `displayAllApplications()` - Shows table
- `findApplicationByID()` - Searches by ID
- `displayApplicationDetails()` - Shows details
- `updateApplicationStatus()` - Approves/rejects
- `runLenderPortal()` - Main interface loop

**Handlers:**

- `handleViewAllApplications()`
- `handleSearchApplication()`
- `handleApproveReject()`

**Dependencies:** application, utils, ui_display

**Lines:** ~338

---

### Helpers Module (helpers/)

#### utils.cpp/h

**Purpose:** Common utility functions

**String Functions:**

- `toLower()` - Converts to lowercase
- `trim()` - Removes whitespace/commas
- `extractFilename()` - Extracts filename from path
- `getFileExtension()` - Gets extension

**Display Functions:**

- `printError()` - Red error message
- `printSuccess()` - Green success message
- `printWarning()` - Yellow warning
- `printInfo()` - Cyan info
- `printSectionHeader()` - Colored header

**File Functions:**

- `copyFile()` - Copies file

**Constants:**

- Color codes (RED, GREEN, YELLOW, CYAN, BLUE, RESET)

**Dependencies:** None

**Lines:** ~100

---

#### error_handling.cpp/h

**Purpose:** Input validation functions

**Text Validation:**

- `isValidName()` - Letters, spaces, hyphens only
- `isValidEmail()` - Contains @ and .
- `isValidContact()` - 03xxxxxxxxx format
- `isValidCNIC()` - 13 digits

**Date Validation:**

- `isValidDate()` - DD-MM-YYYY format

**Numeric Validation:**

- `isValidMenuChoice()` - Menu range validation
- `isValidPositiveInteger()` - Positive integers
- `isValidPositiveAmount()` - Positive amounts
- `isValidIntegerInRange()` - Range validation
- `isValidReasonableAmount()` - Up to 1B PKR

**File Validation:**

- `isValidFilePath()` - File exists check
- `isValidImageFile()` - JPG/PNG validation

**Dependencies:** utils

**Lines:** ~150

---

#### ui_display.cpp/h

**Purpose:** UI formatting and display

**Functions:**

- `displayWelcomeHeader()` - Welcome banner
- `displayGoodbyeFooter()` - Goodbye message
- `displayPaymentSchedule()` - Payment breakdown table
- `displayApplicationStatus()` - Color-coded status

**Dependencies:** utils

**Lines:** ~100

---

#### application_input.cpp/h

**Purpose:** Collects and validates user data

**Helper:**

- `getValidatedInput()` - Generic validator with retry loop

**Collection Functions:**

- `collectPersonalInformation()` - 10 fields: Name, Father's Name, Address, Contact, Email, CNIC, CNIC Expiry, Employment, Marital, Gender
- `collectFinancialInformation()` - Dependents (0-20), Income (min 100K), Bills (0-100K), Existing loans
- `collectReferenceInformation()` - 2 referees: Name, CNIC, Issue Date, Phone, Email
- `collectDocuments()` - Validates 4 files (JPG/PNG), copies to application_documents/

**Dependencies:** application, error_handling, utils

**Lines:** ~320

---

### Models Module (models/)

#### home_loan.cpp/h

**Purpose:** Home loan plan model

**Classes:**

- `HomeLoanPlan` - Single plan details
- `HomeLoanManager` - Manages plans by area

**HomeLoanPlan:**

- `display()` - Shows plan
- Getters/Setters for size, installments, price, downPayment, monthlyInstallments

**HomeLoanManager:**

- `setArea()` - Adds plan to area
- `displayHomeLoanPlan()` - Shows all plans for area
- `getPlanCount()` - Count for area
- `getPlan()` - Gets specific plan
- `displayMonthlyInstallment()` - Payment schedule (deprecated)

**Dependencies:** utils

**Lines:** ~95

---

#### car.cpp/h

**Purpose:** Car loan plan model

**Classes:**

- `CarPlan` - Single car plan
- `CarPlanManager` - Manages plans by make

**CarPlan:**

- `display()` - Shows plan
- Getters/Setters for make, model, engine, year, installments, price, downPayment, monthlyInstallments

**CarPlanManager:**

- `setMake()` - Adds plan to make
- `displayCarPlan()` - Shows all plans for make
- `getPlanCount()` - Count for make
- `getPlan()` - Gets specific plan
- `displayMonthlyInstallment()` - Payment schedule (deprecated)

**Dependencies:** utils

**Lines:** ~115

---

#### scooter.cpp/h

**Purpose:** Scooter loan plan model

**Classes:**

- `ScooterPlan` - Single scooter plan
- `ScooterPlanManager` - Manages plans by make

**ScooterPlan:**

- `display()` - Shows plan
- Getters/Setters for make, model, distancePerCharge, chargingTime, maxSpeed, installments, price, downPayment, monthlyInstallments

**ScooterPlanManager:**

- `setMake()` - Adds plan to make
- `displayScooterPlan()` - Shows all plans for make
- `getPlanCount()` - Count for make
- `getPlan()` - Gets specific plan
- `displayMonthlyInstallment()` - Payment schedule (deprecated)

**Dependencies:** utils

**Lines:** ~115

---

## Data Flow

### User Application Flow

1. `main.cpp` loads all data files (utterances, loan plans, applications)
2. `runChatbot()` starts main loop
3. User input routed to appropriate state handler
4. State handlers call model classes to display loan options
5. Application submission calls `application_input` functions
6. Data validated by `error_handling` functions
7. Application saved via `ApplicationManager`

### Lender Portal Flow

1. `lender_main.cpp` creates `LenderManager`
2. `runLenderPortal()` loads applications and starts menu loop
3. Lender views/searches applications
4. Status updates saved back to applications.txt

---

## Dependencies Graph

```
main.cpp → chatbot → state_handlers → {application, models, ui_display}
       ↓
    file_io → {models, utils}
       ↓
    application → utils

lender_main → lender → {application, ui_display} → utils

state_handlers → application_input → {application, error_handling, utils}

All modules → utils (base dependency)
```

---

## File Size Summary

| File                  | Lines | Purpose                 |
| --------------------- | ----- | ----------------------- |
| chatbot.cpp           | 80    | Main loop orchestration |
| state_handlers.cpp    | 500   | State-specific logic    |
| application.cpp       | 250   | Data model & management |
| file_io.cpp           | 210   | File loading            |
| lender.cpp            | 338   | Lender portal           |
| utils.cpp             | 100   | Common utilities        |
| error_handling.cpp    | 150   | Validation functions    |
| ui_display.cpp        | 100   | Display formatting      |
| application_input.cpp | 320   | Form collection         |
| home_loan.cpp         | 95    | Home loan model         |
| car.cpp               | 115   | Car loan model          |
| scooter.cpp           | 115   | Scooter loan model      |

**Total:** ~2,373 lines (down from ~3,500+ before refactoring)

---

## Key Design Patterns

### Separation of Concerns

- Core logic separated from UI (ui_display)
- Validation separated from business logic (error_handling)
- Data models independent of business logic (models/)

### DRY Principle

- Common utilities in helpers/
- Reusable validation functions
- Generic input collection helper

### Modular Architecture

- Each module under 500 lines
- Clear dependencies
- Single responsibility per file

---

## Coding Standards

- **Naming:** lowerCamelCase for all identifiers
- **Comments:** Javadoc style for all public functions
- **File Size:** Maximum 500 lines per file
- **Getters/Setters:** Inline in headers
- **Formatting:** 4-space indentation, K&R brace style

See `ISE_CODING_STANDARDS.pdf` for complete guidelines.

---

## Contributors

Team members working on ISE Project loan application system.

Last Updated: November 23, 2025
