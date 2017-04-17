// main test driver for BST
// Created by Frank M. Carrano and Tim Henry.
// modified by Alan Nguyen
// Did you write comments for the new functions? Yes, I wrote comments for the new functions.
// Did you completely test the program? I completely tested the program with multiple test cases regarding the search/delete functions.
// Did you save the updated output at the end of this source file as a comment? I saved an updated output onto a text file titled "BST_Output.txt."
//
// Student Score: 100
// Instructor Score:
//



#include "BinarySearchTree.h"  // BST ADT 
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

// display function to pass to BST traverse functions
void display(string & anItem, string& aName, string& aGPA) // traversal
{
	cout << "Displaying item, name, and GPA: " << anItem << " " << aName << " " << aGPA << endl;
}
// indent function to print an indented list representing the BST
void indent(string& anItem, string& aName, string& aGPA, int level) { // indent
	cout << level << ": " << anItem << " " << aName << " " << aGPA << endl;
}

void check(bool success) // deleting a node
{
	if (success)
		cout << "Done." << endl;
	else
		cout << " Entry not in tree." << endl;
}
char menu(char& key);
void hidden();

template <class ItemType>
// fileReader reads the input file, then parses the text into a tree with three member objects.
BinarySearchTree<ItemType>* fileReader(BinarySearchTree<ItemType>*);

template <class ItemType>
// displays preorder, inorder, and postorder contents
void depth(BinarySearchTree<ItemType>*);

template <class ItemType>
// calls the breadth function
void breadth(BinarySearchTree<ItemType>*);

template <class ItemType>
// prompts the user for what node to search, then calls the appropriate function.
void searchKey(BinarySearchTree<ItemType>*);

template <class ItemType>
// prints out a statement returning either the min or max
void returnValues(BinarySearchTree<ItemType>*, string&);

int main() {
	char key = ' ';
	string valueKey;
	int level = 1;
	BinarySearchTree<string>* tree1 = new BinarySearchTree<string>();
	fileReader(tree1);
	while (key != 'E') {
		menu(key);
		switch (key) {
		case 'D': depth(tree1); break;
		case 'B': breadth(tree1); break;
		case 'S': searchKey(tree1); break;
		case 'M': valueKey = "smallest";
			returnValues(tree1, valueKey);
			break;
		case 'X': valueKey = "largest";
			returnValues(tree1, valueKey);
			break;
		case 'T': tree1->preIndent(indent, level); break;
		case 'A': hidden(); break;
		case 'H': cout << endl; break;
		case 'E': break;
		default: cout << "The key that you inputted is not apart of the menu! Please try again.\n\n"; break;
		}
	}
	tree1->clear();
}

char menu(char& key) {
	cout << "Enter any of the keys below to start the program.\n"
		<< "Note: ONLY ALL-CAPS WILL BE ACCEPTED, THUS THIS MENU IS CASE SENSITIVE.\n"
		<< "D - Depth-First Traversals: inorder, preorder, postorder\n"
		<< "B - Tree Breadth - First Traversals : Print by level\n" // iterative (Use the CIS22C queue library, no STL please)
		<< "S - Search by the primary key (student ID - unique key)\n" // iterative
		<< "M - Find the smallest\n" // recursive
		<< "X - Find the largest\n" // recursive
		<< "T - Print the BST as an indented list (show level numbers)\n" // recursive
		// << "A - This is a hidden option.When chosen, display the name of the developer.\n"
		<< "H - Help - to show the menu, and\n"
		<< "E - Exit.\n";
	cin >> key;
	return key;
}

void hidden() { cout << "This program was developed by Alan Nguyen.\n"; }

template <class ItemType>
BinarySearchTree<ItemType>* fileReader(BinarySearchTree<ItemType>* treePtr) {
	ifstream fin; 
	ItemType buffer, number, gpa;
	fin.open("gpa.txt");
	if (!fin.good()) {
		cout << "Error opening file!\n";
		exit(-1);
	}
	while (!fin.eof()) {
		fin >> number; // gets key
		fin.ignore(); // ignore ws
		getline(fin, buffer, ';');
		fin >> gpa; // gets gpa
		treePtr->insert(number, gpa, buffer);
	}
	fin.close();
	return treePtr;
}

template <class ItemType>
void depth(BinarySearchTree<ItemType>* treePtr) {
	cout << "\nCalling preOrder:\n\n";
	treePtr->preOrder(display);
	cout << "\nCalling inOrder:\n\n";
	treePtr->inOrder(display);
	cout << "\nCalling postOrder:\n\n";
	treePtr->postOrder(display);
	cout << endl;
}

template <class ItemType>
void breadth(BinarySearchTree<ItemType>* treePtr) {
	cout << "\nBreadth-first traversal:\n\n";
	treePtr->breadth(display);
	cout << endl;
}

template <class ItemType>
void searchKey(BinarySearchTree<ItemType>* treePtr) {
	ItemType uniqueKey;
	string returnedString;
	cout << "\nWhat student ID would you like to search for? ";
	cin >> uniqueKey;
	cout << "Node " << uniqueKey << " returns " << treePtr->getEntry(uniqueKey, returnedString) << "!\n\n";
}

template <class ItemType>
void returnValues(BinarySearchTree<ItemType>* treePtr, string& button) {
	cout << "The " << button << " value is " << treePtr->minMax(button) << ".\n\n";
}