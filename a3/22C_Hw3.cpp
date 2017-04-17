//
//  CIS 22C - Winter 2017
//  Homework 1
//
//  Build and process a sorted sinlgly-linked list of Mountain objects
//
//  Created by Alan Nguyen
//
// GRADING
//
// 10 - Create a project consisting of at least 5 source and header files
// 10 - Display the number of items in the list
// 20 - Replace the Mountain structure by a Mountain class
// 10 - Improved displayList()
// 10 - Improved searchList()
// 10 - Improved other functions
// 25 - New feature
//  5 - Self assessment
// Did you write comments for the new functions? Yes, I wrote comments for the new functions.
// Did you completely test the program? I completely tested the program with multiple test cases regarding the search/delete functions.
// Did you save the updated output at the end of this source file as a comment? I saved an updated output at the end of the source file.
//
// Student Score: 96 - File parsing may be inefficient (nested loop) and I may have not accounted for backwards traversal in the while loops
//					   themselves in the list functions.
// Instructor Score:
//

#include "MountainList.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

void printInfo();
void readFromFile(MountainList &list);
void deleteManager(MountainList &list);
void searchManager(const MountainList &list);

int main()
{
    MountainList list;
    printInfo();
    readFromFile(list);
	list.displayList();
    list.displayList("d");
    searchManager(list);
    deleteManager(list);
	list.displayList();
	list.displayList("d");
    return 0;
}
//**************************************************
// Print info about the project
//**************************************************
void printInfo()
{
    cout << "\t\t\t Build and process a sorted linked list\n"
         << "\t\t\t     data: Mountains in US\n\n";
}

//**************************************************
// Read items from file and inserts them into a
// sorted linked list
//**************************************************
void readFromFile(MountainList &list)
{
    Mountain temp;
	string buffer;
    ifstream inputfile;
    inputfile.open("mountains.txt");
	if (!inputfile.good()) {
		cout << "Error opening file!\n";
		exit(-1);
	}
	while (!inputfile.eof()) {
		int x = 0, count = 0;
		int tokenArray[4];
		getline(inputfile, buffer);
		// order: name, elevation, range, state
		while (buffer.find(";", x) != string::npos) { // assume that there are only 4 semicolons and categories
			tokenArray[count] = buffer.find(";", x);
			x = buffer.find(";", x) + 1;
			count++;
		}
		temp.set_name(buffer.substr(0, tokenArray[0]));
		temp.set_elevation(stoi(buffer.substr(tokenArray[0] + 1, tokenArray[1])));
		temp.set_range(buffer.substr(tokenArray[1] + 1, tokenArray[2] - (tokenArray[1] + 1)));
		temp.set_state(buffer.substr(tokenArray[2] + 1, tokenArray[3] - (tokenArray[2] + 1)));
		list.insertNode(temp);
	}
    inputfile.close();
}

//**************************************************
// Delete manager: prompt the user to enter
// items, and if found, delets them from the list
//**************************************************
void deleteManager(MountainList &list)
{
    string deleteName;
    
    cout << "\n ====== DELETE ======\n\n";
    do
    {
        
        cout<<"What Mountain do you want to delete? If you dont want to delete a Mountain, enter QUIT \n";
        getline(cin,deleteName);
        if(deleteName!= "quit" && deleteName != "QUIT")
        {
            if(list.deleteNode(deleteName))
                cout<<  deleteName << " deleted\n";
            else
                cout<< deleteName << " not found\n";
                
        }
            
    }while(deleteName!= "quit" && deleteName != "QUIT");
    
}
//**************************************************
// Search manager: prompt the user to enter
// items, and if found, displays related information
//**************************************************
void searchManager(const MountainList &list)
{
    string mountainName;
    
    cout << "\n ====== SEARCH ======\n\n";
    do
    {
        cout <<"What mountain name do you want to search for? If you dont want to search for a mountain enter QUIT \n";
        getline(cin, mountainName);
        if (mountainName!= "quit" && mountainName != "QUIT")
        {
           list.searchList(mountainName);
        }
            
    } while (mountainName!= "quit" && mountainName != "QUIT");
    
}

