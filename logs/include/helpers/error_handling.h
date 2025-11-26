#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H

#include <string>
using std::string;

// ==================== INPUT VALIDATION FUNCTIONS ====================
// These functions validate user input and return true if valid, false otherwise

/**
 * @brief Validates a name (must contain at least one letter, allows spaces, hyphens, apostrophes)
 * @param name: The name string to validate
 * @return true if valid, false otherwise
 */
bool isValidName(const string& name);

/**
 * @brief Validates a 13-digit Pakistani CNIC number
 * @param cnic: The CNIC string to validate
 * @return true if exactly 13 digits, false otherwise
 */
bool isValidCNIC(const string& cnic);

/**
 * @brief Validates an 11-digit Pakistani phone number starting with 03
 * @param contact: The phone number string to validate
 * @return true if valid format (03XXXXXXXXX), false otherwise
 */
bool isValidContact(const string& contact);

/**
 * @brief Validates an email address (basic format: text@domain.extension)
 * @param email: The email string to validate
 * @return true if contains @ and dot in correct positions, false otherwise
 */
bool isValidEmail(const string& email);

/**
 * @brief Validates a date in DD-MM-YYYY format
 * @param date: The date string to validate
 * @return true if format is correct and values are in valid ranges, false otherwise
 */
bool isValidIssueDate(const string& date);

/**
 * @brief Validates a date in DD-MM-YYYY format
 * @param date: The date string to validate
 * @return true if format is correct and values are in valid ranges, false otherwise
 */
bool isValidExpiryDate(const string& date);

/**
 * @brief Validates a positive integer (no leading zeros, digits only)
 * @param str: The string to validate
 * @return true if all digits and positive, false otherwise
 */
bool isValidPositiveInteger(const string& str);

/**
 * @brief Validates a positive amount (must be > 0)
 * @param str: The string to validate
 * @return true if numeric and > 0, false otherwise
 */
bool isValidPositiveAmount(const string& str);

/**
 * @brief Validates integer within specified range
 * @param input String to validate
 * @param min Minimum value (inclusive)
 * @param max Maximum value (inclusive)
 * @return true if valid and within range
 */
bool isValidIntegerInRange(const string& input, int min, int max);

/**
 * @brief Validates reasonable monetary amount (0 to 1 billion PKR)
 * @param input String to validate
 * @return true if valid and reasonable
 */
bool isValidReasonableAmount(const string& input);


/**
 * @brief Validates a menu choice is within a given range
 * @param choice: The user's input
 * @param min: Minimum valid value (inclusive)
 * @param max: Maximum valid value (inclusive)
 * @return true if choice is a number between min and max, false otherwise
 */
bool isValidMenuChoice(const string& choice, int min, int max);

/**
 * @brief Checks if file path exists
 * @param filepath Path to validate
 * @return true if exists, false otherwise
 */
bool isValidFilePath(const string& filepath);

/**
 * @brief Validates if file is a jpg or png image
 * @param filepath Path to validate
 * @return true if valid image, false otherwise
 */
bool isValidImageFile(const string& filepath);

#endif // ERROR_HANDLING_H