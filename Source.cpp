#include <stdlib.h>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <time.h>

#pragma region Definition of the person struct to be used.
struct Person {
	char firstName[40];
	char lastName[40];
	int	year;
	struct Person *pNext;
};
#pragma endregion

#pragma region Prototypes for Functions used in this program.

int comparePeople(Person *left, Person *right);

char getRandUpperCaseChar();

Person *initializePersonNode(Person *pNext);

Person *createList(int size);

Person *swapWithNext(Person *node, Person *previousNode);

Person *bubbleSortLinkedList(Person *initialNode);

Person *insertationSortLinkedList(Person *initialNode);

Person *sortLinkedList(Person *initialNode, bool print);

void printList(Person *initialNode);

#pragma endregion

#pragma region Main Entry Point.
/* Main entry point for this application. */
void main() {
	printf("Do you want to print the linked list in this session? (Y, N)\n");
	char result = 0;
	while (result != 'Y' && result != 'N') {
		scanf("%c", &result);
	}
	while (true) {
		printf("\n\nPlease enter the size of the list:\n");
		int i = 0;
		scanf("%d", &i);
		/* Create a list and get the reference to its head. */
		Person *list = createList(i);
		/* Pass a reference of the list to the sort function and get the reference to the sorted list header. */
		list = sortLinkedList(list, result == 'Y' ? true : false);
	}
}
#pragma endregion

#pragma region Comparison of the person structs.
/*
Compares two person structs. If the return value is 0 the two structs are equal. If the
return value is greater than 0 the right struct is smaller than the left one. If the return
value is less than 0 the left struct is smaller than the right one.
*/
int comparePeople(Person *left, Person *right) {
	/* Compare the first name. */
	int comparisonResult = strcmp(left->firstName, right->firstName);
	if (comparisonResult != 0) {
		/* If the first names aren't equal, return the comparison result. */
		return comparisonResult;
	}
	else {
		/* If the first names are equal, return the comparison result of the last name instead of the first name. */
		return strcmp(left->lastName, right->lastName);
	}
}
#pragma endregion

#pragma region List initialization.
/* Get the length of the list. */
int getLength(Person *head) {
	int i = 0;
	while (head != NULL) {
		head = head->pNext;
		i++;
	}
	return i;
}

/* Gets a random upper case character. */
char getRandUpperCaseChar() {
	/* Return a random of the 26 chars after the value of 65 in ASCII. */
	return (char)(rand() % 26 + 65);
}

/* Initializes a new person struct with a specified next node. Returns the pointer to the element. */
Person *initializePersonNode(Person *pNext) {
	/* Allocate the person struct in memory. */
	Person *pElement = (Person*)malloc(sizeof(Person));
	/* Set the first name and end it with \0. */
	pElement->firstName[0] = getRandUpperCaseChar();
	pElement->firstName[1] = '\0';
	/* Set the last name and end it with \0. */
	pElement->lastName[0] = getRandUpperCaseChar();
	pElement->lastName[1] = '\0';
	/* Set a random year between 1917 and 2016. */
	pElement->year = rand() % 99 + 1917;
	/* Set the next node following the current created node. */
	pElement->pNext = pNext;
	/* Return the pointer to the created node. */
	return pElement;
}

/* Creates a list of a specified size. Links the list together and returns the head. */
Person *createList(int size) {
	/* Initialize the last node of the list. The last node of the list will be having no reference to a next node (pass NULL). */
	Person *currentNode = initializePersonNode(NULL);
	for (int counter = 0; counter < size - 1; counter++) {
		/* Create a new node until the given size is reached. Set the next node
		of the node to be created to the previously created node and assign the ret
		urned value to the current node for the next iteration to be used. */
		currentNode = initializePersonNode(currentNode);
	}
	/* Return the head of the list. */
	return currentNode;
}
#pragma endregion

#pragma region Bubble sort.
/*
Swaps the given node with the next following node. It requires the node previous to the first given node.
"previousNode" must be the node previous to "node". Swaps "node" with "node->pNext".
*/
Person *swapWithNext(Person *node, Person *previousNode) {
	/* Store the node to switch temporarely. */
	Person *tmp = node;
	/* Set the value of the given node to it's following node. */
	node = node->pNext;
	/* Set the following node of the initially given node to the next value of the overwritten node. */
	tmp->pNext = node->pNext;
	/* Assign the temporary node to the next node of the overwritten node. */
	node->pNext = tmp;
	if (previousNode != NULL) {
		/* If the given previous node is not null, set the following node. */
		previousNode->pNext = node;
	}
	return node;
}

/* Bubble sorts a linked list. Requires the head of the linked list to sort. Returns the sorted head of the list. */
Person *bubbleSortLinkedList(Person *initialNode) {
	bool exchanged = false;
	if (initialNode == NULL || initialNode->pNext == NULL) {
		/* If the given node is null or it has no following nodes return the node itself. */
		return initialNode;
	}
	/* Create a temporary node to be used to iterate the list. */
	Person *current = initialNode;
	do {
		exchanged = false;
		Person *previous = NULL;
		/* Loop through the linked list as long as the current node or its next value isn't NULL. */
		while (current != NULL && current->pNext != NULL) {
			if (comparePeople(current, current->pNext) > 0) {
				/* If the comparison succeeds, swap the current node with its next node. */
				current = swapWithNext(current, previous);
				/* Changes were made. Set flag to true. */
				exchanged = true;
				if (previous == NULL) {
					/* The head of the list changed. Overwrite the head of the list to keep changes. */
					initialNode = current;
				}
			}
			/* Set the previous node of the current to be used in the next iteration. */
			previous = current;
			/* Set the current node for the next iteration. */
			current = current->pNext;
		}
		/* Set the current value for the loop. */
		current = initialNode;
	} while (exchanged);
	return initialNode;
}
#pragma endregion

