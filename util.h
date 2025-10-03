#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
    //function that takes both sets and returns another one with elements that were in both sets
    std::set<T> intersect;      // this is the set that will hold elements from both sets

    for(typename std::set<T>::iterator it = s1.begin(); it != s1.end(); ++it){   //loops thru all values of s1
        if(s2.find(*it) != s2.end()){             //count (from <set>) will return 0 if not found and 1 if found,    if the iterator's value (s1's value) is in s2, it will return 1
            intersect.insert(*it);          //meaning we insert it
        }
    }

    return intersect;           

}
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{

    //takes both sets and returns new set with all values, no duplicates (already ignored from set)

    std::set<T> unify;      //returing set

    for(typename std::set<T>::iterator s1it = s1.begin(); s1it != s1.end(); ++s1it){
        unify.insert(*s1it);                                                       //we basically want to add all s1 values
    }

    //then add all s2, set class ignores duplicates
    for(typename std::set<T>::iterator s2it = s2.begin(); s2it != s2.end(); ++s2it){
        unify.insert(*s2it);                                                      
    }

    return unify;  


}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
