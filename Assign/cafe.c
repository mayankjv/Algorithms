// this program allows a user to place an order at cafe and generates respective bill corresponding the order.
#include<stdio.h>

int main(){
	int items[]={1,2,3,4,5,6,7,8}; //Simple item codes taken in an array so as to make it easy to map to prices
	char names[][30]={"Burger","Sandwich","Fries","Pizza","Pasta","Coke","Mojito","Cold Coffee"}; //names taken as an array to display in innvoice as well as menu
	int prices[]={50,80,60,150,120,40,80,60}; //prices taken as an array to be mapped to the item codes
	int choices[100]; //The items that the user will add to the order
	int quantities[100];	//quantities of the items user will add
	//The below code displays menu
	printf("============================Welcome to Mayank's Cafe============================\n\n");
	printf("======================================MENU======================================\n");
	printf("Item Code\t\tItem Name\t\tPrice\n");
	printf("=========\t\t=========\t\t=====\n");
	for(int i=0;i<8;i++){
		printf("%-10d\t\t%-10s\t\t%-5d\n",items[i],names[i],prices[i]);
	}
	int i=0; //iterator variable
	int ch=1; //varibale to check if the user wants to add more items to order or not
	// loop accepting the order and storing the choices and corresponding quantities in arrays
	do{
		printf("Enter Item code to order:");
		scanf("%d",&choices[i++]);
		printf("Enter The quantity of %s to order:",names[choices[i-1]-1]);
		scanf("%d",&quantities[i-1]);
		printf("More Items to add ?/n Enter 1 if Yes, 0 otherwise:");
		scanf("%d",&ch);
	}while(ch==1);
	// generating Bill 
	printf("Thank you for placing order with us!/n Your Innvoice is:\n\n\n\n");
	printf("======================================BILL======================================\n");
	printf("  S.No.  \t\tItem Name\t\tPrice\t\tQuantity\t\tAmount\n");
	printf("=========\t\t=========\t\t=====\t\t========\t\t======\n");
	int total=0; //variable that will store the current total amount at any instant
	//Loop for desplaying the all items in the bill along with their quantities and proices and total amounts
	choices[i]=-1;
	for(i=0;choices[i]!=-1;i++){
		printf("%-3d\t\t\t%-10s\t\t%-5d\t\t%-3d\t\t\t%-5d\n",i+1,names[choices[i]-1],prices[choices[i]-1],quantities[i],quantities[i]*prices[choices[i]-1]); //formatting the bill properly
		total+=quantities[i]*prices[choices[i]-1]; 
		//printf("Current Total=%n\ld",total);
	}
	printf("Total:%d",total);
	printf("================================================================================\n");
	printf("Taxes(18%)= %f\n",(float)0.18*(float)total);  //Calculating the taxes as 18 percent of the total amount and displaying them
	printf("================================================================================\n");	
	printf("\n                                      Total Amount to be paid=%f\n",(float)(0.18*(float)total)+(float)total ); //Displaying the Total amount inclusive of taxes

	return 0;
}
