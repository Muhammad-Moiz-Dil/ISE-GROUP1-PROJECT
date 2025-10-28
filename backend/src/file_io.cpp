#include "../../logs/include/file_io.h"
#include <fstream>
#include <iostream>
using namespace std;

// Make space for global vectors
vector<Utterance> utterancesList;
vector<LoanPlan> loanPlans;

bool loadUtterances(const string &filePath)
{
    utterancesList.clear();

    ifstream utterancesFile;
    utterancesFile.open(filePath.c_str());

    if (!utterancesFile)
    {
        cout << "Error: Could not open " << filePath << endl;
        return false;
    }

    string line;
    while (getline(utterancesFile, line))
    {
        string inp = "", out = "";
        bool foundHash = false;

        for (int i = 0; i < line.size(); ++i)
        {
            if (!foundHash && line[i] == '#')
            {
                foundHash = true;
                continue;
            }

            if (!foundHash)
                inp += line[i];
            else
                out += line[i];
        }

        if (!inp.empty() || !out.empty())
        {
            Utterance newUtterance;
            newUtterance.setUserInput(inp);
            newUtterance.setResponse(out);
            utterancesList.push_back(newUtterance);
        }
    }
    utterancesFile.close();
    return true;
}

// Dummy implementation for completeness (reuse later)
bool loadLoanPlans(const string &filePath)
{
    loanPlans.clear();
    // Implement similarly later as above
    return true;
}
