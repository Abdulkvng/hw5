#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// gelper func
void generateWords(std::string current, std::string floating, size_t index, const std::set<std::string>& dict, std::set<std::string>& results);

//  wordle function
std::set<std::string> wordle(
const std::string& in,
 const std::string& floating,
    const std::set<std::string>& dict)
{std::set<std::string> results; 
		generateWords(in, floating, 0, dict, results);
		return results; }

// hleper functions
void generateWords(std::string current, std::string floating, size_t index, const std::set<std::string>& dict, std::set<std::string>& results) {
    if (index == current.size()) {
        if (floating.empty() && dict.find(current) != dict.end()) {
 results.insert(current); }
        return;}
if (current[index] != '-') {
 generateWords(current, floating, index + 1, dict, results);
   return;}

    // Try floating letters first
    for (size_t i = 0; i < floating.size(); ++i) {
     char c = floating[i];
     std::string next = current;
     next[index] = c;
     std::string newFloating = floating;
     newFloating.erase(i, 1);
     generateWords(next, newFloating, index + 1, dict, results); }

    // Try other letters only if theres room for remaining floating letters
    size_t remainingBlanks = 0;
    for (size_t i = index + 1; i < current.size(); ++i) {
 if (current[i] == '-') remainingBlanks++;}

    if (remainingBlanks >= floating.size()) {
    for (char c = 'a'; c <= 'z'; ++c) {
    if (floating.find(c) != std::string::npos) continue; // Skip floating letters (already tried)
 std::string next = current;
 next[index] = c;
generateWords(next, floating, index + 1, dict, results); } }}