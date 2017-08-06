#include "commands.h"


AddressBookList * commandLoad(char * userCommand)
{
	char lineRead[150];
	char *lineToken;
	char *name;
	int id;
	FILE * fp;
	AddressBookList * list = NULL;
	AddressBookNode * node = NULL;

	printf("> Opening the file %s\n", userCommand);
	/*open a file to read only */
	fp = fopen(userCommand, "r");

	if (fp == NULL)
	{
		printf("Error: No file by that name\n\n");

		/* free list if not already empty */
		if (list != NULL)
		{
			freeAddressBookList(list);
			list = createAddressBookList();
		}
		return list;
	}

	list = createAddressBookList();

	while (feof(fp) == FALSE)
	{
		lineRead[0] = '#';

		fgets(lineRead, 150, fp);
		lineRead[strlen(lineRead)-1] = '\0';

		if (lineRead[0] != '#')
		{
			lineToken = strtok(lineRead, ",");
			if (lineToken == NULL)
			{
				printf("> Error: File in wrong format\n");
				freeAddressBookList(list);
				list = createAddressBookList();
				return list;
			}
			else
			{
				if (lineToken == NULL)
				{
					printf("> Error: File in wrong format\n");
					freeAddressBookList(list);
					list = createAddressBookList();
					return list;
				}

				/* create id as an int */
				id = (int) strtol(lineToken, NULL, 10);
				if (id == 0)
				{
					printf("> Error: File in wrong format\n");
					if (list != NULL)
					{
						freeAddressBookList(list);
						list = createAddressBookList();
					}
					return list;
				}
			}

			lineToken = strtok(NULL, ", ");

			if (lineToken != NULL)
			{
				name = lineToken;
			}
			else
			{
				printf("> Error: File in wrong format\n");
				freeAddressBookList(list);
				list = createAddressBookList();
				return list;
			}
			/* create node and initialise array*/
			node = createAddressBookNode(id, name);

			while (lineToken != NULL)
			{
				lineToken = strtok(NULL, ", ");
				if (lineToken != NULL)
				{
					/* fill array with telephone numbers*/
					addTelephone(node->array, lineToken);
				}
			}
			/* insert node w/ full telephone array to list */
			insertNode(list, node);
		}
	}

	printf("> %d phone book entries have been loaded from the file\n", list->size);

	printf("> Closing the file\n\n");
	fclose(fp);

	return list;
}

void commandUnload(AddressBookList * list)
{
	freeAddressBookList(list);
}

void commandDisplay(AddressBookList * list)
{
	/* creates the value of current so the current value can be used to scroll through the list */
	AddressBookNode * listCheck;
	AddressBookNode * currentTemp = list->current;
	int i;
	int serial;
	int nameSize = 0;

	/* used to track number of each entry as well as total number */
	serial = 0;

	list->current = list->head;

	for (i = 0; i < list->size; i++)
	{
		if (strlen(list->current->name) > nameSize)
		{
			nameSize = strlen(list->current->name);
		}
		if (list->current == list->tail)
		{
			break;
		}
		list->current = list->current->nextNode;
	}

	if (nameSize < 7)
	{
		nameSize = 7;
	}

	list->current = currentTemp;

	/* print header of display */
	printf("---------------------------------------------\n");
	printf("| Pos | Serial | ID  | Name %*s| Telephones  | \n", nameSize - 5, "");
	printf("---------------------------------------------\n");
	if (list->head != NULL)
	{
		listCheck = list->current;
		list->current = list->head;

		while (list->current != NULL)
		{
			serial++;
			if (list->current == listCheck)
			{
				printf("| CUR |");
			}
			else
			{
				printf("|     |");
			}

			/* prints the serial, id and name with dynamic spacing */
			printf("%-*d|", 8, serial);
			printf("%-*d|", 5, list->current->id);
			printf("%-*s|", nameSize + 1, list->current->name);

			/* loop through and print all the telephones */
			for (i = 0; i < list->current->array->size; i++)
			{
				/* prints comma before each telephone except the first */
				if (i != 0)
				{
					printf(",");
				}
				printf(" %s", list->current->array->telephones[i]);
			}
			printf("\n");

			list->current = list->current->nextNode;
		}
		if (listCheck != NULL)
		{
			list->current = listCheck;
		}
		else
		{
			list->current = list->head;
		}


	}
	/* prints for blank list */
	else
	{
		printf("|                                           | \n");
	}
	printf("---------------------------------------------\n");
	printf("Total number of phone book entries: %d\n", list->size);
	printf("---------------------------------------------\n\n");
}

