//***************************************************************************//
//**
//**  Simple Heap implementation
//**
//***************************************************************************//

#ifndef __HEAP_H
#define __HEAP_H
#include <iostream>
#include <vector>
#include <stdexcept> // std::out_of_range
#include <math.h>	 // pow()
#include <string>
#include <limits>

/**
 *  Declaring Heap class
 */
template <typename T>
class Heap
{

private:
	std::vector<T> _items; // Main vector of elements for heap storage. The first item in the array is a placeholder.

	/*********************************************************************/
	/*********************** Start assignment zone **********************/

	/**
	 *  Percolates the item specified at by index down 
     *   into its proper location within a heap.
	 *  Used for dequeue operations and array to heap conversions
	 *  TODO: Implement percolateDown
	 */
	void percolateDown(unsigned int hole)
	{
		unsigned int child; // child node in question
		T tmp = std::move(_items[hole]);

		for ( ; hole *2 < _items.size(); hole = child)
		{
			child = hole*2; // the left child is double the index, and right is double + 1 
			
			if (child != _items.size() - 1 && _items[child + 1] < _items[child]) {
            	++child; // right child
			}

			// move child up
			if (_items[child] < tmp) {
				_items[hole] = std::move(_items[child]);
			} else {
            	break;
			}
        }
		_items[hole] = std::move(tmp);
	}

	/**
	 *  Add a new item to the end of the heap and percolate up this item to fix heap property
	 *  Used in inserting new nodes into the heap
	 *  TODO: Implement percolateUp
	 */
	void percolateUp(const T& item) {
		int hole = _items.size();  
		_items.push_back(item);    

		for (; item < _items[hole / 2]; hole /= 2) {
			_items[hole] = std::move(_items[hole / 2]);
		}
		_items[hole] = item;
	}


	/********************** End Microassigment zone *********************/

public:
	/**
	 *  Default empty constructor
	 */
	Heap()
	{
		_items.push_back(std::numeric_limits<T>::min()); // Push a placeholder for the first item in the array
	}

	/**
	 *  Adds a new item to the heap
	 */
	void push(T item)
	{
		percolateUp(item);
	}

	/**
	 *  Removes minimum value from heap 
	 */
	T pop()
	{
		long unsigned int last_index = _items.size() - 1; // Calc last item index
		int root_index = 1;								  // Root index (for readability)

		if (size() == 0)
		{
			throw std::out_of_range("pop() - No elements in heap");
		}

		T minItem = _items[root_index];

		_items[root_index] = _items[last_index]; // Move last item to root
		_items.pop_back();						 // Erase last element entry

		if (size() > 0)
		{					  // Only runs if the heap isn't empty now
			percolateDown(1); // Fix heap property
		}
		return minItem;
	}

	/**
	 *  Returns true if heap is empty, else false
	 *  Consider the first placeholder in the array
	 */
	bool empty() const
	{
		if (_items.size() == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	/**
	 *  Returns current quantity of elements in heap (N)
	 *  Consider the first placeholder in the array
	 */
	long unsigned int size() const
	{
		return _items.size() - 1;
	}

	/**
	 *  Return heap data in order from the _items vector
	 */
	std::string to_string() const
	{
		std::string ret = "";
		for (unsigned int i = 1; i < _items.size(); i++)
		{
			ret += std::to_string(_items[i]) + " ";
		}
		return ret;
	}
};

#endif
