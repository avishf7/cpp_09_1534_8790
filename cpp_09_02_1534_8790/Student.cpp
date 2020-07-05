/*
File: Student.cpp
Description:
Course: 150018 C++ Workshop, Exercise 9, Question 2
Author: Dan Zilberstein
Students: eli iluz 311201354
		& avishay farkash 205918790
*/
#include "Student.h"
using namespace std;

std::istream& operator>>(std::istream& in, Student& st)
{
	cout << "Enter student details:" << endl;
	cout << "\nid(1 - 999) - ";
	in >> st._id;

	if (st._id < 1 || st._id > 999)
		throw "ERROR: id out of range\n";

	cout << "first name - ";
	in >> setw(21) >> st._name;

	cout << "last name - ";
	in>> setw(21) >> st._lastName;

	return in;
}

ostream& operator<<(ostream& out, const Student& st)
{
	out << "id: " << st._id << endl
		<< "first name: " << st._name << endl
		<< "last name: " << st._lastName << endl;
		

	return out;
}

