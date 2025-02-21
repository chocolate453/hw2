#include "book.h"
#include <sstream>
#include "product.h"
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;


//Book:
Book::Book(const std::string& name, const std::string& author, double price, int qty, const std::string& isbn)
    : Product("book", name, price, qty), author_(author), isbn_(isbn) 
{
    
}

//keywords()
std::set<std::string> Book::keywords() const
{
  //get the keyword
  std::set<std::string> keywords = parseStringToWords(name_);
  //get the keyword from author
  std::set<std::string> Authorkeywords = parseStringToWords(author_);
  //insert the author 
  keywords.insert(Authorkeywords.begin(), Authorkeywords.end());
  keywords.insert(isbn_);

  //now return the set
  return keywords;
}

//displayString()
std::string Book::displayString() const
{
  //how it should look: 
  // <name>
  // Author: <author> ISBN: <isbn>
  // <price> <quantity> left.

  stringstream ss("");
  ss << fixed << setprecision(2) << price_;
  string results = name_ + "\nAuthor: " + author_ + " ISBN: " + isbn_ + "\n" + ss.str() + " " + to_string(qty_) + " left.";
  return results;


}

//dump()
void Book::dump(std::ostream& os) const
{
  os << category_ << std::endl;
  os << name_ << std::endl; 
  os << fixed << setprecision(2) << price_ << std::endl;
  os << to_string(qty_) << std::endl;
  os << isbn_ << std::endl;
  os << author_ << std::endl; 
  
}