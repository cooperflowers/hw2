#ifndef CLOTHING_H
#define CLOTHING_H

#include "product.h"
#include <set>
#include <string>

class Clothing : public Product{

public: 
    Clothing(const std::string& name, double price, int qty, const std::string&size, const std::string& brand) : 
        Product("clothing", name, price, qty), size_(size), brand_(brand)               //set the category to clothing, also including size and brand (unique to clothing)
    {}

    std::set<std::string> keywords() const;
    std::string displayString() const;
    void dump(std::ostream& os) const;

private:

    std::string size_;
    std::string brand_;
};

#endif