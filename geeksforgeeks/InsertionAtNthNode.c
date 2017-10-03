/* -Insert Node at nth position or Insert next to created node, 
   
   -Delete a node at nth position.

   -Reverse a linked list -Iterative method.

   -Reverse a linked list -Recursive method.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node{

	unsigned int data;
	struct node* next;
}node;

node* head = NULL;

void Insert(unsigned int n, int position){

	int i;
	node* temp1 = (node*)malloc(sizeof(node));
	temp1->data = n;

	if(position == 1)
	{
		temp1->next = head;
		head = temp1;
		return;
	}

	node* temp2 = head;
	if(temp2 == NULL)
	{
		printf("First node is not created");
		return;
	}

	for(i=1; i<position-1; ++i)
	{
		temp2 = temp2->next;
	}

	temp1->next = temp2->next;
	temp2->next = temp1;
}

void Delete(int position){

	node* temp1;
	node* temp2;
	node* temp3;
	int n = 1;

	temp1 = head;
	while(n != (position-1))
	{
		temp1 = temp1->next;
		n++;
	}
	temp2 = temp1->next;
	temp1->next = temp1->next->next;
	free(temp2);
}

void Reverse(){

	node* current, *prev, *next;
	current = head;
	prev = NULL;

	while(current != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	head = prev;
}

void ReverseRecursive(node* head){

	node* temp = head;

	if(temp->next == NULL){

		head = temp;
		return;
	}

	ReverseRecursive(temp->next);

	node* temp1 = temp->next;
	temp1->next = temp;
	temp->next = NULL;
}

void printRecursive(node* head)
{
	node* temp = head;

	if(temp == NULL)
	{
		return;
	}

	printf("%d ", temp->data);
	printRecursive(temp->next);
}

void printlist(){

	node* temp = head;

	printf("List is : ");
	while (temp != NULL){
		printf("%d ", temp->data);
		temp = temp->next;
	}
	printf("\n");
}

int main (){

	printf("Enter the Number of lists to be created\n");
	int a;
	scanf("%d", &a);

	int i;
	for(i=1; i<=a; i++){

		printf("Enter the number to be stored in the list: ");
		unsigned int b;
		scanf("%d", &b);
		Insert(b,i);
		printlist();
	}

	Insert(4,4);
	printlist();
	Delete(4);
	printlist();
	//Reverse();
	ReverseRecursive(head);
	printf("Reversed ");
	printRecursive(head);
}