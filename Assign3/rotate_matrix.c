//this program performs in-place matrix rotation in case of square matrices and uses extra space foro rectangular matrices.
//For square matrices, this program rotates the matrix cloclwise or anticlockwise as per user requirements as many number of times as user wants to.
//the matrix accepts characters.

#include<stdio.h>
#include<stdlib.h>


void rotate_anticlock(char** arr,int n);
void rotate_clock(char** arr,int n);
void print(char** arr, int row,int col);
void rotate_clock_rec(char** arr,char** arr1, int row, int col);
void rotate_anticlock_rec(char** arr,char** arr1, int row, int col);

int main(){	

	int row,col; //variables that store the number of rows and columns
	char ch='o'; //character used to handle to extra null character
	printf("Enter the number of rows:");
	scanf("%d",&row); 
	ch=getchar();
	printf("Enter the number of columns:");
	scanf("%d",&col);
	ch=getchar();
//	fflush(stdin);
	char **arr = (char **)malloc(row * sizeof(char *));  //Allocating the memory to the two dimesional character array at runtime as per the size entered by the user
    	for (int i=0; i<row; i++)
		arr[i] = (char *)malloc(col * sizeof(char));
	printf("Enter the matrix:");
	for(int i=0;i<row;i++){ //Loop which takes input
		for(int j=0;j<col;j++){
		//	fflush(stdin);
			scanf("%c",&arr[i][j]);
			ch=getchar();
	//		printf("Entered at (%d,%d)\n",i,j);
		}
	}
	printf("The matrix you entered is:\n");
	print(arr,row,col); //printing the matrix entered by the user
	if(row==col){  //The case when the matrix is a square matrix, in place rotation is performed
		int n=row;
		printf("How do you want to perform rotaion(Clockwise/Anti-clockwise) \n"); //prompting user about to direction
		printf("Press 0 for clockwise and 1 for Anti-clockwise rotation:");	
		int choice=0,num=0;
		scanf("%d",&choice);
		printf("Number of times rotation is to be performed:"); //primpting user about the number of times rotaion is to be performed
		scanf("%d",&num);
		if(num==0){ //handling the case when user enters 0
			print(arr,n,n);
			return 0;
		}
		num=num%4; //avoidind useless roations
		if(choice==0){ //when clockwise rotation is to be done
			for(int i=0;i<num;i++)
				rotate_clock(arr,n);
		}
		else if(choice==1){ //when anti-clockwise rotation is to be done
			for(int i=0;i<num;i++)
				rotate_anticlock(arr,n);
		}
		else{ //erro when the user enters an invalid value
			printf("Invalid Choice !!");
			return 0;
		}
		print(arr,n,n); //printing after rotation
	}
	else{
        	char **arr1 = (char **)malloc(col * sizeof(char *)); //if the matrix is rectangular, allocating extra space because in place not possible.
	        for (int i=0; i<col; i++)
        	        arr1[i] = (char *)malloc(row * sizeof(char));
                printf("How do you want to perform rotaion(Clockwise/Anti-clockwise) \n"); //prompting for the direction 
                printf("Press 0 for clockwise and 1 for Anti-clockwise rotation:\n");
                int choice=0,num=0;
                scanf("%d",&choice);
                printf("Number of times rotation is to be performed:"); //prompting for the number of times to perform rotation
                scanf("%d",&num);
		if(num==0){ //if user enters zero
			print(arr,row,col);
			return 0;
		}
		num=num%4;	//avoiding useless rotations
                if(choice==0){	//case when clockwise rotation to be performed
                        for(int i=0;i<num;i++)
                                rotate_clock_rec(arr,arr1,row,col);
                } 
                else if(choice==1){ //case when anti-clockwise rotation is to be performed
                        for(int i=0;i<num;i++)
                                rotate_anticlock_rec(arr,arr1,row,col);
                }
                else{ //when user provides invalid input
                        printf("Invalid Choice !!");
                        return 0;
                }
		print(arr1,col,row); //printing the rotated matrix
	}
}


//A function to rotate rectangular matrix clockwise
void rotate_clock_rec(char** arr,char** arr1, int row, int col){

	for(int i=0;i<col;i++){
		for(int j=0;j<row;j++){
			arr1[i][j]=arr[row-j-1][i];
		}
	}
}

//A function to rotate rectangular matrix anti-clockwise
void rotate_anticlock_rec(char** arr,char** arr1,int row,int col){

        for(int i=0;i<col;i++){
                for(int j=0;j<row;j++){
                        arr1[i][j]=arr[j][col-i-1];
                }
        }

}

//A function that prints a given matrix(2-d array) 
void print(char** arr, int row, int col){
	printf("\n\n");
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			printf("%c ",arr[i][j]);
		}
		printf("\n");
	}

}

//A fucntion to rotate square matrix in clockwise direction in place.
void rotate_clock(char** arr, int n){
        n--;
        int i=0;
	char temp='0';
/*      for(r=0,c=n-1;r<c;r++,c--){
                for(i=r;i<c;i++){
                        off= r-i;
                        
                        temp=arr[i][r];
                        arr[i][r]=arr[c+off][r];
                        arr[c+off][r]=arr[c][c+off];
                        arr[c][c+off]=arr[i][c];
                        arr[i][c]=temp;
                }
        }*/
        for(i=0;i<=n/2;i++){
                for(int j=i;j<n-i;j++){
                        temp=arr[j][n-i];
                        arr[j][n-i]=arr[i][j];
                        arr[i][j]=arr[n-j][i];
                        arr[n-j][i]=arr[n-i][n-j];
                        arr[n-i][n-j]=temp;
                }
        }
}


//A function to rotate a square matrix in anti-clockwise direction in place
void rotate_anticlock(char** arr,int n){
	for(int i=0;i<3;i++)
		rotate_clock(arr,n);
}
