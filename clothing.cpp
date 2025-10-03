#include "clothing.h"
#include "util.h"
#include <set>
#include <string>
#include <sstream>  //need the same stuff as book
#include <iomanip>


std::set<std::string> Clothing::keywords() const{

    //need keywords for product name and brand, size is not considered a keyword

    std::set<std::string> keys;         //setup the entire clothing key set

    //grab keys from the product name
    std::set<std::string> pNameKey = parseStringToWords(name_);

    for(std::set<std::string>::iterator it = pNameKey.begin(); it != pNameKey.end(); ++it){
        keys.insert(*it);
    }

    //grab clothing brand keys

    std::set<std::string> brandKey = parseStringToWords(brand_);

    for(std::set<std::string>::iterator it = brandKey.begin(); it != brandKey.end(); ++it){
        keys.insert(*it);
    }

    //size is not a keyword

    return keys;
}

std::string Clothing::displayString() const{    //essentially same as book. only diff is size and brand
    
    std::stringstream stream;
    stream << name_ << "\n";
    stream << "Size: " << size_ << " Brand: " << brand_ << "\n";
    stream << std::fixed << std::setprecision(2) << price_ << " " << std::setw(2) << qty_ << " left.";  

    return stream.str();     

}

void Clothing::dump(std::ostream& os) const{
    Product::dump(os); //this prints the basic stuff that is in all products
    os << size_ << "\n" << brand_ << "\n"; //prints stuff unique to clothing
}