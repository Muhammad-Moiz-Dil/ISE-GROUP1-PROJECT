// The entry point for the CLI program. Calls initialization, sets up the loop, and brings together all logic.

#include <iostream>
#include "../logs/include/chatbot.h"
#include "../logs/include/error_handling.h"
#include "../logs/include/file_io.h"
#include "../logs/include/utils.h"

int main() {
    
    // Initialize resources and read files
    if (!loadUtterances("data/Utterances.txt")) {
        handleFileError("Utterances.txt");
        return 1; // Clean exit on error
    }

    if (!loadLoanPlans("data/Home.txt")) {
        handleFileError("Home.txt");
        return 1;
    }

    // Main chatbot loop
    showWelcome();
    while (true) {
        std::string userInput = getUserInput();
        if (userInput == "X" || userInput == "x") {
            showGoodbye();
            break;
        }
        
        // Core chat logic (menu navigation and plan display)
        if (!handleUserInput(userInput)) {
            handleUnknownInput(userInput);
        }
    }

    cleanupResources(); // if you manage dynamic memory/files
    return 0;
}
