// Created by: Timothy Li & Alan Nguyen
// This class represents all of the data members of the input file.

#ifndef _VACATION
#define _VACATION

#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

class Vacation {
protected:
	string code;
	string city;
	string currency;
	string location;
	double price;
public:
	// accessors
	void setCode(const string& aCode) { code = aCode; }
	void setCity(const string& aCity) { city = aCity; }
	void setCurrency(const string& aCurrency) { currency = aCurrency; }
	void setLocation(const string& aLocation) { location = aLocation; }
	void setTicket(const double& aTicket) { price = aTicket; }

	// mutators
	string getCode() const { return code; }
	string getCity() const { return city; }
	string getCurrency() const { return currency; }
	string getLocation() const { return location; }
	double getTicket() const { return price; }

	void print() const; // for hashing

	// overloaded operators that compare getCode()
	bool operator>(const Vacation& compare) const;
	bool operator<(const Vacation& compare) const;
	bool operator==(const Vacation& compare) const;
};

#endif