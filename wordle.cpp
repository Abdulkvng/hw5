#include <set>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

void generateWords(int index, string current, const string& in, string floating, const set<string>& dict, set<string>& result) {
    if (index == in.size()) {
        if (floating.empty() && dict.find(current) != dict.end()) {
            result.insert(current);}
        return;}

if (in[index] != '-') {
        // Fixed position, must use this character
        generateWords(index + 1, current + in[index], in, floating, dict, result);} else {
        // Try each floating letter first
    for (size_t i = 0; i < floating.size(); ++i) {
            char c = floating[i];
            string new_floating = floating.substr(0, i) + floating.substr(i + 1);
            generateWords(index + 1, current + c, in, new_floating, dict, result);}
        int remaining_positions = in.size() - (index + 1);
        if (remaining_positions >= (int)floating.size()) {
for (char c = 'a'; c <= 'z'; ++c) {
    if (floating.find(c) == string::npos) {
                    generateWords(index + 1, current + c, in, floating, dict, result); } }}}}

set<string> wordle(const string& in, const string& floating, const set<string>& dict) {
    set<string> result;
    generateWords(0, "", in, floating, dict, result);
    return result; }
