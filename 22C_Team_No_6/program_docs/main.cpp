/* main designed by: Alan Nguyen & Elizabeth Chang.
Program Function: This is the main cpp file for this program and it creates both the BST and hash tables. Then, it asks for
user input through a menu.
*/

#include "Vacation.h"
#include "VacationCity.h"
#include "BinarySearchTree.h"
#include "HashTable.h"
#include "Stack.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>


using namespace std;

//**************************************************
// Welcomes the user into the program.
//**************************************************
void intro() {
	cout << "Welcome to the vacation trip planner!\n\n"
		<< "In here, you will be able to view the airport code and its respective city, currency, location, and ticket prices from SFO to target destination.\n\n";
}

//**************************************************
// Provides a menu for the user to navigate through.
//**************************************************
char menu(char& key) {
	cout << "Please enter any of the following keys below to access their functions:\n\n"
		<< "I - Insert Manager\n"
		<< "D - Delete Manager\n"
		<< "N - Undo Delete\n"
		<< "L - List Manager\n"
		<< "S - Search Manager\n"
		<< "E - Exit Program\n";
	cin >> key;
	return key;
}

// display function to pass to BST traverse functions (primary key)
void display(Vacation& searchNode) {
	cout << setw(7) << left << searchNode.getCode()
		<< setw(22) << right << searchNode.getCity() << "  "
		<< setw(24) << left << searchNode.getCurrency() << " " << left
		<< setw(23) << searchNode.getLocation()
		<< setw(7) << right << searchNode.getTicket() << endl;
}

// display function to pass to BST traverse functions (secondary key)
void display(VacationCity& searchNode) {
	cout << setw(7) << left << searchNode.getCode()
		<< setw(22) << right << searchNode.getCity() << "  "
		<< setw(24) << left << searchNode.getCurrency() << " " << left
		<< setw(23) << searchNode.getLocation()
		<< setw(7) << right << searchNode.getTicket() << endl;
}

// indent trees for BST (primary key)
void indent(Vacation& indentNode, int level) {
	cout << level << ": " << indentNode.getCode() << " "
		<< indentNode.getCity() << " "
		<< indentNode.getCurrency() << " "
		<< indentNode.getLocation() << " "
		<< indentNode.getTicket() << endl;
}


void fileReader(BinarySearchTree<Vacation>*, BinarySearchTree<VacationCity>*, HashTable&);
void vacationMenu(BinarySearchTree<Vacation>*, BinarySearchTree<VacationCity>*, HashTable&, Stack<Vacation>*);
void insertManager(BinarySearchTree<Vacation>*, BinarySearchTree<VacationCity>*, HashTable&);
void deleteManager(BinarySearchTree<Vacation>*, BinarySearchTree<VacationCity>*, HashTable&, Stack<Vacation>*);
void undoManager(BinarySearchTree<Vacation>*, BinarySearchTree<VacationCity>*, HashTable&, Stack<Vacation>*);
void searchManager(BinarySearchTree<Vacation>*, BinarySearchTree<VacationCity>*, HashTable&);
void listManager(BinarySearchTree<Vacation>*, BinarySearchTree<VacationCity>*, HashTable&);
int fileLineCounter();

int main() {
	Stack<Vacation> *holdDel = new Stack<Vacation>;
	BinarySearchTree<Vacation>* primaryPlanner = new BinarySearchTree<Vacation>;
	BinarySearchTree<VacationCity>* secondaryPlanner = new BinarySearchTree<VacationCity>;
	int lines = fileLineCounter();
	HashTable hashTable(lines);
	fileReader(primaryPlanner, secondaryPlanner, hashTable);
	intro();
	vacationMenu(primaryPlanner, secondaryPlanner, hashTable, holdDel);
	primaryPlanner->printToFile(display); //prints to outFile sorted by inOrder display
}

//*******************************************************************
// Switch menu that calls other functions based on the user's choice.
//*******************************************************************
void vacationMenu(BinarySearchTree<Vacation>* planner, BinarySearchTree<VacationCity>* secondaryPlanner, HashTable& hashTable, Stack<Vacation> *holdDel) { // core of the program. include copying tree here.
	char key = ' ';
	while (key != 'E' || key != 'e') {
		menu(key);
		switch (key) {
		case 'i':
		case 'I': insertManager(planner, secondaryPlanner, hashTable); break;
		case 'd':
		case 'D': deleteManager(planner, secondaryPlanner, hashTable, holdDel); break;
		case 'n':
		case 'N': undoManager(planner, secondaryPlanner, hashTable, holdDel); break;
		case 'l':
		case 'L': listManager(planner, secondaryPlanner, hashTable); break;
		case 's':
		case 'S': searchManager(planner, secondaryPlanner, hashTable); break;
		case 'e':
		case 'E': return;
		default: cout << "Not a valid input. Please try again!" << endl;
		}
	}
}

//**********************************************************************************
// Reads in the input file and adds its contents to the two BSTs and the hash table.
//**********************************************************************************
void fileReader(BinarySearchTree<Vacation>* vacation1, BinarySearchTree<VacationCity>* vacation2, HashTable& hashTable) {
	Vacation temp;
	string holdName; // buffer
	int numHold1; // buffer for int type

	ifstream inputfile;
	inputfile.open("travelData.txt"); // default
	if (!inputfile.good()) {
		cout << "Error opening file!\n";
		exit(-1);
	}

	while (!inputfile.eof()) {
		getline(inputfile, holdName, ',');
		temp.setCode(holdName);

		getline(inputfile, holdName, ';');
		temp.setCity(holdName);

		getline(inputfile, holdName, ';');
		temp.setCurrency(holdName);

		getline(inputfile, holdName, ';');
		temp.setLocation(holdName);

		getline(inputfile, holdName, '\n');
		numHold1 = atoi(holdName.c_str());
		temp.setTicket(numHold1);

		vacation1->insert(temp);
		vacation2->insert(temp);
		hashTable.insertHash(temp);
	}
	inputfile.close();
}

