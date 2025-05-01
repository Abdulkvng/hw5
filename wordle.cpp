#include <algorithm>
#include <set>
#include <string>

using namespace std;

void generateWords(string current, string floating, size_t index, const set<string>& dict, set<string>& results);

set<string> wordle(const string& in, const string& floating, const set<string>& dict) {
    set<string> results;
    generateWords(in, floating, 0, dict, results);
    return results;}

void generateWords(string current, string floating, size_t index, const set<string>& dict, set<string>& results) {
    if (index == current.size()) {
        if (floating.empty() && dict.count(current)) {
            results.insert(current); }
 return; }

    if (current[index] != '-') { generateWords(current, floating, index + 1, dict, results);
        return; }

    // Count remaining blanks in one pass (Loop #1)
    size_t remainingBlanks = 0;
    for (size_t i = index + 1; i < current.size(); ++i) {
        if (current[i] == '-') remainingBlanks++; }

    // Try floating letters first (Loop #2)
    for (size_t i = 0; i < floating.size(); ++i) {
 char c = floating[i];
 string next = current;
 next[index] = c;
  string newFloating = floating;
 newFloating.erase(i, 1);
        generateWords(next, newFloating, index + 1, dict, results);
    }


// next = current;
           // next[index] = c;
          // generateWords(next, 
    // Try remaining letters only if there's space for floating letters (Loop #3)
    if (remainingBlanks >= floating.size()) {
        for (char c = 'a'; c <= 'z'; ++c) {
            if (floating.find(c) != string::npos) continue;
            string next = current;
            next[index] = c;
            generateWords(next, floating, index + 1, dict, results);} }}