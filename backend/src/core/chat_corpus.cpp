#include "core/chat_corpus.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <set>
#include <cctype>
#include <iostream>

using std::ifstream;
using std::set;
using std::string;
using std::stringstream;
using std::vector;

// Global instance definition
ChatCorpus chatCorpusObj;

// ==================== PRIVATE HELPERS ====================

vector<string> ChatCorpus::tokenize(const string &text) const
{
    vector<string> tokens;
    stringstream ss(text);
    string token;

    while (ss >> token)
    {
        // Convert to lowercase
        std::transform(token.begin(), token.end(), token.begin(), [](unsigned char c) 
        { return static_cast<char>(std::tolower(c)); });

        // Remove punctuation AND control characters (\r, \n, etc.)
        token.erase(std::remove_if(token.begin(), token.end(), [](unsigned char c)
        {
            return std::ispunct(c) || std::iscntrl(c);
        }),
        token.end());

        // 3. Only add non-empty tokens
        if (!token.empty())
        {
            tokens.push_back(token);
        }
    }

    return tokens;
}

double ChatCorpus::calculateIoU(const string &input, const string &corpusText) const
{
    vector<string> tokens1 = tokenize(input);
    vector<string> tokens2 = tokenize(corpusText);

    set<string> set1(tokens1.begin(), tokens1.end());
    set<string> set2(tokens2.begin(), tokens2.end());

    // Intersection
    set<string> intersection;
    std::set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), std::inserter(intersection, intersection.begin()));

    // Union
    set<string> unionSet;
    std::set_union(set1.begin(), set1.end(), set2.begin(), set2.end(), std::inserter(unionSet, unionSet.begin()));

    if (unionSet.empty())
    {
        return 0.0;
    }

    return static_cast<double>(intersection.size()) / static_cast<double>(unionSet.size());
}

// ==================== PUBLIC METHODS ====================

bool ChatCorpus::loadCorpus(const string &filepath)
{
    ifstream file(filepath);
    if (!file.is_open())
    {
        return false;
    }

    string line;
    string currentHuman1;

    while (std::getline(file, line))
    {
        // Handle Windows line endings explicitly for the raw line too
        if (!line.empty() && line.back() == '\r')
        {
            line.pop_back();
        }

        if (line.find("Human 1:") == 0)
        {
            // Remove "Human 1: "
            currentHuman1 = line.substr(9);
        }
        else if (line.find("Human 2:") == 0 && !currentHuman1.empty())
        {
            // Remove "Human 2: "
            string human2 = line.substr(9);

            ConversationPair pair;
            pair.human1 = currentHuman1;
            pair.human2 = human2;

            conversations.push_back(pair);
            currentHuman1.clear();
        }
    }

    file.close();
    return !conversations.empty();
}

string ChatCorpus::getResponse(const string &userInput)
{
    if (conversations.empty())
    {
        return "I'm not sure how to respond to that (Knowledge base empty).";
    }

    double maxIoU = 0.0;
    string bestResponse;

    for (const ConversationPair &pair : conversations)
    {
        double iou = calculateIoU(userInput, pair.human1);

        // Debug print (Uncomment if you still have issues)
        // std::cout << "User: " << userInput << " | Corpus: " << pair.human1 << " | IoU: " << iou << std::endl;

        if (iou > maxIoU)
        {
            maxIoU = iou;
            bestResponse = pair.human2;
        }
    }

    // Threshold check
    const double MIN_IOU_THRESHOLD = 0.30;
    if (maxIoU < MIN_IOU_THRESHOLD)
    {
        return "I'm not sure how to respond to that.";
    }

    return bestResponse;
}

bool ChatCorpus::isLoaded() const
{
    return !conversations.empty();
}