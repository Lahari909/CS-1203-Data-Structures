#include <stdio.h>
#include <stdlib.h>
struct node{
    int key;
    struct node *left, *right;
};

struct snode{
    struct node *info;
    struct snode *next;    
};

typedef struct snode * NODEPTR;
typedef struct stack{
    NODEPTR head;
} STACK;

NODEPTR createsNode(struct node *val){
	NODEPTR p;
	p = (NODEPTR) malloc(sizeof(struct snode));
	p->info = val;
	p->next = NULL;
	return p;
}

int isEmpty(STACK *s4){
	if (s4->head == NULL) return 1;
	else return 0;
}

struct node *pop(STACK *s3){
	NODEPTR temp;
	struct node *val;
    temp = s3->head;
    (s3->head) = (s3->head)->next;
    val = temp->info;
    free(temp); 
    return val;
}

void push(STACK *s2, struct node *elm){
	NODEPTR temp;
	temp = createsNode(elm);
	if (s2->head == NULL)
		s2->head = temp;
	else{
		temp->next = s2->head;
		s2->head = temp;
	}
}

void *printStack(STACK *s1){

	NODEPTR temp;

	if (isEmpty(s1)){ 
		printf("Stack empty\n");
	}
	for (temp = s1->head; temp!= NULL; temp = temp->next)
		printf("%d\n", temp->info);
}

struct node *createNode(int k){
    struct node *temp;

    temp = (struct node *) malloc(sizeof(struct node));
    temp->key = k;
    temp->left = temp->right = NULL;
    return temp;
}

void displayNode(struct node *temp){

	if (temp == NULL)
		printf("Node does not exist\n");
	else
    		printf("%x %d\n", (unsigned int) temp, temp->key);

}

void displayTree(struct node* root, int space)
{
    int i;

    if (root == NULL) return;
 
    space += 10;
 
    // Process right child first
    displayTree(root->right, space);
 
    // Print current node after space count
    printf("\n");
    for (i = 10; i < space; i++)
        printf(" ");
    printf("%d\n", root->key);
 
    // Process left child
    displayTree(root->left, space);
}
 
struct node * search(struct node * anode, int k){

    struct node *temp, *parent;
     
    if (anode == NULL) return NULL;
    
    temp = anode;
    while (temp != NULL){
	if (temp->key == k){
	   return temp;
        }

    	if (k < temp->key){
            temp = temp->left;
        }
        else{
	    temp = temp->right;
        }
    }
    return NULL;
}
        
struct node * insert(struct node * anode, int k){

    struct node *temp, *parent;
    int direction;
     
    if (anode == NULL){
        anode = createNode(k);
	return anode;
    }
    
    temp = anode;
    while (temp != NULL){
	if (temp->key == k){
	   printf("node with value %d exists\n", k);
	   return temp;
        }

    	if (k < temp->key){
	    parent = temp;
            temp = temp->left;
            direction = 0;
        }
        else{
	    parent = temp;
	    temp = temp->right;
            direction = 1;
        }
    }
    temp = createNode(k);
    if (direction == 0)
        parent->left = temp;
    else
        parent->right = temp;
        
   return temp; 
}

struct node * delete (struct node * anode, int k){

    struct node *temp, *parent, *intemp, *inparent;
    int direction, flag = 0, val;
     
    if (anode == NULL){ 
	printf("Tree empty\n");
        return NULL;
    }
   
    parent = NULL; 
    temp = anode;

    while (temp != NULL){
	if (temp->key == k){
           flag = 1;
	   break;
        }
    	if (k < temp->key){
	    parent = temp;
            temp = temp->left;
            direction = 0;
        }
        else{
	    parent = temp;
	    temp = temp->right;
            direction = 1;
        }
    }

    if (flag == 0){
	printf("Node not found\n");
        return NULL;
    }

    if ((temp->left == NULL) && (temp->right == NULL)){
        if (direction == 0) parent->left = NULL;
        else parent->right = NULL;
        return temp;
    }

    if ((temp->left != NULL) && (temp->right == NULL)){
	if (parent == NULL){
		anode = temp->left;
		return temp;
        }
        if (direction == 0) parent->left = temp->left;
        else parent->right = temp->left;
        return temp;
    }

    if ((temp->left == NULL) && (temp->right != NULL)){
	if (parent == NULL){
		anode = temp->right;
		return temp;
        }
        if (direction == 0) parent->left = temp->right;
        else parent->right = temp->right;
        return temp;
    }

