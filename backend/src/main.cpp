#include <iostream>
#include "../../logs/include/file_io.h"
#include "../../logs/include/chatbot.h"
#include "../../logs/include/application.h"

using std::cout;
using std::endl;

// Build Command (run while in src):
// For User: g++ -I..\..\logs\include main.cpp file_io.cpp chatbot.cpp utils.cpp application.cpp loan_plan.cpp car.cpp -o chatbot.exe
// For Lender: g++ -I..\..\logs\include lender_main.cpp application.cpp utils.cpp -o lender.exe
// Then run with: chatbot.exe / ./chatbot.exe (user), or lender.exe / ./lender.exe (lender) 

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

    if (!loadCarPlans("output/Car.txt"))
    {
        cout << "Chatbot could not load car plans. Exiting." << endl;
        return 1;
    }

    // NEW: Load applications (file may not exist initially - that's okay)
    appManager.loadApplications("output/applications.txt");

    runChatbot();
    return 0;
}
