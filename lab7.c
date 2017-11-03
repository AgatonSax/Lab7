//#include "C:/_C/block_2/lab7.h"
#include "lab7.h"

void printMenue(){
	printf("\n");
	printf("\t::1:: Add item to shoppinglist\n");
	printf("\t::2:: Edit shoppinglist item\n");
	printf("\t::3:: Remove shoppinglist item\n");
	printf("\t::4:: Print shoppinglist\n");
	printf("\t::5:: Save to file\n");
	printf("\t::6:: Load from file\n");
	printf("\t::7:: Quit\n");
	printf("\n\t:: Choise: ");
}

void add(groceryItem *tempGroceryItem){
	int inputOK=0;
	float tmp;
	printf("\n\tGrocery item: ");
	gets((*tempGroceryItem).name);
	printf("\tAmount: ");
	while (inputOK==0){
		inputOK=scanf("%f", &tmp);
		while (getchar() != '\n');
		if(tmp<0){
			inputOK=0;
			printf("\tError, type a number greater than zero: ");
		}
		else{
				(*tempGroceryItem).amount=tmp;
			}
	}
	printf("\tunit: ");
	gets((*tempGroceryItem).unit);
}

void print(shoppinglist *myShoppinglist) {
	int i = 0;
	if ((*myShoppinglist).listLength == 0){
		printf("\n\tShoppinglist is empty.\n");
	}
	else{
		printf("\n\tShoppinglist\n\t%s\t%-15s  %s\t%s\n","ID", "Name", "Amount", "Unit");
		while (i < (*myShoppinglist).listLength){
			printf("\t%d\t%-15s  %.1f\t%s\n", i+1, (*myShoppinglist).items[i].name, (*myShoppinglist).items[i].amount, (*myShoppinglist).items[i].unit);
			i++;
		}
	}
}
void editItem(shoppinglist *myShoppinglist, int editId){
	if(editId--<1){
		printf("\ttry again!\n");
		return;
	}
	printf("\tNew amount for %s: ", (*myShoppinglist).items[editId].name);
	scanf("%f", &((*myShoppinglist).items[editId].amount));
	while (getchar() != '\n');
}
void removeItem(shoppinglist *myShoppinglist, int removeId){
	shoppinglist tempList;// = myShoppinglist;// = *myShoppinglist;
	tempList = *myShoppinglist;
	//printf("%x %x\n", tempList, myShoppinglist);
	int i = 0, j = 0;
	if(removeId--<1){
		printf("\ttesta igen!\n");
		return;
	}
	(*myShoppinglist).listLength = tempList.listLength - 1;
	while(i < tempList.listLength){
		if (i == removeId){
			i++;
		}
		else{
			(*myShoppinglist).items[j] = tempList.items[i];
			i++;
			j++;
		}
	}
	(*myShoppinglist).items = (groceryItem*)realloc((*myShoppinglist).items, sizeof(groceryItem) * (*myShoppinglist).listLength);
}
void saveToFile(shoppinglist *tempShoppinglist, int *noItems){
	FILE *fp;
	int antal;
	char filepathName[40] = "C:/_C/", filename[20];
	printf("\n\tFilename: ");
	gets(filename);
	strcat(filepathName, filename);
	fp = fopen(filepathName,"wb");
	if (fp == NULL){
		printf("File could not be opened");
		return;
	}
	fwrite(&(*tempShoppinglist).listLength, sizeof(int), 1, fp);
	antal = fwrite((*tempShoppinglist).items, sizeof(groceryItem), *noItems, fp);
	printf("\n\tSuccessfully wrote %d list items to file\n", antal);
	fclose(fp);
}

void saveToTextFile(shoppinglist *tempShoppinglist, int *noItems){
    FILE *fp;
	int i;
	//char filepathName[250] = PATH, 
	char filename[20];
	printf("\n\tFilename: ");
	gets(filename);
	//strcat(filepathName, filename);
    //fp = fopen(filepathName, "w"); 
	fp = fopen(filename, "w"); 
    if(fp == NULL){
        printf("File could not be opened");
	}
    else
    {
        //printf("Writing to textfile...");
        fprintf(fp, "%d\n", *noItems); //How many cities (helpfull when reading from file)
        for(i = 0; i < *noItems; i++) //print information about all cities in array
        {
            fprintf(fp, "%s\n", (*tempShoppinglist).items[i].name);
            fprintf(fp, "%f\n %s\n", (*tempShoppinglist).items[i].amount, (*tempShoppinglist).items[i].unit);
        }
        fclose(fp); //close file when finished
        printf("Writing complete\n");
    }
}

void readFromFile(shoppinglist *tempShoppinglist, int *noItems){
	FILE *fp;
	groceryItem *tempGroceryItem;
	int antal;
	//char filepathName[250] = PATH, filename[20];
	char filepathName[250] = "C:/Users/ael17003/OneDrive - M\x84lardalens h\x94gskola/DVA117_programmering_C/Laborationer/Block2/", filename[20];
	printf("\n\tFilename: ");
	gets(filename);
	strcat(filename, filename);
	printf("path: %s", filepathName);
	//if ((fp = fopen(filepathName,"rb")) == NULL){
	if ((fp = fopen(filename,"rb")) == NULL){
		printf("File could not be opened");
	}
	else{
		fread(noItems, sizeof(int), 1, fp);
		if ((tempGroceryItem = (groceryItem*)realloc((*tempShoppinglist).items, sizeof(groceryItem) * (*noItems))) == NULL){
				printf("Memory error");
		}
		else{
			(*tempShoppinglist).items = tempGroceryItem;
			antal = fread((*tempShoppinglist).items, sizeof(groceryItem), *noItems, fp);
			printf("\n\tRead %d list items from file\n", antal);
			(*tempShoppinglist).listLength = *noItems;
		}
		fclose(fp);
		}
	}
	
/*
	city* readFromTextFile(int *noCities){
    FILE *fp;
    int i;
    long lastChar = 0;
    city *pCities = NULL;
    fp = fopen("/Users/cul01/Desktop/cities.txt", "r"); //open file in read-mode
    if(fp == NULL) //test if not successful
        printf("File could not be found\n");
    else
    {
        printf("Reading from textfile... \n");
        fscanf(fp, "%d\n", noCities); //how many city-structs
        pCities = (city*)malloc(sizeof(city)*(*noCities)); /*allocate memory of the rigt size (noCities cities), malloc returns a
                                                            pointer*\/
        if(pCities == NULL) //check if not successfull
        {
            printf("Memory error\n");
            return NULL;
        }
        for(i = 0; i < *noCities; i++) //read all information about all cities and store in array
        {
            fgets((pCities+i)->name, sizeof((pCities+i)->name), fp); //also reads the \n - which will be part of string - problematic
            lastChar = strlen((pCities+i)->name); //find length of string
            (pCities+i)->name[lastChar-1] = '\0'; //replace \n with \0 to remove \n from string
            fscanf(fp, "%d\n%f %f\n", &(pCities+i)->population, &(pCities+i)->coor.longitude, &(pCities+i)->coor.latitude);
        }
        fclose(fp); //close file when finished
        printf("Reading complete\n");
    }
    return pCities;
}*/
