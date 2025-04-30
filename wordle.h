#ifndef WORDLE_H
#define WORDLE_H

#include <set>
#include <string>

/**
 * @brief Returns the list of all legal words in the provided dictionary
 *        that meet the criteria provided in the `in` and `floating`
 *        inputs.
 * 
 * @param [in] in - string of fixed, correct characters and `-`s to indicate
 *                  the length of string and locations that must be filled in
 * @param [in] floating  - Characters that must be used somewhere in the word
 * @param [in] dict - Dictionary of strings of legal words
 * @return std::set<std::string> - Set of all words that meet the criteria
 */
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict);

/**
 * @brief Recursive helper function to generate words by replacing '-' 
 *        with valid floating and non-floating characters.
 * 
 * @param template_str - The current string being built
 * @param floating_chars - Characters that must be used somewhere in the word
 * @param valid_words - The set of valid words in the dictionary
 * @param pos - Current position being processed
 * @param result_words - Set that stores the generated words that meet the criteria
 */
void generate_words(
    const std::string& template_str,
    const std::set<char> floating_chars,
    const std::set<std::string>& valid_words,
    unsigned int pos,
    std::set<std::string>& result_words);

#endif // WORDLE_H
