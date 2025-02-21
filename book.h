#ifndef BOOK_H
#define BOOK_H
#include "product.h"
#include "util.h" 
#include <iostream>
#include <string>


//class book, parent is product 
class Book : public Product
{
  public:
    Book(const std::string& name, const std::string& author, double price, int qty, const std::string& isbn);
    
    //all the needed functions:
    //keywords() which returns the appropriate keywords to index the product
    std::set<std::string> keywords() const;

    //displayString() to create a string that contains the product info
    std::string displayString() const;

    //dump() that outputs the database format of the product info
    void dump(std::ostream& os) const;

  private: 
    //data members author and isbn
    std::string author_;
    std::string isbn_;
};


#endif