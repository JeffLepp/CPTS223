#ifndef LINEAR_PROBING_H
#define LINEAR_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include <iostream>
#include "Employee.h"
#include "utils.h"

using namespace std;

// this inplementation follows Figure 5.14 in textbook for quadratic probing
template <typename HashedObj> 
class ProbingHash
{
  public:
    explicit ProbingHash( int size = 101 ) : array( nextPrime( size ) ), currentSize{ 0 }
      { makeEmpty( ); }

    bool contains( const HashedObj & x ) const
    {
        int position = findPos(x);
        bool contained = isActive(position);
        return contained;
        
    }

    void makeEmpty( )
    {
        for (auto &entry : array) {
            entry.info = EMPTY;
        }
        currentSize = 0;
    }

    bool insert( const HashedObj & x )
    {
        int current = findPos(x);
        if (isActive(current)) {
            return false;
        }
        
        array[current] = {x, ACTIVE};
        currentSize += 1; 

        if (loadFactor() >=  .5) {
            rehash();
        }

        return true;
    }
    
    bool insert( HashedObj && x )
    {
        int current = findPos(x);
        if (isActive(current)) {
            return false;
        }
        
        // Same insert but move
        array[current] = {move(x), ACTIVE};
        currentSize += 1; 

        if (loadFactor() >=  .5) {
            rehash();
        }

        return true;
    }

    bool remove( const HashedObj & x )
    {
        int current = findPos(x);
        if (!isActive(current)) {
            return false;
        }

        array[current].info = DELETED;
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
        return array.size();
    }

    enum EntryType { ACTIVE, EMPTY, DELETED };

  private:
    struct HashEntry
    {
        HashedObj element;
        EntryType info;

        HashEntry( const HashedObj & e = HashedObj{ }, EntryType i = EMPTY )
          : element{ e }, info{ i } { }
        
        HashEntry( HashedObj && e, EntryType i = EMPTY )
          : element{ std::move( e ) }, info{ i } { }
    };
    
    vector<HashEntry> array;
    int currentSize;

    bool isActive( int currentPos ) const
      { return array[currentPos].info == ACTIVE; }

    int findPos( const HashedObj & x ) const
    {
        int current = myhash(x);

        while (array[current].info != EMPTY && array[current].element != x) {
            current += 1;
            if (current >= array.size()) {
                current -= array.size();
            }
        }
        return current;
    }

    void rehash( )
    {
        vector<HashEntry> old = array;

        array.resize(nextPrime(2 * old.size()));
        for (auto &entry : array) {
            entry.info = EMPTY;
        }

        currentSize = 0;

        for (auto &list : old) {
            if (list.info == ACTIVE) {
                insert(move(list.element));
            }
        }
    }

    size_t myhash( const HashedObj & x ) const
    {
        static hash<HashedObj> hf;
        return hf( x ) % array.size( );
    }

    double loadFactor()
    {
        return static_cast<double>(currentSize) / array.size();
    }
};

#endif
