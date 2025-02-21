#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
  //help to perform searching 
  //should run in O(nlog(n))

  //hint1: declare an iterator for set<T>, must have the type with the keyword 
  //typename set<T>::iterator it

  //hint2: if you are iterating over a container with iterators,
  //you should NOT modify the content as you iterate 

  //create the set 
  std::set<T> results; 


  //to go faster look at the smaller one first .size()
  if(s1.size() < s2.size())
  {
    //go thru a loop 
    //hint1: declare an iterator for set<T>, must have the type with the keyword 
    //typename set<T>::iterator it
    for(typename std::set<T>::iterator i1 = s1.begin(); i1 != s1.end(); i1++)
    {
      //lookup 
      if(s2.find(*i1) != s2.end())
      {
        //if it is good, insert it 
        results.insert(*i1);
      }
    }
  }
  else
  {
    //look up for s2
    for(typename std::set<T>::iterator i2 = s2.begin(); i2 != s2.end(); i2++)
    {
      //lookup 
      if(s1.find(*i2) != s1.end())
      {
        //if it is good, insert it 
        results.insert(*i2);
      }
    }

  }

  return results;

}
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
  //should copy s1 into the results
  std::set<T> results = s1;

  //now insert every element from s2 
  //worst case would run in O(log(n))
  results.insert(s2.begin(), s2.end());

  return results;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
