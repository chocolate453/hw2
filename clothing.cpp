#include "clothing.h"
#include <sstream>
#include <iomanip>
#include <string>

#include "product.h"
#include <iostream>
using namespace std;

//implementation of all the functions:
//Clothing:
Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand)
:Product(category, name, price, qty), size_(size), brand_(brand)
 {

 }

//keywords
std::set<std::string> Clothing::keywords() const 
{
  //get the keyword
  std::set<std::string> keywords = parseStringToWords(name_);
  //get the keyword from brand
  std::set<std::string> brandkeywords = parseStringToWords(brand_);
  //insert the brand 
  keywords.insert(brandkeywords.begin(), brandkeywords.end());
  return keywords;
}

std::string Clothing::displayString() const 
{
  //how it should look: 
  // <name>
  // Size: <size> Brand: <brand>
  // <price> <quantity> left.

  stringstream ss("");
  ss << fixed << setprecision(2) << price_;
  string results = name_ + "\nSize: " + size_ + " Brand: " + brand_ + "\n" + ss.str() + " " + to_string(qty_) + " left.";
  return results;
  
}

void Clothing::dump(std::ostream& os) const 
{
  os << category_ << std::endl;
  os << name_ << std::endl; 
  os << price_ << std::endl;
  os << qty_ << std::endl;
  os << size_ << std::endl; 
  os << brand_ << std::endl;
}