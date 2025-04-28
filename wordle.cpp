#include <set>
#include <string>

using namespace std;

void generateWords(int index, string current, const string& in, string floating,
    const set<string>& dict, set<string>& result);

void tryChar(int index, string current, const string& in, string floating,
    const set<string>& dict, set<string>& result, char c) {
    // Remove the used character from floating if present
    size_t pos = floating.find(c);
    if (pos != string::npos) { floating.erase(pos, 1);}
    generateWords(index + 1, current + c, in, floating, dict, result);}
// try an allphabet
void tryAlphabet(int index, string current, const string& in, string floating,
             const set<string>& dict, set<string>& result, char c) {
             if (c > 'z') return;
    
    // Only try this character if it's not in floating
    if (floating.find(c) == string::npos) { tryChar(index, current, in, floating, dict, result, c);}
    //  then Try next character
tryAlphabet(index, current, in, floating, dict, result, c + 1);}

void generateWords(int index, string current, const string& in, string floating,
                  const set<string>& dict, set<string>& result) {
    // Base case:  first complete word
    if (index == static_cast<int>(in.size())) {
if (floating.empty() && dict.find(current) != dict.end()) {
    result.insert(current); }
            return;}

    // Handle fixed position
    if (in[index] != '-') {
        generateWords(index + 1, current + in[index], in, floating, dict, result);
        return;  }

    // recursionnnnnnnnnn
    if (!floating.empty()) {
        tryChar(index, current, in, floating, dict, result, floating[0]);
        if (floating.size() > 1) {
            generateWords(index, current, in, floating.substr(1), dict, result); }}

    int remaining_positions = static_cast<int>(in.size()) - (index + 1);
    if (remaining_positions >= static_cast<int>(floating.size())) {
        tryAlphabet(index, current, in, floating, dict, result, 'a'); }}

set<string> wordle(const string& in, const string& floating, const set<string>& dict) {
    set<string> result;
    generateWords(0, "", in, floating, dict, result);
    return result;
}