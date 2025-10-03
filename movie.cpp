  #include "movie.h"
#include "util.h"
#include <set>
#include <string>
#include <sstream>
#include <iomanip>

std::set<std::string> Movie :: keywords() const{
    std::set<std::string> keys;


    //grab the keys from movie title (name)

    std::set<std::string> MovieTitleKeys = parseStringToWords(name_);
    for(std::set<std::string>::iterator it = MovieTitleKeys.begin(); it != MovieTitleKeys.end(); ++it){
        keys.insert(*it);
    }

    //only other keys needed are the movie genre, and we do not need to parse this one, only lowercase it

    keys.insert(convToLower(genre_));

    return keys;

}

std::string Movie::displayString() const{    //essentially same as book. only diff is size and brand
    
    std::stringstream stream;
    stream << name_ << "\n";
    stream << "Genre: " << genre_ << " Rating: " << rating_ << "\n";
    stream << std::fixed << std::setprecision(2) << price_ << " " << std::setw(2) << qty_ << " left.";  

    return stream.str();     

}

void Movie::dump(std::ostream& os) const{
    Product::dump(os); //this prints the basic stuff that is in all products
    os << genre_ << "\n" << rating_ << "\n"; //prints stuff unique to clothing
}