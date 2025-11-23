#include <iostream>
#include "core/file_io.h"
#include "core/chatbot.h"
#include "core/application.h"
#include "core/chat_corpus.h"

using std::cout;
using std::endl;

/* [CHATBOT.EXE COMPILATION]
g++ -I..\..\logs\include `
main.cpp `
core/chatbot.cpp `
core/state_handlers.cpp `
core/file_io.cpp `
core/application.cpp `
core/chat_corpus.cpp `
helpers/utils.cpp `
helpers/error_handling.cpp `
helpers/ui_display.cpp `
helpers/application_input.cpp `
models/home_loan.cpp `
models/car.cpp `
models/scooter.cpp `
models/personal_loan.cpp `
-o chatbot.exe
*/
//./chatbot.exe
int main()
{
    // Load all required data files
    if (!loadUtterances("output/Utterances.txt"))
    {
        cout << "Error: Could not load utterances. Exiting." << endl;
        return 1;
    }

    if (!loadLoanPlans("output/Home.txt"))
    {
        cout << "Error: Could not load home loan plans. Exiting." << endl;
        return 1;
    }

    if (!loadCarPlans("output/Car.txt"))
    {
        cout << "Error: Could not load car plans. Exiting." << endl;
        return 1;
    }

    if (!loadScooterPlans("output/Scooter.txt"))
    {
        cout << "Error: Could not load scooter plans. Exiting." << endl;
        return 1;
    }

    if (!loadPersonalPlans("output/Personal.txt"))
    {
        cout << "Error: Could not load personal loan plans. Exiting." << endl;
        return 1;
    }

    if (!loadChatCorpus("output/human_chat_corpus.txt"))
    {
        cout << "Warning: Could not load chat corpus. General conversation will be limited." << endl;
        // Don't exit - let it continue without general chat
    }
    // Load existing applications
    appManager.loadApplications("output/applications.txt");

    // Run the chatbot
    runChatbot();
    
    return 0;
}