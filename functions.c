#include<stdio.h> 
#include <string.h>
#include <stdlib.h> 
#include <ctype.h>
#include "functions.h"

// LOGIC HAM 

int choice; 
// 1. Menu mo dau cho chuong trinh  //////////////////////////////////////////////////////////////////////////////////////////////////////
void introduction(){
	printf("\n  *** Store Management System ***\n");
	printf("\n===================================");
	printf("\n|        Choose Your Role         |\n"); 
	printf("===================================");
	printf("\n|[1]  Admin.                      |");
	printf("\n|[2]  Exit the program.           |");
	printf("\n===================================\n");
}
void outIntroduction(){
	printf("\n\tEXIT PROGRAM.\n"); 
}

// 2. logic cua Admin///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void specialManagement(){
 	getchar(); 
	printf("\nPlease enter your Email(Thanhdat@123) :"); 
	fgets(input.email, sizeof(input.email), stdin); 
	input.email[strcspn(input.email, "\n")] = '\0';
	
	printf("Please enter your Password(152006) :"); 
	fgets(input.password, sizeof(input.password), stdin);
	input.password[strcspn(input.password, "\n")] = '\0';
	// Kiem tra mk tk 
    if (strncmp(input.email, user.email, sizeof(input.email)) == 0 &&
        strncmp(input.password, user.password, sizeof(input.password)) == 0) {
        system("cls");
        printf("\n\t===================================\n");
        printf("\t|       Login Successfull!        |\n");
        printf("\t===================================\n");
        menu();
    } else {
        printf("\n\t===================================\n");
        printf("\t|   Invalid email or password!    |\n");
        printf("\t===================================\n");
        printf("\t|       ~~~ WARNING ~~~           |\n"); 
        printf("\t|        Account locked           |\n");
        printf("\t===================================\n");
	} 
}
void menu(){
	do{
		printf("\n\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
		printf("\n\t|        Category Management       |\n"); 
		printf("\t|==================================|");
		printf("\n\t|[1]  Display the Category.        |");
		printf("\n\t|[2]  Add Category.                |");
		printf("\n\t|[3]  Repair the Category.         |");
		printf("\n\t|[4]  Delete Category.             |");
		printf("\n\t|[5]  Arranging Category.          |");
		printf("\n\t|[6]  Search for Category.         |");
		printf("\n\t|==================================|\n");
		printf("\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		printf("\n\tEnter the choice : ");
		scanf("%d", &choice);
		switch(choice){
			case 1:
			 	displayCategory();
				break;
			case 2:
				addCategory();
				break;
			case 3:
				repairCategory();
				break;
			case 4:
				deleteCategory();
				break;
			case 5:
				arrangeCategory();
				break;
			case 6:
				searchCategory();
				break;	
		default:
			printf("\nInvalid selection! Please choose again!\n");
		}
	} while(choice!=7); 
	
}

// Display the products  // IN  *****
void displayCategory() {
	int num =0; 
	FILE *ptr = fopen("product.dat", "rb");
    if (ptr == NULL) {
        printf("\n\tERROR OPENING FILE.\n");
        return;
    }

    printf("\t\t==============================\n");
    printf("\t\t| ID  |   Category   |  Qty  |\n");
    printf("\t\t==============================\n");
	// %49[^|] se doc vao chuoi ki tu cho den khi gap ki tu | hoac den khi dat den kt 49 ; gt eof =-1 dung doc den cuoi cung chuoi 
    while (fscanf(ptr, "%d|%49[^|]|%d\n", &category[num].id, category[num].name, &category[num].price) != EOF) {
        printf("\t\t| %-3d | %-12s | %-5d |\n", category[num].id-1, category[num].name, category[num].price);
        printf("\t\t------------------------------\n");
        num++;  
    }
    
    fclose(ptr);
	printf("\n");
	exitBackround();
}
 
// Add product  // Them ****** HOAN THANH  
void addCategory() {
	FILE *str = fopen("product.dat", "rb+");  
    if (str == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    int num = 0;
    while (fscanf(str, "%d|%49[^|]|%d\n", &category[num].id, category[num].name, &category[num].price) != EOF) {
        num++;
    }
    //
	int position;
    printf("\n\tEnter the position where you want to add the dish (0 to %d): ", num);
    scanf("%d", &position);
    if (position < 0 || position > num) {
        printf("Invalid position.\n");
        return;
    }
    char newName[50];
    getchar();  
    printf("\tEnter the dish you want to add to the menu: ");
    fgets(newName, sizeof(newName), stdin);
    newName[strcspn(newName, "\n")] = '\0';  
    // kiem tra trung ten 
    for (int i = 0; i < num; i++) {
        if (strcasecmp(category[i].name, newName) == 0) { 
            printf("/tThe dish name '%s' already exists in the menu. Please enter a different name.\n", newName);
            return;
        }
    }
    // tiep tuc ct sau khi kt trung ten 
    for (int i = num; i > position; i--) {
       category[i] = category[i - 1];
    }
    category[position].id = num + 1;  
    strcpy(category[position].name, newName); // gan lai ten moi 
    printf("\tThe quantity of the dish: ");
    scanf("%d", &category[position].price);
    num++;
    printf("\nMenu after adding dish\n");
	printf("\t===============================\n");
	printf("\t| ID  |   Category   |  Qty   |\n");
	printf("\t===============================\n");
	for (int i = 0; i < num; i++) {
	    printf("\t| %-3d | %-12s | %-6d |\n", category[i].id-1, category[i].name, category[i].price);
	    printf("\t-------------------------------\n");
	}
	// luu file 
	str = fopen("product.dat", "wb"); 
    if (str == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < num; i++) {
        fprintf(str, "%d|%s|%d\n", category[i].id, category[i].name, category[i].price);
    }

    fclose(str);  
    printf("Menu has been saved to file 'product.dat'.\n");
    printf("\n");  
	exitBackround();
    
}

// Repair the product  // Sua ****** HOAN THANH  
void repairCategory() {
	FILE *str = fopen("product.dat", "rb+");  
    if (str == NULL) {
        printf("Error opening file for reading and writing.\n");
        return;
    }
    int num = 0;
    while (fscanf(str, "%d|%49[^|]|%d\n", &category[num].id, category[num].name, &category[num].price) != EOF) {
        num++;
    }
    // b ktra 
	int fixmenu;
	int addmenu;
	printf("\tThe position you want to edit the menu(0 to %d) : ",num-1);
	scanf("%d", &fixmenu);
	if(fixmenu<0 || fixmenu>num-1){
		printf("\n\tINVALID POSITION\n");
		return; 
	}
	// nhap ten moi... 
	getchar(); 
	printf("\tNenter a new name for the menu : ");
	fgets(category[fixmenu].name,sizeof(category[fixmenu].name),stdin);
	category[fixmenu].name[strcspn(category[fixmenu].name, "\n")] = '\0';
	printf("\tThe quantity of the dish : ");
	scanf("%d", &category[fixmenu].price);
	printf("\n"); 
	printf("\t*Menu after modifying the elements as requested : \n");
	printf("\t===============================\n");
	printf("\t| ID  |   Category   |  Qty   |\n");
	printf("\t===============================\n");
	for (int i = 0; i < num; i++) {
	    printf("\t| %-3d | %-12s | %-6d |\n", category[i].id-1, category[i].name, category[i].price);
	}
	printf("\t===============================\n\n"); 
	// luu file 
	str = fopen("product.dat", "wb"); 
    if (str == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < num; i++) {
        fprintf(str, "%d|%s|%d\n", category[i].id, category[i].name, category[i].price);
    }

    fclose(str);  
    printf("Menu has been saved to file 'product.dat'.\n");
    printf("\n");
    exitBackround();
}

// Delete product  // Xoa ****** HOAN THANH 
void deleteCategory() {
	int deleteId;
    int check = -1;

    FILE *str = fopen("product.dat", "rb+");  
    if (str == NULL) {
        printf("Error opening file for reading and writing.\n");
        return;
    }

    int num = 0;
    while (fscanf(str, "%d|%49[^|]|%d\n", &category[num].id, category[num].name, &category[num].price) != EOF) {
        num++;
    }

    fclose(str);

    printf("Enter the ID of the dish to be deleted (1 to %d): ", num);
    scanf("%d", &deleteId);
    if (deleteId < 1 || deleteId > num) {
        printf("\n\tINVALID ID\n");
        return; 
    }
    for (int i = 0; i < num; i++) {
        if (category[i].id == deleteId) {
            check = 1;
            for (int j = i; j < num - 1; j++) {
                category[j] = category[j + 1];
            }
            num--;
            printf("The dish with ID %d has been removed.\n", deleteId);
            break;
        }
    }
    if (check == -1) {
        printf("The dish with ID %d was not found.\n", deleteId);
        return;
    }
	// gan id 
    for (int i = 0; i < num; i++) {
        category[i].id = i + 1; 
    }

    printf("\nMenu after the dish has been removed:\n");
    printf("\t===============================\n");
    printf("\t| ID  |   Category   |  Qty   |\n");
    printf("\t===============================\n");
    for (int i = 0; i < num; i++) {
        printf("\t| %-3d | %-12s | %-6d |\n", category[i].id-1, category[i].name, category[i].price);
    }
    printf("\t===============================\n\n");
	// luu file 
    str = fopen("product.dat", "wb");  	
    if (str == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < num; i++) {
        fprintf(str, "%d|%s|%d\n", category[i].id, category[i].name, category[i].price);
    }

    fclose(str);
    printf("Menu has been saved to file 'product.dat'.\n");
    printf("\n");

    exitBackround();
}

// Arranging products   // Sap Xep ****** HOAN THANH // KHONG DUOC LUU VAO FILE
void arrangeCategory() {
	FILE *str = fopen("product.dat", "rb");
    if (str == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    int num = 0;  
    while (fscanf(str, "%d|%49[^|]|%d\n", &category[num].id, category[num].name, &category[num].price) != EOF) {
        num++;
    }
    fclose(str);
	for (int i = 0; i < num - 1; i++) {
    	for (int j = i + 1; j < num; j++) {
       		if (category[i].price > category[j].price) {
          		struct Dish temp = category[i];
         		category[i] = category[j];
      		    category[j] = temp;
            }
   	 	} 
	}
    printf("\n\tMenu arranged in ascending order\n"); 
    printf("\t===============================\n");
	printf("\t| ID  |   Category   |  Qty   |\n");
	printf("\t===============================\n");
	for (int i = 0; i < num; i++) {
	    printf("\t| %-3d | %-12s | %-6d |\n", category[i].id-1, category[i].name, category[i].price);
	}
	printf("\t===============================\n\n");
    exitBackround(); 
}

// Search for products  // Tim Kiem ****** HOAN THANH 
void searchCategory() {
	fflush(stdin);
    char search[100];  
    printf("\n\tEnter the name of the dish you want to find: ");
    fgets(search, sizeof(search), stdin);
    search[strcspn(search, "\n")] = '\0';  

    if (strlen(search) == 0) {
        printf("\tError: You must enter a dish name.\n");
        return;
    }

    FILE *str = fopen("product.dat", "rb");
    if (str == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    int num = 0;
    while (fscanf(str, "%d|%49[^|]|%d\n", &category[num].id, category[num].name, &category[num].price) != EOF) {
        num++;
    }
    fclose(str);

    int check = -1;
    printf("\n\t+---------------------------------------------------------------+\n");
    printf("\t|                        Search Results                         |\n");
    printf("\t+---------------------------------------------------------------+\n");

    char searchName[100];
    for (int i = 0; i < strlen(search); i++) {
        searchName[i] = tolower(search[i]);
    }

    for (int i = 0; i < num; i++) {
        char cave[50];
        for (int j = 0; j < strlen(category[i].name); j++) {
            cave[j] = tolower(category[i].name[j]);
        }
        cave[strlen(category[i].name)] = '\0';

        if (strstr(cave, searchName) != NULL) {
            printf("\t| Dish found at position: [%3d]                                 |\n", i + 1);
            printf("\t+---------------------------------------------------------------+\n");
            printf("\t| ID: %-5d | Name: %-25s | Qty: %-10d |\n", category[i].id-1, category[i].name, category[i].price);
            printf("\t+---------------------------------------------------------------+\n");
            check = 1;
        }
    }

    if (check == -1) {
        printf("\t|                *** ~~~~ DISH NOT FOUND. ~~~~ ***              |\n");
        printf("\t+---------------------------------------------------------------+\n");
    }
    printf("\n");
    exitBackround();
}

// Quay lai 
void exitBackround(){
	char choiceMenu;
	printf("\tGo back(b)? or Exit(e)? Product(p)? :");
	getchar();
	scanf("%c", &choiceMenu); 
	if(choiceMenu == 'b' || choiceMenu == 'B'){
		system("cls");
		printf("\n\tGo back to menu.\n");
		menu();
	}
	if(choiceMenu == 'p' || choiceMenu == 'P'){
		system("cls");
		view();
	}
	if(choiceMenu == 'e' || choiceMenu == 'E'){
		system("cls"); 
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
					return; 
					break;
			default:
			    printf("\n Invalid selection! Please choose again! \n ");		
			}
		}while(choice!=2);
	} 
	if(choiceMenu!='b' && choiceMenu == 'B' && choiceMenu!='e' && choiceMenu == 'E' && choiceMenu == 'p' && choiceMenu == 'P'){
		printf("\n\tINVALID\n");
		return; 
	} 
}
// logic product
void view(){
	do{
		printf("\n\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
		printf("\n\t|        Product Management        |\n"); 
		printf("\t|==================================|");
		printf("\n\t|[1]  Display the product.         |");
		printf("\n\t|[2]  Add product.                 |");
		printf("\n\t|[3]  Repair the product.          |");
		printf("\n\t|[4]  Delete product.              |");
		printf("\n\t|[5]  Arranging product.           |");
		printf("\n\t|[6]  Search for product.          |");
		printf("\n\t|==================================|\n");
		printf("\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		printf("\n\tEnter the choice : ");
		scanf("%d", &choice);
		switch(choice){
			case 1:
				displayPtd();
				break;
			case 2:
				addPtd();
				break;
			case 3:
				repairPtd();
				break;
			case 4:
				deletePtd();
				break;
			case 5:
				arrangePtd();
				break;
			case 6:
				searchPtd();
				break;	
		default:
			printf("\nInvalid selection! Please choose again!\n");
		}
	} while(choice!=6); 
}
// in them sua xoa sap xep tim kiem 
// in 
void displayPtd(){
	char category[50];
    printf("Enter the category to view products: ");
    fflush(stdin);
    if (fgets(category, sizeof(category), stdin)) {
        category[strcspn(category, "\n")] = '\0';  
    }

    FILE *Tptr = fopen("category.dat", "rb");
    if (Tptr == NULL) {
        printf("Error opening file.\n");
        return;
    }

    Product view;
    int found = 0;
    printf("*=======|===========================|===============|=============*\n");
    printf("|  ID   |       Product Name        |      Price    |   Quantity  |\n");
    printf("|=======|===========================|===============|=============|\n");

    while (fread(&view, sizeof(Product), 1, Tptr) != 0) {
        if (strncasecmp(view.typeProduct, category, strlen(category)) == 0) {
            printf("| %5d | %-25s | %-13s | %11d |\n",
                view.id,
                view.nameProduct,
                view.price,
                view.quantity);
            printf("|-------|---------------------------|---------------|-------------|\n");
            found = 1;
        }
    }

    if (!found) {
        printf("| No products found in category: %-25s        |\n", category);
        printf("|-------|---------------------------|---------------|-------------|\n");
    }

    printf("*=======|===========================|===============|=============*\n");
    fclose(Tptr);
    printf("\n");
	exitProduct();
}
// them 
void addPtd(){
	FILE *ptr = fopen("category.dat", "ab+");
    if (ptr == NULL) {
        printf("Error opening file.\n");
        return;
    }

    Product add[50];
    int n;
    printf("Enter the quantity of products you want to add: ");
    scanf("%d", &n);
    getchar();  

    Product temp;

    for (int i = 0; i < n; i++) {
        printf("*Enter product information*\n");
        int isValidID = 0;
        while (!isValidID) {
            printf("ID: ");
            scanf("%d", &add[i].id);
            getchar();  
			// ktra id 
            if (add[i].id < 1) {
                printf("Invalid ID. Please enter a valid ID (greater than 0): ");
                continue;
            }
            isValidID = 1;  
            fseek(ptr, 0, SEEK_SET);
            while (fread(&temp, sizeof(Product), 1, ptr)) {
                if (temp.id == add[i].id) {
                    printf("ID already exists. Please enter a different ID.\n");
                    isValidID = 0;
                    break;
                }
            }
        }

        // ten bd 
        fflush(stdin);
        printf("Product Name: ");
        fgets(add[i].nameProduct, sizeof(add[i].nameProduct), stdin);
        add[i].nameProduct[strcspn(add[i].nameProduct, "\n")] = '\0'; 

        while (strlen(add[i].nameProduct) == 0) {
            printf("Product name cannot be empty. Please enter again: ");
            fgets(add[i].nameProduct, sizeof(add[i].nameProduct), stdin);
            add[i].nameProduct[strcspn(add[i].nameProduct, "\n")] = '\0';
        }

    	// ktra trung lap 
        fseek(ptr, 0, SEEK_SET); // ham chuan di vao giua file  
        int isValidName = 1;
        while (fread(&temp, sizeof(Product), 1, ptr)) {
            if (strcasecmp(temp.nameProduct, add[i].nameProduct) == 0) {
                printf("Product name already exists. Please choose a different name.\n");
                isValidName = 0;
                break;
            }
        }
        if (!isValidName) {
            i--;  
            continue;
        }
		// gia 
        printf("Product Price: ");
        fgets(add[i].price, sizeof(add[i].price), stdin);
        add[i].price[strcspn(add[i].price, "\n")] = '\0';

        while (strlen(add[i].price) == 0) {
            printf("Product price cannot be empty. Please enter again: ");
            fgets(add[i].price, sizeof(add[i].price), stdin);
            add[i].price[strcspn(add[i].price, "\n")] = '\0';
        }
		// so luong 
        printf("Product Quantity: ");
        scanf("%d", &add[i].quantity);
        getchar();

        while (add[i].quantity < 1) {
            printf("Quantity must be greater than 0. Please enter again: ");
            scanf("%d", &add[i].quantity);
            getchar();
        }

        fflush(stdin);
        printf("Product Type: ");
        fgets(add[i].typeProduct, sizeof(add[i].typeProduct), stdin);
        add[i].typeProduct[strcspn(add[i].typeProduct, "\n")] = '\0';

        while (strlen(add[i].typeProduct) == 0) {
            printf("Product type cannot be empty. Please enter again: ");
            fgets(add[i].typeProduct, sizeof(add[i].typeProduct), stdin);
            add[i].typeProduct[strcspn(add[i].typeProduct, "\n")] = '\0';
        }
    }

    fwrite(add, sizeof(Product), n, ptr);
    printf("\nProducts have been added successfully.\n");
    fclose(ptr);
    printf("\nUpdated Successfully !!!\n");
    printf("\n");
	exitProduct();
}

// sua 
void repairPtd(){
	int addEdit;
    Product edit;
    FILE *Tptr = fopen("category.dat", "rb+");  // Mo file category.dat theo mode doc-va-ghi nh? phân
    if (Tptr == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Tinh tong so luong san pham trong file
    // SEEK_SET dung de di chuyen con tro toi vi tri cu the 
	// SEEK_END dung de di chuyen con tro toi cuoi file.
    fseek(Tptr, 0, SEEK_END);
    int totalProducts = ftell(Tptr) / sizeof(Product);  // Tinh so san pham
    fseek(Tptr, 0, SEEK_SET);  // Reset con tro file ve dau

    // Yeu cau nhap ID san pham muon sua
    printf("Enter the product ID you want to edit: ");
    scanf("%d", &addEdit);
    while (addEdit < 1 || addEdit > totalProducts) {
        printf("Invalid ID. Please enter a valid ID (1 to %d): ", totalProducts);
        scanf("%d", &addEdit);
    }

    // In ra thong tin san pham hien tai
    printf("\nCurrent product details:\n");
    fseek(Tptr, (addEdit - 1) * sizeof(Product), SEEK_SET);
    fread(&edit, sizeof(Product), 1, Tptr);  // Doc san pham de sua
    printf("*=======|===========================|===============|=============*\n");
    printf("|  ID   |       Product Name        |     Price     |   Quantity  |\n");
    printf("|=======|===========================|===============|=============|\n");
    printf("| %5d | %-25s | %-13s | %11d |\n", edit.id, edit.nameProduct, edit.price, edit.quantity);
    printf("*=======|===========================|===============|=============*\n");

    // Bat dau qua trinh sua san pham
    printf("\n*Edit the product details*\n");
    getchar(); 

    // Sua ten san pham
    printf("New product name: ");
    fgets(edit.nameProduct, sizeof(edit.nameProduct), stdin);
    edit.nameProduct[strcspn(edit.nameProduct, "\n")] = '\0';
    while (strlen(edit.nameProduct) == 0) {
        printf("Product name cannot be empty. Please enter again: ");
        fgets(edit.nameProduct, sizeof(edit.nameProduct), stdin);
        edit.nameProduct[strcspn(edit.nameProduct, "\n")] = '\0';
    }

    // Kiem tra xem ten san pham da ton tai hay chua (ngoai tru san pham hien tai)
    fseek(Tptr, 0, SEEK_SET);  // Reset con tro file
    int isValidName = 1;
    Product temp;
    while (fread(&temp, sizeof(Product), 1, Tptr)) {
        if (strcmp(temp.nameProduct, edit.nameProduct) == 0 && temp.id != edit.id) {
            printf("Product name already exists. Please choose a different name.\n");
            isValidName = 0;
            break;
        }
    }
    if (!isValidName) {
        printf("Edit failed due to duplicate product name.\n");
        fclose(Tptr);
        return;
    }

    // Sua loai san pham
    printf("Product Type: ");
    fgets(edit.typeProduct, sizeof(edit.typeProduct), stdin);
    edit.typeProduct[strcspn(edit.typeProduct, "\n")] = '\0';

    // Sua gia san pham
    printf("Product Price: ");
    fgets(edit.price, sizeof(edit.price), stdin);
    edit.price[strcspn(edit.price, "\n")] = '\0';
    while (strlen(edit.price) == 0) {
        printf("Product price cannot be empty. Please enter again: ");
        fgets(edit.price, sizeof(edit.price), stdin);
        edit.price[strcspn(edit.price, "\n")] = '\0';
    }

    // Sua so luong san pham
    printf("Product Quantity: ");
    scanf("%d", &edit.quantity);
    getchar();
    while (edit.quantity < 1) {
        printf("Quantity must be greater than 0. Please enter again: ");
        scanf("%d", &edit.quantity);
        getchar();
    }

    // Ghi lai san pham vao file
    fseek(Tptr, (addEdit - 1) * sizeof(Product), SEEK_SET);
    fwrite(&edit, sizeof(Product), 1, Tptr);  

    // Dong file 
    fclose(Tptr);
    printf("\nProduct details have been successfully updated!\n");
    printf("\n"); 
    exitProduct();
}
// xoa 
void deletePtd(){
	printf("\n\t*** THE STORE SYSTEM IS BEING UPDATED ***\n"); 
	printf("\n");
	exitProduct();
}
// sap sep 
void arrangePtd(){
	printf("\n\t*** THE STORE SYSTEM IS BEING UPDATED ***\n");
	printf("\n");
	exitProduct();
}
// tim kiem 
void searchPtd(){
	printf("\n\t*** THE STORE SYSTEM IS BEING UPDATED ***\n");
	printf("\n");
	exitProduct();
}

// thoat product

void exitProduct(){
	char choiceMenu;
	printf("\tGo back(b)? or Exit(e)? :");
	getchar();
	scanf("%c", &choiceMenu); 
	if(choiceMenu == 'b' || choiceMenu == 'B'){
		system("cls");
		printf("\n\tGo back to menu.\n");
		view();
	}
	if(choiceMenu == 'e' || choiceMenu == 'E'){
		system("cls"); 
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
					return; 
					break;
			default:
			    printf("\n Invalid selection! Please choose again! \n ");		
			}
		}while(choice!=2);
	} 
	if(choiceMenu!='b' && choiceMenu == 'B' && choiceMenu!='e' && choiceMenu == 'E'){
		printf("\n\tINVALID\n");
		return; 
	} 
}
