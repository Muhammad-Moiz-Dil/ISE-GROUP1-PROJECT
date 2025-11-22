#include <iostream>
#include "core/file_io.h"
#include "core/chatbot.h"
#include "core/application.h"

using std::cout;
using std::endl;

/* [CHATBOT.EXE COMPILATION]
g++ -I..\..\logs\include ^
main.cpp ^
core\chatbot.cpp ^
core\state_handlers.cpp ^
core\file_io.cpp ^
core\application.cpp ^
helpers\utils.cpp ^
helpers\error_handling.cpp ^
helpers\ui_display.cpp ^
helpers\application_input.cpp ^
models\home_loan.cpp ^
models\car.cpp ^
models\scooter.cpp ^
-o chatbot.exe
*/

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

    // Load existing applications
    appManager.loadApplications("output/applications.txt");

    // Run the chatbot
    runChatbot();
    
    return 0;
}