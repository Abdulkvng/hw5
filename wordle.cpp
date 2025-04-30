// incase of debuggingg
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"

using namespace std;

// Helper function prototype
void generate_words(
const std::string& template_str,
const std::set<char> extra_chars,
    const std::set<std::string>& valid_words,
 unsigned int pos,
    std::set<std::string>& result_words);

// basically thr Main wordle function
std::set<std::string> wordle(
    const std::string& input,
    const std::string& floating_letters,
    const std::set<std::string>& dict_words)
{ std::set<char> unused_letters(floating_letters.begin(), floating_letters.end());
    std::set<std::string> output;
    generate_words(input, unused_letters, dict_words, 0, output);
    return output;}

// Recursionnnn
void generate_words(
    const std::string& template_str,
    const std::set<char> floating_chars,
const std::set<std::string>& valid_words,
unsigned int pos,
std::set<std::string>& result_words)
{
 std::string current_str = template_str;
std::string all_letters = "abcdefghijklmnopqrstuvwxyz";
const std::set<char> full_alpha(all_letters.begin(), all_letters.end());

    // Base case
    if (pos == current_str.size()) {
 if (floating_chars.empty() && valid_words.count(current_str)) {
 result_words.insert(current_str); }
 return; }

    // If dash is found, replace it
    if (current_str[pos] == '-') {
        // Use floating letters
        for (char ch : floating_chars) {
     current_str[pos] = ch;
     std::set<char> updated_floating = floating_chars;
     updated_floating.erase(ch);
     generate_words(current_str, updated_floating, valid_words, pos + 1, result_words); }

        // Try all letters if not already tried via floating
 for (char alpha : full_alpha) {
if (floating_chars.find(alpha) == floating_chars.end()) {
current_str[pos] = alpha;
generate_words(current_str, floating_chars, valid_words, pos + 1, result_words); } } }
 else {
 generate_words(current_str, floating_chars, valid_words, pos + 1, result_words);}}
