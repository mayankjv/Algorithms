// This program includes representing a binary search tree using an array and implement all the functions: insert, delete, in-order, pre-order, and post-order traversal.
// The approach uses a structure which stores: The value of an element, The index of the left child of that element and the index of the right child of that element.
// The binary search tree is represented as an array of structures.

#include <stdio.h>
#include <stdlib.h>

struct node{
    int value;
    int left;
    int right;
};
static int current=0;

int display_menu();

void insert(struct node* root, int num){
    if(current == 0){
        root[current].value = num;
        root[current].left = -1;
        root[current].right = -1;
    }
    else{
	    int branch = 0, index = 0, lr = 2;
        while(branch != -1){
            if(num < root[branch].value){
                index = branch;
                branch = root[branch].left;
                lr = 0;
            }
            else if(num > root[branch].value){
                index = branch;
                branch = root[branch].right;
                lr = 1;
            }
            else{
                printf("Number is already present, %d can not be inserted\n", num);
                return;
            }
        }
        root = (struct node*)realloc(root, (current+1)*sizeof(struct node));
	if(root==NULL){
		printf("Memory can not be alloted!");
		return ;
	}
        root[current].value = num;
        root[current].left = -1;
        root[current].right = -1;
        
        if(lr == 0){
            root[index].left = current;
        }
        else if(lr == 1)
            root[index].right = current;
    }
    current++;
}

void display(struct node* root){
	int i;
	for(i=0; i<current; i++){
		printf("Value = %d \t Left = %d \t Right = %d\n", root[i].value, root[i].left, root[i].right);
	}
}

void inorder(struct node* root, int index){
	if(current != 0){
		if(root[index].left != -1){
			inorder(root, root[index].left);
		}
		printf("  %d  ", root[index].value);
		if(root[index].right != -1){
			inorder(root, root[index].right);
		}
	}
	else
		printf("BST is Empty");
}

void preorder(struct node* root, int index){
	if(current != 0){
		printf("  %d  ", root[index].value);
		if(root[index].left != -1){
			inorder(root, root[index].left);
		}
		if(root[index].right != -1){
			inorder(root, root[index].right);
		}
	}
	else
		printf("BST is Empty");
}

void postorder(struct node* root, int index){
	if(current != 0){
		if(root[index].left != -1){
			inorder(root, root[index].left);
		}
		if(root[index].right != -1){
			inorder(root, root[index].right);
		}
		printf("  %d  ", root[index].value);
	}
	else
		printf("BST is Empty");
}

int main() {
	int choice=0;
	struct node* root = (struct node *)malloc(sizeof(struct node));
	root[0].value = root[0].left = root[0].right = -1;
	int temp=0;
	do{
		choice=display_menu();
		switch (choice){
	    	case 1:
	        	temp=0;
	        	printf("\nEnter a number to insert: ");
	    	    	scanf("%d",&temp);
	        	insert(root,temp);
	 	       	break;
     	   
     	   case 2:
     	   		inorder(root, 0);
     	   		
     	   case 3:
        	    return 0;
		}
		display(root);
	}while(1);
	return 0;
}

//a function to display the menu and take user choice, and return the choice of the user.
int display_menu(){
	int choice=0;
        printf("1. Insert\n2. Delete\n3. In-order Traversal\n4. Pre-order Traversal\n5. Post-order Traversal\n6. Exit\n\n");
        printf("Enter your choice: ");
	scanf("%d",&choice);
	return choice;
}
