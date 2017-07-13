/*
   To add a node at the front of the linked list
   A new node can be added in three ways

   1) At the front of the linked list
   2) After a given node.
   3) At the end of the linked list

   The file also includes a delete method which is used to delete a node at any given n'th position.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int data;
	struct node* next;
}node;

node* head = NULL;
node* prv_node = NULL; 


void push(int data)
{
	node* new_node = (node*)malloc(sizeof(node));

	new_node->data = data;

	new_node->next = head;

	head = new_node;
}

void Insert_After(node* pre_node, int data)
{
	node* new_node_1 = (node*)malloc(sizeof(node));

	new_node_1->data = data;

	new_node_1->next = pre_node->next;

	pre_node->next = new_node_1;
}

void append(unsigned int data)
{
	node* new_node = (node*)malloc(sizeof(node));
	node* temp_node = head;

	while(temp_node->next != NULL)
	{
		temp_node = temp_node->next;
	}

	new_node->data = data;
	temp_node->next = new_node;
	new_node = NULL;
}

void delete(unsigned int n)
{
	int i;
	node* temp1 = NULL;
	node* temp2 = NULL;
	node* temp3 = NULL;
	temp1 = head;
    temp2 = head;
    temp3 = head;

	for(i=0; i<(n-1); i++)
	{
		temp1 = temp1->next;
	}

	for(i=0; i<(n+1); i++)
	{
		temp2 = temp2->next;
	}

	for(i=0; i<(n); i++)
	{
		temp3 = temp3->next;
	}

	temp1->next = temp3->next;

	printf("%d\n", temp1->data);
	printf("%d\n", temp2->data);

	free(temp3);
}

void print_list()
{
	while(head != NULL)
	{
		printf("%d ", head->data);
		head = head->next;
	}

	printf("\n");
}

int main()
{

	int i;
	//for(i=0; i<5; i++)
	//{
		//push(10);
		push(111);
		Insert_After(head, 112);
		//Insert_After(113);
		//push(110);
		Insert_After(head->next, 113);
		Insert_After(head->next->next, 114);
		Insert_After(head->next->next->next, 115);
		append(116);
		append(117);
		append(118);
		append(119);
		append(120);
		push(110);
		push(108);
		Insert_After(head, 109);
		append(121);
		delete(6);
	//}

	print_list();
}