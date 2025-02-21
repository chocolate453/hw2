#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "product.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include "mydatastore.h"

using namespace std;
struct ProdNameSorter {
    bool operator()(Product* p1, Product* p2) {
        return (p1->getName() < p2->getName());
    }
};
void displayProducts(vector<Product*>& hits);

int main(int argc, char* argv[])
{
    if(argc < 2) {
        cerr << "Please specify a database file" << endl;
        return 1;
    }

    /****************
     * Declare your derived DataStore object here replacing
     *  DataStore type to your derived type
     ****************/
    //DataStore ds;
    //change to:
    DataStore* ds = new MyDataStore();



    // Instantiate the individual section and product parsers we want
    ProductSectionParser* productSectionParser = new ProductSectionParser;
    productSectionParser->addProductParser(new ProductBookParser);
    productSectionParser->addProductParser(new ProductClothingParser);
    productSectionParser->addProductParser(new ProductMovieParser);
    UserSectionParser* userSectionParser = new UserSectionParser;

    // Instantiate the parser
    DBParser parser;
    parser.addSectionParser("products", productSectionParser);
    parser.addSectionParser("users", userSectionParser);

    // Now parse the database to populate the DataStore
    //add the * 
    if( parser.parse(argv[1], *ds) ) {
        cerr << "Error parsing!" << endl;
        return 1;
    }

    cout << "=====================================" << endl;
    cout << "Menu: " << endl;
    cout << "  AND term term ...                  " << endl;
    cout << "  OR term term ...                   " << endl;
    cout << "  ADD username search_hit_number     " << endl;
    cout << "  VIEWCART username                  " << endl;
    cout << "  BUYCART username                   " << endl;
    cout << "  QUIT new_db_filename               " << endl;
    cout << "====================================" << endl;

    vector<Product*> hits;
    bool done = false;
    while(!done) {
        cout << "\nEnter command: " << endl;
        string line;
        getline(cin,line);
        stringstream ss(line);
        string cmd;
        if((ss >> cmd)) {
            if( cmd == "AND") {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds->search(terms, 0);
                displayProducts(hits);
            }
            else if ( cmd == "OR" ) {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds->search(terms, 1);
                displayProducts(hits);
            }
            else if ( cmd == "QUIT") {
                string filename;
                if(ss >> filename) {
                    ofstream ofile(filename.c_str());
                    ds->dump(ofile);
                    ofile.close();
                }
                done = true;
            }
	    /* Add support for other commands here */
            else if(cmd == "ADD")
            {
              //initilize variables  
              string username;
              size_t hitIDX;
              //make the username lowercase for comparision
              username = convToLower(username);
              //read in the argumments 
              if(ss >> username >> hitIDX)
              {
                //try to cast ds to MyDataStore to access methods
                MyDataStore* myDS = dynamic_cast<MyDataStore*>(ds);
                //check if in bound 
                if(hitIDX > 0 && hitIDX <= hits.size()) 
                {
                  //now add the user's product to cart
                  myDS->addToCart(username, hits[hitIDX - 1]);
                }
                //otherwise not in bound
                else 
                {
                  cout << "Invalid ADD command format!" << endl;
                }
              }
            }
            else if (cmd == "VIEWCART") 
            {
              //initilize variables + convert to lowecase to pass
              string username;
              username = convToLower(username);
              //read in the sstream
              if(ss >> username) 
              {
                //try to cast ds to MyDataStore to access methods
                MyDataStore* myDS = dynamic_cast<MyDataStore*>(ds);
                if(myDS) 
                {
                  //call that user's cart to see it 
                  myDS->viewCart(username);
                } 
                else 
                {
                  //otherwise it is an error
                  cout << "Error: Invalid data store type!" << endl;
                }
              } 
              else 
              {
                cout << "Invalid VIEWCART command format!" << endl;
              }
            }
            else if (cmd == "BUYCART") 
            {
              //initilize variables + convert to lowecase to pass
              string username;
              username = convToLower(username);
              //read in the sstream
              if(ss >> username) 
              {
                //try to cast ds to MyDataStore to access methods
                MyDataStore* myDS = dynamic_cast<MyDataStore*>(ds);
                if (myDS) 
                {
                  //if it pass then buy whatever is in that user's cart
                  myDS->buyCart(username);
                } 
                else 
                {
                  cout << "Error: Invalid data store type!" << endl;
                }
              } 
              else 
              {
                cout << "Invalid BUYCART command format!" << endl;
              }
            }

            else {
                cout << "Unknown command" << endl;
            }
        }

    }
    delete ds;
    return 0;
}

void displayProducts(vector<Product*>& hits)
{
    int resultNo = 1;
    if (hits.begin() == hits.end()) {
    	cout << "No results found!" << endl;
    	return;
    }
    std::sort(hits.begin(), hits.end(), ProdNameSorter());
    for(vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it) {
        cout << "Hit " << setw(3) << resultNo << endl;
        cout << (*it)->displayString() << endl;
        cout << endl;
        resultNo++;
    }
}
