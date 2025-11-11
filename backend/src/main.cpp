#include <drogon/drogon.h>
#include <string>
#include <sstream>
#include "../../logs/include/file_io.h"

using namespace drogon;
using namespace std;

int main() {
    // Load data files
    if (!loadUtterances("src/output/Utterances.txt")) {
        cerr << "Chatbot could not load utterances. Exiting." << endl;
        return 1;
    }
    if (!loadLoanPlans("src/output/Home.txt")) {
        cerr << "Chatbot could not load home plans. Exiting." << endl;
        return 1;
    }

    // Set HTTP server address and port
    app().addListener("0.0.0.0", 18080);

    // CORS settings
    app().registerPostHandlingAdvice(
        [](const HttpRequestPtr& req, const HttpResponsePtr& resp) {
            resp->addHeader("Access-Control-Allow-Origin", "*");
            resp->addHeader("Access-Control-Allow-Methods", "POST, GET, OPTIONS");
            resp->addHeader("Access-Control-Allow-Headers", "Content-Type, Accept, X-Requested-With");
            resp->addHeader("Access-Control-Max-Age", "3600");
            resp->addHeader("Access-Control-Allow-Credentials", "true");
        });

    // Chat endpoint
    app().registerHandler(
        "/chat",
        [](const HttpRequestPtr& req,
           std::function<void(const HttpResponsePtr&)>&& callback) {
            // Handle OPTIONS for CORS preflight
            if (req->method() == Options) {
                auto resp = HttpResponse::newHttpResponse();
                callback(resp);
                return;
            }

            // Parse JSON body
            Json::Value jsonBody = *req->getJsonObject();
            string userInput = jsonBody["message"].asString();
            string state = jsonBody["state"].asString();
            string response;
            string newState = state;

            // Convert input to uppercase for case-insensitive comparison
            if (!userInput.empty()) {
                userInput[0] = toupper(userInput[0]);
            }

            // State machine
            if (state == "MAIN_MENU") {
                // First, check if the input matches any greeting in Utterances.txt
                string greetingResponse = uttrObj.getResponse(userInput);
                
                if (userInput == "A") {
                    response = uttrObj.getResponse("A");
                    newState = "LOAN_CATEGORY";
                } else if (userInput == "H") {
                    response = uttrObj.getResponse("H");
                    newState = "HOME_LOAN_AREA";
                } else if (userInput == "X") {
                    response = "Thank you for using our service. Goodbye!";
                    // Optionally, you might want to handle the exit condition here
                } else if (greetingResponse != "[No reply found]" && greetingResponse != uttrObj.getResponse("*")) {
                    // If we found a specific greeting response, use it
                    response = greetingResponse;
                } else {
                    // Default response for unrecognized input in main menu
                    response = uttrObj.getResponse("*");
                }
            }
            else if (state == "LOAN_CATEGORY") {
                if (userInput == "H") {
                    response = uttrObj.getResponse("H");
                    newState = "HOME_LOAN_AREA";
                } else if (userInput == "C" || userInput == "S" || userInput == "P") {
                    response = "Coming soon!";
                    newState = "MAIN_MENU";
                } else if (userInput == "X") {
                    response = "Returning to main menu.";
                    newState = "MAIN_MENU";
                } else {
                    response = "Invalid input. Please press H, C, S, P, or X to exit.";
                }
            }
            else if (state == "HOME_LOAN_AREA") {
                if (userInput == "1" || userInput == "2" || userInput == "3" || userInput == "4") {
                    // Get the area details from the LoanPlanManager
                    string areaName = "Area " + userInput;
                    string areaDetails = LoanPlanManagerObj.getLoanPlanDetails(areaName);
                    
                    if (!areaDetails.empty()) {
                        response = "Home Loan Details for " + areaName + ":\n" + areaDetails;
                        response += "\nType 'A' to apply for another loan or 'X' to exit.";
                    } else {
                        response = "Could not find details for " + areaName + ". Please try another area (1-4).";
                    }
                    newState = "MAIN_MENU";
                } else {
                    response = "Invalid area selection. Please select an area between 1 and 4.";
                    newState = "HOME_LOAN_AREA";
                }
            }
            // Add other state handlers here...

            // Prepare response
            Json::Value jsonResp;
            jsonResp["response"] = response;
            jsonResp["newState"] = newState;

            auto resp = HttpResponse::newHttpJsonResponse(jsonResp);
            callback(resp);
        },
        {Post, Options});

    // Start the server
    cout << "Server running on http://0.0.0.0:18080" << endl;
    app().run();

    return 0;
}