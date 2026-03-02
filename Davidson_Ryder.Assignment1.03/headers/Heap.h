#include "ArrayList.h"

#ifndef HEAP_H
#define HEAP_H

typedef int (*Comparator)(const void *p1, const void *p2);

typedef struct  
{
    ArrayList *heap;
    Comparator compare;
} Heap;

/**
 * Initializes a Heap backed by an ArrayList with elements of size @p oSize.
 * The comparator @p compare defines the heap order (min-heap if compare(a,b) > 0
 * means a > b).
 *
 * @param h pointer to the Heap to initialize
 * @param compare comparison function used to order elements in the heap
 * @param oSize size of each element in bytes
 * @return 0 on success; -1 on failure
 *
 * @note This function assumes @p compare is a valid function pointer and @p oSize > 0.
 *       Passing invalid values may cause damage.
 */
int initHeap(Heap *h, int (*compare)(const void *p1, const void *p2), size_t oSize);

/**
 * Inserts an element into the heap and restores heap order.
 * Grows the underlying storage if needed. Increases size by 1.
 *
 * @param h pointer to the Heap
 * @param item pointer to a buffer with at least the heap's element size (oSize) bytes
 * @return 0 on success; -1 on failure
 *
 * @note This function does not validate that @p item is non-NULL; passing NULL
 *       may cause damage. Make sure @p item is valid.
 */
int heapAdd(Heap *h, void *item);

/**
 * Removes the root element (top of the heap) and copies it into @p item.
 * Restores heap order after removal. Decreases size by 1.
 *
 * @param h pointer to the Heap
 * @param item pointer to a buffer with at least the heap's element size (oSize) bytes
 * @return 0 on success; -1 on failure
 *
 * @note This function does not validate that @p item is non-NULL; passing NULL
 *       may cause damage. Make sure @p item is valid.
 */
int heapPop(Heap *h, void *item);

/**
 * Removes the element at index @p i and copies it into @p removed.
 * Restores heap order after removal. Decreases size by 1.
 *
 * @param h pointer to the Heap
 * @param removed pointer to a buffer with at least the heap's element size (oSize) bytes
 * @param i zero-based index of the element to delete
 * @return 0 on success; -1 on failure
 *
 * @note Ensure @p i is within the current bounds of the heap.
 *       This function does not validate that @p removed is non-NULL; passing NULL may cause damage.
 */
int heapDelete(Heap *h, void *removed, int i);

/**
 * Copies the root element (top of the heap) into @p min without removing it.
 *
 * @param h pointer to the Heap
 * @param min pointer to a buffer with at least the heap's element size (oSize) bytes
 * @return 0 on success; -1 on failure
 *
 * @note This function does not validate that @p min is non-NULL; passing NULL
 *       may cause damage. Make sure @p min is valid.
 */
int heapPeek(Heap *h, void *min);

/**
 * Builds a heap in-place from the elements in @p a using @p compare as the comparator.
 * Returns a Heap that references the provided ArrayList storage.
 *
 * @param a pointer to an initialized ArrayList containing the initial elements
 * @param compare comparison function used to order elements in the heap
 * @return pointer to a Heap on success; NULL on failure
 *
 * @note The resulting Heap uses the storage of @p a; do not modify @p a directly
 *       in ways that would break heap structure. It is recomened you do not use @p a 
 *       after you call this funtion.
 */
Heap *makeHeap(ArrayList *a, int (*compare)(const void *p1, const void *p2));

/**
 * Returns whether the heap is empty.
 *
 * @param h pointer to the Heap
 * @return 1 if empty; 0 if not empty; -1 on failure
 */
int heapEmpty(Heap *h);

/**
 * Destroys the underlying ArrayList even if the Heap does not own it.
 * Does not free the heap.
 *
 * @param h pointer to the Heap
 * @return 0 on success; -1 on failure
 *
 * @note if you make a heap with makeHeap this function will free the underlying ArrayList.
 */
int heapDestroy(Heap *h);

#endif