// Joel Manley
// Linked lists program in C

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct Inventory{
	int partNum;
	float price;
	int quantity;
	struct Inventory *next;
};

struct Inventory *createList(struct Inventory *first);
void printList(struct Inventory *first);
void selectItem(struct Inventory *first, int partNum);
void modifyItem(struct Inventory *first, int partNum);
void deleteItem(struct Inventory **first, int partNum);
void insertItem(struct Inventory **first, int partNum, float price, int quantity);
void saveList(struct Inventory *first, char fileName[15]);
void addFromFile(struct Inventory **first, char fileName[15]);


int main(){
	struct Inventory *first = NULL; // initialize structure as a pointer to hold address from malloc()
	struct Inventory *itemToAdd = NULL; // initialize structure to add new items
	char loopVar = 'Y';
	int command, partNum, cantAdd;
	char fileName[15];
	
	
	
	// begin loop to allow user to enter commands until they're done
	do {
		// print list of commands, prompt for selection, validate input
		printf("\t1. Create\n\t2. Print\n\t3. Select\n\t4. Modify\n\t5. Delete\n\t6. Insert\n\t7. Save\n\t8. Add\n\t9. Exit\n\t10. Help\n");
		
		printf("\nPlease Enter a command (1-10): ");
		scanf(" %d", &command);
		fflush(stdin);	
		while (command < 1 || command > 10){
			printf("\nThat is an invalid selection. Please try again.\n");
			printf("\nPlease Enter a command (1-10): ");
			scanf(" %d", &command);
			fflush(stdin);
		}	
		
		// determine which command was entered
		switch(command){
			case 1:
				first = createList(first);
				// create
				break;
				
			case 2:
				printList(first);
				break;
				
			case 3:
				printf("\nEnter the part number you would like to see: ");
				scanf(" %d", &partNum);
				fflush(stdin);
				while (partNum <= 0){
					printf("\nThat is an invalid entry. Please try again.\n");
					printf("\nEnter the part number you would like to see: ");
					scanf(" %d", &partNum);
					fflush(stdin);
				}
				
				selectItem(first, partNum);
				// select
				break;
				
			case 4:
				printf("\nEnter the part number you would like to modify: ");
				scanf(" %d", &partNum);
				fflush(stdin);
				while(partNum <= 0){
					printf("\nThat is an invalid entry. Please try again.\n");
					printf("\nEnter the part number you would like to modify: ");
					scanf(" %d", &partNum);
					fflush(stdin);
				}
				
				modifyItem(first, partNum);
				break;
				
			case 5:
				printf("\nEnter the part number you would like to delete: ");
				scanf(" %d", &partNum);
				fflush(stdin);
				while(partNum <= 0){
					printf("\nThat is an invalid entry. Please try again.\n");
					printf("\nEnter the part number you would like to modify: ");
					scanf(" %d", &partNum);
					fflush(stdin);
				}
				
				// get rid of first if all list is gone
				deleteItem(&first, partNum);
				break;
				
			case 6:
				printf("\nEnter a number for the part you would like to add: ");
				scanf(" %d", &partNum);
				fflush(stdin);
				while (partNum < 1){
					printf("\nThat is an invalid entry. Please try again.\n");
					printf("\nEnter a number for the part you would like to add: ");
					scanf(" %d", &partNum);
					fflush(stdin);
				}
				// set pointer to first item to iterate through list
				itemToAdd = first;
				
				// check if part number exists
				cantAdd = 0;
				while (itemToAdd != NULL){
					if (partNum == itemToAdd->partNum){
						printf("\nCannot add part. Part number already in use.\n");
						cantAdd = 1;						
					}
					itemToAdd = itemToAdd->next;
				}
				
				// break out of case if part number exists
				if (cantAdd == 1){
					break;
				}
				
				// allocate space for new data if part number not in use
				itemToAdd = (struct Inventory *)malloc(sizeof(struct Inventory)); // allocate space for new data
				
				// fill data
				itemToAdd->partNum = partNum;
				
				printf("\nEnter a price for part #%d: ", itemToAdd->partNum);
				scanf(" %f", &itemToAdd->price);
				fflush(stdin);
				while (itemToAdd->price <= 0){
					printf("\nThat is an invalid entry. Please try again.\n");
					printf("\nEnter a price for part #%d: ", itemToAdd->partNum);
					scanf(" %f", &itemToAdd->price);
					fflush(stdin);
				}
				
				printf("\nEnter a quantity for part #%d: ", itemToAdd->partNum);
				scanf(" %d", &itemToAdd->quantity);
				fflush(stdin);
				while (itemToAdd->quantity <= 0){
					printf("That is an invalid entry. Please try again.\n");
					printf("\nEnter a quantity for part #%d: ", itemToAdd->partNum);
					scanf(" %d", &itemToAdd->quantity);
					fflush(stdin);
				}
				itemToAdd->next = NULL;
				// I know whatever causes the crash happens here.
				insertItem(&first, itemToAdd->partNum, itemToAdd->price, itemToAdd->quantity);
				free(itemToAdd);
				
				//printf("\nNew item: %p", itemToAdd);
				break;
				
			case 7:
				printf("\nEnter the a name for the file: ");
				fflush(stdin);
				fgets(fileName, 15, stdin);
				fileName[strlen(fileName) - 1] = '\0';
				
				saveList(first, fileName);
				break;
				
			case 8:
				printf("\nEnter the file name to add from: ");
				fflush(stdin);
				fgets(fileName, 15, stdin);
				fileName[strlen(fileName) - 1] = '\0';
				
				addFromFile(&first, fileName);
				
				break;
				
			case 9:
				return 0;
				
			case 10:
				printf("\n\tCreate:\tCreate a new linked list\n");
				printf("\n\tPrint:\tDisplay a linked list\n");
				printf("\n\tSelect:\tDisplay a single item from a linked list\n");
				printf("\n\tModify:\tChange a single item in a linked list\n");
				printf("\n\tDelete:\tRemove a single item from a linked list\n");
				printf("\n\tInsert:\tAdd a new item to a specific location in a linked list\n");
				printf("\n\tSave:\tSave a linked list to a file\n");
				printf("\n\tAdd:\tAdd an item to an existing linked list from a file\n");
				printf("\n\tExit:\tExit the program\n");
				printf("\n\tHelp:\tDisplay a list of available commands\n");
				break;
		}
		
		printf("\nWould you like to enter another command? (Y/N): ");
		scanf(" %c", &loopVar);
		fflush(stdin);
		loopVar = toupper(loopVar);
		while (loopVar != 'Y' && loopVar != 'N'){
			printf("\nThat is an invalid entry. Please try again.\n");
			printf("\nWould you like do enter another command? (Y/N): ");
			scanf(" %c", &loopVar);
			fflush(stdin);
			loopVar = toupper(loopVar);
		}
	} while (loopVar != 'N');
		
	
	return 0;
}


