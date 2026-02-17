#ifndef SEEDQUEUE_H
#define SEEDQUEUE_H

struct seed
{
    int x;
    int y;
    char chr;
    struct seed *next;
};
struct seedQueue{
    struct seed *front;
    struct seed *back;
    int size;
};

/**
 * Initializes the seedQueue by setting front and back to NULL and size to 0.
 *
 * @param q pointer to the seedQueue to initialize
 * @return 0 on success; -1 on failure
 */
int initSeedQueue(struct seedQueue *q);

/**
 * Destroys the seedQueue by freeing all nodes and resetting fields.
 * Sets front and back to NULL and size to 0.
 *
 * @param q pointer to the seedQueue to destroy
 * @return 0 on success; -1 on failure
 */
int destroySeedQueue(struct seedQueue *q);

/**
 * Enqueues a new seed with coordinates ( @p x, @p y ) and character @p c
 * at the back of the queue. Increases size by 1.
 *
 * @param q pointer to the seedQueue
 * @param x x-coordinate to store
 * @param y y-coordinate to store
 * @param c character to store
 * @return 0 on success; -1 on failure (e.g., allocation fails)
 */
int enqueueSeed(struct seedQueue *q, int x, int y, char c);

/**
 * Dequeues the seed at the front of the queue and copies its values into
 * @p x, @p y, and @p c. Decreases size by 1.
 *
 * @param q pointer to the seedQueue
 * @param x output pointer to receive the x-coordinate
 * @param y output pointer to receive the y-coordinate
 * @param c output pointer to receive the character
 * @return 0 on success; -1 on failure (e.g., queue is empty)
 *
 * @note This function does not validate that @p x, @p y, and @p c are non-NULL;
 *       passing NULL may cause damage. Make sure all pointers are valid.
 */
int dequeueSeed(struct seedQueue *q, int *x, int *y, char *c);

/**
 * Copies the values from the seed at the front of the queue into
 * @p x, @p y, and @p c without removing it.
 *
 * @param q pointer to the seedQueue
 * @param x output pointer to receive the x-coordinate
 * @param y output pointer to receive the y-coordinate
 * @param c output pointer to receive the character
 * @return 0 on success; -1 on failure (e.g., queue is empty)
 *
 * @note This function does not validate that @p x, @p y, and @p c are non-NULL;
 *       passing NULL may cause damage. Make sure all pointers are valid.
 */
int peekSeedQueue(struct seedQueue *q, int *x, int *y, char *c);

/**
 * Retrieves the current number of elements in the queue.
 *
 * @param q pointer to the seedQueue
 * @param size output pointer to receive the size
 * @return 0 on success; -1 on failure
 *
 * @note This function does not validate that @p size is non-NULL; passing NULL
 *       may cause damage. Make sure @p size is valid.
 */
int sizeQueue(struct seedQueue *q, int *size);

/**
 * Reports whether the queue is empty.
 *
 * @param q pointer to the seedQueue
 * @return 1 if empty; 0 if not empty; -1 on failure
 */
int isEmptyQueue(struct seedQueue *q);




#endif