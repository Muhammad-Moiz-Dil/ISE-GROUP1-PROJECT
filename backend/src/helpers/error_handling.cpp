#include "helpers/error_handling.h"
#include "helpers/utils.h"
#include <cctype>
#include <string>
#include <fstream>


using std::string;
using std::stoi;
using std::stol;

// ==================== INPUT VALIDATION IMPLEMENTATIONS ====================

bool isValidName(const string& name)
{
    if (name.empty()) return false;
    
    bool hasLetter = false;
    bool hasOnlyNumbersAndSpecialChars = true;
    
    for (char c : name)
    {
        if (isalpha(c))
        {
            hasLetter = true;
            hasOnlyNumbersAndSpecialChars = false;
        }
        else if (!isspace(c) && c != '-' && c != '\'' && !isdigit(c))
        {
            // Invalid character (not letter, space, hyphen, apostrophe, or digit)
            return false;
        }
    }
    
    return hasLetter; // Must have at least one letter
}

bool isValidCNIC(const string& cnic)
{
    if (cnic.length() != 13) return false;
    
    for (char c : cnic)
    {
        if (!isdigit(c)) return false;
    }
    
    return true;
}

bool isValidContact(const string& contact)
{
    if (contact.length() != 11) return false;
    if (contact[0] != '0' || contact[1] != '3') return false;
    
    for (char c : contact)
    {
        if (!isdigit(c)) return false;
    }
    
    return true;
}

bool isValidEmail(const string& email)
{
    if (email.empty()) return false;
    
    // Check for spaces
    if (email.find(' ') != string::npos) return false;
    
    // Find @ symbol
    size_t atPos = email.find('@');
    if (atPos == string::npos || atPos == 0) return false;
    
    // Check for domain after @
    if (atPos >= email.length() - 1) return false;
    
    // Check for at least one dot after @
    size_t dotPos = email.find('.', atPos);
    if (dotPos == string::npos) return false;
    if (dotPos == email.length() - 1) return false;
    
    return true;
}

bool isValidIssueDate(const string& date)
{
    if (date.length() != 10) return false;
    if (date[2] != '-' || date[5] != '-') return false;
    
    // Extract components
    string dayStr = date.substr(0, 2);
    string monthStr = date.substr(3, 2);
    string yearStr = date.substr(6, 4);
    
    // Check all are digits
    for (char c : dayStr) if (!isdigit(c)) return false;
    for (char c : monthStr) if (!isdigit(c)) return false;
    for (char c : yearStr) if (!isdigit(c)) return false;
    
    // Validate ranges
    int day = stoi(dayStr);
    int month = stoi(monthStr);
    int year = stoi(yearStr);
    
    if (day < 1 || day > 31) return false;
    if (month < 1 || month > 12) return false;
    if (year < 1900 || year > 2025) return false;
    
    return true;
}

bool isValidExpiryDate(const string& date)
{
    if (date.length() != 10) return false;
    if (date[2] != '-' || date[5] != '-') return false;
    
    // Extract components
    string dayStr = date.substr(0, 2);
    string monthStr = date.substr(3, 2);
    string yearStr = date.substr(6, 4);
    
    // Check all are digits
    for (char c : dayStr) if (!isdigit(c)) return false;
    for (char c : monthStr) if (!isdigit(c)) return false;
    for (char c : yearStr) if (!isdigit(c)) return false;
    
    // Validate ranges
    int day = stoi(dayStr);
    int month = stoi(monthStr);
    int year = stoi(yearStr);
    
    if (day < 1 || day > 31) return false;
    if (month < 1 || month > 12) return false;
    if (year < 1900 || year > 2100) return false;
    
    return true;
}

bool isValidReasonableAmount(const string& input)
{
    if (input.empty()) return false;
    
    for (char c : input)
    {
        if (!isdigit(c)) return false;
    }
    
    try
    {
        long value = stol(input);
        return (value >= 0 && value <= 1000000000);  // Max 1 billion PKR
    }
    catch (...)
    {
        return false;
    }
}

bool isValidIntegerInRange(const string& input, int min, int max)
{
    if (input.empty()) return false;
    
    // Check if all characters are digits
    for (char c : input)
    {
        if (!isdigit(c)) return false;
    }
    
    // Convert to integer and check range
    try
    {
        int value = stoi(input);
        return (value >= min && value <= max);
    }
    catch (...)
    {
        return false;  // Number too large for int
    }
}

bool isValidPositiveInteger(const string& str)
{
    if (str.empty()) return false;
    
    for (char c : str)
    {
        if (!isdigit(c)) return false;
    }
    
    try
    {
        long value = stol(str);
        return (value > 0);
    }
    catch (...)
    {
        return false;  // Number too large for long
    }
}

bool isValidPositiveAmount(const string& str)
{
    if (str.empty()) return false;
    
    for (char c : str)
    {
        if (!isdigit(c) && c != '.') return false;
    }
    
    try
    {
        double value = stod(str);
        return (value > 0);
    }
    catch (...)
    {
        return false;  // Number too large for double
    }
}

bool isValidMenuChoice(const string& choice, int min, int max)
{
    if (choice.empty()) return false;
    
    for (char c : choice)
    {
        if (!isdigit(c)) return false;
    }
    
    int num = stoi(choice);
    return num >= min && num <= max;
}

bool isValidFilePath(const string& filepath)
{
    if (filepath.empty()) return false;
    
    std::ifstream file(filepath);
    return file.good();
}

bool isValidImageFile(const string& filepath)
{
    if (!isValidFilePath(filepath)) return false;
    
    string ext = getFileExtension(filepath);
    return (ext == ".jpg" || ext == ".jpeg" || ext == ".png");
}