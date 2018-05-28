
#include "linkedlist.h"

// create new list and set pointers to null
LinkedList *list_create(void) {
	// allocate memory and set values to null
	struct LinkedList *list = (struct LinkedList*)malloc(sizeof(LinkedList));
	list->head = NULL;
	list->count = 0;
	return list;
}

int list_distroy(LinkedList *list)
{
	if (list->head != NULL)
	{
		MetaData *temp_node, *head = list->head;

		while (head != NULL)
		{
			temp_node = head;
			head = head->next;
			free(temp_node);
		}
		free(list);
		return 0;
	}
	else
	{
		return -1;
	}

}

// add to head of created list
MetaData *list_create_node(char command, char operation[], int cycleTime)
{
	// allocate memory and set values to null
 	MetaData *node = malloc(sizeof(MetaData));
	if (node == NULL)
	{
		return NULL;
	}
	node->next = NULL;
	node->command = command;
	strcpy(node->operation, operation);
	node->cycleTime = cycleTime;
	return node;
}

void insert_node(LinkedList *list, MetaData *newNode)
{
	MetaData *temp;
	temp = list->head;
	if (list->head == NULL)
	{
		list->head = newNode;
	}
	else
	{
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = newNode;
	}
	list->count++;
}