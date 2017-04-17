/*
CIS 22C - Winter 2017
Homework 2

Created by Alan Nguyen

GRADING

10 - Create a project consisting of 2 files: Stack.h and 22C_Hw2.cpp
10 - Create and process the array of strings
45 - Read nmbers from file and process stack
10 - Implement the getTop function
10 - Implement the getCount function
10 - The main() function

// Did you write comments for the new functions? Yes, I wrote comments for the new functions.
// Did you completely test the program? I completely tested the program and the output seems to be aligned with what the assignment expects.
// Did you save the updated output at the end of this source file as a comment? I saved an updated output at the end of the source file.
//
// Student Score: 100
//
// Instructor Score:
*/


#include "Stack.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
using namespace std;

void inputProcess(string, Stack<string>*);
bool popNode(int&, Stack<string>*);
bool print(Stack<string>*);

int main() {
	// numbers4.txt is an empty .txt file
	string fileList[] = {"numbers1.txt", "numbers2.txt", "numbers3.txt", "numbers4.txt", "QUIT"};
	Stack<string> *stack = new Stack<string>;
	int size = 0; // array count initializer
	while (fileList[size] != "QUIT") {
		inputProcess(fileList[size], stack);
		size++;
	}
	delete stack;
	cout << "\n\t*** THE END ***\n";
}

// *****************************************************
// The inputProcess function reads in the text files
// and does the necessary stack functions based on
// the string buffer, and then prints the stack total
// once the end of file is reached.
// *****************************************************
void inputProcess(string file, Stack<string> *stack) {
	ifstream fin;
	string buffer;
	int temp;
	fin.open(file);
	if (fin.fail()) {
		cout << "Error opening " << file << "!\n";
		exit(-1);
	}
	cout << "********OUTPUT FOR " << file << " ********\n";
	while (!fin.eof()) {
		fin >> buffer;
		if (buffer.size() == 0) {
			cout << "Empty " << file << "!\n";
			fin.clear();
			system("PAUSE");
			exit(-2);
		}
		if (buffer.find('-') != string::npos) {
			// assuming there exists a negative number from [-999, 0)
			temp = stoi(buffer.substr(1, 3));
			popNode(temp, stack);
		} else if (buffer == "0") {
			cout << "The stack has " << stack->getCount() << " numbers.\n";
		} else if (buffer == "1") {
			cout << stack->getTop() << endl;
		} else {
			stack->push(buffer);
		}
	}
	print(stack);
	fin.clear();
}

// *****************************************************
// The popNode function calls temp and stack. It pops the
// top node from the stack, and then prints out what was
// popped. If temp is greater than getCount, or in other
// words, the function attempts to pop more nodes than 
// what the stack already has, then the function returns 
// false.
// *****************************************************
bool popNode(int& temp, Stack<string> *stack) {
	if (temp > stack->getCount()) {
		cout << "The stack has less than " << temp << " items.\n";
		return false;
	}
	cout << "Popping . . . : ";
	for (int i = 0; i < temp; i++) {
		string temp1 = stack->getTop();
		stack->pop(stack->getTop());
		cout << temp1 << ' ';
	}
	cout << "\n";
	return true;
}

// *****************************************************
// The print function prints out the top node, then
// deletes the node. This process repeats itself until 
// the stack is empty. If the stack is already empty,
// then the function breaks after outputting a statement.
// *****************************************************
bool print(Stack<string> *stack) {
	string temp;
	if (stack->isEmpty()) {
		cout << "\nEmpty stack!\n\n";
		return false;
	} else cout << "Stack total: " << endl;
	for (stack; !stack->isEmpty(); stack->pop(temp)) {
		cout << stack->getTop() << endl;
	}
	cout << endl;
	return true;
}


/*
********OUTPUT FOR numbers1.txt ********
30
The stack has 4 numbers.
Popping . . . : 50 40
Popping . . . : 25 15 30
Stack total:
80
60
20
10

********OUTPUT FOR numbers2.txt ********
The stack has less than 6 items.
Popping . . . : 50 40 30 20 10

Empty stack!

********OUTPUT FOR numbers3.txt ********
The stack has 4 numbers.
45
The stack has 4 numbers.
The stack has 7 numbers.
75
The stack has 7 numbers.
The stack has less than 50 items.
The stack has 7 numbers.
75
The stack has 7 numbers.
Popping . . . : 75 65 55 45 35
The stack has 9 numbers.
90
The stack has 9 numbers.
Popping . . . : 90 80 70
Popping . . . : 54 43 33 23 13
The stack has 6 numbers.
60
The stack has 6 numbers.
The stack has 24 numbers.
99
Popping . . . : 99 89 79 69 59 49
The stack has 18 numbers.
39
The stack has 22 numbers.
The stack has less than 150 items.
The stack has 24 numbers.
Stack total:
64
54
44
34
24
14
39
29
19
97
87
77
67
57
47
7
27
17
60
50
40
10
25
15

********OUTPUT FOR numbers4.txt ********
Empty numbers4.txt!

*/