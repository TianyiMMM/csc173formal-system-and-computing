/*
 * File: Stack
.c
 * Creator: George Ferguson
 * Created: Thu Jun 30 14:47:12 2016
 * Time-stamp: <Fri Aug  4 10:29:48 EDT 2017 ferguson>
 */

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

/**
 * Structure for each element of a doubly-linked Stack
.
 */
typedef struct Node* Node;
struct Node {
	void *data;
	Node next;
	Node prev;
};

/**
 * Linked list with first and last (head and tail) pointers.
 */
struct Stack {
	Node first;
	Node last;
};

/**
 * Allocate, initialize and return a new (empty) Stack
.
 */
Stack new_Stack() {
	Stack this = (Stack)malloc(sizeof(struct Stack));
	this->first = this->last = NULL;
	return this;
}

static Node new_Node(void *data) {
	Node this = (Node)malloc(sizeof(struct Node));
	this->data = data;
	this->next = this->prev = NULL;
	return this;
}

/**
 * Free the memory used for the given Stack
.
 * If boolean free_data_also is true, also free the data associated with
 * each element.
 */
void Stack_free(Stack this, bool free_data_also) {
	if (this == NULL) {
		return;
	}
	// Free the elements
	Node node = this->first;
	while (node != NULL) {
		Node next = node->next;
		if (free_data_also && node->data != NULL) {
			free(node->data);
		}
		free(node);
		node = next;
	}
	// Free the list itself
	free(this);
}

/**
 * Return true if the given Stack
 is empty.
 */
bool Stack_isEmpty(const Stack this) {
	return this->first == NULL;
}

/**
 * Add the given void* value at the front of the given Stack
.
 */
void Stack_prepend(Stack this, void *data) {
	Node node = new_Node(data);
	node->next = this->first;
	if (this->first != NULL) {
		this->first->prev = node;
	}
	this->first = node;
	if (this->last == NULL) {
		this->last = node;
	}
}

/**
 * Add the given void* value at the end of the given Stack
.
 */
void Stack_push(Stack this, void *data) {
	//printf("stackpush\n");
	Node node = new_Node(data);
	node->prev = this->last;
	if (this->last != NULL) {
		this->last->next = node;
	}
	this->last = node;
	if (this->first == NULL) {
		this->first = node;
	}
}

/**
 * Return true if then given Stack
 contains given void* value.
 * Note this doesn't any kind of equals function, just plain ``==''.
 */
bool Stack_contains(const Stack this, void *data) {
	for (Node node=this->first; node != NULL; node=node->next) {
		if (node->data == data) {
			return true;
		}
	}
	return false;
}

/**
 * Remove the given void* value from the given Stack
 if it is there.
 * This function uses ``=='' to test for the element.
 * Note that this does not free the data associated with the element.
 */
void Stack_remove(Stack this, void *data) {
	for (Node node=this->first; node != NULL; node=node->next) {
		if (node->data == data) {
			if (node == this->first) {
				this->first = node->next;
			}
			if (node == this->last) {
				this->last = node->prev;
			}
			if (node->prev != NULL) {
				node->prev->next = node->next;
			}
			if (node->next != NULL) {
				node->next->prev = node->prev;
			}
			free(node);
			return;
		}
	}
}    

/**
 * Return the void* value at the given index in the given Stack
, or
 * NULL if there is no such.
 * Note that this means you can't store NULL in a Stack
. C'est la vie.
 */
void* Stack_elementAt(Stack this, int index) {
	int i = 0;
	for (Node node=this->first; node != NULL; node=node->next) {
		if (i == index) {
			return node->data;
		}
		i += 1;
	}
	return NULL;
}

/**
 * Remove and return the first element from the given Stack
.
 * Returns NULL if the list is empty.
 */
void* Stack_pop(Stack this) {
	void *data = Stack_elementAt(this, 0);
	if (data != NULL) {
		Stack_remove(this, data); // Removes first occurrence
	}
	return data;
}

/**
 * Call the given function on each element of given Stack
, passing the
 * void* value to the function.
 */
void Stack_iterate(const Stack this, void (*func)(void *)) {
	for (Node node=this->first; node != NULL; node=node->next) {
		func(node->data);
	}
}

/**
 * A Stack
Iterator is simply a pointer to a node. It is initialized
 * to this->first and increments following next pointers until NULL.
 */
struct StackIterator {
	Node next;
};

/**
 * Return an Stack
Iterator for the given Stack
.
 * Don't forget to free() this when you're done iterating.
 */
StackIterator Stack_iterator(const Stack this) {
	StackIterator iterator = (StackIterator)malloc(sizeof(struct StackIterator));
	iterator->next = this->first;
	return iterator;
}

/**
 * Return true if the given Stack
Iterator will return another element
 * if Stack
Iterator_next() is called.
 */
bool StackIterator_hasNext(const StackIterator this) {
	return this->next != NULL;
}

/**
 * Return the next value from the given Stack
Iterator and increment it
 * to point to the next element.
 * Will return NULL if there is no such element.
 * This means that you can't store NULL in a Stack
. C'est la vie.
 * It would be easy to allow it and signal `no such element' some other way...
 */
void* StackIterator_next(StackIterator this) {
	if (this->next == NULL) {
		return NULL;
	} else {
		void *data = this->next->data;
		this->next = this->next->next;
		return data;
	}
}

#ifdef MAIN

/**
 * Print the given Stack
 to stdout, assuming that the values are
 * all null-terminated strings.
 * Also prints a newline (because why not).
 */
void Stack_print_string_list(Stack this) {
	printf("[");
	for (Node node=this->first; node != NULL; node=node->next) {
		printf("%s", (char*)(node->data));
		if (node->next != NULL) {
			printf(" ");
		}
	}
	printf("]\n");
}

int main(int argc, char **argv) {
	Stack
 list = new_Stack
	();
	printf("new list =");
	Stack
_print_string_list(list);

	printf("adding three elements: ");
	Stack
_add_at_end(list, "foo");
	Stack
_add_at_end(list, "bar");
	Stack
_add_at_end(list, "baz");
	Stack
_print_string_list(list);
	printf("adding Ted at front: ");
	Stack
_add_at_front(list, "Ted");
	Stack
_print_string_list(list);

	printf("iterating over list:\n");
	Stack
Iterator iterator = Stack
_iterator(list);
	while (Stack
	Iterator_hasNext(iterator)) {
		void *data = Stack
Iterator_next(iterator);
		char *str = (char*)data;
		printf("%s\n", str);
	}
	free(iterator);

	// Test remove in middle
	printf("removing bar from middle: ");
	Stack
_remove(list, "bar");
	Stack
_print_string_list(list);
	// Test remove at head
	printf("removing Ted from start: ");
	Stack
_remove(list, "Ted");
	Stack
_print_string_list(list);
	// Test remove in end
	printf("removing baz from end: ");
	Stack
_remove(list, "baz");
	Stack
_print_string_list(list);

	// Test remove only element
	void *elt = Stack
_elementAt(list, 0);
	printf("element 0 is \"%s\"\n", (char*)elt);
	printf("removing only remaining element: ");
	Stack
_remove(list, elt);
	Stack
_print_string_list(list);

	printf("list isEmpty: %d\n", Stack
	_isEmpty(list));

	printf("freeing list\n");
	Stack
_free(list, false);
}

#endif
