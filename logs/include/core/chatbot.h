#ifndef CHATBOT_H
#define CHATBOT_H

#include "application.h"
#include <string>
using std::string;

/**
 * Main chatbot loop that handles user interaction and state management.
 * Manages conversation flow through MAIN_MENU, LOAN_CATEGORY, and
 * HOME_LOAN_AREA states.
 * @return void
 */
void runChatbot();

#endif