struct Inventory *createList(struct Inventory *first){
	struct Inventory *previous = NULL;
	struct Inventory *current;
	struct Inventory *next;
	char loopVar;
	// allocate memory for current
	current = (struct Inventory *)malloc(sizeof(struct Inventory));
	
	do {
		// fill current with data
		printf("\nEnter a part number: ");
		scanf(" %d", &current->partNum);
		fflush(stdin);
		printf("\nEnter a price for part #%d: ", current->partNum);
		scanf(" %f", &current->price);
		fflush(stdin);
		printf("\nEnter a quantity for part: ");
		scanf(" %d", &current->quantity);
		fflush(stdin);
		current->next = NULL;
		
		// save next node location in for st
		if (previous == NULL){
			first = current;
		}
		
		// prompt to add another part
		printf("\nWould you like to add another part? (Y/N): ");
		fflush(stdin);
		scanf(" %c", &loopVar);
		loopVar = toupper(loopVar);
		fflush(stdin);
		while (loopVar != 'Y' && loopVar != 'N'){
			printf("\nThat is an invalid selection. Please try again.\n");
			printf("\nWould you like to add another part? (Y/N): ");
			scanf(" %c", &loopVar);
			loopVar = toupper(loopVar);
			fflush(stdin);
		}
		// if yes, allocate for next, save address of next as reference for current
		if (loopVar == 'Y'){
			next = (struct Inventory *)malloc(sizeof(struct Inventory));
			
			current->next = next;
			
			// rename next to current, and current to previous
			previous = current;
			current = next;
		}
	} while (loopVar == 'Y');
	// return address of first item
	return first;
}


