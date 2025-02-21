#ifndef MOVIE_H
#define MOVIE_H
#include "product.h"
#include "util.h"
#include <string>
#include <set>

//class Movie, parent is product 
class Movie : public Product 
{
  public:
    Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating);
    
    //keywords() which returns the appropriate keywords to index the product
    std::set<std::string> keywords() const;

    //displayString() to create a string that contains the product info
    std::string displayString() const;

    //dump() that outputs the database format of the product info
    void dump(std::ostream& os) const;

  private:
    //data members: genre and rating 
    std::string genre_;
    std::string rating_;
};

#endif