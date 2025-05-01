#ifndef RECCHECK
#include <iostream>
#include <algorithm> 
#include <map>
#include <set>
#endif

// maybe iostream cause for for loop count??
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
void generateWords(std::string current, std::string floating, size_t index, const std::set<std::string>& dict, std::set<std::string>& results){
	if(index == current.size()){
		if(floating.empty() && dict.find(current)!= dict.end()){
			results.insert(current);}
		return;}
	size_t blanks = 0; 
	for(size_t i = index; i < current.size(); ++i){
		if(current[i] == '-'){
			++blanks;}}

	if(floating.size() > blanks){
		return; }
		if(current[index] != '-'){
		generateWords(current, floating, index + 1, dict, results);
		return;}
	for(char c = 'a'; c <= 'z'; ++c){
std::string down = current; 
	down[index] = c;
				
std::string updated = floating; 
bool isFloating = false; 

for(size_t i = 0; i < floating.size(); i++){
if(floating[i] == c){
updated = floating.substr(0,i) + floating.substr(i+1);
	isFloating = true; 
break;}			}

			if(isFloating){generateWords(down, updated, index+1, dict, results);
				} else{ generateWords(down, floating,index + 1, dict, results);}}}
