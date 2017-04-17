#ifndef _HASH_TABLE
#define _HASH_TABLE

#include "VacationList.h"
#include <iostream>
using namespace std;

/*
Purpose: Creates a hash table with a linked list collision resolution in order to perform the main functions
insert, delete, and search.
*/

// Created by: Anastasiya Osher.
// coded in non-template format


class HashTable {
private:
    int tableSize;
    int load;
    double loadFactor;
    int numberCollisions;
    int count;
	VacationList* array;
	int hash (string);
	int hashBad(string key);
public:
	HashTable(int atableSize);
	~HashTable();
	void insertHash(Vacation&);
	void insertBadHash(Vacation&);
	bool deleteHash(Vacation&);
	void searchHash(string);
	void printHash() const;
	void countStatistics();
	void statistics();
	void rehashing();
	int findNextPrime(int);



	// getters
	int getArray() const;
	int getSize() const;

};

#endif
