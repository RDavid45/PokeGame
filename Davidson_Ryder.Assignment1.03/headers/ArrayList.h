#include <stddef.h>

#ifndef ARRAYLIST_H
#define ARRAYLIST_H

typedef struct ArrayList
{
    void *data;
    size_t oSize;
    size_t aSize;
    size_t max;
} ArrayList;

/**
 * Reserves a place in memory for the array that can hold 4 objects.
 *  Sets aSize to 0 and oSize to @p objectSize
 * 
 * @param a pointer to the ArrayList that you want to initialize
 * @param objectSize size of the objects being stored in bytes;
 * @return 0 on success; -1 on failure
 */
int ArrayListinit(ArrayList *a, size_t objectSize);

/**
 * Retrieves the element at index i and copies it into the memory pointed to by @p item.
 * The index is zero-based.
 *
 * @param a pointer to the ArrayList
 * @param item pointer to a buffer with at least oSize bytes where the element will be copied to
 * @param i zero-based index of the element to retrieve (0 <= i < a->aSize)
 * @return 0 on success; -1 on failure
 * 
 * @note This function does not validate that @p item is non-NULL; passing NULL
 *       may cause damage. Make sure @p item is valid.
 */
int ArrayListget(ArrayList *a,  void *item, int i);

/**
 * Removes the last element in the ArrayList and copies it into the memory
 * pointed to by @p removed. Decreases aSize by 1.
 *
 * @param a pointer to the ArrayList
 * @param removed pointer to a buffer with at least oSize bytes where the
 *        removed element will be copied to
 * @return 0 on success; -1 on failure
 *
 * @note This function does not validate that @p removed is non-NULL; passing NULL
 *       may cause damage. Make sure @p removed is valid.
 */
int ArrayListpop(ArrayList *a, void *removed);

/**
 * Inserts an element at index @p i, shifting existing elements at and after @p i
 * one position to the right. Grows the array if needed. Increases aSize by 1.
 *
 * @param a pointer to the ArrayList
 * @param item pointer to a buffer with at least oSize bytes holding the element to insert
 * @param i zero-based position at which to insert (0 <= i <= a->aSize)
 * @return 0 on success; -1 on failure
 *
 * @note This function does not validate that @p item is non-NULL; passing NULL
 *       may cause damage. Make sure @p item is valid.
 */
int ArrayListinsert(ArrayList *a,  void *item, int i);

/**
 * Swaps the elements at indices @p i and @p j.
 *
 * @param a pointer to the ArrayList
 * @param i zero-based index of the first element to swap
 * @param j zero-based index of the second element to swap
 * @return 0 on success; -1 on failure
 *
 * @note Both @p i and @p j must be valid indices (0 <= index < a->aSize).
 */
int ArrayListswap(ArrayList *a, int i, int j);

/**
 * Appends an element to the end of the ArrayList. Grows array if needed. Increases aSize by 1.
 *
 * @param a pointer to the ArrayList
 * @param item pointer to a buffer with at least oSize bytes holding the element to append
 * @return 0 on success; -1 on failure
 *
 * @note This function does not validate that @p item is non-NULL; passing NULL
 *       may cause damage. Make sure @p item is valid.
 * @note this function does not make sure that item is the same type as everything else.
 */
int ArrayListadd(ArrayList *a, void *item);

/**
 * Removes the element at index @p i and copies it into the memory pointed to by
 * @p removed.
 * Shifts subsequent elements left by one position and decreases aSize by 1.
 *
 * @param a pointer to the ArrayList
 * @param i zero-based index of the element to remove (0 <= i < a->aSize)
 * @param removed pointer to a buffer with at least oSize bytes where the removed
 *        element will be copied to
 * @return 0 on success; -1 on failure
 *
 * @note This function does not validate that @p removed is non-NULL; passing NULL
 *       may cause damage. Make sure @p removed is valid. Also ensure @p i is within bounds.
 */
int ArrayListremove(ArrayList *a, int i, void*removed);

/**
 * Frees the memory used by the ArrayList's internal storage.
 * Does not free the ArrayList struct itself and does not reset fields.
 *
 * @param a pointer to the ArrayList
 * @return 0 on success; -1 on failure
 *
 * @note This function assumes @p a is non-NULL. Passing NULL is undefined behavior.
 */

int ArrayListdestroy(ArrayList *a);

/**
 * Grows the capacity of the underlying array to accommodate more elements.
 * Doubles the current max capacity and preserves existing elements.
 *
 * @param a pointer to the ArrayList
 * @return 0 on success; -1 on failure (e.g., allocation fails)
 *
 * @note On success, both @p a->data and @p a->max are updated. On failure,
 *       the original data pointer and capacity remain unchanged.
 */
int growArrayList(ArrayList *a);

/**
 * gets how many elements are in the array @p a
 * 
 * @param a pointer to an ArrayList
 * @return num elements in the array
 */
int arraySize(ArrayList *a);



#endif