#ifndef WORDLE_H
#define WORDLE_H

#ifndef RECCHECK
#include <string>
#include <set>
#endif

/**
 * Generates all valid words based on the pattern, floating letters, and dictionary.
 * 
 * @param in The input string containing letters and '-' for blanks.
 * @param floating A string containing all the floating letters that must be used.
 * @param dict A set containing all valid English words.
 * @return A set of strings containing all valid words that match the criteria.
 */
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict);

#endif // WORDLE_H
