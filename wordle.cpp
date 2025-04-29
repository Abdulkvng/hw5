#include <set>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

void generateCombinations(size_t pos, string& current, const string& pattern,
               vector<int>& floatIndices, size_t nextFloat,
       const unordered_map<char, int>& floatCount,
           const string& uniqueFloats, const set<string>& dict,
          set<string>& results) {
    // Base case: completed the word
    if (pos == pattern.size()) {
     if (dict.find(current) != dict.end()) {
      results.insert(current); }
        return; }
    if (pattern[pos] != '-') {
 current[pos] = pattern[pos];
        generateCombinations(pos + 1, current, pattern, floatIndices, nextFloat,
     floatCount, uniqueFloats, dict, results);
        return; }

    // Try floating characters first
    if (nextFloat < floatIndices.size()) {
        int floatPos = floatIndices[nextFloat];
        for (size_t i = 0; i < uniqueFloats.size(); ++i) {
 char c = uniqueFloats[i];
  if (floatCount.at(c) > 0) {
    current[pos] = c;
  floatIndices[nextFloat] = pos;
 generateCombinations(pos + 1, current, pattern, floatIndices, nextFloat + 1,
    floatCount, uniqueFloats, dict, results); } }
        floatIndices[nextFloat] = floatPos; 
        return; }

    // Try all other letters
    for (char c = 'a'; c <= 'z'; ++c) {
        if (floatCount.find(c) == floatCount.end()) {
            current[pos] = c;
   generateCombinations(pos + 1, current, pattern, floatIndices, nextFloat,
        floatCount, uniqueFloats, dict, results); }  }
}

set<string> wordle(const string& in, const string& floating, const set<string>& dict) {
    set<string> results;
    if (in.empty()) return results;

    unordered_map<char, int> floatCount;
    string uniqueFloats;
    for (char c : floating) {
        if (floatCount[c]++ == 0) {
    uniqueFloats += c; }  }

    vector<int> floatIndices(floating.size(), -1);
    string current = in;
    generateCombinations(0, current, in, floatIndices, 0, floatCount, uniqueFloats, dict, results);
    return results;
}