#include "DataHandler.h"

int convert_data(LinkedList* meta_list)
{
	if (meta_list->head == NULL)
	{
		return -1;
	}
	MetaData *head = meta_list->head;
	while (head->next != NULL)
	{
		head = head->next;
	}
	return 0;
}
