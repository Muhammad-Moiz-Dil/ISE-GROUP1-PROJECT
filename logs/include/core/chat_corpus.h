#ifndef CHAT_CORPUS_H
#define CHAT_CORPUS_H

#include <string>
#include <vector>

using std::string;
using std::vector;

// Structure to hold conversation pairs
struct ConversationPair {
    string human1;  // Question
    string human2;  // Response
};

class ChatCorpus {
private:
    vector<ConversationPair> conversations;
    
    // Helper functions
    vector<string> tokenize(const string& text);
    double calculateIoU(const string& input, const string& corpusText);
    
public:
    // Load corpus from file
    bool loadCorpus(const string& filepath);
    
    // Get response based on IoU matching
    string getResponse(const string& userInput);
    
    // Check if corpus is loaded
    bool isLoaded() const;
};

#endif