    if ((temp->left != NULL) && (temp->right != NULL)){
        inparent = temp;	
        intemp = temp->right;
        printf("%d %d\n", inparent->key, intemp->key);

    	while(intemp->left != NULL){ 
	   inparent = intemp;
           intemp = intemp->left;
        }
        printf("%d %d\n", inparent->key, intemp->key);

	val = temp->key;
	temp->key = intemp->key;
        intemp->key = val;

        printf("%d %d\n", temp->key, intemp->key);

	if ((intemp->left == NULL) && (intemp->right == NULL))
		inparent->right = NULL;
	else
        	inparent->left = intemp->right;

	return intemp;
    }

    return NULL;
}


void recurinorder(struct node * anode){
    if (anode != NULL) {
        recurinorder(anode->left);
        printf("%d ", anode->key);
        recurinorder(anode->right);
    }
}


void iterinorder(struct node * anode){
    STACK s;
    s.head = NULL;
    struct node *temp;
    temp = anode;
    while(1){
        if(temp!=NULL){
            push(&s, temp);//pushes parents into stack
            temp = temp->left;//moves to left-most node in tree
        }
        else if(!isEmpty(&s)){
            temp = pop(&s);//pops parent from stack 
            printf("%d ", temp->key);//prints parents from stack
            temp = temp->right;//moves to right subtree
        }
        else{
            //if the stack is empty and the temp node is NULL then we have traversed through the whole tree
            break;
        }
    }
}

void recurpreorder(struct node * anode){
    if (anode != NULL) {
        printf("%d ", anode->key);
        recurpreorder(anode->left);
        recurpreorder(anode->right);
    }
}

void iterpreorder(struct node* anode){
    STACK spre;
    spre.head = NULL;
    struct node *temp;
    temp = anode;
    while(1){
        if(temp!=NULL){
            printf("%d ", temp->key);//prints the parent
            push(&spre, temp);//stores parents in stack
            temp = temp->left;//moves to left subtree
        }
        else if(!isEmpty(&spre)){
            temp = pop(&spre);//pops parent from stack
            temp = temp->right;//moves to right subtree
        }
        else{
            break;
        }
    }
}

void recurpostorder(struct node * anode){
    if (anode != NULL) {
        recurpostorder(anode->left);
        recurpostorder(anode->right);
        printf("%d ", anode->key);
    }
}

void freeTree(struct node * anode){
    if (anode != NULL) {
        freeTree(anode->left);
        freeTree(anode->right);
        free(anode);
    }
}

int main()
{
    struct node * root = NULL, *temp;
    int elm, menu;

    while(1){
      printf("\n0. exit, 1. initialize, 2. search, 3. insert, 4. delete,\n ");
      printf("5. recursive inorder, 6. iterative inorder, 7. recursive preorder, 8. iterative preorder, 9. recursive postorder\n");
      printf("10. free tree, 11. display. Input Choice: ");
          scanf("%d", &menu);

          switch(menu){
           case 0: exit(0);

           case 1: root = NULL;
                   break;

           case 2: printf("Give element to search: ");
                   scanf("%d", &elm);
		   temp = search(root, elm);
		   displayNode(temp);
                   break;

           case 3: printf("Give element to insert: ");
                   scanf("%d", &elm);
		   if (root == NULL)
		   	temp = root = insert(root, elm);
		   else
		   	temp = insert(root, elm);
		   displayNode(temp);
                   break;

           case 4: printf("Give element to delete: ");
                   scanf("%d", &elm);
		   if (root == NULL)
                      printf("Tree empty\n");
		   else if ((root->key == elm) && (root->left == NULL) && (root->right == NULL)){
		      temp = root;
                      root = NULL;
		   }
		   else if ((root->key == elm) && (root->left != NULL) && (root->right == NULL)){
			temp = root;
			root = root->left;
		   }
		   else if ((root->key == elm) && (root->left == NULL) && (root->right != NULL)){
			temp = root;
			root = root->right;
		   }
		   else
		   	temp = delete(root, elm);

		   displayNode(temp);
                   break;

           case 5: recurinorder(root);
		   printf("\n");
                   break;

           case 6: iterinorder(root);
                   printf("\n");
                   break;

           case 7: recurpreorder(root);
                   printf("\n");
                   break;

           case 8: iterpreorder(root);
                   printf("\n");
                   break;

           case 9: recurpostorder(root);
                   printf("\n");
                   break;

           case 10:freeTree(root);
                   root = NULL;
                   break;

           case 11: if (root == NULL) printf("Tree empty\n");
		   displayTree(root, 0);
                   break;


           default: printf("Wrong choice\n");
         }
        }

    return 0;
}
