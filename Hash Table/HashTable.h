#pragma once

#include <list>
#include <string>

#define MAGIC_NUMBER 0x5F3759DF // Equivalent to 1,597,463,007

template <class K, class V>
class HashTable
{
public:
	class KeyValuePair;

	HashTable()
	{
		// Make an array of lists as big as currentSize
		table = new std::list<typename HashTable::KeyValuePair>[currentSize];
	}

	HashTable(unsigned int maxSize) : currentSize(maxSize)
	{
		// Make an array of lists as big as currentSize (maxSize)
		table = new std::list<typename HashTable::KeyValuePair>[currentSize];
	}

	~HashTable()
	{
		// Make sure to delete the entire table table afterwards so there are no memory leaks
		delete [] table;
	}

	void insert(K key, V value)
	{
		// Check to make sure there is space (even though we are imposing a fake limit on the table)
		if (amountFilled >= currentSize)
		{
			// If there isn't enough space, make it bigger (2x as big)
			resize(currentSize * 2);
		}

		// Hash the key
		unsigned int position = hash(key);
		bool foundInTable = false;
		// Go to that spot in the array
		// Look through the list to see if there is already a value with that key
		for (std::list<typename HashTable::KeyValuePair>::iterator it = table[position].begin(); it != table[position].end(); ++it)
		{
			// If the key is already in the array, return so it doesn't add the value
			if (it->key == key)
			{
				foundInTable = true;
				return;
			}
		}
		// If there isn't, add the new item to the list
		table[position].push_back(KeyValuePair(key, value));
		// Increment the number of used spaces by 1
		++amountFilled;
	}

	V retrieve(K key) const
	{
		// Hash the key
		unsigned int position = hash(key);
		// Go to that position in the array
		// Loop through every item in the list and check if one of their keys is equal to the key we are looking for
		for (std::list<typename HashTable::KeyValuePair>::iterator it = table[position].begin(); it != table[position].end(); ++it)
		{
			if (it->key == key)
			{
				// Found it so return its value
				return it->value;
			}
		}

		// Nothing was found so return nothing
		return 0;
	}

	// Alias for retrieve()
	V operator[](K key) const
	{
		return retrieve(key);
	}

	bool remove(K key)
	{
		// Check if the table is empty. If it is, there's no reason to search for the key
		if (amountFilled == 0)
		{
			return false;
		}

		// Hash the key
		unsigned int position = hash(key);
		// Go to that position in the array
		// Loop through every item in the list and check if one of their keys is equal to the key we are looking for
		for (std::list<typename HashTable::KeyValuePair>::iterator it = table[position].begin(); it != table[position].end(); ++it)
		{
			if (it->key == key)
			{
				// Found it so delete it
				table[position].erase(it);
				// Decrement the amount of things populating the table
				--amountFilled;
				return true;
			}
		}

		return false;
	}

private:
	// Hash function
	unsigned int hash(std::string key) const
	{
		// Make sure there is enough space for what is about to happen
		unsigned long long hashNumber = 1;
		
		// Multiply the hash number by the ASCII value of each character of the string
		for (size_t i = 0; i < key.size(); ++i)
		{
			hashNumber *= key[i];
		}

		// Multiply by the magic number
		hashNumber *= MAGIC_NUMBER;

		// Take the modulus of the hash number by the size so there are a max of (size) unique keys
		hashNumber %= currentSize;

		// Return that number casted as an int
		return (unsigned int) hashNumber;
	}

	void resize(unsigned int newSize) {
		// Store the old size of the table
		unsigned int oldSize = currentSize;
		// Make a pointer to the old table
		std::list<typename HashTable::KeyValuePair> * tempOldTable = table;
		// Set the new size of the table
		currentSize = newSize;
		// Make the table a new table of the bigger size
		table = new std::list<typename HashTable::KeyValuePair>[currentSize];
		// Reset the "amount filled" counter
		amountFilled = 0;

		// Go through each position of the old table's array
		for (unsigned int position = 0; position < oldSize; ++position)
		{
			// Go through each KV pair in each list in the table
			for (std::list<typename HashTable::KeyValuePair>::iterator it = tempOldTable[position].begin(); it != tempOldTable[position].end(); ++it)
			{
				// Rehash the key and insert the key value pair into the new table
				insert(it->key, it->value);
			}
		}

		// Delete the old table from memory
		delete [] tempOldTable;
	}

	// A pointer to a list so that we can make a dynamic array
	std::list<typename HashTable::KeyValuePair> * table;
	unsigned int currentSize = 50;
	unsigned int amountFilled = 0;

public:
	class KeyValuePair
	{
		friend class HashTable;
		K key;

	public:
		V value;

		KeyValuePair(K newKey, V newValue) : key(newKey), value(newValue) {}
	};
};
