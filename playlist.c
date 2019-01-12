/*
 * GWU - CSCI 2113 - Spring 2018
 * Lab 4 - Julia Bristow
 *
 * Exercise 3.1
 * 1. I defined the strings with a pointer because decalring a large char array to hold the string would probably end up allocating more memory than is needed.
 * 2. The consequences of defining artist and title as character pointers is that since they are pointers, they have to be treated differently and you have to keep track of what is pointing where and know when to dereference, etc.
 * 3. The biggest consequence of using a char array is that since you don't know how long each of the strings will be, you have to make the array a fixed, large size, which is likely to allocate too much memory and is why I didn't do it that way.
 *
 * Exercise 3.2
 * 1. The track parameter is a pointer, which means it has to be passed by reference in order to actually access the correct thing. If you tried to pass it by value, you would basically be making a carbon copy with those title and artist values instead of changing what the pointer is pointing to. 
 * 2. In the print function, track is not a pointer, so it needs to be passed by value because you aren't trying to access a memory location. 
 *
 * Exercise 3.3
 * 1. node1, node2, and node3 are all pointers of type node_t
 * 2. When dealloc is called on node1, the space in memory that p1 and p2 point to would be freed, so if you try to dereference p1 it will be pointing to nothing which would cause problems. If you called dealloc on p2, it would try to free space that has already been freed and you could get an error. 
 *
 * Exercise 3.4
 * 1. 2 loops are used because they have to be done individually, otherwise you might accidentally use memory that has already been freed, so you need to print everything first and then free everything. Loop 1 prints out all of the nodes (the title and artist for each track), and Loop 2 calls dealloc for each node.
 * 2. A linked list is used because it makes it easier to shift, add, and remove elements (all you have to do is change the pointers rather than try to change the size or oder of an array)
 *
 * Exercise 3.5
 * 1. To remove the first node from the list, you have to modify the head pointer so that it points to the second node instead, meaning the list will start there. 
 * 2. When putting the node back into the list at the end, you have to change tail to be now pointing at node1, and change the node3 next pointer to be pointing at node1 instead of null, and then make the node1 next pointer null instead of pointing to node2
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Struct to give each track a title and artist
struct track_t {
	char* title;
	char* artist;
};

// Assigns data to each track 
void update (struct track_t* track, char* title, char* artist) {
	//arrow is used becuase track is passed by reference
	track->title = title;
	track->artist = artist;
}

void print (struct track_t track) {
	printf("%s by %s \n", track.title, track.artist);
};

// Creates a node for each track and assigns a next pointer
struct node_t {
	struct track_t track;
	struct node_t* next;
};

// Allocate space for a node
struct node_t* allocate (void) {
	struct node_t* node = (struct node_t*)malloc(sizeof(struct node_t));
	node->next = NULL;
};

void dealloc (struct node_t* node) {
	free(node);
}

// Prints all of the nodes in the list
void print_list (struct node_t* curr_node) {
	while (curr_node != NULL) {
		print(curr_node->track);
		curr_node = curr_node->next;
	}
}

// Deallocate the entire list
void dealloc_list (struct node_t* curr_node) {
	while (curr_node != NULL) {
		dealloc(curr_node);
		curr_node = curr_node->next;
	}
}

int main (void)
{
	// Make 3 nodes and allocate memory for them
	struct node_t* node1;
	struct node_t* node2;
	struct node_t* node3;
	node1 = allocate();
	node2 = allocate();
	node3 = allocate();

	// Fill each node with a track
	update(&(node1->track), "Feel It Still", "Portugal, The Man");
	update(&(node2->track), "&Run", "Sir Sly");
	update(&(node3->track), "Money", "Pink Floyd");

	// Declare and assign head and tail pointers
	struct node_t *head;
	struct node_t *tail; 
	head = node1;
	tail = node3;
	head->next = node2;
	node2->next = tail;

	// Remove node1 from the list
	head = node2;

	// Insert node1 at the end of the list
	tail = node1;
	node3->next = node1;
	node1->next = NULL;

	// Print every node
	print_list(head);

	// Deallocate every node
	dealloc_list(head);

	return 0;
}
