#include <iostream>
#include "../../logs/include/file_io.h"
using namespace std;

int main()
{
    // Load the utterances file into utterancesList at the very start
    if (!loadUtterances("../data/Utterances.txt"))
    {
        cout << "Chatbot could not load utterances. Exiting." << endl;
        return 1;
    }

    cout << "Chatbot ready! Type your message (X to exit)." << endl;

    // Main Chat Loop
    while (true)
    {
        cout << "> ";
        string userInput;
        getline(cin, userInput);

        // Exit condition
        if (userInput == "X" || userInput == "x")
            break;

        // Find a matching response
        bool found = false;
        string defaultResponse = "";
        for (int i = 0; i < utterancesList.size(); ++i)
        {
            // Store defaultResponse if trigger is '*'
            if (utterancesList[i].getUserInput() == "*")
                defaultResponse = utterancesList[i].getResponse();

            // Direct match
            if (utterancesList[i].getUserInput() == userInput)
            {
                cout << utterancesList[i].getResponse() << endl;
                found = true;
                break;
            }
        }

        // If no match, use defaultResponse
        if (!found && defaultResponse != "")
            cout << defaultResponse << endl;
    }

    cout << "Chatbot session ended." << endl;
    return 0;
}
