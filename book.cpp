#include "book.h"
#include "util.h"         //lets me use parseStringToWords, convToLower
#include <set>
#include <string>
#include <sstream> //makes output of display very simple
#include <iomanip> //setprecision



std::set<std::string> Book::keywords() const{

    std::set<std::string> keys;             //this will hold all the keys 

    //we want to create the keywords for books, we will have keywords for the title(name), author, and isbn (this one does not need to be split)

    //title tokens
    std::set<std::string> titleKey = parseStringToWords(name_);         //gets all possible keys from the title

    for(std::set<std::string>::iterator it = titleKey.begin(); it != titleKey.end(); ++it){ //loops thru the recently parsed keys and inserts into the overarching book key set
        keys.insert(*it);
    }

    //author tokens
    std::set<std::string> authorKey = parseStringToWords(author_);

    for(std::set<std::string>::iterator it = authorKey.begin(); it != authorKey.end(); ++it){ //same idea as above
        keys.insert(*it);
    }

    //isbn tokens, remember we do not parse isbn
    keys.insert(convToLower(isbn_));            //all we need to do is just convert to lowercase and it will be a valid key

    return keys;
}

std::string Book::displayString() const{
    //to return as one string will want to use a stream to achieve format and setprecision
    
    std::stringstream stream;
    stream << name_ << "\n";
    stream << "Author: " << author_ << " ISBN: " << isbn_ << "\n";
    stream << std::fixed << std::setprecision(2) << price_ << " " << std::setw(2) << qty_ << " left.";  //use set precision so price always shows 2 num after decimal (fixed)

    return stream.str();      //convert back to returnable string

}

void Book::dump(std::ostream& os) const{
    Product::dump(os); //this prints the basic stuff that is in all products
    os << isbn_ << "\n" << author_ << "\n"; //prints stuff uniqie to book
}