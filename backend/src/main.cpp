#include <iostream>
#include "../../logs/include/file_io.h"
#include "../../logs/include/chatbot.h"
#include "../../logs/include/application.h"  // NEW: Include application header

using std::cout;
using std::endl;

// Build Command (run while in src):
// g++ -I../../logs/include main.cpp file_io.cpp chatbot.cpp utils.cpp application.cpp -o chatbot.exe; if ($?) { .\chatbot.exe }

int main()
{
    if (!loadUtterances("output/Utterances.txt"))
    {
        cout << "Chatbot could not load utterances. Exiting." << endl;
        return 1;
    }

    if (!loadLoanPlans("output/Home.txt"))
    {
        cout << "Chatbot could not load home plans. Exiting." << endl;
        return 1;
    }

    // NEW: Load applications (file may not exist initially - that's okay)
    appManager.loadApplications("output/applications.txt");

    runChatbot();
    return 0;
}
