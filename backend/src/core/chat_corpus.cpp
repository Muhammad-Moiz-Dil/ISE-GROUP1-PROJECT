#include "core/chat_corpus.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <set>
#include <cctype>

// Tokenize function - space se split karo
std::vector<std::string> ChatCorpus::tokenize(const std::string &text)
{
    std::vector<std::string> tokens;
    std::stringstream ss(text);
    std::string token;

    while (ss >> token)
    {
        // Convert to lowercase
        std::transform(token.begin(), token.end(), token.begin(), ::tolower);
        
        // Remove punctuation (ADD THIS PART)
        token.erase(std::remove_if(token.begin(), token.end(), ::ispunct), token.end());
        
        // Only add non-empty tokens
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }
    return tokens;
}

// IoU calculation
double ChatCorpus::calculateIoU(const std::string &input, const std::string &corpusText)
{
    auto tokens1 = tokenize(input);
    auto tokens2 = tokenize(corpusText);

    std::set<std::string> set1(tokens1.begin(), tokens1.end());
    std::set<std::string> set2(tokens2.begin(), tokens2.end());

    // Intersection
    std::set<std::string> intersection;
    std::set_intersection(set1.begin(), set1.end(),
                          set2.begin(), set2.end(),
                          std::inserter(intersection, intersection.begin()));

    // Union
    std::set<std::string> unionSet;
    std::set_union(set1.begin(), set1.end(),
                   set2.begin(), set2.end(),
                   std::inserter(unionSet, unionSet.begin()));

    if (unionSet.empty())
        return 0.0;

    return static_cast<double>(intersection.size()) / unionSet.size();
}

// Load corpus from file
bool ChatCorpus::loadCorpus(const std::string &filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open())
        return false;

    std::string line;
    std::string currentHuman1;

    while (std::getline(file, line))
    {
        if (line.find("Human 1:") == 0)
        {
            currentHuman1 = line.substr(9); // Remove "Human 1: "
        }
        else if (line.find("Human 2:") == 0 && !currentHuman1.empty())
        {
            std::string human2 = line.substr(9); // Remove "Human 2: "
            conversations.push_back({currentHuman1, human2});
            currentHuman1.clear();
        }
    }

    file.close();
    return !conversations.empty();
}

// Get best matching response
std::string ChatCorpus::getResponse(const std::string &userInput)
{
    if (conversations.empty())
    {
        return "I'm not sure how to respond to that.";
    }

    double maxIoU = 0.0;
    std::string bestResponse;

    for (const auto &pair : conversations)
    {
        double iou = calculateIoU(userInput, pair.human1);
        if (iou > maxIoU)
        {
            maxIoU = iou;
            bestResponse = pair.human2;
        }
    }

    // Threshold check - agar IoU bahut kam hai toh generic response
    if (maxIoU < 0.1)
    {
        return "I'm not quite sure what you mean. Could you rephrase that?";
    }

    return bestResponse;
}

bool ChatCorpus::isLoaded() const
{
    return !conversations.empty();
}