#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    //we must return a set of strings
    //a set class is like a list but each value can appear just once
    //taking a string of many words and splitting it into individual keyword 
    //if punctuation split, conver to lowercase, only get words with at least 2 words

    //make a set to store the words
    std::set<std::string> words;
    //make a string to have a current point
    std::string current;

    //covert everything to lowercase
    rawWords = convToLower(rawWords);

    //make a loop to go thru the word
    for (size_t i = 0; i < rawWords.size(); i++) 
    {
      char c = rawWords[i];
      //check if it's a letter (only lowercase is necesarry)
      if(c >= 'a' && c <= 'z')
      {
        //then you can add it to the current 
        current += c;
      }
      else
      {
        //other wise it should separated it (needs to be a word(2 or bigger))
        if(current.length() >= 2)
        {
          //then it is a word
          words.insert(current);
        }
        //now reset the current word, to detatch from the others
        current.clear();
      }
    }
    //should be at the end (check the 2 word requirment)
    if(current.length() >= 2)
    {
      //then it is a word
      words.insert(current);
    }
    
    return words;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
