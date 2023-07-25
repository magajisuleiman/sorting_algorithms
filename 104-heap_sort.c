#include <stdio.h>
#include <stdlib.h>

/**
 * struct listint_s - Doubly linked list node
 *
 * @n: Integer stored in the node
 * @prev: Pointer to the previous element of the list
 * @next: Pointer to the next element of the list
 */
typedef struct listint_s
{
    const int n;
    struct listint_s *prev;
    struct listint_s *next;
} listint_t;

/**
 * createNode - Function to create a new node for the doubly linked list
 * @data: Integer value to store in the node
 * Return: Pointer to the newly created node
 *
 * Description: This function creates a new node for the doubly linked list
 * with the given data value and returns a pointer to the newly created node.
 */
listint_t *createNode(int data)
{
    listint_t *newNode = (listint_t *)malloc(sizeof(listint_t));
    if (newNode == NULL)
        return NULL;

    newNode->n = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

/**
 * swap - Function to swap two elements in the doubly linked list
 * @a: First element to swap
 * @b: Second element to swap
 *
 * Description: This function swaps the values of two elements
 * in the doubly linked list.
 */
void swap(listint_t *a, listint_t *b)
{
    int temp = a->n;

    a->n = b->n;
    b->n = temp;
}

/**
 * heap_sort - Function to perform the Heap sort algorithm on the doubly linked list
 * @head: Pointer to the head of the doubly linked list
 * @size: Size of the doubly linked list
 *
 * Description: This function sorts the doubly linked list using the Heap sort algorithm.
 * It first builds the heap from the list, then extracts elements one by one to obtain
 * the sorted list. The doubly linked list will be printed after each swap to demonstrate
 * the sorting steps.
 */
void heap_sort(listint_t **head, size_t size)
{
    // Build the heap (rearrange the doubly linked list)
    for (int i = size / 2 - 1; i >= 0; i--)
    {
        listint_t *root = *head;
        for (int j = 0; j < i; j++)
        {
            root = root->next;
        }

        listint_t *largest = root;
        listint_t *leftChild = root->next;
        listint_t *rightChild = root->next->next;

        // Compare root with left child
        if (leftChild != NULL && leftChild->n > largest->n)
            largest = leftChild;

        // Compare largest with right child
        if (rightChild != NULL && rightChild->n > largest->n)
            largest = rightChild;

        // If the largest element is not the root, then swap and continue sifting down
        if (largest != root)
        {
            swap(root, largest);
            // Print the doubly linked list after each swap
            listint_t *current = *head;
            while (current != NULL)
            {
                printf("%d ", current->n);
                current = current->next;
            }
            printf("\n");
        }
    }

    // Extract elements from the heap one by one
    listint_t *last = *head;
    while (last->next != NULL)
    {
        last = last->next;
    }
    for (int i = size - 1; i > 0; i--)
    {
        // Move the current root to the end
        swap(*head, last);
        // Print the doubly linked list after each swap
        listint_t *current = *head;
        while (current != NULL)
        {
            printf("%d ", current->n);
            current = current->next;
        }
        printf("\n");

        // Call siftDown on the reduced heap
        last = last->prev;

        // Sift down the new root
        listint_t *largest = *head;
        listint_t *leftChild = (*head)->next;
        listint_t *rightChild = (*head)->next->next;

        // Compare root with left child
        if (leftChild != NULL && leftChild->n > largest->n)
            largest = leftChild;

        // Compare largest with right child
        if (rightChild != NULL && rightChild->n > largest->n)
            largest = rightChild;

        // If the largest element is not the root, then swap and continue sifting down
        if (largest != *head)
        {
            swap(*head, largest);
            // Print the doubly linked list after each swap
            listint_t *current = *head;
            while (current != NULL)
            {
                printf("%d ", current->n);
                current = current->next;
            }
            printf("\n");
        }
    }
}

int main(void)
{
    listint_t *head = NULL;
    size_t size = 6;

    // Sample data for the doubly linked list
    head = createNode(12);
    head->next = createNode(11);
    head->next->prev = head;
    head->next->next = createNode(13);
    head->next->next->prev = head->next;
    head->next->next->next = createNode(5);
    head->next->next->next->prev = head->next->next;
    head->next->next->next->next = createNode(6);
    head->next->next->next->next->prev = head->next->next->next;
    head->next->next->next->next->next = createNode(7);
    head->next->next->next->next->next->prev = head->next->next->next->next;

    printf("Original Doubly Linked List: ");
    listint_t *current = head;
    while (current != NULL)
    {
        printf("%d ", current->n);
        current = current->next;
    }
    printf("\n");

    printf("Heap Sort Steps:\n");
    heap_sort(&head, size);

    printf("Sorted Doubly Linked List: ");
    current = head;
    while (current != NULL)
    {
        printf("%d ", current->n);
        current = current->next;
    }
    printf("\n");

    // Clean up: free memory allocated for the doubly linked list
    current = head;
    while (current != NULL)
    {
        listint_t *temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}

