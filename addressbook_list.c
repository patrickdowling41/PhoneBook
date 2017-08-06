 #include "addressbook_list.h"

AddressBookNode * createAddressBookNode(int id, char * name)
{
    /* Allocates and initialises a new AddressBookNode */
	AddressBookNode * addressBookNode = malloc(sizeof(*addressBookNode));
	if(addressBookNode != NULL)
	{
		addressBookNode->id = id;
		strcpy(addressBookNode->name, name);
		addressBookNode->nextNode = NULL;
		addressBookNode->previousNode = NULL;
		addressBookNode->array = createAddressBookArray();
	}
	return addressBookNode;
}

AddressBookList * createAddressBookList()
{
  /* Allocates and initialises a new AddressBookList. */
	AddressBookList * addressBookList = malloc(sizeof(*addressBookList));
	if (addressBookList != NULL)
	{
		addressBookList->head = NULL;
		addressBookList->tail = NULL;
		addressBookList->current = NULL;
		addressBookList->size = 0;
	}

	return addressBookList;
}

void freeAddressBookList(AddressBookList * list)
{

	AddressBookNode * listCurrentTemp = NULL;

	/* set current to first node */
	list->current = list->head;

	/* free all nodes first */
	while (list->current != NULL)
	{
		listCurrentTemp = list->current;
		list->current = list->current->nextNode;
		freeAddressBookNode(listCurrentTemp);
	}
	/* free list after nodes are all free */
	free(list);

}

void freeAddressBookNode(AddressBookNode * node)
{
    /*  Free's the array within the node and the AddressBookNode itself.*/
	freeAddressBookArray(node->array);
	free(node);
}

Boolean insertNode(AddressBookList * list, AddressBookNode * node)
{
	 /* stores the current value in a variable that isn't
	 affected by the use of current to track place in the linked list */
	 AddressBookNode * listCurrent;
	 listCurrent = list->current;

	 if (list->head == NULL)
	 {
		 list->head = node;
		 list->tail = node;
     list->current = node;
		 list->size += 1;
		 return TRUE;
	 }

	 list->current = list->head;

	 /* make sure id doesn't match any node in list */
	 while (TRUE)
	 {
		 if (list->current == NULL)
		 {
			 break;
		 }

		 if (list->current->id == node->id)
		 {
			 return FALSE;
		 }
		 else
		 {
			 list->current = list->current->nextNode;
		 }
	 }
	 list->current = node;

	 /* add node to list of nodes */
	 list->tail->nextNode = list->current;
	 list->current->previousNode = list->tail;
	 list->tail = list->current;

	 list->size += 1;

	 /* make list current is equal to head if not specified,
	 if specified, reset it to the temp value stored at the start */
	 if (listCurrent != NULL)
	 {
		 list->current = listCurrent;
	 }
	 else
	 {
		 list->current = list->head;
	 }

    return TRUE;
}

Boolean deleteCurrentNode(AddressBookList * list)
{
	 AddressBookNode * listPrev;
	 AddressBookNode * listNext;

   /* cases need to be taken into account for deleting are, if there is no list, node is only
   one in list, first in list, last in list and any other position in list */

	 /* for case where no nodes are in list */
	 if (list->current == NULL)
	 {
		 list->current = list->head;
		 /* for empty list */
		 if (list->head == NULL)
		 {
			 return FALSE;
		 }
	 }

	 /* for case where it is only node in the list */
	 if (list->size == 1)
	 {
     /* frees whole list because there is no other node that can be deleted */
		 freeAddressBookList(list);
		 list = createAddressBookList();
		 return TRUE;
	 }

	 /* for case where node is first value in list */
	 if (list->current == list->head)
	 {
		 list->current->nextNode->previousNode = NULL;
		 list->head = list->current->nextNode;
		 freeAddressBookNode(list->current);
		 list->current = list->head;
		 list->size--;
		 return TRUE;
	 }
	 /* for case where node is last value in list */
	 else if (list->current == list->tail)
	 {
		 list->current->previousNode->nextNode = NULL;
		 list->tail = list->current->previousNode;
		 freeAddressBookNode(list->current);
		 list->current = list->tail;
		 list->size--;
		 return TRUE;
	 }
	 /* for all other cases */
	 else if (list->head != NULL)
	 {
		listPrev = list->current->previousNode;
		listNext = list->current->nextNode;
		listPrev->nextNode = list->current->nextNode;
		listNext->previousNode = list->current->previousNode;
		freeAddressBookNode(list->current);
		list->current = listNext;
		list->size--;
		return TRUE;
	 }
	 else
	 {
		return FALSE;
	 }


}

Boolean forward(AddressBookList * list, int forward)
{
	int i;

	/* loop moving forwards for number of times provided */
	for (i = 0; i < forward; i++)
	{
		/* for NULL list */
		if (list->current == NULL)
		{
			return FALSE;
		}
		if (list->current->nextNode == NULL)
		{
			/* move backward same number of times you moved forward using i
			if tries to go out of bounds*/
			while(i != 0)
			{
				list->current = list->current->previousNode;
				i--;
			}
			return FALSE;
		}
		list->current = list->current->nextNode;
	}
	return TRUE;
}

Boolean backward(AddressBookList * list, int backward)
{
    int i;

	/* moving backward for number of times provided */
	for (i = 0; i < backward; i++)
	{
		/* for NULL list */
		if (list->current == NULL)
		{
			return FALSE;
		}
		if (list->current->previousNode == NULL)
		{
			/* move forward same number of times it moved backward using i
			if tries to go out of bounds */
			while(i != 0)
			{
				list->current = list->current->nextNode;
				i--;
			}
			return FALSE;
		}
		list->current = list->current->previousNode;
	}
    return TRUE;
}

AddressBookNode * findByName(AddressBookList * list, char * name)
{

  /* stores initial list->current value, so it can be altered as a tracker*/
	AddressBookNode * listCurrent;
	listCurrent = list->current;

	list->current = list->head;


	/* search through list and check list name against name provided */
	while (TRUE)
	 {
		 if (list->current == NULL)
		 {
			 list->current = listCurrent;
			 return NULL;
		 }
     /* if strcmp matches, returns the current value */
		 if (strcmp(list->current->name, name) == 0)
		 {
			 return list->current;
		 }
		 else
		 {
			 list->current = list->current->nextNode;
		 }
	 }
}