void printList(struct Inventory *first){
	while (first != NULL){ // while it exists in memory
		// print it
		printf("\nPart Number: %d", first->partNum);
		printf("\nItem Price: %.2f", first->price);
		printf("\nItem Quantity: %d\n", first->quantity);
		
		//test
		printf("\nAddress in memory: %p", first);
		printf("\nNext address: %p\n\n", first->next);
		
		// move to next item
		first = first->next;
	}
}


void selectItem(struct Inventory *first, int partNum){
	// while it exists in memory
	while (first != NULL){
		// if the part numbers match
		if (first->partNum == partNum){
			// print it
			printf("\nPart Number: %d", first->partNum);
			printf("\nPart Price: %.2f", first->price);
			printf("\nPart Quantity: %d", first->quantity);
			return;
		}
		// move to next item
		first = first->next;
	}
	// if none of the part numbers match print error message
	printf("\nUnable to select part\n");
}


void modifyItem(struct Inventory *first, int partNum){
	int modifySelection;
	// while it exists in memory
	while (first != NULL){
		// if the part numbers match
		if (first->partNum == partNum){
			// prompt for what to modify and validate
			printf("\nWould you like to change the price(1) the quantity(2) or both(3): ");
			scanf(" %d", &modifySelection);
			fflush(stdin);
			while (modifySelection < 1 || modifySelection > 3){
				printf("\nThat is an invalid entry. Please try again.\n");
				printf("\nWould you like to change the price(1) the quantity(2) or both(3): ");
				scanf(" %d", &modifySelection);
				fflush(stdin);
			}
			// prompt for new data and replace
			switch(modifySelection){
				case 1:
					printf("\nEnter new price: ");
					scanf(" %f", &first->price);
					fflush(stdin);
					break;
				case 2:
					printf("\nEnter new quantity: ");
					scanf(" %d", &first->quantity);
					fflush(stdin);
					break;
				case 3:
					printf("\nEnter new price: ");
					scanf(" %f", &first->price);
					fflush(stdin);
					printf("\nEnter new quantity: ");
					scanf(" %d", &first->quantity);
					fflush(stdin);
					break;
				default:
					printf("\nInvalid Entry\n");
			}
		}
		// move to next item
		first = first->next;
	}
}


void deleteItem(struct Inventory **first, int partNum){ // send a pointer to the pointer of first to account for deletion of first item
	struct Inventory *previous; 
	struct Inventory *current = *first;  // set *current equal to first
	
	// check to see if first node is the one being deleted
	if (current != NULL && current->partNum == partNum){
		*first = current->next; // change address of first item, to make second item the new first
		free(current); // free space for deleted structure
		return; // if this happens, go back to main
	}
	// while first item not being deleted, iterate through list to find matching part number
	while (current != NULL){
		if (current->partNum != partNum){ // if part numbers dont match move to next item
			previous = current; // keep track of previous item
			current = current->next; // move to next item
		}
		else{
			break; // break loop when part numbers match
		}
	}
	
	if (current == NULL){ // at end of list, part not found
		printf("\nThe part number was not found\n");
		return;
	}
	
	//if the part was found, remove it from list and free space
	previous->next = current->next;
	free(current);
}