//*********************************************************
// Inserts user input into 2 of the BSTs and 1 hash table.
//*********************************************************
void insertManager(BinarySearchTree<Vacation>* planner, BinarySearchTree<VacationCity>* planner2, HashTable& hashTable) {
	string buffer;
	Vacation temp, result;
	int ticket;
	cin.ignore();
	cout << "Please enter the airport code: ";
	getline(cin, buffer);
	temp.setCode(buffer);
	if(planner->getEntry(temp, result))
    	{
	    cout << "Code already exists\n";
	    return;
	}
	cout << "Please enter the desired city: ";
	getline(cin, buffer);
	temp.setCity(buffer);
	cout << "Please enter the country's currency: ";
	getline(cin, buffer);
	temp.setCurrency(buffer);
	cout << "Please enter the most popular location: ";
	getline(cin, buffer);
	temp.setLocation(buffer);
	cout << "Please enter the ticket price from SFO to the destination: ";
	cin >> ticket;
	temp.setTicket(ticket);

	planner->insert(temp);
	planner2->insert(temp);
	hashTable.insertHash(temp);
}

//************************************************************
// Remove node from 2 BSTs and hash table based on user input
//************************************************************
void deleteManager(BinarySearchTree<Vacation>* planner, BinarySearchTree<VacationCity>* planner2, HashTable& hashTable, Stack<Vacation>* holdDel) {
	string buffer;
	Vacation temp, result;
	cout << "What airport code would you like to delete?\n";
	cin >> buffer;
	temp.setCode(buffer);
	bool found = false;

	if (planner->getEntry(temp, result))
	{
		holdDel->push(result);
		found = planner->remove(temp);
		planner2->remove(temp);
		hashTable.deleteHash(temp);
		if (found)
			cout << "The node has been removed!\n";
	}
	else
		cout << "Node deletion was unsuccessful.\n";
}

//**************************************************
// Uses a stack to undo deletion.
//**************************************************
void undoManager(BinarySearchTree<Vacation>* planner, BinarySearchTree<VacationCity>* planner2, HashTable& hashTable, Stack<Vacation>* holdDel) {
	Vacation temp;
	if (holdDel->isEmpty())
		cout << "Nothing has been deleted.\n";
	else
	{
		holdDel->pop(temp);
		planner->insert(temp);
		planner2->insert(temp);
		hashTable.insertHash(temp);
		cout << "Deleted item restored!\n";
	}


}

//**************************************************************
// Prompts the user to print the list based on various orders.
//**************************************************************
void listManager(BinarySearchTree<Vacation>* planner, BinarySearchTree<VacationCity>* secondaryPlanner, HashTable& hashTable) {
	char key = ' '; // initializer
	int level = 1; // initializer
	cout << "U - Print the list by unsorted order (in hash table sequence).\n"
		<< "P - Print the list by primary key order.\n"
		<< "S - Print the list by secondary key order.\n"
		<< "I - Print the list in (primary) indent order.\n"
		<< "B - Go back to the main menu.\n";
	cin >> key;
	switch (key) {
	case 'u':
	case 'U': hashTable.printHash(); hashTable.statistics(); break; // unsorted
	case 'p':
	case 'P': planner->inOrder(display); break; // primary key
	case 's':
	case 'S': secondaryPlanner->inOrder(display); break; // secondary key
	case 'i':
	case 'I': planner->printTree(indent, level); cout << endl; break; // indent
	case 'b':
	case 'B': break; // go back to main menu
	}
}

//*********************************************************
// Prompts the user to search for an airport code or city.
//*********************************************************
void searchManager(BinarySearchTree<Vacation>* planner, BinarySearchTree<VacationCity>* secondaryPlanner, HashTable& hashTable) {
	char key = ' ';
	Vacation target, result;
	VacationCity cityTarget, cityResult;
	string buffer;

	target.setCity("");
	target.setCode("");
	cout << "P - Search for an airport code.\n"
		<< "S - Search for a city.\n"
		<< "B - Go back to the main menu.\n";
	cin >> key;
	switch (key) {
	case 'p':
	case 'P':
		cout << "Please enter the airport code: ";
		cin >> buffer;
		target.setCode(buffer);
		/*if (planner->getEntry(target, result))
		{
			display(result);
		} else
			cout <<"NOT FOUND! " <<endl;*/
		hashTable.searchHash(buffer);
		break; // primary key
	case 's':
	case 'S':
		cin.ignore();
		cout << "Please enter the city: ";
		getline(cin, buffer);
		cityTarget.setCity(buffer);
		if (secondaryPlanner->getEntry(cityTarget, cityResult))
		{
			display(cityResult);
		} else
			cout <<"NOT FOUND! " <<endl;
		break; // secondary key
	case 'b':
	case 'B': break; // go back to main menu
	default: cout << "Not a valid input. Please try again!" << endl;
	}
}

//*********************************************************
// function to count how many lines of input is read from the file
//*********************************************************
int fileLineCounter() {
	int counter = 0;
	string holdName;
	ifstream inputfile;
	inputfile.open("travelData.txt"); // default
	if (!inputfile.good()) {
		cout << "Error opening file!\n";
		exit(-1);
	}
	while (!inputfile.eof()) {
		getline(inputfile, holdName, '\n');
		counter++;
	}
	inputfile.close();

	return counter;
}
