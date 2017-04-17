//
//  Mountain.h
//
//
//  Created by: Alan Nguyen
//
//


#ifndef MOUNTAIN_H
#define MOUNTAIN_H

#include <iostream>
#include <string>
using namespace std;

class Mountain {
	string name, range, state;
	int elevation;
public:
	string get_name() const;
	string get_range() const;
	string get_state() const;
	int get_elevation() const;
	void set_name(string temp = "");
	void set_range(string temp = "");
	void set_state(string temp = "");
	void set_elevation(int temp = 0);
};

#endif