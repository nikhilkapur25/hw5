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


// Add prototypes of helper functions here
void wordleHelper(
  string& current, 
  const string& floating, 
  size_t floatingNeeded, 
  const set<string>& dict,
  set<string>& results, 
  size_t pos);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
  set<string> results;
  string current = in;

  wordleHelper(current, floating, floating.length(), dict, results, 0);
  return results;
    // Add your code here

}

void wordleHelper(
  string& current, 
  const string& floating, 
  size_t floatingNeeded, 
  const set<string>& dict,
  set<string>& results, 
  size_t pos) {

    if (pos == current.length()) {
      if(dict.find(current) != dict.end() && floatingNeeded == 0) {
        results.insert(current);
      }
      return;
    }

    if(current[pos] != '-') {
      bool letterIsFloating = false;
      for (size_t i = 0; i < floating.length(); i++) {
        if (current[pos] == floating[i] && floatingNeeded > 0) {
          letterIsFloating = true;
          break;
        }
      }
      if (letterIsFloating) {
        wordleHelper(current, floating, floatingNeeded - 1, dict, results, pos + 1);
        
      } else {
        wordleHelper(current, floating, floatingNeeded, dict, results, pos + 1);
      }
      return;
    }
  
    size_t blanksRemaining = 0; 
    for (size_t i = pos; i < current.length(); i++) {
      if(current[i] == '-') {
        blanksRemaining++;
      }
    }
    if (blanksRemaining < floatingNeeded) {
      return;
    }
    for (char c = 'a'; c <= 'z'; c++) {
      current[pos] = c;
      bool isFloatingLetter = false; 
      int floatingIdx = -1;

      for(size_t i = 0; i < floating.length(); i++) {
        if (c == floating[i]) {
          isFloatingLetter = true;
          floatingIdx = i;
          break;
        }
        
      }
      if (isFloatingLetter && floatingNeeded > 0) {
        string newFloating = floating;
        newFloating.erase(floatingIdx, 1); 
        wordleHelper(current, newFloating, floatingNeeded - 1, dict, results, pos + 1);
      }
      else if (blanksRemaining > floatingNeeded) {
        wordleHelper(current, floating, floatingNeeded, dict, results, pos + 1);
      }
    }
  current[pos] = '-';
  }

// Define any helper functions here
 