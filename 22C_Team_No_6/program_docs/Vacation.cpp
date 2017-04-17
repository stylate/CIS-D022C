#include "Vacation.h"
#include <iostream>
using namespace std;

//*********************************************************
// Display for hash table
//*********************************************************
void Vacation::print() const {
        cout << setw(7) << left << code
             << setw(22) << right << city << "  "
             << setw(24) << left << currency << " " << left
             << setw(23) << location
             << setw(7) << right << price << endl;	
}

bool Vacation::operator>(const Vacation& compare) const {
	if (this->getCode() > compare.getCode())
		return true;
	else
		return false;	
}

bool Vacation::operator<(const Vacation& compare) const {
	if (this->getCode() < compare.getCode())
		return true;
	else
		return false;	
}

bool Vacation::operator==(const Vacation& compare) const {
	if (this->getCode() == compare.getCode())
		return true;
	else
		return false;
}