//
//  Mountain.cpp
//
//
//  Created by: Alan Nguyen
//
//


#include "Mountain.h"
#include <iostream>
#include <string>
using namespace std;

Mountain::Mountain() {
	name = "";
	range = "";
	state = "";
	elevation = 0;
}

//**************************************************
// The get_name function returns the name.
//**************************************************
string Mountain::get_name() const {
	return name;
}

//**************************************************
// The get_range function returns the range.
//**************************************************
string Mountain::get_range() const {
	return range;
}

//**************************************************
// The get_state function returns the state.
//**************************************************
string Mountain::get_state() const {
	return state;
}

//**************************************************
// The get_elevation function returns the elevation.
//**************************************************
int Mountain::get_elevation() const {
	return elevation;
}

//**************************************************
// The set_name function calls string temp and
// initializes name as temp. By default, it is
// initialized as "".
//**************************************************
void Mountain::set_name(string temp) {
	name = temp;
}

//**************************************************
// The set_range function calls string temp and
// initializes range as temp. By default, it is
// initialized as "".
//**************************************************
void Mountain::set_range(string temp) {
	range = temp;
}

//**************************************************
// The set_state function calls string temp and
// initializes state as temp. By default, it is
// initialized as "".
//**************************************************
void Mountain::set_state(string temp) {
	state = temp;
}

//**************************************************
// The set_elevation function calls string temp and
// initializes elevation as temp. By default, it is
// initialized as 0.
//**************************************************
void Mountain::set_elevation(int temp) {
	elevation = temp;
}