void insertItem(struct Inventory **first, int partNum, float price, int quantity){
    struct Inventory *newItem = (struct Inventory *)malloc(sizeof(struct Inventory));
    struct Inventory *current = *first;
    struct Inventory *previous = NULL;

    // fill new item with data
    newItem->partNum = partNum;
    newItem->price = price;
    newItem->quantity = quantity;
    newItem->next = NULL;

    // If the list is empty or the new item should be the first
    if (current == NULL || partNum < current->partNum){
        newItem->next = current; // if no list, current = NULL, if there is a list the first item becomes reference for new
        *first = newItem; // new becomes first item
        return;
    }
	// If not changing the first item, find the correct position to insert the new item
    while (current != NULL && partNum > current->partNum){
        previous = current;
        current = current->next;
    }

    // Insert the new item in current position
    previous->next = newItem;
    newItem->next = current;
}


void saveList(struct Inventory *first, char fileName[15]){
	int saveFormat;
	printf("\nWould you like to save it as (1)CSV, or in (2)display format?");
	scanf(" %d", &saveFormat);
	fflush(stdin);
	while (saveFormat != 1 && saveFormat != 2){
		printf("\nThat is an invalid entry. Please try again.\n");
		printf("\nWould you like to save it as (1)CSV, or in (2)display format?");
		scanf(" %d", &saveFormat);
		fflush(stdin);
	}
	
	// create file pointer
	FILE *fpOut;
	
	switch(saveFormat){
		case 1:
			// add necessary extension
			if (strstr(fileName, ".csv") == NULL){
				strcat(fileName, ".csv");
			}
			
			// attempt to open file
			fpOut = fopen(fileName, "w");
	
			// check for open failure
			if (fpOut == NULL){
				printf("\nUnable to write to file\n");
				exit(0);
			}
	
			// iterate through list, and print to file
			while (first != NULL){
				fprintf(fpOut, "%d,%.2f,%d\n", first->partNum, first->price, first->quantity);
				first = first->next;
			}
			break;
			
		case 2:
			// add necessary extension
			if (strstr(fileName, ".txt") == NULL){
				strcat(fileName, ".txt");
			}
			// attempt to open file
			fpOut = fopen(fileName, "w");
	
			// check for open failure
			if (fpOut == NULL){
				printf("\nUnable to write to file\n");
				exit(0);
			}
	
			// print header to file
			fprintf(fpOut, "Part Number\tPrice\t\tQuantity\n");
			
			// iterate through list, print to file
			while (first != NULL){
				fprintf(fpOut, "%d\t\t%.2f\t\t%d\n", first->partNum, first->price, first->quantity);
				first = first->next;
			}
			break;
	}
	
	// close file
	fclose(fpOut);
}


void addFromFile(struct Inventory **first, char fileName[15]){
	struct Inventory *newItem;
	int x;
	FILE *fpIn;
	
	// check filename has correct extension
	if (strstr(fileName, ".csv") == NULL){
		strcat(fileName, ".csv");
	}
	
	fpIn = fopen(fileName, "r");
	
	if (fpIn == NULL){
		printf("\nUnable to read from file\n");
		exit(0); // return?
	}
	
	// allocate memory for new item
	newItem = (struct Inventory *)malloc(sizeof(struct Inventory));
	
	// fill new item with data from file
	newItem->next = NULL;
	x = fscanf(fpIn, "%d,%f,%d", &newItem->partNum, &newItem->price, &newItem->quantity);
	
	while (x != EOF){
		insertItem(first, newItem->partNum, newItem->price, newItem->quantity); // insert data into list
		x = fscanf(fpIn, "%d,%f,%d", &newItem->partNum, &newItem->price, &newItem->quantity); // move to next line
	}
	
	// close file
	fclose(fpIn);
	
	// deallocate temp memory
	free(newItem);
}




