#include <stdbool.h>

// KHAI BAO CAU TRUC DU LIEU

// Dung cho email va pass tk Admin 
struct User {
    char email[100];
    char password[100];
};
struct User user = {"Thanhdat@123", "152006"};
struct User input;

// Dung cho them, sua, xoa, sap xep, tim kiem cua Admin 
struct Dish{
	int id;
	char name[50];
	int price;
	int quantity; 
};
struct Dish category[50]={
	{1,"Drinks", 6},
	{2,"Food", 5},
}; 
typedef struct{
	int id;
	char nameProduct[50];
	char price[25];
	int quantity;
	char typeProduct[25];
}Product;
