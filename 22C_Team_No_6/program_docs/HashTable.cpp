#include "HashTable.h"
#include <iostream>
#include <iomanip>
using namespace std;

///////////////////// public definitions /////////////////////
/* constructor
	dynamically allocates memory with an array of linked lists (as the collision resolution) */
HashTable::HashTable(int numLines) {
    tableSize = findNextPrime(numLines*2);
	array = new VacationList[tableSize];
    load = 0;
}

HashTable::~HashTable() {
    delete [] array;
}


/* hash function
   input: processes the key and adds the sum based on the 3rd power
   output: returns the key's location based on modular division */

int HashTable::hash(string key) {
	long int sum = 0;
	for (unsigned i = 0; i < key.length(); i++) {
		sum += key[i] * key[i] * key[i];
	}
	return sum % tableSize;
}
/* bad hash function
   input: processes the key and adds the sum
   output: returns the key's location based on modular division */

int HashTable::hashBad(string key) {
	long int sum = 0;
	for (unsigned i = 0; i < key.length(); i++) {
		sum += key[i];
	}
	return sum % 5;
}

/* insert item into hash
	input: takes in a new item and adds the primary key to the hash table */
void HashTable::insertHash(Vacation& newVacation) {
	int index = hash(newVacation.getCode());
	if (array[index].getCount() == 0)
        load++;
	array[index].insertNode(newVacation);
	rehashing();
}




/* insert item into bad hash
input: takes in a new item and adds the primary key to the hash table */
void HashTable::insertBadHash(Vacation& newVacation) {
	int index = hashBad(newVacation.getCode());
	if (array[index].getCount() == 0)
		load++;
	array[index].insertNode(newVacation);
	rehashing();
}

/* delete item from hash
	input: takes in a possibly existing item and removes the primary key from the hash table
	output: returns true/false depending on deleteNode */
bool HashTable::deleteHash(Vacation& vacation) {
	int index = hash(vacation.getCode());
	cout << "index: " << index << endl;
	system("PAUSE");
	if (array[index].deleteNode(vacation.getCode())) {
 	  if (array[index].getCount() == 0)
         load--;
       return true;
	}
	return false;
}

void HashTable::searchHash(string code) {
	int index = hash(code);
	return array[index].searchList(code);
}

/* print the hash table and the linked list collision reoslutions */
void HashTable::printHash() const {
	cout << "Hash Table:\n";
	for (int i = 0; i < tableSize; i++) {
		array[i].displayList();
	}
}
// Hash table statistics
void HashTable::countStatistics(){
    numberCollisions = 0;
    count = 0;

    for (int i = 0; i < tableSize; i++) {
		count += array[i].getCount();

        if(array[i].getCount() > 1)
        numberCollisions++;
    }
}

// Hash table statistics
void HashTable::statistics(){
    countStatistics();
	loadFactor = (static_cast<double>(load) / static_cast<double>(tableSize)) * 100;
    cout << " Table size: " << tableSize << "\n";
    cout << " Total number of elements: " << count << "\n";
    cout << " Total number of Collisions: " << numberCollisions <<"\n";
    cout << " Total load Factor: " << load << "/" << tableSize << " => " << fixed << setprecision(2) << loadFactor << "% \n";
}

// returns the # of locations in hash table
int HashTable::getSize() const {
	return tableSize;
}

bool isPrime(int number) {
  for (int i=2; i<number; i++) {
    if(number%i == 0)
       return false;
  }
  return true;
}

int HashTable::findNextPrime(int x)
{
    if (x <= 2)
        return 2;
    if (x % 2 == 0)
        x++;
    while (!isPrime(x)) {
        x += 2;
    }
    return x;
}


void HashTable::rehashing()
{
    loadFactor = load*100/tableSize;

    if(loadFactor > 75 ){
        int oldTableSize = tableSize;
        tableSize = findNextPrime(tableSize*2);
        VacationList* oldArray = array;
        array = new VacationList[tableSize];
        load = 0;

        for (int i = 0; i < oldTableSize; i++) {
            ListNode* cur = oldArray[i].nextNode(NULL);
            while (cur  != NULL) {
                insertHash(cur->vacation);
                cur = oldArray[i].nextNode(cur);
            }
        }

        delete [] oldArray;
    }
}





