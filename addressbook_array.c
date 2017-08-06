#include "addressbook_array.h"

AddressBookArray * createAddressBookArray()
{
    /* Allocates and initialises a new AddressBookArray.*/

	 AddressBookArray * addressBookArray = malloc(sizeof(*addressBookArray));

	 if (addressBookArray != NULL)
	 {
		addressBookArray->size = 0;
		addressBookArray->telephones = NULL;
		return addressBookArray;
	 }
	else
	{
		return NULL;
	}
}

void freeAddressBookArray(AddressBookArray * array)
{
  int i;

  /* free all telephones in array */
  for (i = 0; i < array->size; i++)
  {
    free(array->telephones[i]);
  }

  /* free array itself */
	free(array);

}

Boolean addTelephone(AddressBookArray * array, char * telephone)
{
	 int i;
	 char * newTelephone;

   /* make sure telephone isn't already in list */
	 for (i = 0; i < array->size; i++)
	 {
		if (strcmp(array->telephones[i], telephone) == 0)
		{
			return FALSE;
		}
	 }

   /* allocate memory for telephone to be added */
	 newTelephone = malloc(TELEPHONE_LENGTH);
	 strcpy(newTelephone, telephone);

   /* increase the allocation size to 1 larger than what it
   already was in order to store the new telephone */
	 array->telephones = realloc(array->telephones, sizeof(*array->telephones) * (array->size + 1));

   /* add new telephone to last end of array */
	 array->telephones[array->size] = newTelephone;
	 array->size += 1;

    return TRUE;
}

Boolean removeTelephone(AddressBookArray * array, char * telephone)
{
	int i;
	char * temp;

	for (i = 0; i < array->size; i++)
	{
		if (strcmp(telephone, array->telephones[i]) == 0)
		{
			/* free if last telephone */
			if (array->size == 1)
			{
				free(array->telephones);
				array->size--;
				return TRUE;
			}
			else
			{
				/* use temp to set telephone to be removed to end */
				temp = array->telephones[array->size - 1];
				array->telephones[array->size - 1] = array->telephones[i];
				array->telephones[i] = temp;

        /* free last telephone in the array */
				free(array->telephones[array->size - 1]);

        /* reallocate memory of array for 1 less telephone */
				array->telephones = realloc(array->telephones, sizeof(*array->telephones) * (array->size - 1));
				array->size--;
				return TRUE;
			}
		}
	}
    return FALSE;
}
