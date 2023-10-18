#include <stdio.h>
#include <stdlib.h>

struct snode {
    char* slab;//stores a string
    struct snode* next;
};

typedef struct snode* NODEPTR;

typedef struct stack {
    NODEPTR head;
} STACK;

NODEPTR createNode(char* in) {
    NODEPTR p = (NODEPTR)malloc(sizeof(struct snode));
    p->slab = in;
    p->next = NULL;
    return p;
}

NODEPTR row(int val, int n) {
    NODEPTR temp;
    char* brick = (char*)malloc((n + 1) * sizeof(char));
    int space = (n - val) / 2;
    for (int i = 0; i < n; i++) {
        if (i >= space && i < space + val) {
            brick[i] = 'T';
        } else {
            brick[i] = ' ';
        }
    }
    brick[n] = '\0'; // Null-terminate the string
    temp = createNode(brick);
    return temp;
}

int isEmpty(STACK* s4) {
    return s4->head == NULL;
}

char* pop(STACK* s3) {
    if (isEmpty(s3)) {
        printf("Stack is empty\n");
        return NULL;
    }
    NODEPTR temp = s3->head;
    s3->head = s3->head->next;
    char* val = temp->slab;
    free(temp);
    return val;
}

void push(STACK* s2, int elm, int n) {
    NODEPTR temp = row(elm, n);
    if (s2->head == NULL)
		s2->head = temp;
	else{
		temp->next = s2->head;
		s2->head = temp;
	}
}

void printStack(STACK* s1) {
    NODEPTR temp = s1->head;
    while (temp != NULL) {
        printf("%s\n", temp->slab);
        temp = temp->next;
    }
}

void pushs(STACK* s2, char* a) {
    NODEPTR temp = createNode(a);
    if (s2->head == NULL)
		s2->head = temp;
	else{
		temp->next = s2->head;
		s2->head = temp;
	}
}

int findDepth(STACK* s) {//finds depth of stack
    NODEPTR temp = s->head;
    int depth = 0;
    while (temp != NULL) {
        temp = temp->next;
        depth++;
    }
    return depth;
}

void printTower(STACK** st, int n) {
    NODEPTR* temp = (NODEPTR *)malloc(3*sizeof(NODEPTR));
    for(int k = 0; k<3;k++) temp[k] = st[k]->head;//array to store pointers for traversal of stacks
    int dep;
    char* empty = (char*)malloc((2 * n + 2) * sizeof(char)); // Allocate space for the empty string
    for (int p = 0; p < (2 * n + 1); p++) empty[p] = ' ';//creates empty string
    empty[2 * n + 1] = '\0';
    for(int i = n; i>0;i--){
        printf("|   ");
        for(int j = 0; j<3;j++){
            dep = findDepth(st[j]);
            if(i>dep) printf("%s   |   ", empty);//if there is nothing at that level in the tower, print nothing
            else{
                printf("%s   |   ", temp[j]->slab);//print the disk present at that level in each tower
                temp[j] = temp[j]->next;//traverses the towers
            }
        }
        printf("\n");
    }
    for(int k = 0;k<(3*(2*n+1)+22);k++){
        printf("_");
    }
    printf("\n\n");
}

void towerofHanoi(int n, STACK** starr, int pos1, int pos2, int pos3, int p) {
    char* temp;
    if (n != 0) {
        towerofHanoi(n - 1, starr, pos1, pos3, pos2, p);//moves everything but last one from tower 1 to tower 2 using tower 3
        temp = pop(starr[pos1]);
        pushs(starr[pos3], temp);//moves a last disk from tower 1 to tower 3
        printf("Move %d to %d\n\n", pos1, pos3);
        printTower(starr, p);//prints towers
        towerofHanoi(n - 1, starr, pos2, pos1, pos3, p);//moves everything in tower 2 to tower 3 using tower 1
    }
}

int main() {
    int x;
    printf("Please enter the number of disks: ");
    scanf("%d", &x);

    STACK** starr = (STACK**)malloc(3 * sizeof(STACK*));//creates an array of pointers to stack structures
    for (int i = 0; i < 3; i++) {//allocates memory to each stack and initialises head pointer
        starr[i] = (STACK*)malloc(sizeof(STACK));
        starr[i]->head = NULL;
    }

    for (int i = x; i > 0; i--) {
        push(starr[0], (2 * i) + 1, (2 * x) + 1);//pushes disks into stack 1
    }
    printf("Starting Arrangment of Towers \n\n");
    printTower(starr, x);//prints starting arrangement of all three towers
    towerofHanoi(x, starr, 0, 1, 2, x);
    printf("Finished.");
    for (int i = 0; i < 3; i++) {
    NODEPTR temp = starr[i]->head;
    while (temp != NULL) {
        NODEPTR next = temp->next;
        free(temp);
        temp = next;
    }
    free(starr[i]);
}
    return 0;
}
