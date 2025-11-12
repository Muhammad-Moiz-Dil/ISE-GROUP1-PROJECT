#include <iostream>
#include "../../logs/include/file_io.h"
#include "../../logs/include/chatbot.h"

using std::cout;
using std::endl;

// Build Command (run while in src): 
// g++ -I../../logs/include main.cpp file_io.cpp chatbot.cpp utils.cpp -o main.exe; if ($?) { .\main.exe }

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

    runChatbot();

    return 0;
}