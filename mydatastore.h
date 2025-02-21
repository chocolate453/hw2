#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include "datastore.h"
#include "util.h"
#include <map>
#include <vector>
#include <set>

//make a class that is a child or datastore
class MyDataStore: public DataStore
{
  public:
    //searching, adding products and users, saving the database....
    MyDataStore();
    ~MyDataStore();

    void addProduct(Product* p);
    void addUser(User* u);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);

    void viewCart(const std::string& username); 
    void buyCart(const std::string& username);  
    User* getUser(const std::string& username);
    void addToCart(const std::string& username, Product* p);
    bool userExists(const std::string& username);

  private: 
    //to stores all the products
    std::vector<Product*> products_; 
    //to store all the users
    std::vector<User*> users_;       
    //to maps the keywords to the products
    std::map<std::string, std::set<Product*>> keywordMap_; 
    std::map<std::string, std::vector<Product*>> carts_;
};



#endif