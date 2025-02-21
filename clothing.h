#ifndef CLOTHING_H
#define CLOTHING_H
#include "product.h"
#include "util.h"
#include <string>
#include <set>

//class Clothing, parent is product 
class Clothing : public Product 
{
  public:
    Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand);
    
    //keywords() which returns the appropriate keywords to index the product
    std::set<std::string> keywords() const;

    //displayString() to create a string that contains the product info
    std::string displayString() const;
  
    //dump() that outputs the database format of the product info
    void dump(std::ostream& os) const;

  private:
    //data members: size and brand 
    std::string size_;
    std::string brand_;
};

#endif