/*
Build and process a sorted linked list
data: Mountains in US


=====             =========  =====                  =====
Name              Elevation  Range                  State
=====             =========  =====                  =====
Adams                 12281  Cascade Range          Washington
Antero                14276  Sawatch Range          Colorado
Bachelor               9068  Cascade Range          Oregon
Castle Peak            9109  Sierra Nevada          California
Churchill             15638  Saint Elias Mountains  Alaska
Doublet Peak          13600  Wind River Range       Wyoming
Granite Peak          12807  Beartooth Mountains    Montana
Half Dome              8836  Yosemite National Park California
Jeff Davis Peak       12771  Snake Range            Nevada
Mauna Kea             13803  Mauna Kea              Hawaii
Pyramid Peak           9985  Crystal Range          California
Rainier               14411  Cascade Range          Washington
Shasta                14179  Cascade Range          California
Torbert               11413  Tordillo Mountains     Alaska
=================================================================
There are 14 items in the list

=====             =========  =====                  =====
Name              Elevation  Range                  State
=====             =========  =====                  =====
Torbert               11413  Tordillo Mountains     Alaska
Shasta                14179  Cascade Range          California
Rainier               14411  Cascade Range          Washington
Pyramid Peak           9985  Crystal Range          California
Mauna Kea             13803  Mauna Kea              Hawaii
Jeff Davis Peak       12771  Snake Range            Nevada
Half Dome              8836  Yosemite National Park California
Granite Peak          12807  Beartooth Mountains    Montana
Doublet Peak          13600  Wind River Range       Wyoming
Churchill             15638  Saint Elias Mountains  Alaska
Castle Peak            9109  Sierra Nevada          California
Bachelor               9068  Cascade Range          Oregon
Antero                14276  Sawatch Range          Colorado
Adams                 12281  Cascade Range          Washington
=================================================================
There are 14 items in the list


====== SEARCH ======

What mountain name do you want to search for? If you dont want to search for a mountain enter QUIT
Castle Peak
FOUND: Castle Peak 9109 Sierra Nevada California

What mountain name do you want to search for? If you dont want to search for a mountain enter QUIT
ANtero
ANtero NOT FOUND

What mountain name do you want to search for? If you dont want to search for a mountain enter QUIT
quit

====== DELETE ======

What Mountain do you want to delete? If you dont want to delete a Mountain, enter QUIT
Churchill
Churchill deleted
What Mountain do you want to delete? If you dont want to delete a Mountain, enter QUIT
Granite Peak
Granite Peak deleted
What Mountain do you want to delete? If you dont want to delete a Mountain, enter QUIT
Shasta
Shasta deleted
What Mountain do you want to delete? If you dont want to delete a Mountain, enter QUIT
what?
what? not found
What Mountain do you want to delete? If you dont want to delete a Mountain, enter QUIT
SHasta
SHasta not found
What Mountain do you want to delete? If you dont want to delete a Mountain, enter QUIT
QUIT
=====             =========  =====                  =====
Name              Elevation  Range                  State
=====             =========  =====                  =====
Adams                 12281  Cascade Range          Washington
Antero                14276  Sawatch Range          Colorado
Bachelor               9068  Cascade Range          Oregon
Castle Peak            9109  Sierra Nevada          California
Doublet Peak          13600  Wind River Range       Wyoming
Half Dome              8836  Yosemite National Park California
Jeff Davis Peak       12771  Snake Range            Nevada
Mauna Kea             13803  Mauna Kea              Hawaii
Pyramid Peak           9985  Crystal Range          California
Rainier               14411  Cascade Range          Washington
Torbert               11413  Tordillo Mountains     Alaska
=================================================================
There are 11 items in the list

=====             =========  =====                  =====
Name              Elevation  Range                  State
=====             =========  =====                  =====
Torbert               11413  Tordillo Mountains     Alaska
Rainier               14411  Cascade Range          Washington
Pyramid Peak           9985  Crystal Range          California
Mauna Kea             13803  Mauna Kea              Hawaii
Jeff Davis Peak       12771  Snake Range            Nevada
Half Dome              8836  Yosemite National Park California
Doublet Peak          13600  Wind River Range       Wyoming
Castle Peak            9109  Sierra Nevada          California
Bachelor               9068  Cascade Range          Oregon
Antero                14276  Sawatch Range          Colorado
Adams                 12281  Cascade Range          Washington
=================================================================
There are 11 items in the list

DEBUG - Destructor: Now deleting Adams
DEBUG - Destructor: Now deleting Antero
DEBUG - Destructor: Now deleting Bachelor
DEBUG - Destructor: Now deleting Castle Peak
DEBUG - Destructor: Now deleting Doublet Peak
DEBUG - Destructor: Now deleting Half Dome
DEBUG - Destructor: Now deleting Jeff Davis Peak
DEBUG - Destructor: Now deleting Mauna Kea
DEBUG - Destructor: Now deleting Pyramid Peak
DEBUG - Destructor: Now deleting Rainier
DEBUG - Destructor: Now deleting Torbert
Program ended with exit code: 0
*/