#ifndef UTILS_H
#define UTILS_H

#include <string>

/**
 * Converts a string to lowercase for case-insensitive comparisons.
 * @param str: the input string to convert
 * @return: lowercase version of the input string
 */
std::string toLower(std::string str);

/**
 * Removes leading and trailing whitespace and carriage returns from a string.
 * @param s: the input string to trim
 * @return: trimmed version of the input string
 */
std::string trim(const std::string &s);

#endif