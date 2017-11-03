/* -------------------------\
|       ANDERS EKWALL       |
|      DVA117, block 2      |
\--------------------------*/

//#include "C:/_C/block_2/lab7.h"
#include "lab7.h"

int main(void) {
	int go = 1, choice = 0, noItems = 0;
	shoppinglist myShoppinglist, temp;
	myShoppinglist.listLength = noItems;
	temp.items = (groceryItem*)malloc(sizeof(groceryItem));
	if (&temp.items != NULL)
	myShoppinglist = temp;
	while(go){
		printMenue();
		scanf("%d", &choice);
		while (getchar() != '\n');
		switch (choice) {
			case 1:// Add
						temp.items = (groceryItem*)realloc(myShoppinglist.items, sizeof(groceryItem)*(noItems+1));
						if (&temp.items != NULL)
						myShoppinglist = temp;
						add(&myShoppinglist.items[noItems]);
						noItems++;
						myShoppinglist.listLength = noItems;
						break;
			case 2:// Edit
					printf("\tWhich item do you want to edit? ");
					scanf("%d", &choice);
					editItem(&myShoppinglist, choice);
					break;
			case 3:// Remove
					printf("\tWhich item do you want to remove? ");
					scanf("%d", &choice);
					removeItem(&myShoppinglist, choice);
					noItems = myShoppinglist.listLength;
					break;
			case 4:// Print
					print(&myShoppinglist);
					break;
			case 5:// Save
					//saveToFile(&myShoppinglist, &noItems);
					saveToTextFile(&myShoppinglist, &noItems);
					break;
			case 6:// Load
					readFromFile(&myShoppinglist, &noItems);
					//readFromTextFile(&myShoppinglist, &noItems);
					noItems = myShoppinglist.listLength;
					break;
			case 7:// Quit
					go=0;
					free(myShoppinglist.items);
					myShoppinglist.items = NULL;
					break;
			default:printf("\nfel\n");
		}
	}
	return 0;
}
