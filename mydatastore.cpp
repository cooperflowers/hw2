#include "mydatastore.h"
#include "util.h"

MyDataStore::MyDataStore()
{} //nothing to initialize explicitly at start

MyDataStore::~MyDataStore()
{
  // free products
  for (std::size_t i = 0; i < products_.size(); ++i) {
    delete products_[i];
  }
  // free users
  for (std::size_t i = 0; i < users_.size(); ++i) {
    delete users_[i];
  }
}

void MyDataStore::addProduct(Product* p)
{
  if (p == NULL) return;  //NULl test
  products_.push_back(p); //there is a product so add it to products_
  std::set<std::string> keys = p->keywords();   //grabbing the products keywords

  for (std::set<std::string>::iterator it = keys.begin(); it != keys.end(); ++it) {
    std::string k = convToLower(*it);       //being safe    
    keySearch_[k].insert(p);                    //adds the product so it relates to the key
  }
}

void MyDataStore::addUser(User* u)      //
{
  if (u == NULL) return;

  users_.push_back(u);  //valid name, add to users_ in datastore
  std::string uname = convToLower(u->getName());   // 
  userLookup_[uname] = u;                         //key is uname, value is now u
  carts_[uname] = std::queue<Product*>();          // empty FIFO cart
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
  //here need to use setIntersection and setUnion for proper search 
  //type = 0 means AND, type = 1 means OR


  std::vector<Product*> searchResults;  //this is what will hold which products align with the terms
  if (terms.size() == 0) {
    return searchResults;   //nor terms check
  }

  
  std::set<Product*> match;   //will store
  std::string t0 = convToLower(terms[0]);  //only first term easy
  std::map<std::string, std::set<Product*> >::iterator it0 = keySearch_.find(t0);  //lookup of product initial
  if (it0 != keySearch_.end()) { //if term exists, count couold work here too
    match = it0->second;          //go over that set of products meeting match, match is set to have keys in set
  }
  // For AND: if first term missing, match will empty/ remains empty
  // For OR: starting empty is also fine; subsequent unions will add matches.

  //  remaining terms
  for (std::size_t i = 1; i < terms.size(); ++i) {      //loop goes thru each additional term
    std::string tk = convToLower(terms[i]); //goes thru all terms
    std::set<Product*> set2;  //will store
    std::map<std::string, std::set<Product*> >::iterator it = keySearch_.find(tk);
    if (it != keySearch_.end()) {
      set2 = it->second;           //fills up with others matches for keys
    }

    if (type == 0) {                  // AND
      match = setIntersection(match, set2);
    } else {                          // OR
      match = setUnion(match, set2);
    }
  }

  // Convert set -> vector for displayProducts()
  for (std::set<Product*>::iterator sit = match.begin(); sit != match.end(); ++sit) {
    searchResults.push_back(*sit);     //puts all products into searchREsults
  }
  return searchResults;
}

void MyDataStore::dump(std::ostream& ofile)
{
  // Products section
  ofile << "<products>\n";
  for (std::size_t i = 0; i < products_.size(); ++i) {
    products_[i]->dump(ofile);      //every product prints itself and its specifics
  }
  ofile << "</products>\n";

  // Users section
  ofile << "<users>\n";
  for (std::size_t i = 0; i < users_.size(); ++i) {
    users_[i]->dump(ofile);       //same idea here for users (balance,type)
  }
  ofile << "</users>\n";
}

bool MyDataStore::isRealUser(const std::string& username) const
{
  std::string uname = convToLower(username);      //case insens
  return userLookup_.find(uname) != userLookup_.end();      //will return true if the name is fonud
}

void MyDataStore::addToCart(const std::string& username, Product* p)
{
  if (p == NULL) return;      //checker
  std::string uname = convToLower(username); //cases
  if (userLookup_.find(uname) != userLookup_.end()) {   //if true means the name (cart) was found
    carts_[uname].push(p);    // access taht names cart, add the product FIFO (use push)
  }
}

std::vector<Product*> MyDataStore:: viewCart(const std::string& username) const
{
  std::vector<Product*> cartContent;        //will eventuallyhave contents of cart
  std::string uname = convToLower(username);
  std::map<std::string, std::queue<Product*> >::const_iterator it = carts_.find(uname);   //finds the cart under username, iterates over
  if (it == carts_.end()) return cartContent;       //if the user is not found, cartContent is returned empty

  // Copy queue so we can iterate in order without mutating original
  std::queue<Product*> copy = it->second;   //copies cart view (queue)
  while (!copy.empty()) {                     //goes thru with pop as iteration
    cartContent.push_back(copy.front());    //appends
    copy.pop();                               //then pops, does not change cartContent
  }
  return cartContent;
}

void MyDataStore::buyCart(const std::string& username)
{
  std::string uname = convToLower(username);
  std::map<std::string, User*>::iterator userIt = userLookup_.find(uname);
  if (userIt == userLookup_.end()) return;  // invalid username 

  User* u = userIt->second;
  std::queue<Product*>& finalCart = carts_[uname];

  // Process exactly the current size items; rotate any unpurchased to back
  std::size_t n = finalCart.size();
  for (std::size_t i = 0; i < n; ++i) {
    Product* purchasedProduct = finalCart.front();    //looks at first item in cart
    if (purchasedProduct->getQty() > 0 && u->getBalance() >= purchasedProduct->getPrice()) { //item is in stock, we have enough funds
      finalCart.pop();                        // remove from cart
      purchasedProduct->subtractQty(1);              // decrement stock
      u->deductAmount(purchasedProduct->getPrice()); // deduct user balance
    } else {
      finalCart.pop();                        // take from front
      finalCart.push(purchasedProduct);                      // rotate to back (remains in cart)
    }
  }
}
