#include "addressbook.h"

int main(int argc, char ** argv)
{
	startMenu();
	menu(argc, argv);

    return EXIT_SUCCESS;
}

/* on load of menu program, print student information */
void startMenu()
{
	printf("----------------Welcome to Phone Book------------------\n");
	printf("To get started, type any command accepted by phone book\n");
	printf("If you are new, type help for a list of all commands\n");
	printf("--------------------------------------------------------\n\n");
}


/* takes user input and runs command based on it using if else */
void menu(int argc, char ** argv)
{
	char userInput[50];
	char *userCommand = NULL;
	int moves;

	AddressBookList * list;

	/* when there are 2 arguments, run commandLoad using second argument */
	if(argc == 2)
	{
		list = commandLoad(argv[1]);
	}
	else
	{
		list = createAddressBookList();
	}


	/* menu loop runs until quit is selected */
	while (TRUE)
	{
		printf("Enter command: ");
		fgets(userInput, 50, stdin);

		if (userInput[strlen(userInput) - 1] != '\n')
		{
			readRestOfLine();
			printf("Don't spam your keyboard at me!!!\n\n");
			continue;
		}

		userInput[strlen(userInput)-1] = '\0';

		userCommand = strtok(userInput, " ");

		if (userCommand == NULL)
		{
			printf("You just typed nothing\n\n");
			continue;
		}

		if (strcmp(userCommand, "load") == 0)
		{
			userCommand = strtok(NULL, " ");

			if (userCommand != NULL)
			{
				if (list != NULL)
				{
					freeAddressBookList(list);
				}

				list = commandLoad(userCommand);
			}
			else
			{
				printf("\nPlease enter a file name to load\n\n");
			}
			continue;
		}
		else if (strcmp(userCommand, "unload") == 0)
		{
			if (list != NULL)
			{
				printf("\nAnndddd it's gone!\n\n");
				commandUnload(list);
				list = createAddressBookList();
			}
			else
			{
				printf("Nothing to unload!\n");
			}
			continue;
		}
		else if (strcmp(userCommand, "display") == 0)
		{
			commandDisplay(list);
			continue;
		}
		else if (strcmp(userCommand, "forward") == 0)
		{
			userCommand = strtok(NULL, " ");

			if (userCommand != NULL)
			{
				moves = (int) strtol(userCommand, NULL, 0);
				if (moves == 0)
				{
					printf("Moving is hard anyway\n");
				}
				else
				{
					commandForward(list, moves);
				}
			}
			else
			{
				printf("\nPlease enter a number of moves\n\n");
			}
			continue;
		}
		else if (strcmp(userCommand, "backward") == 0)
		{
			userCommand = strtok(NULL, " ");
			if (userCommand != NULL)
			{
				moves = (int) strtol(userCommand, NULL, 0);
				if (moves == 0)
				{
					printf("Moving is hard anyway\n");
				}
				else
				{
					commandBackward(list, moves);
				}
			}
			else
			{
				printf("\nPlease enter a number of moves\n\n");
			}
			continue;
		}
		else if (strcmp(userCommand, "insert") == 0)
		{
			userCommand = strtok(NULL, " ");

			if (userCommand != NULL)
			{
				commandInsertTokeniser(list, userCommand);
			}
			else
			{
				printf("\nPlease enter a CSV style book entry to insert\n\n");
			}
			continue;
		}
		else if (strcmp(userCommand, "remove") == 0 )
		{
			userCommand = strtok(NULL, " ");

			if (userCommand != NULL)
			{
				commandRemove(list, userCommand);
			}
			else
			{
				printf("\nPlease enter a valid telephone to remove\n\n");
			}
			continue;
		}
		else if (strcmp(userCommand, "find") == 0 )
		{
			userCommand = strtok(NULL, " ");

			if (userCommand != NULL)
			{
				commandFind(list, userCommand);
			}
			else
			{
				printf("\nPlease enter a valid telephone to remove\n\n");
			}
			continue;
		}
		else if (strcmp(userCommand, "delete") == 0)
		{
			commandDelete(list);
			continue;
		}
		else if (strcmp(userCommand, "save") == 0)
		{
			userCommand = strtok(NULL, " ");

			if (userCommand != NULL)
			{
				commandSave(list, userCommand);
			}
			else
			{
				printf("\nPlease enter a file name to load\n\n");
			}
			continue;
		}
		else if (strcmp(userCommand, "add") == 0)
		{
			userCommand = strtok(NULL, " ");

			if (userCommand != NULL)
			{
				commandAdd(list, userCommand);
			}
			else
			{
				printf("\nPlease enter a phone number to add\n\n");
			}
			continue;
		}
		else if (strcmp(userCommand, "help") == 0)
		{
			helpMenu();
			continue;
		}
		else if (strcmp(userCommand, "quit") == 0)
		{
			if (list != NULL)
			{
				freeAddressBookList(list);
			}

			printf("Thank you for using Phone Book\n");
			exit(0);
		}
		printf("\nInvalid Input, please try again\n\n");
	}
}

/* menu to be printed when help is entered */
void helpMenu()
{
	printf("\n\n-------------------Commands list-------------------\n\n");
	printf("Load:\nload a text file of comma seperated values into phone book\n");
	printf("command - load [FILE_NAME]\n\n");
	printf("Unload:\nunload the text file from the phone book\n");
	printf("command - unload\n\n");
	printf("Display:\ndisplays all phones book entries\n");
	printf("command - display\n\n");
	printf("Forward:\nmoves the current tag forward a selected number of times\n");
	printf("command - forward [NUMBER_OF_MOVES]\n\n");
	printf("Backward:\nmoves the current tag backward a selected number of times\n");
	printf("command - backward [NUMBER_OF_MOVES]\n\n");
	printf("Insert:\ninserts a persons data into the phone book\n");
	printf("command - insert [ID] [NAME] [TELEPHONE]\n\n");
	printf("Remove:\nremoves selected telephone number.");
	printf("\n(number must be selected from entry with current tag)\n");
	printf("command - remove [TELEPHONE_NUMBER]\n\n");
	printf("Find:\nfinds an entry based on the name and assigns them the current tag\n");
	printf("command - find [NAME]\n\n");
	printf("Delete:\ndeletes entry with the current tag\n");
	printf("command - delete\n\n");
	printf("Save:\nwrites to a .txt file specified\n");
	printf("command - save [FILE_NAME]\n\n");
	printf("Add:\nadds a telephone number to entry with current tag\n");
	printf("command - add [TELEPHONE_NUMBER]\n\n");
	printf("Quit:\ncloses program\n");
	printf("command - quit\n\n");
}
