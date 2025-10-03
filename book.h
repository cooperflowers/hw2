#ifndef BOOK_H
#define BOOK_H

#include "product.h"
#include <string>
#include <set>

class Book : public Product{

public:

    Book(const std::string& name, double price, int qty, const std::string& isbn, const std::string& author) :  //constructor using initializer format
        Product("book", name, price, qty), isbn_(isbn), author_(author)                     //since its a book also set category to book, and also make sure to include isbn and author
    {}

    //virtual functions from Product header
    std::set<std::string> keywords() const;
    std::string displayString() const;
    void dump(std::ostream& os) const;

private:

    std::string isbn_;  //these are kept private, they are only for book class
    std::string author_;

};

#endif