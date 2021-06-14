// A complete working C program to
// demonstrate all insertion
// methods
#include <stdio.h>
#include <stdlib.h>

// A linked list node
struct Node
{
    int data;
    struct Node *next;
    struct Node *prev;
};

/* Given a reference (pointer to pointer) to the head of a
   list and an int, inserts a new node on the front of the
   list. */
void push(struct Node **head_ref, int new_data)
{
    /* 1. allocate node */
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));

    /* 2. put in the data  */
    new_node->data = new_data;

    /* 3. Make next of new node as head and previous as NULL
     */
    new_node->next = (*head_ref);
    new_node->prev = NULL;

    /* 4. change prev of head node to new node */
    if ((*head_ref) != NULL)
        (*head_ref)->prev = new_node;

    /* 5. move the head to point to the new node */
    (*head_ref) = new_node;
}

/* Given a node as prev_node, insert a new node after the
 * given node */
void insertAfter(struct Node *prev_node, int new_data)
{
    /*1. check if the given prev_node is NULL */
    if (prev_node == NULL)
    {
        printf("the given previous node cannot be NULL");
        return;
    }

    /* 2. allocate new node */
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));

    /* 3. put in the data  */
    new_node->data = new_data;

    /* 4. Make next of new node as next of prev_node */
    new_node->next = prev_node->next;

    /* 5. Make the next of prev_node as new_node */
    prev_node->next = new_node;

    /* 6. Make prev_node as previous of new_node */
    new_node->prev = prev_node;

    /* 7. Change previous of new_node's next node */
    if (new_node->next != NULL)
        new_node->next->prev = new_node;
}

/* Given a reference (pointer to pointer) to the head
   of a DLL and an int, appends a new node at the end  */
void append(struct Node **head_ref, int new_data)
{
    /* 1. allocate node */
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));

    struct Node *last = *head_ref; /* used in step 5*/

    /* 2. put in the data  */
    new_node->data = new_data;

    /* 3. This new node is going to be the last node, so
          make next of it as NULL*/
    new_node->next = NULL;

    /* 4. If the Linked List is empty, then make the new
          node as head */
    if (*head_ref == NULL)
    {
        new_node->prev = NULL;
        *head_ref = new_node;
        return;
    }

    /* 5. Else traverse till the last node */
    while (last->next != NULL)
        last = last->next;

    /* 6. Change the next of last node */
    last->next = new_node;

    /* 7. Make last node as previous of new node */
    new_node->prev = last;

    return;
}

void delateList(struct Node **head_ref)
{
    struct Node *prev = *head_ref;

    while (*head_ref)
    {
        *head_ref = (*head_ref)->next;

        free(prev);
        prev = *head_ref;
    }
}

// This function prints contents of linked list starting
// from the given node
void printList(struct Node *node)
{
    struct Node *last;
    printf("\nTraversal in forward direction \n");
    while (node != NULL)
    {
        printf(" %d ", node->data);
        last = node;
        node = node->next;
    }

    printf("\nTraversal in reverse direction \n");
    while (last != NULL)
    {
        printf(" %d ", last->data);
        last = last->prev;
    }
}

void printListNum(struct Node *node) //print a list in reverse
{
    struct Node *last;
    while (node != NULL)
    {
        last = node;
        node = node->next;
    }
    while (last != NULL)
    {
        printf("%d", last->data);
        last = last->prev;
    }
}

void reciprocalList(struct Node **head_ref)
{
    struct Node *head = *head_ref;
    while (*head_ref != NULL)
    {
        (*head_ref)->data = -((*head_ref)->data); //if is - become +
        *head_ref = (*head_ref)->next;
    }
    *head_ref = head; //head ref become = the head and no the last element
}

/*
add two list struct Node *node1, struct Node *node2 and return struct Node *
*/
struct Node *addTwoLists(struct Node *node1, struct Node *node2)
{
    int num1, num2, sum, carry = 0;
    struct Node *tmp = NULL;
    struct Node *resultat = NULL;
    while (1)
    {
        if (node1 == NULL && node2 == NULL)
        {
            break;
        }

        num1 = 0;
        num2 = 0;
        if (node1 != NULL)
        {
            num1 = node1->data;
            node1 = node1->next;
        }
        if (node2 != NULL)
        {
            num2 = node2->data;
            node2 = node2->next;
        }

        if ((num1 + num2 < 0) && (num1 > 0 || num2 > 0))
        {
            if (node1 != NULL)
            {
                num1 += 10;
                node1->data -= 1;
            }
            else
            {
                num2 += 10;
                node2->data -= 1;
            }
        }

        sum = num1 + num2 + carry;
        carry = sum / 10;
        sum -= carry * 10;

        append(&resultat, sum);
    }

    if (carry != 0)
    {
        append(&resultat, sum);
    }
    return resultat;
}

struct Node *subtractTwoLists(struct Node *node1, struct Node *node2)
{
    reciprocalList(&node2); // es 123 -21 = 123+(-21)
    return addTwoLists(node1, node2);
}

struct Node *multiplyTwoLists(struct Node *node1, struct Node *node2) //maybe resultat is using memory form the previous loops so BIG MEMORY USAGE
{
    int multiply, carry = 0;
    struct Node *resultat = NULL;
    struct Node *head_node2 = node2;
    struct Node *tmp_resultat = NULL;

    for (int i = 0; node1 != NULL; i++)
    {
        node2 = head_node2;
        delateList(&tmp_resultat);

        for (int y = 0; y < i; y++)
        {
            append(&tmp_resultat, 0);
        }
        while (node2 != NULL)
        {
            multiply = (node1->data * node2->data) + carry;
            carry = 0;
            carry = multiply / 10;
            multiply -= carry * 10;
            append(&tmp_resultat, multiply);
            node2 = node2->next;
        }
        if (carry != 0)
        {
            append(&tmp_resultat, carry);
            carry = 0;
        }
        resultat = addTwoLists(resultat, tmp_resultat);
        node1 = node1->next;
    }
    return resultat;
}

/* Driver program to test above functions*/
int main()
{
    /* Start with the empty list */
    struct Node *list_1 = NULL;
    push(&list_1, 8);
    push(&list_1, 7);
    push(&list_1, 2);

    struct Node *list_2 = NULL;
    push(&list_2, 7);
    push(&list_2, 9);

    struct Node *list_3 = NULL;

    printListNum(list_1);
    printf(" - ");
    printListNum(list_2);
    printf("\n");

    list_3 = subtractTwoLists(list_1, list_2);
    printListNum(list_3);
    return 0;
}