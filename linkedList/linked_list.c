#include <stdio.h>
#include <stdlib.h>

typedef struct listitem{

	long data;
	struct listitem* next;

}LISTITEM;

int main(){

	LISTITEM* head = NULL;

	long i;

	for(i=0 ; i<=3; i++){

		LISTITEM* temp = (LISTITEM*)malloc(sizeof(LISTITEM));

		temp->data = i+99;
		temp->next = head;
		head = temp;
	}

	while(head != NULL){

		printf("List current address %x : List pointed to address %x: List current data %d \n", head, head->next, (int)head->data);
		head = head->next;
	}

}