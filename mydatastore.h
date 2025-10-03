#ifndef MYDATASTORE_H                            
#define MYDATASTORE_H                           

#include "datastore.h"                           
#include "util.h"                               
#include <map>                                  
#include <set>                                  
#include <vector>                              
#include <queue>                               
#include <string>       

class MyDataStore : public DataStore{

public:
  MyDataStore();
  virtual ~MyDataStore();

  //function headers from DataStore,  could have virtual there to show they came from DataStore
  void addProduct(Product* p);
  void addUser(User* u);
  std::vector<Product*> search(std::vector<std::string>& terms, int type);
  void dump(std::ostream& ofile);


    //functions used in amazon to help with user choices
  void addToCart(const std::string& username, Product* p);   //will push p to username's the cart
  std::vector<Product*> viewCart(const std::string& username) const; //will reach username's cart
  void buyCart(const std::string& username);                        //purchases what it can in FIFO
  bool isRealUser(const std::string& username) const;                //checks for a valid user, for when we need to add to a certain person's cart

private:
  // these are for all the products/users we add
  std::vector<Product*> products_;
  std::vector<User*> users_;

  
  std::map<std::string, User*> userLookup_; //make a map stores username as key and pointer to User as value
  
  std::map<std::string, std::set<Product*> > keySearch_;  //use this for searching keywords, giving products to them
  std::map<std::string, std::queue<Product*> > carts_; //string is user, the value is their cart
};

#endif



