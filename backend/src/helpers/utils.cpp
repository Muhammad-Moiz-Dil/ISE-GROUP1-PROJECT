#include "helpers/utils.h"
#include <iostream>
#include <cctype>
#include <string>
#include <fstream>
#include <filesystem>

using std::cout;
using std::endl;
using std::string;

// ==================== STRING MANIPULATION ====================

/**
 * @brief Converts a string to lowercase
 */
string toLower(string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        str[i] = tolower(str[i]);
    }
    return str;
}

/**
 * @brief Trims whitespace and commas from a string
 */
string trim(const string& s)
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

// ==================== DISPLAY HELPERS ====================

/**
 * @brief Prints an error message in red color
 * @param message: The error message to display
 */
void printError(const string& message)
{
    cout << COLOR_RED << message << COLOR_RESET << endl;
}

/**
 * @brief Prints a success message in green color
 * @param message: The success message to display
 */
void printSuccess(const string& message)
{
    cout << COLOR_GREEN << message << COLOR_RESET << endl;
}

/**
 * @brief Prints a warning message in yellow color
 * @param message: The warning message to display
 */
void printWarning(const string& message)
{
    cout << COLOR_YELLOW << message << COLOR_RESET << endl;
}

/**
 * @brief Prints an informational message in cyan color
 * @param message: The info message to display
 */
void printInfo(const string& message)
{
    cout << COLOR_CYAN << message << COLOR_RESET << endl;
}

/**
 * @brief Prints a section header with top and bottom borders
 * @param title: The title text for the section
 */
void printSectionHeader(const string& title)
{
    cout << COLOR_CYAN << "========================================" << COLOR_RESET << endl;
    cout << COLOR_CYAN << title << COLOR_RESET << endl;
    cout << COLOR_CYAN << "========================================" << COLOR_RESET << endl;
}

/**
 * @brief Copies a file from source to destination
 * @param sourcePath Original file path
 * @param destPath Destination file path
 * @return true if copy successful, false otherwise
 */
bool copyFile(const string& sourcePath, const string& destPath)
{
    std::ifstream source(sourcePath, std::ios::binary);
    std::ofstream dest(destPath, std::ios::binary);
    
    if (!source.is_open() || !dest.is_open())
    {
        return false;
    }
    
    dest << source.rdbuf();
    
    source.close();
    dest.close();
    
    return true;
}

/**
 * @brief Extracts filename from a full path
 * @param path Full file path (e.g., "C:/Users/Documents/image.jpg")
 * @return Filename only (e.g., "image.jpg")
 */
string extractFilename(const string& path)
{
    // Find last slash or backslash
    size_t lastSlash = path.find_last_of("/\\");
    
    if (lastSlash != string::npos)
    {
        return path.substr(lastSlash + 1);
    }
    
    return path; // No slash found, already just a filename
}

/**
 * @brief Gets file extension from a path
 * @param path File path
 * @return Extension in lowercase (e.g., ".jpg", ".png")
 */
string getFileExtension(const string& path)
{
    size_t lastDot = path.find_last_of('.');
    
    if (lastDot != string::npos)
    {
        string ext = path.substr(lastDot);
        return toLower(ext);
    }
    
    return "";
}