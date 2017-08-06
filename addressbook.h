#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H

#include "commands.h"

AddressBookList * loadMenu(FILE *fp);
void startMenu();
void menu(int argc, char ** argv);
void helpMenu();

#endif
