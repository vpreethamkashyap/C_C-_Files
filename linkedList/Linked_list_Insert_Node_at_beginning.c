#include <stdio.h>
#include <stdlib.h>

void Insert(int x);
void print();

struct Node{
    
    int data;
    struct Node* next;
};

struct Node* head = NULL;

int main()
{
    printf("Enter the number of list : ");
    int input;
    scanf("%d", &input);
    
    int i, data_input;
    for(i=0; i<input; i++){
        printf("Enter the data : ");
        scanf("%d", &data_input);
        Insert(data_input);
        print();
    }
}

void Insert(int x){
    
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    
    temp->data = x;
    temp->next = head;
    head = temp;
}

void print(){
    
    struct Node* temp = head;
    
    printf("List is : ");
    while(temp != NULL)
    {
        printf(" %d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// A slight modification code
/*#include <stdlib.h>
#include <stdio.h>

struct Node* Insert(struct Node* head, int x);
void print(struct Node* head);

struct Node{
    
    int data;
    struct Node* next;
};

int main()
{
    struct Node* head = NULL;
    
    printf("Enter the number of list : ");
    int input;
    scanf("%d", &input);
    
    int i, data_input;
    for(i=0; i<input; i++){
        printf("Enter the data : ");
        scanf("%d", &data_input);
        head = Insert(head,data_input);
        print(head);
    }
}

struct Node* Insert(struct Node* top, int x){
    
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    
    temp->data = x;
    temp->next = top;
    top = temp;
    return top;
}

void print(struct Node* head){
    
    struct Node* temp = head;
    
    printf("List is : ");
    while(temp != NULL)
    {
        printf(" %d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}*/





