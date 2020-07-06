/*
File: menu.h
Description:
Course: 150018 C++ Workshop, Exercise 9, Question 2
Author: Dan Zilberstein
Students: eli ialoz 311201354
		& avishay farkash 205918790
*/
#ifndef __MENU_H
#define __MENU_H

enum MenuOption {
	EXIT, ADD, REMOVE, SEARCH, PRINT_BY_ID, PRINT_BY_NAME,
	FIRST_MENU_OPTION = EXIT, LAST_MENU_OPTION = PRINT_BY_NAME
};

MenuOption menu();

#endif // __MENU_H
