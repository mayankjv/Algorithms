#include <stdio.h>
#include <stdlib.h>


//Structure for the node of BST
struct node{
    int value;
    int left;
    int right;
};

static int current=0, space_free = 0;

//defination of function to insert elements to the BST
void insert(struct node* root, int num){
    if(space_free == 0){
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
                	printf("\nNumber is already present, %d can not be inserted", num);
                	return;
            	}
        	}
        	root = (struct node*)realloc(root, sizeof(struct node));
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
                	printf("\nNumber is already present, %d can not be inserted", num);
                	return;
            	}
        	}
        	root[current-space_free].value = num;
        	root[current-space_free].left = -1;
        	root[current-space_free].right = -1;
        
        	if(lr == 0){
            	root[index].left = current-space_free;
        	}
        	else if(lr == 1)
            	root[index].right = current-space_free;
		space_free--;
	}
}

//defination of function to display content of BST
void display(struct node* root){
	int i;
	for(i=0; i<current-space_free; i++){
		printf("\nValue = %d \t Left = %d \t Right = %d", root[i].value, root[i].left, root[i].right);
	}
}

//defination of function for printing In-Order Traversal
void inorder(struct node* root, int index){
	if(current-space_free != 0){
		if(root[index].left != -1){
			inorder(root, root[index].left);
		}
		printf("  %d  ", root[index].value);
		if(root[index].right != -1){
			inorder(root, root[index].right);
		}
	}
	else
		printf("\nBST is Empty");
}

//defination of function for printing Pre-Order Traversal
void preorder(struct node* root, int index){
	if(current-space_free != 0){
		printf("  %d  ", root[index].value);
		if(root[index].left != -1){
			inorder(root, root[index].left);
		}
		if(root[index].right != -1){
			inorder(root, root[index].right);
		}
	}
	else
		printf("\nBST is Empty");
}

//defination of function for printing Post-Order Traversal
void postorder(struct node* root, int index){
	if(current-space_free != 0){
		if(root[index].left != -1){
			inorder(root, root[index].left);
		}
		if(root[index].right != -1){
			inorder(root, root[index].right);
		}
		printf("  %d  ", root[index].value);
	}
	else
		printf("\nBST is Empty");
}

//defination of function for finding Maximum Value from left sub-tree of a node
int leftMax(struct node* root, int branch){
	int index = 0;
	int leftmax = root[branch].left;
	while(leftmax != -1){
		index = leftmax;
		leftmax = root[leftmax].right;
	}
	return index;
}

//defination of function for finding Minimum Value from right sub-tree of a node
int rightMin(struct node* root, int branch){	
	int index = 0;
	int rightmin = root[branch].right;
	while(rightmin != -1){
		index = rightmin;
		rightmin = root[rightmin].left;
	}
	return index;
}

//Definition of function to shift and adjust the data elements of BST after deletion of element
void shift(struct node* root, int index){
	int i;
	int element;
	element = current - space_free - 1;
	for(i=0; i<element; i++){
		if(i < index){
			if(root[i].left == index){
				root[i].left = -1;
			}
			if(root[i].right == index){
				root[i].right = -1;
			}
			if(root[i].left > index){
				root[i].left--;
			}
			if(root[i].right > index){
				root[i].right--;
			}
		}
		else if(i >= index){
			root[i].value = root[i+1].value;
			root[i].left = root[i+1].left;
			root[i].right = root[i+1].right;
		}
	}
}

void shift_between(struct node* root, int index){
	int i;
	int element;
	element = current - space_free - 1;
	for(i=0; i<element; i++){
		if(i < index){
			if(root[i].left > index){
				root[i].left--;
			}
			if(root[i].right > index){
				root[i].right--;
			}
		}
		else if(i >= index){
			root[i].value = root[i+1].value;
			root[i].left = root[i+1].left;
			root[i].right = root[i+1].right;
		}
	}
}

//defination of function for deleting element from binary search tree
void delete_element(struct node* root, int element, int branch, int index, int lr)
{
	if(root[branch].value == element){
		printf("Element Found: %d\n", element);
		if(root[branch].left == -1 && root[branch].right == -1){
			if(lr == 0)
				root[index].left = -1;
			else if(lr == 1)
				root[index].right = -1;
			shift(root, branch);
			space_free++;
		}
		else if(root[branch].left != -1 && root[branch].right == -1){
			if(root[root[branch].left].right == -1){
				int index_left_max = root[branch].left;
				root[branch].value = root[index_left_max].value;
				if(root[index_left_max].left == -1){
					root[branch].left = -1;
				}
				shift_between(root, index_left_max);
				space_free++;
			}
			else{
				int index_left_max = leftMax(root, branch);
				root[branch].value = root[index_left_max].value;
				shift(root, index_left_max);
				space_free++;
			}
		}
		else if(root[branch].left == -1 && root[branch].right != -1){
			if(root[root[branch].right].left == -1){
				int index_right_min = root[branch].right;
				root[branch].value = root[index_right_min].value;
				if(root[index_right_min].right == -1){
					root[branch].right = -1;
				}
				shift_between(root, index_right_min);
				space_free++;
			}
			else{
				int index_right_min = rightMin(root, branch);
				root[branch].value = root[index_right_min].value;
				shift(root, index_right_min);
				space_free++;
			}
		}
		else if(root[branch].left != -1 && root[branch].right != -1){ 
			if(root[root[branch].right].left == -1){
				int index_right_min = root[branch].right;
				root[branch].value = root[index_right_min].value;
				if(root[index_right_min].right == -1){
					root[branch].right = -1;
				}
				shift_between(root, index_right_min);
				space_free++;
			}
			else{
				int index_right_min = rightMin(root, branch);
				root[branch].value = root[index_right_min].value;
				shift(root, index_right_min);
				space_free++;
			}
		}
		printf("Element is deleted from BST");
	}
	else if(element < root[branch].value && root[branch].left != -1){
		index = branch;
		branch = root[branch].left;
		lr = 0;
		delete_element(root, element, branch, index, lr);
	}
	else if(element > root[branch].value && root[branch].right != -1){
		index = branch;
		branch = root[branch].right;
		lr = 1;
		delete_element(root, element, branch, index, lr);
	}
	else{
		printf("\nElement is not present");
	}
}

int main() {
	int choice=0;
	struct node* root = NULL;
	root = (struct node*)malloc(sizeof(struct node));
	root[0].value = root[0].left = root[0].right = -1;
	int temp=0, element;
	do{
		printf("\nChoose 1. To Insert, 2. Inorder Traversal, 3. Preorder Traversal, 4. Postorder Traversal, 5. Delete Element, 6. Exit: ");
		scanf("%d", &choice);
		switch (choice){
	    	case 1:
	        	temp=0;
	        	printf("\nEnter a number to insert: ");
	    	    scanf("%d", &temp);
	        	insert(root, temp);
	 	       	break;
    		
     		case 2:
     	   		inorder(root, 0);
     	   		break;
     		
			case 3:
     	   		preorder(root, 0);
     	   		break;
     		
			case 4:
     	   		postorder(root, 0);
     	   		break;
     	   	
			case 5:
				printf("\nEnter an element to delete it from BST: ");
				scanf("%d", &element);
				delete_element(root, element, 0, 0, 2);
				break;
					
     	    case 6:
        	    return 0;
		}
		display(root);
		printf("\n");
	}while(1);
	free( root );
	root = NULL;
	return 0;
}
