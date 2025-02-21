#include "movie.h"
#include "util.h"
#include <iomanip>
#include <string>
#include <sstream>
#include "product.h"
#include <iostream>
using namespace std;

//implementation of all the functions:
//Moving: 
Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating)
:Product(category, name, price, qty), genre_(genre), rating_(rating) 
{}

//keywords:
std::set<std::string> Movie::keywords() const 
{
  //get the keyword
  std::set<std::string> keywords = parseStringToWords(name_);
  //insert the genre + conver to lower for the genre
  keywords.insert(convToLower(genre_));
  return keywords;
}

std::string Movie::displayString() const 
{
  //should look like this:
  //   <name>
  // Genre: <genre> Rating: <rating>
  // <price> <quantity> left.

  stringstream ss("");
  ss << fixed << setprecision(2) << price_;
  string results = name_ + "\nGenre: " + genre_ + " Rating: " + rating_ + "\n" + ss.str() + " " + to_string(qty_) + " left.";
  return results;

}

void Movie::dump(std::ostream& os) const 
{
  os << category_ << std::endl;
  os << name_ << std::endl; 
  os << price_ << std::endl;
  os << qty_ << std::endl;
  os << genre_ << std::endl; 
  os << rating_ << std::endl;
  
}