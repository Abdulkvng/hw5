#include <set>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

void tryCharacter(size_t pos, string& current, const string& pattern,
 const vector<char>& floats, vector<bool>& used,
    const set<string>& dict, set<string>& results, char c);
void generateWords(size_t pos, string& current, const string& pattern,
                 const vector<char>& floats, vector<bool>& used,
                 const set<string>& dict, set<string>& results) {
    // Base case: if the word is completed 
    if (pos == pattern.size()) {

    bool allUsed = true;
    for (bool u : used) {
    if (!u) {
allUsed = false;
 break; } }
        if (allUsed && dict.find(current) != dict.end()) {
  results.insert(current); }
        return; }

    // Handle fixed position
    if (pattern[pos] != '-') {
 current[pos] = pattern[pos];
  generateWords(pos + 1, current, pattern, floats, used, dict, results);
        return; }

    // Try floating characters first
    for (size_t i = 0; i < floats.size(); ++i) {  // Loop #2
        if (!used[i]) {
     used[i] = true;
    current[pos] = floats[i];
            generateWords(pos + 1, current, pattern, floats, used, dict, results);
            used[i] = false; } }

    // Try other letters only if enough positions remain
    size_t remaining = pattern.size() - pos;
    size_t unused = 0;
    for (bool u : used) {  // Loop #3
        if (!u) unused++;}
    
    if (remaining > unused) {
        for (char c = 'a'; c <= 'z'; ++c) {  // Loop #4
     bool isFloating = false;
            for (char f : floats) {  // Loop #5
     if (f == c) {
    isFloating = true;
                    break;} }
            if (!isFloating) {
                current[pos] = c;
                generateWords(pos + 1, current, pattern, floats, used, dict, results);} } }
}

set<string> wordle(const string& in, const string& floating, const set<string>& dict) {
    set<string> results;
    string current = in;
    vector<char> floats;
    vector<bool> used(floating.size(), false);
    // Process floating characters (no loopppp)
    floats = vector<char>(floating.begin(), floating.end());

    generateWords(0, current, in, floats, used, dict, results);
    return results;
}