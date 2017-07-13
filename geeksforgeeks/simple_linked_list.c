/*A simple C program to introduce a linked list*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
	int data;

	struct Node* next;

}Node;

void print_list(Node* head)
{
	while(head != NULL){
		printf("%d\n", head->data);
		head = head->next;
	}

}

/*main routine*/
/*Program to create a simple linked list with 3 nodes*/

int main(void)
{
	Node* head   = (Node*)malloc(sizeof(Node));
	Node* second = (Node*)malloc(sizeof(Node));
	Node* three  = (Node*)malloc(sizeof(Node));

	head->data = 15;
	head->next = second;

	second->data = 225;
	second->next = three;

	three->data = 3375;
	three->next = NULL;

	print_list(head);

	free(head);
	free(second);
	free(three);

	//print_list(head);

}