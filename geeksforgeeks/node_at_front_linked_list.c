/*To add a node at the front of the linked list*/

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
	//}

	print_list();
}