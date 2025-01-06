#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
 
int main(int argc, char *argv[]) {
	int choice; 
	do{
		introduction();
		printf("\n\tEnter the choice : ");
		scanf("%d", &choice);
		switch(choice){
			case 1:
				specialManagement();
				break;	
			case 2:
				outIntroduction();
				return 0; 
				break;
		default:
		    printf("\n Invalid selection! Please choose again! \n ");		
		}
	}while(choice!=2);
	return 0;
}
