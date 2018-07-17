// this program allows a user to place an order at cafe and generates respective bill corresponding the order.
#include<stdio.h>

int main(){
	int items[]={1,2,3,4,5,6,7,8};
	char names[][30]={"Burger","Sandwich","Fries","Pizza","Pasta","Coke","Mojito","Cold Coffee"};
	int prices[]={50,80,60,150,120,40,80,60};
	int choices[100];
	int quantities[100];
	printf("============================Welcome to Mayank's Cafe============================\n\n");
	printf("======================================MENU======================================\n");
	printf("Item Code\t\tItem Name\t\tPrice\n");
	printf("=========\t\t=========\t\t=====\n");
	for(int i=0;i<8;i++){
		//printf("%d.       \t\t%s       \t\t%d\n",items[i],names[i],prices[i]);
		printf("%-10d\t\t%-10s\t\t%-5d\n",items[i],names[i],prices[i]);
	}
	int i=0;
	int ch=1;
	do{
		printf("Enter Item code to order:");
		scanf("%d",&choices[i++]);
		printf("Enter The quantity of %s to order:",names[choices[i-1]-1]);
		scanf("%d",&quantities[i-1]);
		printf("More Items to add ?/n Enter 1 if Yes, 0 otherwise:");
		scanf("%d",&ch);
	}while(ch==1);

	printf("Thank you for placing order with us!/n Your Innvoice is:\n\n\n\n");
	printf("======================================BILL======================================\n");
	printf("  S.No.  \t\tItem Name\t\tPrice\t\tQuantity\t\tAmount\n");
	printf("=========\t\t=========\t\t=====\t\t========\t\t======\n");
	int total=0;
	for(i=0;choices[i]!='\0';i++){
		printf("%-3d\t\t\t%-10s\t\t%-5d\t\t%-3d\t\t\t%-5d\n",i+1,names[choices[i]-1],prices[choices[i]],quantities[i],quantities[i]*prices[choices[i]]);
		total+=quantities[i]*prices[choices[i]];
	}
	printf("================================================================================\n");
	printf("Taxes(18%)= %f\n",0.18*(float)total);
	printf("                                      Total Amount to be paid=%f\n",(0.18*(float)total)+(float)total );


	return 0;
}