#pragma region Insertation sort. 
/* Insertation sorts a list. Requires the head of the linked list to sort. It returns the sorted head of the list. */
Person *insertationSortLinkedList(Person *initialNode) {
	if (initialNode == NULL || initialNode->pNext == NULL) {
		/* If the head of the list or its next value is NULL return the head of the list. */
		return initialNode;
	}
	Person *head = NULL;
	/* Loop through list. */
	while (initialNode != NULL) {
		/* Set current node and the next node for the next iteration.*/
		Person *current = initialNode;
		initialNode = initialNode->pNext;
		if (head == NULL || comparePeople(current, head) < 0) {
			/* If the comparison succeeds or the head is NULL set the next value of the current node and set the head. */
			current->pNext = head;
			head = current;
		} else {
			Person *p = head;
			/* If the head is null or the comparison does not succeed loop through the current state of the head of the list. */
			while (p != NULL) {
				if (p->pNext == NULL || comparePeople(current, p->pNext) < 0) {
					/* If the end of the list is reached or the comparison succeeds, relink the list.*/
					current->pNext = p->pNext;
					p->pNext = current;
					break;
				}
				/* Set the value for the next iteration. */
				p = p->pNext;
			}
		}
	}
	return head;
}
#pragma endregion

#pragma region Selection sort.
/* Perform a selection sort on the given head on the linked list and return its new sorted head. */
Person *selectionSortLinkedList(Person *head) {
	Person *a = head;
	Person *b = NULL;
	Person *c = head;
	Person *d = NULL;
	Person *tmp = NULL;
	/* Loop through list as long as the next value is not null. */
	while (a->pNext != NULL) {
		d = a->pNext;
		b = a->pNext;
		/* Loop through the current status of the list to select the minimum and set the references. */
		while (b != NULL) {
			if (comparePeople(a, b) > 0) {
				/* If the comparison succeeds, relink the nodes. */
				if (a->pNext == b) {
					if (a == head) {
						/* If a is equal to the head of the list, exchange the nodes and set
						the next value for b and change the head of the list for return value.
						The head needs to be overwritten because it means the head changed. */
						a->pNext = b->pNext;
						b->pNext = a;
						tmp = a;
						a = b;
						b = tmp;
						head = a;
						c = a;
						d = b;
						b = b->pNext;
					}
					else {
						/* Exchange the nodes and set the nodes for the next iteration. */
						a->pNext = b->pNext;
						b->pNext = a;
						c->pNext = b;
						tmp = a;
						a = b;
						b = tmp;
						d = b;
						b = b->pNext;
					}
				}
				else {
					if (a == head) {
						/* If the head of the list needs to be changed overwrite the head and relink the list. */
						tmp = b->pNext;
						b->pNext = a->pNext;
						a->pNext = tmp;
						d->pNext = a;
						tmp = a;
						a = b;
						b = tmp;
						d = b;
						b = b->pNext;
						head = a;
					}
					else {
						/* Else, only relink the list and set the variables to be used for the next iteration. */
						tmp = b->pNext;
						b->pNext = a->pNext;
						a->pNext = tmp;
						c->pNext = b;
						d->pNext = a;
						tmp = a;
						a = b;
						b = tmp;
						d = b;
						b = b->pNext;
					}
				}
			}
			else {
				/* If the comparison not succeeds, assign the values to be used for the next iteration. */
				d = b;
				b = b->pNext;
			}
		}
		c = a;
		a = a->pNext;
	}
	return head;
}
#pragma endregion

#pragma region Prompt the user, which algorithm to use.
/* Sorts the given linked list and prompts the user to select the sorting algorithm. Returns the sorted list. */
Person *sortLinkedList(Person *initialNode, bool print) {
	/* Prompt the user as long as the user types in a valid value ('I', 'B', 'S') and return the sorted list. */
	printf("Please select your preferred sorting algorithm:\nInsertation Sort (I)\nBubble Sort (B)\nSelection Sort(S)\n");
	char result = 0;
	while (result != 'B' && result != 'I' && result != 'S') {
		printf("(B, I, S)");
		scanf(" %c", &result);
	}
	Person *res = NULL;
	clock_t start = clock();
	if (result == 'I') {
		res = insertationSortLinkedList(initialNode);
	}
	else if (result == 'B') {
		res = bubbleSortLinkedList(initialNode);
	}
	else if (result == 'S') {
		res = selectionSortLinkedList(initialNode);
	}
	clock_t end = clock();
	/* Print out the list if the user wants to print it. */
	if (print) {
		printList(res);
	}
	printf("List with length %i and algorithm '%c' took %i milliseconds.\n", getLength(res), result, (end - start));
	return res;
}
#pragma endregion

#pragma region Print the list.
/* Prints out all persons in a list. */
void printList(Person *initialNode) {
	while (initialNode != NULL) {
		printf("FirstName:\t%s\n", initialNode->firstName);
		printf("LastName:\t%s\n", initialNode->lastName);
		printf("Year:\t%i\n", initialNode->year);
		initialNode = initialNode->pNext;
	}
}
#pragma endregion
