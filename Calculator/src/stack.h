/*
 * File: Stack.h
 * Creator: George Ferguson
 * Created: Thu Jun 30 14:43:29 2016
 * Time-stamp: <Mon Sep  5 14:13:59 EDT 2016 ferguson>
 *
 * Singly-linked list with end pointers.
 */

#ifndef _Stack_h_gf
#define _Stack_h_gf

#include <stdbool.h>

// Partial declaration
typedef struct Stack* Stack;

/**
 * Allocate, initialize and return a new (empty) Stack.
 */
extern Stack new_Stack();

/**
 * Free the memory used for the given Stack.
 * If boolean free_data_also is true, also free the data associated with
 * each element.
 */
extern void Stack_free(Stack list, bool free_data_also);

/**
 * Return true if the given Stack is empty.
 */
extern bool Stack_isEmpty(const Stack this);

/**
 * Add the given element (void*) at the front of the given Stack.
 */
extern void Stack_prepend(Stack this, void *value);

/**
 * Add the given element (void*) at the end of the given Stack.
 */
extern void Stack_push(Stack this, void *value);

/**
 * Return true if then given Stack contains given void* value.
 * Note this doesn't any kind of equals function, just plain ``==''.
 */
extern bool Stack_contains(const Stack this, void *value);

/**
 * Remove the given void* value from the given Stack if it is there.
 * This function uses ``=='' to test for the element.
 * Note that this does not free the data associated with the element.
 */
extern void Stack_remove(Stack this, void *data);

/**
 * Return the void* value at the given index in the given Stack, or
 * NULL if there is no such.
 * Note that this means you can't store NULL in a Stack. C'est la vie.
 */
extern void *Stack_elementAt(Stack this, int index);

/**
 * Remove and return the first element from the given Stack.
 * Returns NULL if the list is empty.
 */
extern void *Stack_pop(Stack this);

/**
 * Call the given function on each element of given Stack, passing the
 * void* value to the function.
 */
extern void Stack_iterate(const Stack this, void (*func)(void*));

// Partial declaration
typedef struct StackIterator *StackIterator;

/**
 * Return an StackIterator for the given Stack.
 * Don't forget to free() this when you're done iterating.
 */
extern StackIterator Stack_iterator(const Stack this);

/**
 * Return true if the given StackIterator will return another element
 * if StackIterator_next() is called.
 */
extern bool StackIterator_hasNext(const StackIterator iterator);

/**
 * Return the next value from the given StackIterator and increment it
 * to point to the next element.
 * Will return NULL if there is no such element.
 * This means that you can't store NULL in a Stack. C'est la vie (again).
 */
extern void *StackIterator_next(StackIterator iterator);


/**
 * Print the given Stack to stdout, assuming that the values are
 * all null-terminated strings.
 */
extern void Stack_print_string_list(Stack this);


#endif
