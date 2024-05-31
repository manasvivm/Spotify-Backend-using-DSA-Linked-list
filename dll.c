#include "dll.h"
#include <stdio.h>
#include <stdlib.h>
 
list_t* create_list()  // return a newly created empty doubly linked list
{
	// DO NOT MODIFY!!!
	list_t* l = (list_t*) malloc(sizeof(list_t));
	l->head = NULL;
	l->tail = NULL;
	l->size = 0;
	return l;
}

void insert_front(list_t* list, int data)  // TODO: inserts data to the beginning of the linked list
{  
   node_t* temporary=(node_t*)malloc(sizeof(node_t));
   temporary->data=data;
   temporary->prev=temporary->next=NULL;
   if (list->head==NULL)
   {
	   list->head=temporary;
	   list->size++;
   }
   else
   {
	   temporary->next=list->head;
	   list->head->prev=temporary;
	   list->head=temporary;
	   list->size++;
   }
   node_t* current=list->head;
   node_t* prev=NULL;
   while(current!=NULL)
   {
	   prev=current;
	   current=current->next;
   }
   list->tail=prev;
}

void insert_back(list_t* list, int data) // TODO: inserts data to the end of the linked list
{  
   node_t* temporary=(node_t*)malloc(sizeof(node_t));
   temporary->data=data;
   temporary->prev=temporary->next=NULL;
   if (list->head==NULL)
   {
	   list->head=temporary;
	   list->tail=temporary;
	   list->size++;
   }
   else
   {
	   node_t* current=list->head;
	   node_t* prev=NULL;
	   while(current!=NULL)
	   {
			prev=current;
			current=current->next;
		}
       list->tail=prev;
	   list->tail->next=temporary;
	   temporary->prev=list->tail;
	   list->tail=temporary;
	   list->size++;
   }
}

void insert_after(list_t* list, int data, int prev) // TODO: inserts data after the node with data “prev”. Do not insert or do anything if prev doesn't exist
{
   node_t* temporary=(node_t*)malloc(sizeof(node_t));
   temporary->data=data;
   temporary->prev=temporary->next=NULL;
   node_t* current=search(list,prev);
   if (current==NULL)
   {
   		return;
   }
   else
   {
	   if (current->next!=NULL)
	   {
			node_t* second=current->next;
			temporary->next=second;
			temporary->prev=current;
			current->next=temporary;
			second->prev=temporary;
	   }
	   else
	   {
		   current->next=temporary;
		   temporary->prev=current;
		   list->tail=temporary;
	   }
 	}
 list->size++;
 
} 


void delete_front(list_t* list) // TODO: delete the start node from the linked list.
{
	if (list->size==0)
	{
		return;
	}
	else
	{
		node_t* current=list->head;
		node_t* second=current->next;
		if (second==NULL)
		{
			list->head=list->tail=NULL;
			free(current);
			current=NULL;
		}
		else
		{
			list->head=second;
			second->prev=NULL;
			free(current);
			current=NULL;
		}
	}
	list->size--;   
}

void delete_back(list_t* list) // TODO: delete the end node from the linked list.
{	
	if (list->size==0)
	{
		return ;
	}
 	else if(list->size==1)
	{
	 list->head=list->tail=NULL;
 	}
	else
	{
		node_t* last=list->tail;
		node_t* secend=last->prev;
		list->tail=secend;
		secend->next=NULL;
		free(last);
		last=NULL;
	}list->size--;	 
 }


void delete_node(list_t* list, int data) // TODO: delete the node with “data” from the linked list.
{
	if (list->size==0)
	{
		return ;
	}
 	else
	{
		node_t* current=search(list,data);
		if (current==NULL)
		{
			return ;
		}
		else
		{
			if (current->prev==NULL)
			{
				delete_front(list);
			}
			else if(current->next==NULL)
			{
				delete_back(list);
			}
			else
			{
				node_t* before =current->prev;
				before->next=current->next;
				current->next->prev=before;
				free(current);
				current=NULL;
			}
		}
 	}
}

node_t* search(list_t* list, int data) // TODO: returns the pointer to the node with “data” field. Return NULL if not found.
{	
	node_t* found=list->head;
	while(found->data!=data && found!=NULL)
	{
		found=found->next;
	}
	return found;
}

int is_empty(list_t* list) // return true or 1 if the list is empty; else returns false or 0
{
	// DO NOT MODIFY!!!
	return list->size == 0;
}

int size(list_t* list) // returns the number of nodes in the linked list.  
{
	// DO NOT MODIFY!!!
	return list->size;
}

void delete_nodes(node_t* head) // helper
{
	// DO NOT MODIFY!!!
	if(head == NULL)
		return;
	delete_nodes(head->next);
	free(head);	
}

void delete_list(list_t* list) // free all the contents of the linked list
{
	// DO NOT MODIFY!!!
	delete_nodes(list->head);
	free(list);
}

void display_list(list_t* list) // print the linked list by separating each item by a space and a new line at the end of the linked list.
{
	// DO NOT MODIFY!!!
	node_t* it = list->head;
	while(it != NULL)
	{
		printf("%d ", it->data);
		it = it->next;
	}
	printf("\n");
}

