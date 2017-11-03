#ifndef _lab7_h_
#define _lab7_h_

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#define MAX_NAME_SIZE 15

typedef struct {
	char name[MAX_NAME_SIZE];
	float amount;
	char unit[5];
}groceryItem;

typedef struct {
	int listLength;
	groceryItem *items;
}shoppinglist;

void printMenue();
void add(groceryItem *tempGroceryItem);
void print(shoppinglist *myShoppinglist);
void editItem(shoppinglist *myShoppinglist, int editId);
void removeItem(shoppinglist *myShoppinglist, int removeId);
void saveToFile(shoppinglist *myShoppinglist, int *noItems);
void readFromFile(shoppinglist *tempGroceryItem, int *noItems);
//saveToTextFile(&myShoppinglist, &noItems);
//readFromFile(&myShoppinglist, &noItems);

#endif
