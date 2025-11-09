#include "../../logs/include/file_io.h"
#include <fstream>
#include <iostream>
using namespace std;

bool loadUtterances(const string &filePath)
{
    Utterance uttrObj;
    ifstream readData;

    readData.open(filePath);
    if (!readData.is_open())
    {
        cout << "File not opened." << endl;
        return false;
    }
    else
    {
        string line;
        while (getline(readData, line))
        {
            int pos = line.find('#');
            string userInput = line.substr(0, pos);
            string resposne = line.substr(pos + 1);

            uttrObj.setResponse(userInput,resposne);
        }
    }
}

// Dummy implementation for completeness (reuse later)
bool loadLoanPlans(const string &filePath)
{
    
}
