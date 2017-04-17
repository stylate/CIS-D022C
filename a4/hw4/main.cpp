// main test driver for BST
// Created by Frank M. Carrano and Tim Henry.
// modified by Elizabeth Chang
// Student Score: 91
// Instructor Score:

#include "BinarySearchTree.h"  // BST ADT
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Student
{
private:
    string id;
    string name;
    double gpa;
public:
    void setId(string y) {id=y;}
    void setName(string s) {name=s;}
    void setGpa(double x) {gpa=x;}
    string getId() {return id;}
    string getName() {return name;}
    double getGpa() {return gpa;}
    
};


// display function to pass to BST traverse functions
void display(Student & studentSearchNode)
{
    cout << studentSearchNode.getId() <<" "
         << studentSearchNode.getName() <<" "
         << studentSearchNode.getGpa() << endl;
    
}
//checks for entry
void check(bool success)
{
    if (success)
        cout << "Done." << endl;
    else
        cout << " Entry not in tree." << endl;
}

//**************************************************
// displays the menu
//**************************************************
char menu()
{
    char choice;
    cout << "D – Depth-First Traversals: inorder, preorder, postorder " <<endl
        << "B – Tree Breadth-First Traversals: Print by level " <<endl
        << "S – Search by the primary key (student ID – unique key)" << endl
        << "M – Find the smallest ID" <<endl
        << "X – Find the largest ID" <<endl
        << "T – Print the BST as an indented list " <<endl
        << "H – Help – to show the menu" <<endl
        << "E – Exit." <<endl;
    cout << "What would you like to do? ";
    cin >> choice;
    
    return choice;
}
//**************************************************
// Read items from file and inserts them into a
// sorted linked list
//**************************************************
void readFromFile( BinarySearchTree <Student> *studentSearch)
{
    
    Student temp;
    string space;
    string holdId, holdName, holdGpa;
    double numHold1;
    
    
    ifstream inputfile;
    inputfile.open("gpa.txt");
    if(!inputfile.good())
        cout <<"Error opening file!\n";
    
    getline(inputfile, holdId, ' ' );
    temp.setId(holdId);

    
    while(inputfile.good())
    {
        
        getline(inputfile, holdName, ';');
        temp.setName(holdName);
        
        getline(inputfile, holdGpa);
        numHold1=stod(holdGpa);
        temp.setGpa(numHold1);

        
        studentSearch->insert(temp);
        inputfile.clear();
        
        getline(inputfile, holdId, ' ');
        temp.setId(holdId);

        
    }
    inputfile.close();
}

int main()
{
    BinarySearchTree <Student> * studentSearch =new BinarySearchTree<Student>;
    
    readFromFile(studentSearch);
    char choice= menu();

    while (choice!='E' && choice!='e')
    {
        
        switch (choice)
        {
            case 'd':
            case 'D': {
                cout <<"INORDER DISPLAY: " <<endl;
                studentSearch->inOrder(display);
                cout <<"PREORDER DISPLAY: " <<endl;
                studentSearch->preOrder(display);
                cout <<"POSTORDER DISPLAY: " <<endl;
                studentSearch->postOrder(display);
            }
                break;
            case 'b':
            case 'B': {
                cout <<"BREADTH FIRST TRAVERSAL " <<endl;
                studentSearch->breadthTraversal(display);
            }
                break;
            case 's':
            case 'S': {
                Student target;
                Student result;
                result.setId("");
                string holdId;
                cout <<"Please enter student ID number: ";
                cin >>holdId;
                target.setId(holdId);
                studentSearch->getEntry(target, result);
                
            }
                break;
            case 'm':
            case 'M':
            {
                Student result;
                studentSearch->getSmallestEntry(result);
                cout <<"The smallest entry is: " <<result.getId() <<endl;
            }
                break;
            case 'x':
            case 'X':
            {
                Student result;
                studentSearch->getLargestEntry(result);
                cout <<"The largest entry is: " <<result.getId() <<endl;
            }
                break;
            case 't':
            case 'T': //Print the BST as an indented list (show level numbers)// see below // recursive
                studentSearch->printTree(display);
                break;
            case'a':
            case 'A': cout <<"Developer: Elizabeth Chang" <<endl;
                break;
            case 'h':
            case 'H': menu();
                break;
            default: cout <<"NOT VALID ENTRY! " <<endl;
                
        }
        cout <<"What would you like to do? ";
        cin >> choice;
    }
     return 0;
}

