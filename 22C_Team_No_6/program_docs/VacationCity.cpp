// Created by: Timothy Li & Alan Nguyen

#include "VacationCity.h"
#include <iostream>
#include <string>
using namespace std;

bool VacationCity::operator>(const Vacation& compare) const {
    string c1 = getCity();
    string c2 = compare.getCity();
    if (c1 > c2)
        return true;
    else
        return false;	
}

bool VacationCity::operator<(const Vacation& compare) const {
    string c1 = getCity();
    string c2 = compare.getCity();
    if (c1 < c2)
        return true;
    else
        return false;	
}

bool VacationCity::operator==(const Vacation& compare) const {
    string c1 = getCity();
    string c2 = compare.getCity();
    if (c1 == c2)
        return true;
    else
        return false;	
}

//*********************************************************
// Copies contents of Vacation -> VacationCity.
//*********************************************************
void VacationCity::operator=(const Vacation& vac) {
    this->code = vac.getCode();
    this->city = vac.getCity();
    this->currency = vac.getCurrency();
    this->location = vac.getLocation();
    this->price = vac.getTicket();	
}