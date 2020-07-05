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
	int id , size;
	MenuOption choice;

	tree.mode(INORDER);


	//GET_LEAVES, GET_HEIGHT, REFLECT, LEFT_SONS, GET_LEVEL, REMOVE
	while ((choice = menu()) != EXIT) {
		switch (choice)
		{
		case ADD:
			cout << "Insert student : ";
			cin >> *(st[size]);
			tree.add(st[size++]);
			cout << "Tree after insertion: ";
			tree.process();
			cout << endl;
			break;
		case REMOVE:
			cout << "Insert student id to remove: ";
			cin >> id;
			tree.remove(id);
			cout << "Tree after removing :";
			tree.process();
			cout << endl;
			break;
		case SEARCH:
			cout << "Insert student id to search: ";
			cin >> id;

			try { cout << *(tree.search(id)); }
			catch (const char* str) { cout << str; };
			break;
		case PRINT_BY_ID:
			cout << "inorder(by id):" << endl;
			tree.process();
			cout << endl;
			break;
		case PRINT_BY_NAME:
			treeByName = new SearchTree<Student*,string>([](Student* const& st) {return st->getFullName(); }, [](Student*& st) { delete st; });
			
			for (int j = 0; j < size; ++j)
				treeByName->add(st[j]);
			cout << "inorder(by name):" << endl;
			treeByName->process();
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



