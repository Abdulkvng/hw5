#ifndef RECCHECK
#include <iostream>
#include <algorithm> 
#include <map>
#include <set>
#endif
// endif
#include "wordle.h"
#include "dict-eng.h"
using namespace std;

// ghelper func
void generateWords(std::string current, std::string floating, size_t index, const std::set<std::string>& dict, std::set<std::string>& results);
// genwords find each char return when full word found 

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{std::set<std::string> results; 
		generateWords(in, floating, 0, dict, results);
		return results; }

// create the helper func
void generateWords(std::string current, std::string floating, size_t index, const std::set<std::string>& dict, std::set<std::string>& results){
	if(index == current.size()){
		if(floating.empty() && dict.find(current)!= dict.end()){
			results.insert(current);}
            // results.inserts
		return;}
	size_t blanks = 0; 
	for(size_t i = index; i < current.size(); ++i){
		if(current[i] == '-'){
			++blanks;}}
            //size_t blanks = 0; 
	//for(size_t i = index; i < current.size(); ++i){
	//	if(current[i] == '-'){
		//	++blanks;}}

	if(floating.size() > blanks){
	return;}
		if(current[index] != '-'){
	generateWords(current, floating, index + 1, dict, results);
		return;}
	for(char c = 'a'; c <= 'z'; ++c){
        //ststd::string down =
				std::string down = current; 
				down[index] = c;
				std::string updated = floating; 
				bool isFloating = false; 

				for(size_t i = 0; i < floating.size(); i++){
					if(floating[i] == c){
						updated = floating.substr(0,i) + floating.substr(i+1);
						isFloating = true; 
						break;}	}

				if(isFloating){
					generateWords(down, updated, index+1, dict, results);}
				else{
					generateWords(down, floating,index + 1, dict, results);
				}
				//j[i] gen words 
                }}
