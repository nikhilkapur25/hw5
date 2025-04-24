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
  std::string& current,
  std::map<char, int>& floatingMap,
  int floatingNeeded,
  const std::set<std::string>& dict,
  std::set<std::string>& results,
  size_t pos);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
  set<string> results;
  string current = in;
  std::map<char, int> floatingMap;
  for(char c : floating) {
    floatingMap[c]++;
  }

  wordleHelper(current, floatingMap, floating.length(), dict, results, 0);
  return results;
    // Add your code here

}

void wordleHelper(
  string& current, 
  std::map<char, int>& floatingMap, 
  int floatingNeeded, 
  const set<string>& dict,
  set<string>& results, 
  size_t pos) {
    if (pos == current.length()) {
      if (floatingNeeded == 0 && dict.find(current) != dict.end()) {
        results.insert(current);
      }
      return;
    }

    if (current[pos] != '-') {
      wordleHelper(current, floatingMap, floatingNeeded, dict, results, pos+1);
      return;
    }

    int blanksRemaining = 0;
    for(size_t i = pos; i < current.length(); ++i) {
      if (current[i] == '-') blanksRemaining++;

    }
    if (blanksRemaining < floatingNeeded) {
      return;
    }

    for (char c = 'a'; c <= 'z'; c++) {
      current[pos] = c;
      if (floatingMap[c] > 0) {
        floatingMap[c] --;
        wordleHelper(current, floatingMap, floatingNeeded - 1, dict, results, pos+1);
        floatingMap[c]++;
      }
      else if (blanksRemaining > floatingNeeded) {
        wordleHelper(current, floatingMap, floatingNeeded, dict, results, pos+1);
    }
   
    
    }
    current[pos] = '-';
  
  }

// Define any helper functions here
 