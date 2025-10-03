#ifndef MOVIE_H
#define MOVIE_H

#include "product.h"
#include <set>
#include <string>

class Movie : public Product{ //same format as other .h

public: 
    Movie(const std::string& name, double price, int qty, const std::string& genre, const std::string& rating) :
        Product("movie", name, price, qty), genre_(genre), rating_(rating)
    {}

    std::set<std::string> keywords() const;
    std::string displayString() const;
    void dump(std::ostream& os) const;

private:

    std::string genre_;
    std::string rating_;
};

#endif