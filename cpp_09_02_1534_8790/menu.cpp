/*
File: menu.cpp
Description:
Course: 150018 C++ Workshop, Exercise 9, Question 2
Author: Dan Zilberstein
Students: eli ialoz 311201354
		& avishay farkash 205918790
*/
#include<iostream>
#include<iomanip>
#include"menu.h"

using namespace std;

MenuOption operator++(MenuOption& rhs) {
	rhs = MenuOption(int(rhs) + 1);
	return rhs;
}

const char* MenuOptionLine[LAST_MENU_OPTION + 1] {
	"Exit",
	"Insert Student to searchTree",
	"Remove Student from searchTree by id",
	"Search Student in the searchTree by id",
	"Print out all Students by id order",
	"Print out all Students by name order",
};

istream& operator >> (istream& in, MenuOption& rhs) {
	int value;
	in >> value;
	rhs = MenuOption(value);
	return in;
}

ostream& operator<<(ostream& out, MenuOption rhs) {
	out << setw(4) << int(rhs) << "\t--\t" << MenuOptionLine[rhs];
	return out;
}

MenuOption menu() {
	MenuOption chosen;

	cout << endl << "Menu options:" << endl << endl;

	for (chosen = FIRST_MENU_OPTION; chosen <= LAST_MENU_OPTION; ++chosen)
		cout << chosen << endl;
	cout << endl;

	cout << "Please choose a menu option: ";
	cin >> chosen;
	return chosen;
}