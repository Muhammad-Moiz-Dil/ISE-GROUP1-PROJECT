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
        if (s[i] != ',' && s[i] != ' ')
        {
            result += s[i];
        }
    }

    return result;
}
