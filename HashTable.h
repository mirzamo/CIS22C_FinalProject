/**
	Hash Table Specification
**/

#ifndef _HASH_TABLE
#define _HASH_TABLE

#include<string>
#include<vector>
#include<iostream>
#include<iomanip>
#include"Athlete.h"

//using namespace std;

// hash table class
class HashTable
{
private:
	// bucket definition
	struct HashEntry
	{
		Athlete *athlete;
		string searchKey;
		HashEntry *next;

		// copy constructor
		HashEntry(Athlete *newEntry, const string& newKey)
		{ 
			this->athlete = newEntry; 
			this->searchKey = newKey;
			next = NULL;
		}
	};

	HashEntry** hashTable;
	int TableSize;
	int itemCount;
	int collisionFlag;
	
public:
	// constructor
	HashTable(int size);
	// destructor
	~HashTable();

	// Hash table operations	
	int getCollisions() const;
	int getCount() const;
	double getLoadFactor() const;
	bool addEntry(Athlete *ath, const string& newKey);
	bool removeEntry(const string& searchKey);
	void getEntry(void visit(), const string key);
	void displayBucket() const;
	void printTable() const;
	void tableStatistics();
	void clearTable();

private:
	int hashFunction(const string searchKey);
	HashEntry* searchEntry(const string key);
};


/******************* public function definitions *******************/

// constructor
HashTable::HashTable(int size)
{
	itemCount = 0; 
	collisionFlag = 0;
	TableSize = size;

	// initialize each entry of the hash table
	hashTable = new HashEntry*[TableSize];

	for (int i = 0; i<TableSize; i++)
	{
		hashTable[i] = NULL;
	}
}

// add item into the hash table
bool HashTable::addEntry(Athlete *ath, const string& newKey)
{
	int tableIndex = hashFunction(newKey);

	if (hashTable[tableIndex] == NULL)
	{
		hashTable[tableIndex] = new HashEntry(ath,newKey);
	}
	else
	{
		HashEntry *entry = hashTable[tableIndex];
		
		while (entry->next != NULL)
		{
			entry = entry->next;
		}
		entry->next = new HashEntry(ath,newKey);

		collisionFlag++; 
	}
	itemCount++;

	return true;
}

// remove an entry from the hash table
bool HashTable::removeEntry(const string& searchKey)
{
	bool found = false;
	int tableIndex = hashFunction(searchKey);
	
	if (hashTable[tableIndex] != NULL)
	{
		HashEntry *prevEntry = NULL;
		HashEntry *removeEntry = hashTable[tableIndex];

		while (removeEntry->next != NULL && removeEntry->searchKey != searchKey)
		{
			prevEntry = removeEntry;
			removeEntry = removeEntry->next;
		}
		if (removeEntry->searchKey == searchKey)
		{
			if (prevEntry == NULL)
			{
				HashEntry *nextEntry = removeEntry->next;
				delete removeEntry;
				hashTable[tableIndex] = nextEntry;
				found = true;
			}
			else
			{
				HashEntry *nextEntry = removeEntry->next;
				delete removeEntry;
				prevEntry->next = nextEntry;
				found = true;
			} 
		} // end if
	}// end if
	return found;
} // end remove function

//
void HashTable::getEntry(void visit(), const string key)
{
	HashEntry *find = searchEntry(key);
	
	if (find != NULL)
	{
		//find->athlete->visit();
	}
	else
		cout << "Not Found in the hash table." << endl;
}

// display the hash table's items
void HashTable::printTable() const
{
	for (int i = 0; i<TableSize; i++)
	{
		HashEntry *walk = hashTable[i];
		
		while (walk != NULL)
		{
			//walk->athlete->visit();

			walk = walk->next;
		}
	}
}

// display each bucket of the hash table in indented format
void HashTable::displayBucket() const
{
	for (int i = 0; i<TableSize; i++)
	{
		HashEntry *walk = hashTable[i];

		cout << "Index[" <<  i << "]: ";

		if (walk == NULL)
			cout << " " << endl;
		else
		{
			//walk->athlete->visit();

			while (walk->next != NULL)
			{
				cout << "             ";
				walk->athlete->visit();
				walk = walk->next;
			} // end while
		} //end if
	} // end for
}

// show statistics of the hash table
void HashTable::tableStatistics()
{
	vector<int> nodeCount; // record number of nodes of each bucket
	int linkedListCount = 0; // count number of linked lists
	int longestList = 0; // look up the longest linked list in the hash table
	double averageNode= 0; // average nodes stored in linked lists

	for (int i = 0; i<TableSize; i++)
	{
		int count = 0; // count number of nodes in each bucket
		HashEntry *walk = hashTable[i];
		
		while (walk != NULL)
		{
			walk = walk->next;
			count++; // increment count
		}
		// push back count into the vector
		nodeCount.push_back(count); 

		if (count > 1)
			linkedListCount++; // increment linked list count 
	}

	// calculate average nodes stored in linked list
	averageNode = (double)getCollisions() / linkedListCount;

	for (int i = 0; i<nodeCount.size(); i++)
	{
		// look up the bucket contains longest linked list
		if (nodeCount[i] >= longestList)
		{
			longestList = nodeCount[i];
		}
	}

	cout << "Number of linked lists: " << linkedListCount << endl;
	cout << "Average number of nodes stored in linked lists: ";
	cout << setprecision(3) << averageNode << endl;
	cout << "The longest linked list contains " << longestList << " items.\n";
}

// count total collisions in the hash table
int HashTable::getCollisions() const 
{	
	return collisionFlag;
}

// get total items in the hash table
int HashTable::getCount() const 
{ 
	return itemCount; 
}

// calculate the load factor
double HashTable::getLoadFactor() const
{
	return (double)itemCount / (double)TableSize;
}

// clear up the data stored in the bucket
void HashTable::clearTable()
{
	for (int i = 0; i<TableSize; i++)
	{
		if (hashTable[i] != NULL)
		{
			HashEntry *prev = NULL;
			HashEntry *entry = hashTable[i];

			while (entry != NULL)
			{
				prev = entry;
				entry = entry->next;
				delete prev;
			}
		}
		delete[] hashTable;
	}
}


// destructor
HashTable::~HashTable()
{
	clearTable();
	TableSize = 0;
	itemCount = 0;
	collisionFlag = 0;
}


/******************* private functions definitions *******************/

// hash function
int HashTable::hashFunction(const string searchKey)
{
	int index = 0;
	int temp = 0;

	for (int i = 0; i<searchKey.length(); i++)
	{
		temp += searchKey[i];
	}
	index = temp % TableSize;

	return index;
}

// search the item in the hash entry
HashTable::HashEntry* HashTable::searchEntry(const string key)
{
	int tableIndex = hashFunction(key);

	HashEntry *entry = hashTable[tableIndex];

	if (entry == NULL)
		return 0;

	while (entry != NULL && entry->searchKey != key)
	{
		entry = entry->next;
	}
	return entry;
}

#endif