void commandForward(AddressBookList * list, int moves)
{
	if (forward(list, moves) == FALSE)
	{
		printf("Oak's words echoed... There's a time and place for everything, but not now\n\n");
	}
	else
	{
		printf("Successfully moved\n\n");
	}
}

void commandBackward(AddressBookList * list, int moves)
{
	if (backward(list, moves) == FALSE)
	{
		printf("Oak's words echoed... There's a time and place for everything, but not now\n\n");
	}
	else
	{
		printf("Successfully moved\n\n");
	}
}

/* tokenises values user provides to save room in menu */
void commandInsertTokeniser(AddressBookList * list, char * token)
{
	int id;
	char * name;
	char * telephone;

	token = strtok(token, ",");

	if (token != NULL)
	{
		id = (int) strtol(token, NULL, 0);

		/* check the id doesn't fail to be converted from string to long */
		if (id == 0)
		{
			printf("Please enter a valid ID and name\n");
			token = NULL;
		}
		if (token != NULL)
		{
			token = strtok(NULL, ", ");
			if (token != NULL)
			{
				name = token;
				token = strtok(NULL, ",");
				if (token != NULL)
				{
					telephone = token;
				}
				commandInsert(list, id, name, telephone);
			}
			else
			{
				printf("Please enter a valid name\n");
			}
		}
	}
}

void commandInsert(AddressBookList * list, int id, char * name, char * telephone)
{
	AddressBookNode * node;

	node = createAddressBookNode(id, name);
	if (insertNode(list, node) == FALSE)
	{
		printf("ID is already in use\n");
	}
	else
	{
		if (telephone != NULL)
		{
			if (addTelephone(list->tail->array, telephone) == TRUE)
			{
				printf("Successfully entered phone book user\n\n");
			}
			else
			{
				printf("Telephone already stored\n\n");
			}
		}
	}
}

void commandAdd(AddressBookList * list, char * telephone)
{
	if (addTelephone(list->current->array, telephone) == TRUE)
	{
		printf("Successfully added telephone\n\n");
	}
	else
	{
		printf("Entry invalid\n\n");
	}
}

void commandFind(AddressBookList * list, char * name)
{
	AddressBookNode * findByNameTemp = findByName(list, name);

	if (findByNameTemp != NULL)
	{
		printf("Search Successful\n\n");
		list->current = findByName(list, name);
	}
	else
	{
		printf("Unable to find name\n\n");
	}
}

void commandDelete(AddressBookList * list)
{
	if (deleteCurrentNode(list) == TRUE)
	{
		printf("Successfully deleted entry\n\n");
	}
	else
	{
		printf("Entry invalid\n\n");
	}

}

void commandRemove(AddressBookList * list, char * telephone)
{
	if (removeTelephone(list->current->array, telephone) == TRUE)
	{
		printf("Successfully removed telephone\n\n");
	}
	else
	{
		printf("Telephone not found\n\n");
	}
}

void commandSave(AddressBookList * list, char * fileName)
{
	FILE * fp;
	char * extension;
	AddressBookNode * currentTemp = list->current;
	int i;
	char fileArray[50];

	/* copy to array from pointer */
	strcpy(fileArray, fileName);

	printf("> Opening file %s\n", fileName);

	/* create extension value to find the file extension */
	extension = strtok(fileArray, ".");
	if (extension != NULL)
	{
		/* set extension to value after . delimitter */
		extension = strtok(NULL, ". ");
	}
	else
	{
		printf("File in wrong format, please include .txt extension\n");
		return;
	}

	if (extension == NULL)
	{
		printf("File in wrong format, please include .txt extension\n");
		return;
	}
	/* makes sure it has .txt extension */
	if (strcmp(extension, "txt") != 0)
	{
		printf("File in wrong format, please include .txt extension\n");
		return;
	}

	/* open mode write */
	fp = fopen(fileName, "w");

	printf("> Writing list content to file\n");

	list->current = list->head;

	/* loops through all values in list printing name, id and telephones in CSV form to file */
	while (list->current != NULL)
	{
		fprintf(fp, "%d,%s", list->current->id, list->current->name);
		for (i = 0; i < list->current->array->size; i++)
		{
			fprintf(fp, ",%s", list->current->array->telephones[i]);
		}
		fprintf(fp, "\n");
		list->current = list->current->nextNode;
	}
	list->current = currentTemp;

	printf("> Closing file\n\n");
	fclose(fp);
}
