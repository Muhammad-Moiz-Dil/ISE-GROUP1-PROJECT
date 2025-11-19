#ifndef UTILS_H
#define UTILS_H

#include <string>

/**
 * Converts a std::string to lowercase for case-insensitive comparisons.
 * @param str: the input std::string to convert
 * @return: lowercase version of the input std::string
 */
std::string toLower(std::string str);

/**
 * Removes leading and trailing whitespace and carriage returns from a std::string.
 * @param s: the input std::string to trim
 * @return: trimmed version of the input std::string
 */
std::string trim(const std::string &s);

/**
 * Checks if a given std::string is a valid name.
 * @param name: the name to validate
 * @return true if the name is valid, false otherwise
 */
bool isValidName(const std::string& name);

/**
 * Checks if a given std::string is a valid CNIC.
 * @param cnic: the CNIC to validate
 * @return true if the CNIC is valid, false otherwise
 */
bool isValidCNIC(const std::string& cnic);

/**
 * Checks if a given std::string is a valid contact number.
 * @param contact: the contact number to validate
 * @return true if the contact number is valid, false otherwise
 */
bool isValidContact(const std::string& contact);

/**
 * Checks if a given std::string is a valid email address.
 * @param email: the email address to validate
 * @return true if the email address is valid, false otherwise
 */
bool isValidEmail(const std::string& email);

/**
 * Checks if a given std::string is a valid date in the format DD-MM-YYYY.
 * @param date: the date to validate
 * @return true if the date is valid, false otherwise
 */
bool isValidDate(const std::string& date);

/**
 * Checks if a given std::string is a valid positive integer.
 * @param str: the std::string to validate
 * @return true if the std::string is a valid positive integer, false otherwise
 */
bool isValidPositiveInteger(const std::string& str);

/**
 * Checks if a given std::string is a valid positive amount.
 * @param str: the std::string to validate
 * @return true if the std::string is a valid positive amount, false otherwise
 */
bool isValidPositiveAmount(const std::string& str);

/**
 * Checks if a given std::string is a valid menu choice within a given range.
 * @param choice: the menu choice to validate
 * @param min: the minimum value of the range
 * @param max: the maximum value of the range
 * @return true if the menu choice is valid, false otherwise
 */
bool isValidMenuChoice(const std::string& choice, int min, int max);

#endif