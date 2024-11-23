#ifndef SEPARATE_CHAINING_H
#define SEPARATE_CHAINING_H

#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <functional>
#include <iostream>
#include "Employee.h"
#include "utils.h"

using namespace std;

template <typename HashedObj>
class ChainingHash
{
  public:
    explicit ChainingHash( int size = 101 ) : currentSize{ 0 }
      { theLists.resize( 101 ); }


    bool contains( const HashedObj & x ) const
    {
        // Get list locations among vector of lists
        const list<HashedObj> &listLocation = theLists[myhash(x)];
        // std::find() not a function of ours, use it to see if its in the list. Saves the trouble of making a loop based on size
        if (find(listLocation.begin(), listLocation.end(), x) != listLocation.end()){
            return true;
        }
        return false;
    }

    void makeEmpty( )
    {
        // Clear list then set current size to 0
        for (auto &thisList : theLists) {
            thisList.clear(); //std::clear()
        }
        currentSize = 0;
    }

    bool insert( const HashedObj & x )
    {
        // check if element is in the hash table
        list<HashedObj> &listLocation = theLists[myhash(x)];
        if (contains(x)) {
            return false;
        }

        listLocation.push_back(x);
        currentSize += 1;

        // check if load factor is still sub 1
        if (loadFactor() >= 1) {
            rehash();
        }
        return true;
    }
    
    bool insert( HashedObj && x )
    {
        // check if element is in the hash table
        list<HashedObj> &listLocation = theLists[myhash(x)];
        if (contains(x)) {
            //printf("Already in");
            return false;
        }

        // move x for R value
        listLocation.push_back(std::move(x));
        currentSize += 1;

        // check if load factor is still sub 1
        if (loadFactor() >= 1) {
            rehash();
        }
        return true;
    }

    bool remove( const HashedObj & x )
    {
        list<HashedObj> &listLocation = theLists[myhash(x)];
        auto iterator = find(listLocation.begin(), listLocation.end(), x);

        // iterator does not find it
        if (iterator == listLocation.end()) {
            return false;
        }

        listLocation.erase(iterator);
        currentSize -= 1;
        return true;
    }

    double readLoadFactor() 
    {
        return loadFactor();
    }

    double readCurrentSize() 
    {
        return currentSize;
    }

    double readArraySize() 
    {
        return theLists.size();
    }

  private:
    vector<list<HashedObj>> theLists;   // The array of Lists
    int currentSize;

    // used https://stackoverflow.com/questions/20037963/rehashing-a-table to help me formulate this, particularly the for loops. Idea is implemented in linearprobing as well.
    void rehash( )
    {
        // old list
        vector<list<HashedObj>> old = theLists;

        theLists.resize(nextPrime(2* theLists.size()));
        for (list<HashedObj> &list : theLists){
            list.clear();
        }

        currentSize = 0;


        // hash table now exists only in old, we can now update it
        for (auto &list : old) {
            for (auto &x : list) {
                insert(move(x));
            }
        }
    }

    size_t myhash( const HashedObj & x ) const
    {
        static std::hash<HashedObj> hf;
        return hf( x ) % theLists.size( );
    }

    double loadFactor()
    {
        return static_cast<double>(currentSize) / static_cast<double>(theLists.size());
    }
};

#endif
