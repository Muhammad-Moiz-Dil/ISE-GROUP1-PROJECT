using namespace std;
#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H

// Prints a message when a file cannot be loaded
void handleFileError(const string& fileName);

// Handles unrecognized or invalid user input
void handleUnknownInput(const string& input);

// Prints a closing goodbye message
void showGoodbye();


#endif // ERROR_HANDLING_H
