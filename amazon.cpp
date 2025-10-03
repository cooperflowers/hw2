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
#include "mydatastore.h" //need for my derived

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
    MyDataStore ds;  //my
    


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
    if( parser.parse(argv[1], ds) ) {
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
                hits = ds.search(terms, 0);
                displayProducts(hits);
            }
            else if ( cmd == "OR" ) {
                string term;
                vector<string> terms;
                while(ss >> term) {
                    term = convToLower(term);
                    terms.push_back(term);
                }
                hits = ds.search(terms, 1);
                displayProducts(hits);
            }
            else if ( cmd == "QUIT") {
                string filename;
                if(ss >> filename) {
                    ofstream ofile(filename.c_str());
                    ds.dump(ofile);
                    ofile.close();
                }
                done = true;
            }
	    /* Add support for other commands here */

        
            else if ( cmd == "ADD" ) {
                // ADD username x search_hit_number
                //need to validate uname, check for invalidity, 
                string username;
                int hitIndex;   //going off hit vec
                if (!(ss >> username) || !(ss >> hitIndex)) {    //there is nothing for it to parse
                    cout << "Invalid request" << endl;          // missing args
                }
                else if (hitIndex < 1 || hitIndex > (int)hits.size()) {
                    cout << "Invalid request" << endl;          // product out-of-range index
                }
                else if (!ds.isRealUser(username)) {                     //found user
                    cout << "Invalid request" << endl;          // invalid username 
                }
                else {
                    Product* p = hits[hitIndex - 1];            // 1-based to 0-based
                    ds.addToCart(username, p);                  // FIFO add
                }
            }
            else if ( cmd == "VIEWCART" ) {
                //if username is not valid print out "Invalid Username"
                //otherwise format MUST be
                //Item #
                //name
                //type speciffic
                //price and qty left
                //need to use \n //not true
                string username;
                if (!(ss >> username)) {
                    cout << "Invalid username" << endl;         // no username provided
                }
                else if (!ds.isRealUser(username)) {
                    cout << "Invalid username" << endl;         // user not found
                }
                else {
                    vector<Product*> cart = ds.viewCart(username); //make sure FIFO
                    int itemNum = 1;
                    for (vector<Product*>::iterator it = cart.begin(); it != cart.end(); ++it) {
                        cout << "Item " << itemNum << endl;           //gives cart organization
                        cout << (*it)->displayString() << endl;         //this will output the correct format, dereference and call func
                        cout << endl;
                        itemNum++;          //increment number of items as we move along
                    }
                }
            }
            else if ( cmd == "BUYCART" ) {
                //BUYCART username
                //check for valid username, try to buy items, needs to be FIFO and affordable and in stock (been chcekd)
                string username;
                if (!(ss >> username)) {
                    cout << "Invalid username" << endl;  //no arg
                }
                else if (!ds.isRealUser(username)) {            //not real
                    cout << "Invalid username" << endl;
                }
                else {
                    ds.buyCart(username);                        // purchases what it can, rest stays FIFO
                }
            }



            else {
                cout << "Unknown command" << endl;
            }
        }

    }
    
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
