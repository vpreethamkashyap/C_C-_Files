#include <stdio.h>
#include <stdlib.h>

typedef struct node{

	unsigned int data;
	struct node* next;
}node;

node* head = NULL;

void Insert(unsigned int n){

	node* temp = (node*)malloc(sizeof(node));

	temp->data = n;
	temp->next = head;
	head  = temp;
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
	for(i=0; i<a; i++){

		printf("Enter the number to be stored in the list: ");
		unsigned int b;
		scanf("%d", &b);
		Insert(b);
		printlist();
	}

}