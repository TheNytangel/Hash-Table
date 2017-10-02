#include <iostream>
#include <string>
#include "HashTable.h"

void testHashTable(HashTable<std::string, unsigned long long> & hashTable);

int main()
{
	// Evidently phone numbers are really big numbers and overflow a normal unsigned long
	HashTable<std::string, unsigned long long> phoneBook(5);

	std::cout << "Performing automated testing suite...\n\n";
	testHashTable(phoneBook);

	system("pause");
	return 0;
}


void testHashTable(HashTable<std::string, unsigned long long> & hashTable)
{
	unsigned int successes = 0;
	unsigned int failures = 0;

	std::cout << "Trying to remove a key from an empty hash table\n";
	if (!hashTable.remove("Maxine"))
	{
		std::cout << "Test PASSED. The function could not remove anything from the hash table.";
		++successes;
	}
	else
	{
		std::cout << "Test FAILED. The function somehow removed something from the has table.";
		++failures;
	}
	std::cout << "\n\n";



	std::cout << "Testing the insert function by adding a key-value pair and checking the value based on the key\n";
	hashTable.insert("Maxine", 18005551234);
	if (hashTable["Maxine"] == 18005551234)
	{
		std::cout << "Test PASSED. The function found the right value for the provided key.";
		++successes;
	}
	else
	{
		std::cout << "Test FAILED. The function could not find the right value for the provided key.";
		++failures;
	}
	std::cout << "\n\n";



	std::cout << "Filling up the table to 5 values...\n";
	hashTable.insert("Damn Daniel", 6623074240);
	hashTable.insert("Brian", 7744133556);
	hashTable.insert("Pepe", 3526341195);
	hashTable.insert("Harambe", 4789971823);

	std::cout << "Testing the insert function (with resizing) by adding a key-value pair and checking all 6 values based on the keys\n";
	// Insert 6th KVP
	hashTable.insert("Harold", 5733722976);
	if (hashTable["Maxine"] == 18005551234 && hashTable["Damn Daniel"] == 6623074240 && hashTable["Brian"] == 7744133556
		&& hashTable["Pepe"] == 3526341195 && hashTable["Harambe"] == 4789971823 && hashTable["Harold"] == 5733722976)
	{
		std::cout << "Test PASSED. The function found all 6 correct values after resizing.";
		++successes;
	}
	else
	{
		std::cout << "Test FAILED. The function could not find all the right values for the provided keys.";
		++failures;
	}
	std::cout << "\n\n";



	std::cout << "Testing the remove function by removing the first and last keys that were inserted\n";
	if (hashTable.remove("Maxine") && hashTable.remove("Harold") && hashTable["Maxine"] == 0 && hashTable["Harold"] == 0)
	{
		std::cout << "Test PASSED. The function successfully deleted both key-value pairs and they were confirmed deleted.";
		++successes;
	}
	else
	{
		std::cout << "Test FAILED. The function failed to delete both key-value pairs and/or they were not confirmed to be deleted.";
		++failures;
	}
	std::cout << "\n\n";



	std::cout << "Testing the retrieve function by checking that the remaining 4 values are correct\n";
	if (hashTable.retrieve("Damn Daniel") == 6623074240 && hashTable.retrieve("Brian") == 7744133556
		&& hashTable.retrieve("Pepe") == 3526341195 && hashTable.retrieve("Harambe") == 4789971823)
	{
		std::cout << "Test PASSED. The function successfully found the correct values for the 4 remaining keys.";
		++successes;
	}
	else
	{
		std::cout << "Test FAILED. The function could not find the correct values for the 4 remaining keys.";
		++failures;
	}
	std::cout << "\n\n";



	std::cout << "\nSuccesses: " << successes << "\tFailures: " << failures << "\tTotal: " << successes + failures << "\n\n";
}
