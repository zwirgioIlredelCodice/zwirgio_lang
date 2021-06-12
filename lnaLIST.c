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

void reverse1(struct Node **head_ref)
{
    struct Node *prev = NULL;
    struct Node *current = *head_ref;
    struct Node *next;
    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head_ref = prev;
}

int reverse(struct Node** head_ref)
{
    struct Node* prev = NULL;
    struct Node* current = *head_ref;
    struct Node* next;
    int len = 0;
    while (current != NULL) {
        len++;
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head_ref = prev;
    return len;
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

void printListNum(struct Node *node)
{
    struct Node *last;
    while (node != NULL)
    {
        printf("%d", node->data);
        last = node;
        node = node->next;
    }
}

/*
add two list struct Node *node1, struct Node *node2 and return struct Node *
*/
struct Node *addTwoLists(struct Node *node1, struct Node *node2)
{
    int sum, carry = 0;
    struct Node *resultat = NULL;
    while (node1 != NULL && node2 != NULL)
    {
        sum = node1->data + node2->data + carry; // es 13
        carry = 0;
        carry = sum / 10;     // carry = 1
        sum -= carry * 10;    //sum = 13-(1*10) = 3
        push(&resultat, sum); //push perchè cosi lo mette al inizio cosi centinaia->decine
        node1 = node1->next;
        node2 = node2->next;
    }
    if (node1 == NULL && node2 == NULL) //same size
    {
        if (carry != 0)
        {
            push(&resultat, carry);
        }
    }

    else if (node1 == NULL) //size node1 < size node2
    {
        while (node2 != NULL)
        {
            sum = node2->data + carry; // es 13
            carry = 0;
            carry = sum / 10;     // carry = 1
            sum -= carry * 10;    //sum = 13-(1*10) = 3
            push(&resultat, sum); //push perchè cosi lo mette al inizio cosi centinaia->decine
            node2 = node2->next;
        }
        if (carry != 0)
        {
            push(&resultat, carry);
        }
    }

    else //size node1 > size node2
    {
        while (node1 != NULL)
        {
            sum = node1->data + carry; // es 13
            carry = 0;
            carry = sum / 10;     // carry = 1
            sum -= carry * 10;    //sum = 13-(1*10) = 3
            push(&resultat, sum); //push perchè cosi lo mette al inizio cosi centinaia->decine
            node1 = node1->next;
        }
        if (carry != 0)
        {
            push(&resultat, carry);
        }
    }

    return resultat;
}

struct Node *multiplyTwoLists1(struct Node *node1, struct Node *node2)
{
    int multiply, carry = 0, issecond = 0;
    struct Node *resultat = NULL;
    struct Node *tmp_resultat = NULL;
    struct Node *tmp_node1 = node1; //head of node1
    struct Node *tmp_node2 = node2; //head of node2

    for (int i = 0; node1 != NULL; i++)
    {
        node2 = tmp_node2;
        while (node2 != NULL)
        {
            multiply = (node1->data * node2->data) + carry;
            //printf("%d * %d = %d\n",node1->data,node2->data,multiply);
            carry = 0;
            carry = multiply / 10;  // carry = 1
            multiply -= carry * 10; //sum = 13-(1*10) = 3

            push(&tmp_resultat, multiply);

            //printf("%d", multiply);
            node2 = node2->next;
        }
        if (carry != 0)
        {
            //printf("%d", carry);
            push(&tmp_resultat, carry);
            carry = 0;
        }
        for (int y = 0; y < i; y++)
        {
            //printf("0");
            append(&tmp_resultat, 0);
        }
        printListNum(tmp_resultat);

        resultat = addTwoLists(tmp_resultat, resultat); //errore perchè somma enemento prima lista e ultimo elemento deconda lista
        delateList(&tmp_resultat);
        //delateList(&resultat);
        node1 = node1->next;
        printf("\n");
    }

    return resultat;
}

struct Node *make_empty_list(int size)
{
    struct Node *head = NULL;
    while (size--)
        push(&head, 0);
    return head;
}

// Multiply contents of two linked lists => store
// in another list and return its head
struct Node *multiplyTwoLists(struct Node *first, struct Node *second)
{
    // reverse the lists to muliply from end
    // m and n lengths of linked lists to make
    // and empty list
    int m = reverse(&first), n = reverse(&second);

    // make a list that will contain the result
    // of multiplication.
    // m+n+1 can be max size of the list
    struct Node *result = make_empty_list(m + n + 1);

    // pointers for traverse linked lists and also
    // to reverse them after
    struct Node *second_ptr = second, *result_ptr1 = result, *result_ptr2, *first_ptr;

    // multiply each Node of second list with first
    while (second_ptr)
    {

        int carry = 0;

        // each time we start from the next of Node
        // from which we started last time
        result_ptr2 = result_ptr1;

        first_ptr = first;

        while (first_ptr)
        {

            // multiply a first list's digit with a
            // current second list's digit
            int mul = first_ptr->data * second_ptr->data + carry;

            // Assigne the product to corresponding Node
            // of result
            result_ptr2->data += mul % 10;

            // now resultant Node itself can have more
            // than 1 digit
            carry = mul / 10 + result_ptr2->data / 10;
            result_ptr2->data = result_ptr2->data % 10;

            first_ptr = first_ptr->next;
            result_ptr2 = result_ptr2->next;
        }

        // if carry is remaining from last multiplication
        if (carry > 0)
        {
            result_ptr2->data += carry;
        }

        result_ptr1 = result_ptr1->next;
        second_ptr = second_ptr->next;
    }

    // reverse the result_list as it was populated
    // from last Node
    reverse(&result);
    reverse(&first);
    reverse(&second);

    // remove if there are zeros at starting
    while (result->data == 0)
    {
        struct Node *temp = result;
        result = result->next;
        free(temp);
    }

    // Return head of multiplication list
    return result;
}

/* Driver program to test above functions*/
int main()
{
    /* Start with the empty list */
    struct Node *list_1 = NULL;

    // Insert 6.  So linked list becomes 6->NULL
    append(&list_1, 8);
    append(&list_1, 7);
    append(&list_1, 2);

    struct Node *list_2 = NULL;
    append(&list_2, 7);
    append(&list_2, 9);
    append(&list_2, 8);
    append(&list_2, 9);
    append(&list_2, 9);
    append(&list_2, 9);
    append(&list_2, 9);
    append(&list_2, 9);
    append(&list_2, 9);
    append(&list_2, 9);

    struct Node *list_3 = NULL;

    printListNum(list_1);
    printf(" * ");
    printListNum(list_2);
    printf("\n");

    list_3 = multiplyTwoLists(list_2, list_1);
    printListNum(list_3);
    return 0;
}