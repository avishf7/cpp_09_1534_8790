/*
File: Student.h
Description:
Course: 150018 C++ Workshop, Exercise 9, Question 2
Author: Dan Zilberstein
Students: eli ialoz 311201354
		& avishay farkash 205918790
*/
#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
#include <iomanip>

class Student
{
	int _id;
	std::string _name;
	std::string _lastName;

public:
	Student(int id = 0, std::string name = "", std::string lastName = "") :_id(id), _name(name), _lastName(lastName) {}

	//Getter
	const int getId() const { return _id; } 
	const std::string getFullName() const { return std::string(_name + " " + _lastName); }


	friend std::ostream& operator << (std::ostream& out, const Student& st);
	friend std::istream& operator >> (std::istream& in, Student& st);
};

std::istream& operator >> (std::istream& in, Student& st);
std::ostream& operator << (std::ostream& out, const Student& st);

#endif // !STUDENT_H

