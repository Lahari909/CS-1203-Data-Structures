#include <stdio.h>
#include <stdlib.h>
struct node {
    int data;
    struct node *next;
};
typedef struct node *NODEPTR;

typedef struct queue{
    NODEPTR head, tail;
} QUEUE;

NODEPTR createNode(int val){
	NODEPTR p;
	p = (NODEPTR) malloc(sizeof(struct node));//memory allocated for new node
	p->data = val;//data stored in new node
	p->next = NULL;
	return p;
}

void insert(QUEUE* q3, int a){
    NODEPTR nn;
    nn = createNode(a);//creates new node
    if(q3->head==NULL){
        //if the queue is empty, the new node is both the first node and the last node in the queue
        q3->head = nn;
        q3->tail = nn;
    }
    else{
        //the address of the new node is stored in the last node of the queue, essentially adding it to the rear end of the queue
        q3->tail->next = nn;
        q3->tail = nn;//the new last node is the new node
    }
}
void delete(QUEUE* q1){
    int y;//stores the vlaue of the element that has been dequeued
    if(q1->head==NULL){
        printf("The queue is empty.\n");
    }
    else{
        y = q1->head->data;//the value to be dequeued is in the foremost node in the queue
        q1->head = q1->head->next;//the second node is saved as the first, essentially deleting the first value
        if(q1->head==NULL) q1->tail=NULL;//in case the queue becomes empty after the dequeue
        printf("Popped Value: %d\n", y) ;//prints the deleted value
    }
}

void *printQueue(QUEUE* q2){
    NODEPTR temp;
    if(q2->head==NULL){
        printf("The queue is empty.\n");
    }
    else{
        for(temp = q2->head; temp!=NULL;temp = temp->next){
            //loop traverses the queue until it reaches the last element in the queue
            printf("%d-->", temp->data);//prints traversed elements
        }
        printf("NULL\n");
    }
}

int main()
{;
	int elm, menu;
	QUEUE q;
	q.head = q.tail = NULL;//initialises head and tail in queue structure
	while(1){
          printf("0. Exit, 1. Delete, 2. Insert, 3. Print. \nInput Choice: ");
	  scanf("%d", &menu);

	  switch(menu){
	   case 0: exit(0);
           case 1: delete(&q); 
                   break;
           case 2: printf("Give element: "); 
                   scanf("%d", &elm); 
                   insert(&q, elm); 
                   break;
           case 3: printQueue(&q); 
                   break;
	   default: printf("Wrong choice\n");
         }
        }
    
}


