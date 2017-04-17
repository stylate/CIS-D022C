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
// Student Score: 100
//
// Instructor Score:
//

#include "MountainList.h"

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

void printInfo();
void readFromFile(MountainList &list);
void deleteManager(MountainList &list);
void searchManager(const MountainList &list);
void stateManager(const MountainList &list);

int main()
{
    MountainList list;
    printInfo();
    readFromFile(list);
    list.displayList();
    cout << "There are " << list.getCount() << " items in the list\n\n";
    searchManager(list);
	stateManager(list);
    deleteManager(list);
    cout << "There are " << list.getCount() << " items in the list\n\n";
    list.displayList();
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
	string space, buffer, buffer2;
	int buff;
    ifstream inputfile;
    inputfile.open("mountains.txt");
    if(!inputfile.good())
        cout <<"Error opening file!\n";
   
    getline(inputfile, buffer);
	temp.set_name(buffer);
    while(!inputfile.eof())
    {
		inputfile >> buff;
		temp.set_elevation(buff);
        inputfile.ignore();
        inputfile.clear();
        getline(inputfile, buffer);
		temp.set_range(buffer);
        getline(inputfile, buffer);
		temp.set_state(buffer);
        getline(inputfile, space);
        list.insertNode(temp);
        getline(inputfile, buffer);
		temp.set_name(buffer);
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
        if(mountainName!= "quit" && mountainName != "QUIT")
        {
           list.searchList(mountainName);
        }
            
    }while(mountainName!= "quit" && mountainName != "QUIT");
    
}

//**************************************************
// State manager: prompt the user to enter
// state, and if found, displays all mountains
// related to such state.
//**************************************************
void stateManager(const MountainList &list)
{
	string stateName;

	cout << "\n ====== STATE ======\n\n";
	do
	{
		cout << "What state do you want to search for? If you dont want to search for a mountain enter QUIT \n";
		getline(cin, stateName);
		if (stateName != "quit" && stateName != "QUIT")
		{
			list.searchState(stateName);
		}

	} while (stateName != "quit" && stateName != "QUIT");

}

/*                          Build and process a sorted linked list
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


 ====== SEARCH ======

What mountain name do you want to search for? If you dont want to search for a mountain enter QUIT
Adams
FOUND: Adams 12281 Cascade Range Washington

What mountain name do you want to search for? If you dont want to search for a mountain enter QUIT
MAuna Kea
MAuna Kea NOT FOUND

What mountain name do you want to search for? If you dont want to search for a mountain enter QUIT
Mauna Kea
FOUND: Mauna Kea 13803 Mauna Kea Hawaii

What mountain name do you want to search for? If you dont want to search for a mountain enter QUIT
Shasta
FOUND: Shasta 14179 Cascade Range California

What mountain name do you want to search for? If you dont want to search for a mountain enter QUIT
Sentinel
Sentinel NOT FOUND

What mountain name do you want to search for? If you dont want to search for a mountain enter QUIT
QUIT

 ====== STATE ======

What state do you want to search for? If you dont want to search for a mountain enter QUIT
California
FOUND: Castle Peak 9109 Sierra Nevada California

FOUND: Half Dome 8836 Yosemite National Park California

FOUND: Pyramid Peak 9985 Crystal Range California

FOUND: Shasta 14179 Cascade Range California

What state do you want to search for? If you dont want to search for a mountain enter QUIT
Montana
FOUND: Granite Peak 12807 Beartooth Mountains Montana

What state do you want to search for? If you dont want to search for a mountain enter QUIT
Alaska
FOUND: Churchill 15638 Saint Elias Mountains Alaska

FOUND: Torbert 11413 Tordillo Mountains Alaska

What state do you want to search for? If you dont want to search for a mountain enter QUIT
Washington
FOUND: Adams 12281 Cascade Range Washington

FOUND: Rainier 14411 Cascade Range Washington

What state do you want to search for? If you dont want to search for a mountain enter QUIT
Sentinel
Sentinel NOT FOUND

What state do you want to search for? If you dont want to search for a mountain enter QUIT
california
california NOT FOUND

What state do you want to search for? If you dont want to search for a mountain enter QUIT
QUIT

 ====== DELETE ======

What Mountain do you want to delete? If you dont want to delete a Mountain, enter QUIT
Adams
Adams deleted
What Mountain do you want to delete? If you dont want to delete a Mountain, enter QUIT
Sentinel
Sentinel not found
What Mountain do you want to delete? If you dont want to delete a Mountain, enter QUIT
Mauna Kea
Mauna Kea deleted
What Mountain do you want to delete? If you dont want to delete a Mountain, enter QUIT
Torbert
Torbert deleted
What Mountain do you want to delete? If you dont want to delete a Mountain, enter QUIT
Quit
Quit not found
What Mountain do you want to delete? If you dont want to delete a Mountain, enter QUIT
QUIT
There are 11 items in the list

=====             =========  =====                  =====
Name              Elevation  Range                  State
=====             =========  =====                  =====
Antero                14276  Sawatch Range          Colorado
Bachelor               9068  Cascade Range          Oregon
Castle Peak            9109  Sierra Nevada          California
Churchill             15638  Saint Elias Mountains  Alaska
Doublet Peak          13600  Wind River Range       Wyoming
Granite Peak          12807  Beartooth Mountains    Montana
Half Dome              8836  Yosemite National Park California
Jeff Davis Peak       12771  Snake Range            Nevada
Pyramid Peak           9985  Crystal Range          California
Rainier               14411  Cascade Range          Washington
Shasta                14179  Cascade Range          California
=================================================================
DEBUG - Destructor: Now deleting Antero
DEBUG - Destructor: Now deleting Bachelor
DEBUG - Destructor: Now deleting Castle Peak
DEBUG - Destructor: Now deleting Churchill
DEBUG - Destructor: Now deleting Doublet Peak
DEBUG - Destructor: Now deleting Granite Peak
DEBUG - Destructor: Now deleting Half Dome
DEBUG - Destructor: Now deleting Jeff Davis Peak
DEBUG - Destructor: Now deleting Pyramid Peak
DEBUG - Destructor: Now deleting Rainier
DEBUG - Destructor: Now deleting Shasta
Program ended with exit code: 0
*/