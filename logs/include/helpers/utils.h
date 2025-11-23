#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <set>
#include <sstream>
#include <algorithm>
#include <cctype>
using std::string;

// ==================== COLOR CODES ====================
#define COLOR_RESET "\033[0m"
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_CYAN "\033[36m"
#define COLOR_BRIGHT_RED "\033[91m"

// ==================== STRING MANIPULATION ====================

/**
 * @brief Converts a string to lowercase
 * @param str: The input string
 * @return: Lowercase version of the string
 */
string toLower(string str);

/**
 * @brief Trims whitespace and commas from a string
 * @param s: The input string
 * @return: Trimmed string
 */
string trim(const string& s);

/**
 * @brief Parses a string with commas into an integer
 * @param s: The input string (e.g., "1,000,000")
 * @return: Integer value
 */
int parseNumberWithCommas(string s);

// ==================== DISPLAY HELPERS ====================

/**
 * @brief Prints an error message in red color
 * @param message: The error message to display
 */
void printError(const string& message);

/**
 * @brief Prints a success message in green color
 * @param message: The success message to display
 */
void printSuccess(const string& message);

/**
 * @brief Prints a warning message in yellow color
 * @param message: The warning message to display
 */
void printWarning(const string& message);

/**
 * @brief Prints an informational message in cyan color
 * @param message: The info message to display
 */
void printInfo(const string& message);

/**
 * @brief Prints a section header with top and bottom borders
 * @param title: The title text for the section
 */
void printSectionHeader(const string& title);


/**
 * @brief Copies a file from source to destination
 * @param sourcePath Original file path
 * @param destPath Destination file path
 * @return true if successful, false otherwise
 */
bool copyFile(const string& sourcePath, const string& destPath);

/**
 * @brief Extracts filename from full path
 * @param path Full file path
 * @return Filename only
 */
string extractFilename(const string& path);

/**
 * @brief Gets file extension from path
 * @param path File path
 * @return Extension in lowercase (e.g., ".jpg")
 */
string getFileExtension(const string& path);

#endif // UTILS_H