#ifndef CHAT_CORPUS_H
#define CHAT_CORPUS_H

#include <string>
#include <vector>

using std::string;
using std::vector;

/**
 * @brief Represents a simple pair of human utterances in the corpus
 * 
 * Each pair links a user-like message (human1) to a response (human2).
 */
struct ConversationPair
{
    string human1;  ///< Input-like text (Question/Prompt)
    string human2;  ///< Response text (Answer/Reply)
};

/**
 * @brief ChatCorpus handles IoU-based matching using a human conversation corpus
 * 
 * The corpus is loaded from a file containing lines in the format:
 *   "Human 1: <text>"
 *   "Human 2: <text>"
 * 
 * For a given user input, it finds the most similar "Human 1" line by
 * Intersection-over-Union (IoU) over token sets, and returns the paired "Human 2".
 */
class ChatCorpus
{
private:
    vector<ConversationPair> conversations; ///< Loaded conversation pairs

    /**
     * @brief Splits text into lowercase tokens, removing punctuation and control chars
     * @param text Input text
     * @return Vector of cleaned tokens
     */
    vector<string> tokenize(const string &text) const;

    /**
     * @brief Calculates IoU between user input and a corpus text
     * 
     * IoU is computed as:
     *   |intersection(tokens1, tokens2)| / |union(tokens1, tokens2)|
     * 
     * @param input User input text
     * @param corpusText Text from corpus (Human 1 side)
     * @return IoU score in range [0, 1]
     */
    double calculateIoU(const string &input, const string &corpusText) const;

public:
    /**
     * @brief Default constructor
     */
    ChatCorpus() = default;

    /**
     * @brief Loads conversation corpus from file
     * 
     * File format:
     *   Human 1: <text>
     *   Human 2: <text>
     * 
     * Every "Human 1" line must be followed by a "Human 2" line to form a pair.
     * 
     * @param filepath Path to corpus file
     * @return true if at least one pair is loaded, false otherwise
     */
    bool loadCorpus(const string &filepath);

    /**
     * @brief Gets best-matching response for user input
     * 
     * Uses IoU over token sets to find the closest "Human 1" entry.
     * If the best IoU is below a small threshold, returns a generic reply.
     * 
     * @param userInput Raw user input text
     * @return Response text (either best Human 2 or generic fallback)
     */
    string getResponse(const string &userInput);

    /**
     * @brief Checks if any conversations are loaded
     * @return true if corpus is loaded, false otherwise
     */
    bool isLoaded() const;
};

/**
 * @brief Global ChatCorpus instance for general conversation
 * 
 * This is the single instance used by state handlers and file loaders.
 * It replaces the conflicting definitions from file_io and chat_corpus.cpp.
 */
extern ChatCorpus chatCorpusObj;

#endif // CHAT_CORPUS_H