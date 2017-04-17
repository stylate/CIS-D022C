// Created by: Timothy Li & Alan Nguyen
// This class is derived from Vacation.h with intent to represent the secondary key.
#ifndef _VACATION_CITY
#define _VACATION_CITY

#include "Vacation.h"
#include <iostream>
using namespace std;

class VacationCity : public Vacation {
public:
	VacationCity() {} // default constructor
    VacationCity(const Vacation &vac) {*this = vac;} // copy constructor
	// overloaded operators that compare getCity()
    bool operator>(const Vacation&) const;
    bool operator<(const Vacation&) const;
    bool operator==(const Vacation&) const;
    void operator=(const Vacation& vac);



};
#endif