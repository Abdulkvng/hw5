#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"

using namespace std;

void try_floating_letters(
 const std::string& pattern,
  const std::set<char>& remaining_floats,
 const std::set<std::string>& dictionary,
  unsigned int idx,
 std::set<std::string>& results,
 std::string candidate,
    std::set<char>::iterator it);

void try_nonfloating_letters(
    const std::string& pattern,
    const std::set<char>& remaining_floats,
    const std::set<std::string>& dictionary,
    unsigned int idx,
    std::set<std::string>& results,
    std::string candidate,
    char current_char);

void generate_combinations(
   const std::string& pattern,
  const std::set<char>& remaining_floats,
  const std::set<std::string>& dictionary,
 unsigned int idx,
    std::set<std::string>& results)
{
    if (idx == pattern.size()) {
 if (remaining_floats.empty() && dictionary.find(pattern) != dictionary.end()) {
 results.insert(pattern);}
        return; }

std::string candidate = pattern;
if (pattern[idx] == '-') {
   try_floating_letters(pattern, remaining_floats, dictionary, idx, results, candidate, remaining_floats.begin());
    } else {   generate_combinations(candidate, remaining_floats, dictionary, idx + 1, results);}}

void try_floating_letters(
    const std::string& pattern,
    const std::set<char>& remaining_floats,
    const std::set<std::string>& dictionary,
    unsigned int idx,
    std::set<std::string>& results,
    std::string candidate,
    std::set<char>::iterator it)
{if (it == remaining_floats.end()) {
        // Done with floating chars, try non-floating starting with 'a''
        try_nonfloating_letters(pattern, remaining_floats, dictionary, idx, results, pattern, 'a');
        return;}
    char ch = *it;
    std::set<char> updated_floats = remaining_floats;
    updated_floats.erase(ch);
    candidate[idx] = ch;
    generate_combinations(candidate, updated_floats, dictionary, idx + 1, results);
    try_floating_letters(pattern, remaining_floats, dictionary, idx, results, pattern, std::next(it));}

void try_nonfloating_letters(
    const std::string& pattern,
    const std::set<char>& remaining_floats,
    const std::set<std::string>& dictionary,
    unsigned int idx,
    std::set<std::string>& results,
    std::string candidate,
    char current_char)
{if (current_char > 'z') {
        return; }

 if (remaining_floats.find(current_char) == remaining_floats.end()) {
candidate[idx] = current_char;
generate_combinations(candidate, remaining_floats, dictionary, idx + 1, results);}
    // Recursionnn
    try_nonfloating_letters(pattern, remaining_floats, dictionary, idx, results, pattern, current_char + 1);}

std::set<std::string> wordle(
    const std::string& input_pattern,
    const std::string& float_chars,
    const std::set<std::string>& dictionary)
{ std::set<char> float_set(float_chars.begin(), float_chars.end());
 std::set<std::string> result_words;
    generate_combinations(input_pattern, float_set, dictionary, 0, result_words);
    return result_words;}