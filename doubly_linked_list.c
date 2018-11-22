/* Julia Bristow
 * CS 2113 - Software Engineering
 * Doubly Linked List in C
 */

#include <stdlib.h>
#include <stdio.h>


struct node_t {
	int data;
	struct node_t* next;
	struct node_t* prev;
};

// Global Variables
struct node_t* head;
struct node_t* tail;
int size;

struct node_t* initializeList()
{
	// create a header node that is initially empty
	struct node_t* node = (struct node_t*)malloc(sizeof(struct node_t));
	node->next = NULL;
	node->prev = NULL;
	node->data = 0;
	
	head = node;
	tail = node;
	size = 1;

	// return the node
	return node;
};


// Free all the memory that was allocated
void clearList()
{
	struct node_t* curr_node;
	curr_node = head->next;
	while (curr_node->next != NULL) { // this will stop when it gets to the tail node
		free(curr_node->prev);
		curr_node = curr_node->next;
	}

	// free tail
	free(curr_node);
}


// add new item at the end of the current list and place int data in that item
void insertAtEnd (int newData)
{
	// create a new node and fill it with the new data
	struct node_t* newNode = (struct node_t*)malloc(sizeof(struct node_t));
	newNode->data = newData;

	// change the pointers of the nodes so that the new node is the last one
	newNode->next = NULL;
	newNode->prev = tail;
	tail->next = newNode;
	tail = newNode;

	// increase size of list
	size++;
}


// Find the index of the node carrying a specific data point
// Move that node forward the number indicated by moveDistance
int findPositionAndMove (int newData, int moveDistance)
{
	// moveDistance controls how far forward in you will move the item once found
	// if the data point is at index 10 and moveDistance is 4, the data point should be 6
	
	int nodeNum, i;
	nodeNum = 1; 
	
	// Find the position of the data
	struct node_t* curr_node;
	curr_node = head;
	while (curr_node != NULL) {
		// If curr_node has the data we're looking for nodeNum stays the same 
		// if it doesn't, move curr_node forward and nodeNum increases
		if(curr_node->data != newData) {
			curr_node = curr_node->next;
			nodeNum++;
		}
		else {
			break;
		}
	}

	int tailTrack = 0;

	// Move the node holding newData
	if (moveDistance < size-1) {
		// move back one space until the correct number of moves is reached
		for (i=0; i<moveDistance; i++) {
			// if the data is found at the tail
			if (nodeNum == size) {
				// change pointers
				if (tailTrack == 0) {
					// the node before it should now have next pointing to null
					curr_node->prev->next = NULL;
					// change the tail pointer
					tail = curr_node->prev;
					// increase tailTrack so this doesn't run again
					tailTrack++;
				}
				else {
					// don't change the tail
					// make the nodes before and after curr_node point to each other
					curr_node->prev->next = curr_node->next;
					curr_node->next->prev = curr_node->prev;
				}
				// make the prev and next pointers of curr_node replace those of the one before it
				curr_node->prev = curr_node->prev->prev;
				curr_node->next = curr_node->prev->next;
				// make the nodes before and after the new spot for curr_node point to node
				curr_node->prev->next = curr_node;
				curr_node->next->prev = curr_node;
			}
		
	
			// if the data is found at the beginning (head)
			else if (nodeNum == 1) {
				// already at the front; can't move forward
				break;
			}
			// if the data is somewhere in the middle
			else {
				// don't need to worry about head or tail pointers
				// make the nodes before and after node point to each other 
				curr_node->prev->next = curr_node->next;
				curr_node->next->prev = curr_node->prev;
				// make the prev and next pointers of curr_node replace those of the one before it
				curr_node->prev = curr_node->prev->prev;
				curr_node->next = curr_node->prev->next;
				// make the nodes before and after the new spot for curr_node point to node
				curr_node->prev->next = curr_node;
				curr_node->next->prev = curr_node;
			}
		}
	}
	// if moveDistance is >= than the size of the list
	// move the node to the beginning of the list
	else {
		// if the data is found at the tail
		if (nodeNum == size) {
			// change pointers
			// make the 2nd to last node the new tail
			curr_node->prev->next = NULL;
			tail = curr_node->prev;
			// put curr_node before the head
			curr_node->next = head;
			head->prev = curr_node;
			// make curr_node the new head
			curr_node->prev = NULL;
			head = curr_node;
		}
		else {
			// change pointers
			// make the nodes before and after curr_node point to each other
			curr_node->next->prev = curr_node->prev;
			curr_node->prev->next = curr_node->next;
			// put curr_node before head
			curr_node->next = head;
			head->prev = curr_node;
			// make curr_node the new head
			head = curr_node;
			curr_node->prev = NULL;
		}
	}

	
	// Return the index of newData or -1
	if (nodeNum > size) {
		return -1;
	}
	else {
		return nodeNum;
	}
}

void printList()
{
	struct node_t* curr_node;
	curr_node = head;
	int i = 1;
	while (curr_node != NULL) {
		printf("node %d = %d\n", i, curr_node->data);
		curr_node = curr_node->next;
		i++;
	}
	printf("\n");
}

int main ()
{
	// create list with one null node
	struct node_t* node1;
	node1 = initializeList();
	// fill the node with data
	node1->data = 5;

	// make 4 new nodes and print
	insertAtEnd(3);
	insertAtEnd(9);
	insertAtEnd(4);
	insertAtEnd(12);
	printf("Original List:\n");
	printList();

	// move the tail to the middle of the list
	findPositionAndMove(12,2);
	printf("Move data point 12 up 2 spaces:\n");
	printList();

	// move the tail to the front of the list
	findPositionAndMove(4,5);
	printf("Move data point 4 up 5 spaces:\n");
	printList();

	// move a node in the middle to the front
	findPositionAndMove(3,4);
	printf("Move data point 3 up 4 spaces:\n");
	printList();

	// move a node in the middle to somewhere else in the middle
	findPositionAndMove(9,2);
	printf("Move data point 9 up 2 spaces:\n");
	printList();

	// free memory
	clearList();

	return 0;
}
