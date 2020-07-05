#ifndef __MENU_H
#define __MENU_H

enum MenuOption {
	EXIT, ADD, REMOVE, SEARCH, PRINT_BY_ID, PRINT_BY_NAME,
	FIRST_MENU_OPTION = EXIT, LAST_MENU_OPTION = PRINT_BY_NAME
};

MenuOption menu();

#endif // __MENU_H
