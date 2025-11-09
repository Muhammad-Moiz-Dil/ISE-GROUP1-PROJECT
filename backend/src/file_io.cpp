#include "../../logs/include/file_io.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
using namespace std;

Utterance uttrObj;
LoanPlanManager LoanPlanManagerObj;
bool loadUtterances(string filePath)
{
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

            uttrObj.setResponse(userInput, resposne);
        }
    }
    readData.close();
    return true;
}
bool loadLoanPlans(string filePath)
{
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
            stringstream ss(line);
            string area, size, instStr, priceStr, dpStr;

            getline(ss, area, '#');
            getline(ss, size, '#');
            getline(ss, instStr, '#');
            getline(ss, priceStr, '#');
            getline(ss, dpStr, '#');

            LoanPlan lp;
            lp.setSize(size);
            lp.setDownPayment(dpStr);
            lp.setInstallments(instStr);
            lp.setprice(priceStr);

            LoanPlanManagerObj.setArea(area, lp);
        }
    }
    readData.close();
    return true;
}
