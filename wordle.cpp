// incase of debugging
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"

using namespace std;


//helper func
void generate_combinations(
    const std::string& pattern,
    const std::set<char> remaining_floats,
    const std::set<std::string>& dictionary,
    unsigned int idx,
  std::set<std::string>& results);

std::set<std::string> wordle(
    const std::string& input_pattern,
    const std::string& float_chars,
    const std::set<std::string>& dictionary)
{ std::set<char> float_set(float_chars.begin(), float_chars.end());
    std::set<std::string> result_words;
generate_combinations(input_pattern, float_set, dictionary, 0, result_words);
return result_words;}
// generating combinations 
void generate_combinations(
    const std::string& pattern,
    const std::set<char> remaining_floats,
    const std::set<std::string>& dictionary,
    unsigned int idx,
    std::set<std::string>& results)
{
 std::string candidate = pattern;
std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
 std::set<char> letters(alphabet.begin(), alphabet.end());

if (idx == candidate.length()) {
if (remaining_floats.empty() && dictionary.find(candidate) != dictionary.end()) {
   results.insert(candidate);}
 return;  }
// floattt
    if (candidate[idx] == '-') {
        std::set<char>::iterator float_it = remaining_floats.begin();
 while (float_it != remaining_floats.end()) {
char chosen = *float_it;
candidate[idx] = chosen;
std::set<char> updated_floats = remaining_floats;
  updated_floats.erase(chosen);
 generate_combinations(candidate, updated_floats, dictionary, idx + 1, results);
++float_it;  }

 std::set<char>::iterator letter_it = letters.begin();
while (letter_it != letters.end()) {
    char option = *letter_it;
if (remaining_floats.find(option) == remaining_floats.end()) {
 candidate[idx] = option;
    generate_combinations(candidate, remaining_floats, dictionary, idx + 1, results); }
            ++letter_it; }} 
            else {
generate_combinations(candidate, remaining_floats, dictionary, idx + 1, results); }
}
