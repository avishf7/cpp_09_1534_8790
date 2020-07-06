/*
File: program.cpp
Description:
Course: 150018 C++ Workshop, Exercise 9, Question 2
Author: Dan Zilberstein
Students: eli ialoz 311201354
		& avishay farkash 205918790
*/
#include<iostream>
#include"menu.h"
#include"SearchTree.h"
#include "Student.h"
#include <string>
#include <array>

using namespace std;

int main() {
	SearchTree<Student*, int> tree([](Student* const &st) {return st->getId(); }, [](Student* &st) { delete st; });
	SearchTree<Student*, string>* treeByName;
	array<Student*,100> st;
	int id , size = 0;
	MenuOption choice;


	tree.mode(INORDER);


	while ((choice = menu()) != EXIT) {
		switch (choice)
		{
		case ADD:
				st[size] = new Student();

				cin >> *st[size];
				tree.add(st[size++]);
				cout << "Tree after insertion: " << endl;
				tree.process([](Student*& value) { cout << *value << " "; });
				cout << endl;

			break;
		case REMOVE:
			cout << "Insert student id to remove: ";
			cin >> id;
			try 
			{
				tree.remove(id);
				cout << "Tree after removing :";
				tree.process([](Student*& value) { cout << *value << " "; });
				cout << endl;
			}
			catch (const char* str) { cout << str << endl; }
			break;
		case SEARCH:
			cout << "Insert student id to search: ";
			cin >> id;

			try { cout << *(tree.search(id)); }
			catch (const char* str) { cout << str <<endl; };
			break;
		case PRINT_BY_ID:
			cout << "inorder(by id):" << endl;
			tree.process([](Student*& value) { cout << *value << " "; });
			cout << endl;
			break;
		case PRINT_BY_NAME:
			treeByName = new SearchTree<Student*,string>([](Student* const& st) {return st->getFullName(); }, [](Student*& st) {});
			
			for (int j = 0; j < size; ++j)
				treeByName->add(st[j]);
			cout << "inorder(by name):" << endl;
			treeByName->process([](Student*& value) { cout << value->getFullName() << endl; });
			cout << endl;

			delete treeByName;
			treeByName = nullptr;
			break;
		default:
			cout << "ERROR!" << endl;
			break;
		}
	}
	return 0;
}



