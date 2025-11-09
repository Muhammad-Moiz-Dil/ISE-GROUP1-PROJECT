#include "../../logs/include/file_io.h"
#include <fstream>
#include <iostream>
using namespace std;

bool  loadUtterances(string filePath)
{
    Utterance uttrObj;
    ifstream readData;

    readData.open("Utterances.txt");
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
    readData.close();
    return true;
}

// Dummy implementation for completeness (reuse later)
