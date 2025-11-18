#include "../../logs/include/utils.h"
#include <algorithm>
#include <cctype>
#include <string>

using std::find_if;
using std::string;

/**
 * Converts a string to lowercase.
 * Iterates through each character and converts it using tolower().
 * @param str: the input string
 * @return: lowercase version of the string
 */
string toLower(string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        str[i] = tolower(str[i]);
    }
    return str;
}

string trim(const string &s)
{
    string result = "";
    int start = 0;
    int end = s.length() - 1;

    // Skip leading whitespace
    while (start < s.length() && (s[start] == ' ' || s[start] == '\t' || s[start] == '\r' || s[start] == '\n'))
    {
        start++;
    }

    // Skip trailing whitespace
    while (end >= start && (s[end] == ' ' || s[end] == '\t' || s[end] == '\r' || s[end] == '\n'))
    {
        end--;
    }

    // Build result string
    for (int i = start; i <= end; i++)
    {
        if (s[i] != ',')
        {
            result += s[i];
        }
    }

    return result;
}

// ==================== NEW VALIDATION FUNCTIONS ====================

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

bool isValidDate(const string& date)
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
    int day = std::stoi(dayStr);
    int month = std::stoi(monthStr);
    int year = std::stoi(yearStr);
    
    if (day < 1 || day > 31) return false;
    if (month < 1 || month > 12) return false;
    if (year < 1900 || year > 2100) return false;
    
    return true;
}

bool isValidPositiveInteger(const string& str)
{
    if (str.empty()) return false;
    
    for (char c : str)
    {
        if (!isdigit(c)) return false;
    }
    
    return true;
}

bool isValidPositiveAmount(const string& str)
{
    if (str.empty()) return false;
    
    for (char c : str)
    {
        if (!isdigit(c)) return false;
    }
    
    long amount = std::stol(str);
    return amount > 0;
}

bool isValidMenuChoice(const string& choice, int min, int max)
{
    if (choice.empty()) return false;
    
    for (char c : choice)
    {
        if (!isdigit(c)) return false;
    }
    
    int num = std::stoi(choice);
    return num >= min && num <= max;
}
