#include "mydatastore.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <sstream>
using namespace std;

MyDataStore::MyDataStore()
{
  //nothing 
}

MyDataStore::~MyDataStore()
{
  //free the dynamically allocated products 
  for(size_t i = 0; i < products_.size(); i++)
  {
    delete products_[i];
  }
  //free the dynamically allocated users
  for(size_t i = 0; i < users_.size(); i++)
  {
    delete users_[i];
  }

}

//add products 
void MyDataStore::addProduct(Product* p)
{
  //store the products, so push back the product that you want to add
  products_.push_back(p);
  //get the keywords to work
  std::set<std::string> keywords = p->keywords();
  //map each keyword to this product 
  for(std::set<std::string>::iterator it = keywords.begin(); it != keywords.end(); it++) 
  {
    keywordMap_[*it].insert(p);
  }
}

//add the user
void MyDataStore::addUser(User* u)
{
  //store the user, same as for product 
  users_.push_back(u);
}


//do a search using the keywords
//type 0 = AND search --> intersection of results
//type 1 = OR search --> union of results
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
  std::set<Product*> resultSet;

  //if empty just return 
  if(terms.empty())
  {
    return {};
  }

  //go thru the entire size of the terms 
  for (size_t i = 0; i < terms.size(); i++) 
  {
    //find the keyword in the map
    if (keywordMap_.find(terms[i]) != keywordMap_.end()) 
    {
      //get the set of products
      std::set<Product*> currentSet = keywordMap_[terms[i]]; 
            
      if (resultSet.empty()) 
      {
        //this will be the first terms 
        resultSet = currentSet; 
      } 
      else if (type == 0) 
      {
        //AND search
        resultSet = setIntersection(resultSet, currentSet);
      } 
      else 
      { 
        // OR search
        resultSet = setUnion(resultSet, currentSet);
      }
    } 
    else if (type == 0) 
    {
      //AND search: If any term has no results, return empty
      return {}; 
    }
  }
  //now return 
  return std::vector<Product*>(resultSet.begin(), resultSet.end());

}

void MyDataStore::dump(std::ostream& ofile)
{
  //dump for the product 
  ofile << "<products>" << std::endl;
  vector<Product*>::iterator it1; 
  for(it1 = products_.begin(); it1 != products_.end(); it1++)
  {
    (*it1)->dump(ofile);
  }
  ofile << "</products>" << std::endl;

  //dump for the user 
  ofile << "<users>" << std::endl;
  vector<User*>::iterator it2;
  for(it2 = users_.begin(); it2 != users_.end(); it2++)
  {
    (*it2)->dump(ofile);
  }
  ofile << "</users>" << std::endl;

 
}
 

void MyDataStore::viewCart(const std::string& username)
{
  // Get the user
  User* user = getUser(username);
  //verify that the user is valid 
  if (!user) 
  {
    cout << "Invalid username" << endl;
    return;
  }

  //check if user has a cart
  std::map<std::string, std::vector<Product*>>::iterator it = carts_.find(username);
  if (it == carts_.end() || it->second.empty()) 
  {
    cout << "Cart is empty." << endl;
    return;
  }

  //get the cart's reference to avoid copying
  const vector<Product*>& cart = it->second;

  //output the cart's contents
  for (size_t i = 0; i < cart.size(); i++) 
  {
    cout << "Item " << i + 1 << "\n" << cart[i]->displayString() << endl;
  }
  
}

void MyDataStore::buyCart(const std::string& username)
{
  //get the user 
  User* user = getUser(username);
  //verify if the user is valid
  if (!user) 
  {
    cout << "Invalid username" << endl;
    return;
  }

  //get a reference to the user's cart
  vector<Product*>& cart = carts_[username];
  if (cart.empty()) 
  {
    cout << "Cart is empty." << endl;
    return;
  }

  //create a temp vector to store the items that could not be purchased
  vector<Product*> remainingItems;
  //go thru the products in the user's cart 
  for (Product* p : cart) 
  {
    //get the price of the current products 
    double price = p->getPrice();
    //check if in stock and if user can afford it 
    if (p->getQty() > 0 && user->getBalance() >= price) 
    {
      //yes user can purchase it so:
      //reduce the count by 1
      //subtract the amount of money from the user 
      p->subtractQty(1);
      user->deductAmount(price);
      //the user did purchase it 
      cout << "Purchased: " << p->getName() << endl;
    } 
    else 
    {
      //else it did not get purchased 
      remainingItems.push_back(p);
    }
  }
  //only the items that were not purchased are in the cart 
  carts_[username] = remainingItems;
}

User* MyDataStore::getUser(const std::string& username) 
{
  //go thru the list of users 
  for (size_t i = 0; i < users_.size(); i++) 
  {
    //if the names match
    if (users_[i]->getName() == username) 
    {
      //then return the user 
      return users_[i]; 
    }
  }
  //else no match 
  return nullptr; 
}

void MyDataStore::addToCart(const std::string& username, Product* p) 
{
  //get the user 
  User* user = getUser(username);
  //check if the request is vald 
  if (!user || !p) 
  {
    cout << "Invalid request" << endl;
    return;
  }

  //see if the cart exist: 
  if(carts_.find(username) == carts_.end())
  {
    carts_[username] = std::vector<Product*>();
  }

  //if it does then add to cart
  carts_[username].push_back(p);
}

bool MyDataStore::userExists(const std::string& username) 
{
  //exact same idea as for getUser() but using a bool 
  for (size_t i = 0; i < users_.size(); i++) 
  {
    if (users_[i]->getName() == username) 
    {
      return true;
    }
  }
  return false;

}