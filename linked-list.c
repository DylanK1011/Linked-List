// Dylan Krejci
// dkrejci

// do not include other libraries
#include <stdio.h>
#include <stdlib.h>

// ***************************************
// *** struct definitions ****************
// *** do not change these ***************
// ***************************************
typedef struct NODE {int data; struct NODE* next;} NODE; // nodes of the linked list
typedef struct LINKED_LIST {struct NODE *head;} LINKED_LIST; // struct to act as the head of the list


// ***************************************
// *** provided functions  ****************
// ***************************************

// this function returns a LINKED_LIST struct to
// act as the head of the linked list.
// do not change this function
LINKED_LIST Create_List(void) {LINKED_LIST list = {NULL}; return list;}

// call this function to verify malloc worked when you create new nodes
void Verify_Malloc(NODE *node) {if (node == NULL) {printf("Malloc Failed\n"); exit(1);} return;}

// do not change this function
// this function prints out all of the nodes in the linked list
void Print_List(FILE *out, LINKED_LIST list) {
    if (list.head == NULL) {printf("\n"); return;} //empty list
    NODE *current = list.head;
    while (current->next != NULL) {
        fprintf(out, "%d -> ",current->data);
        current = current->next;
    }
    fprintf(out, "%d\n",current->data);
    return;
}

// ******************************************************
// *** Complete the following functions  ****************
// ******************************************************

// this function returns the number
// of elements in the linked list
int Size(LINKED_LIST list){
    int count = 0;
    struct NODE *current;
    for (current = list.head; current != NULL; current = current->next) ++count;  // Traverse through every node in list; count is size of list
    return count;
}
// this function adds an element to
// the front of the list
void Push_Front(LINKED_LIST *list, int data) {
    struct NODE *newNode = malloc(sizeof(struct NODE));  // Allocate space on heap for a new NODE
    newNode->data = data;

    // Position newNode at head of list
    newNode->next = list->head;
    list->head = newNode;
    return;
}

// this function adds an element
// to the end of the linked list
void Push_Back(LINKED_LIST *list, int data) {
    struct NODE *newNode = malloc(sizeof(struct NODE));  // Allocate space on heap for a new NODE
    newNode->data = data;
    newNode->next = NULL;

    // Case: Empty List
    if (list->head == NULL) {
        list->head = newNode;
        return;
    }

    // Position newNode at end of list
    struct NODE *current = list->head;
    for (current; current->next != NULL; current = current->next)
        ;
    current->next = newNode;
    return;
}


// if the list is not empty
// the value of the first element of the list is returned by reference in the parameter data
// the first element of the list is deleted
// returns 0 if the list is empty otherwise returns 1
// remember to free the deleted node
int Pop_Front(LINKED_LIST *list, int *data) {
    struct NODE *head = list->head;

    // Empty Case
    if (head == NULL)
        return 0;

    // Adjust front of list to remove previous head
    *data = head->data;
    list->head = head->next;
    free(head);
    return 1;
}


// if the list is not empty
// the value of the last element of the list is returned by reference in the parameter data
// the last element of the list is deleted
// returns 0 if the list is empty otherwise returns 1
// remember to free the deleted node
int Pop_Back(LINKED_LIST *list, int *data) {
    struct NODE *curr = list->head;

    // Empty Case
    if (curr == NULL)
        return 0;

    // One Node Case
    if (curr->next == NULL) {
        list->head = NULL;
        *data = curr->data;
        free(curr);
        return 1;
    }

    // Multiple Nodes Case
    for (curr; curr->next->next != NULL; curr = curr->next)
        ;
    *data = curr->next->data;
    free(curr->next);
    curr->next = NULL;
    return 1;
}

// this function returns the number
// of times that the value of the parameter
// data appears in the list
int Count_If(LINKED_LIST list, int data) {
    struct NODE *curr = list.head;
    int count = 0;
    for (curr; curr != NULL; curr = curr->next)
        if (curr->data == data) ++count;
    return count;
}

// delete the first node containing the data value
// return 1 if something was deleted otherwise 0
// remember to free the deleted node
int Delete(LINKED_LIST *list, int data) {
    struct NODE *curr = list->head;

    // Empty Case OR node to delete is in head
    if (Size(*list) == 0 || list->head->data == data)
        return Pop_Front(list, &data);

    // All other cases
    for (curr; curr->next != NULL; curr = curr->next) {
        if (curr->next->data == data) {
            struct NODE *remove = curr->next;
            curr->next = curr->next->next;
            free(remove);
            return 1;
        }
    }
    return 0;
}

// return 1 if the list is empty otherwise returns 0
int Is_Empty(LINKED_LIST list) {
    if (Size(list) == 0)
        return 1;
    return 0;
}

// delete all elements of the list
// remember to free the nodes
void Clear(LINKED_LIST *list) {
    while (Size(*list)) {
        int x;
        Pop_Front(list, &x);
    }
    return;
}


// if an element appears in the list
// retain the first occurance but
// remove all other nodes with the same
// data value
void Remove_Duplicates(LINKED_LIST *list) {
    struct NODE *curr;   // Pointer to node to compare to
    struct NODE *check;  // Pointer to node to be checked against curr; if curr and check have same data, check is removed
    struct NODE *prev;   // Pointer to node before check; if check is removed, prev is used to reposition pointers

    // Traverse through every node in list to ensure it is the only node with it's given data
    for (curr = list->head; curr != NULL; curr = curr->next) {
        check = curr->next;                   // Check is set to next node after curr and traversed through entire remainder of list
        while (check != NULL) {

            // Match
            if (check->data == curr->data) {

                // Determine node right before check
                prev = curr;
                while (prev->next != check)
                    prev = prev->next;

                // Reposition pointers and free the memory allocated to check
                prev->next = check->next;
                free(check);
                check = prev->next;

            // Not a match - continue traversal
            } else
                check = check->next;
        }
    }
    return;
}

// modify main to completely test your functions
int main() {

    printf("\n  Test Suite\n\tDesigned by Dylan Krejci\n\tMarch 22, 2022\n\n\n");
    // Create a linked list - Test Size
        LINKED_LIST list = Create_List();

    // add some data (hardcoded for testing)
        NODE *first  = malloc(sizeof(NODE)); Verify_Malloc(first);
        NODE *second = malloc(sizeof(NODE)); Verify_Malloc(second);
        first->data  = 1;
        second->data = 2;

    // Hardcoded Size Test
        printf("  Size\n");
        printf("\n\tSize of empty list (expected: 0) = %d\n", Size(list));
        list.head = first;
        printf("\tSize of list with one element (expected: 1) = %d\n", Size(list));
        first->next = second;
        second->next = NULL;
        printf("\tSize of list with multiple elements (expected: 2) = %d\n", Size(list));

    // print the list
        printf("\n\n  Print_List\n");
        printf("\n\tPrinted List (expected: 1 -> 2) = ");
        Print_List(stdout, list);

    // Push_Front Test
        printf("\n\n  Push_Front\n");
        LINKED_LIST test = Create_List();
        Push_Front(&test, 0);
        printf("\n\tPushing node to front of empty list (expected: 0) = ");
        Print_List(stdout, test);
        printf("\tSize (expected: 1) = %d\n", Size(test));
        printf("\tHead of list (expected: 0) = %d\n", test.head->data);

        Push_Front(&test, 1);
        printf("\n\tPushing node to front of non-empty list (expected: 1 -> 0) = ");
        Print_List(stdout, test);
        printf("\tSize (expected: 2) = %d\n", Size(test));
        printf("\tHead of list (expected: 1) = %d\n", test.head->data);

    // Push_Back Test
        printf("\n\n  Push_Back\n");
        LINKED_LIST testTwo = Create_List();
        Push_Back(&testTwo, 3);
        printf("\n\tPushing node to back of empty list (expected: 3) = ");
        Print_List(stdout, testTwo);
        printf("\tHead of list (expected: 3) = %d\n", testTwo.head->data);

        Push_Back(&testTwo, 4);
        printf("\n\tPushing node to back of non-empty list (expected: 3 -> 4) = ");
        Print_List(stdout, testTwo);
        printf("\tHead of list (expected: 3) = %d\n", testTwo.head->data);

    // Pop_Front Test
        printf("\n\n  Pop_Front\n");
        LINKED_LIST empty = Create_List();
        LINKED_LIST one = Create_List();
        Push_Front(&one, 3);

        {
        printf("\n\tTest popping from empty list: ");
        int x;
        int not_empty = Pop_Front(&empty, &x);
        if (!not_empty)
            printf("List was empty\n");
        else
            printf("Error\n");
        }

        {
        printf("\n\tTest popping from list with one node\n");
        int x;
        int not_empty = Pop_Front(&one, &x);
        if (not_empty) {
            printf("\tElement popped (expected: 3) = %d\n",x);
            printf("\tPrinted List (expected: ) = ");
            Print_List(stdout,one);
            printf("\tSize (expected: 0) = %d\n", Size(one));
            //printf("\tHead (expected: NULL) = %d\n", one.head->data);
        } else
            printf("Error\n");
        }

        {
        printf("\n\tTest popping from list with multiple nodes\n");
        int x;
        int not_empty = Pop_Front(&test, &x);
        if (not_empty) {
            printf("\tElement popped (expected: 1) =  %d\n", x);
            printf("\tPrinted List (Expected: 0) = ");
            Print_List(stdout, test);
            printf("\tSize (expected: 1) = %d\n", Size(test));
            printf("\tHead (expected: 0) = %d\n", test.head->data);
        } else
            printf("Error\n");
        }


    // Pop_Back Test
        printf("\n\n  Pop_Back\n");
        LINKED_LIST emptyBack = Create_List();
        LINKED_LIST oneBack = Create_List();
        Push_Front(&oneBack, 4);
        LINKED_LIST multiple = Create_List();
        for (int i = 0; i < 5; ++i)
            Push_Front(&multiple, i);

        {
        printf("\n\tTest popping from empty list: ");
        int x;
        int not_empty = Pop_Back(&emptyBack, &x);
        if (!not_empty)
            printf("List was empty\n");
        else
            printf("Error\n");
        }

        {
        printf("\n\tTest popping from list with one node\n");
        int x;
        int not_empty = Pop_Back(&oneBack, &x);
        if (not_empty) {
            printf("\tElement popped (expected: 4) =  %d\n",x);
            printf("\tPrinted List (expected: ) = ");
            Print_List(stdout,oneBack);
            printf("\tSize (expected: 0) = %d\n",Size(oneBack));
        } else
            printf("Error\n");
        }

        {
        printf("\n\tTest popping from list with multiple nodes\n");
        int x;
        int not_empty = Pop_Back(&multiple, &x);
        if (not_empty) {
            printf("\tElement popped (expected: 0) = %d\n",x);
            printf("\tPrinted List (expected: 4 -> 3 -> 2 -> 1) = ");
            Print_List(stdout,multiple);
            printf("\tSize (expected: 4) = %d\n",Size(multiple));
        } else {
            printf("Error\n");
        }
        }

    // Testing Count_If
        printf("\n\n  Count_If\n");
        LINKED_LIST emptyList = Create_List();
        LINKED_LIST noOccurrences = Create_List();
        for (int i = 0; i < 5; ++i)
            Push_Front(&noOccurrences, i);
        LINKED_LIST someOccurrences = Create_List();
        for (int j = 0; j < 2; ++j)
            for (int i = 0; i < 5; ++i)
                Push_Front(&someOccurrences, i);
        LINKED_LIST allOccurrences = Create_List();
        for (int i = 0; i < 4; ++i)
            Push_Front(&allOccurrences, 3);

        printf("\n\tCount from an empty list (expected: 0) = %d\n", Count_If(emptyList, 5));
        printf("\tCount from a non-empty list without node to search for (expected: 0) = %d\n", Count_If(noOccurrences, 5));
        printf("\tCount from a non-empty list with some entries of node to search for, but not all (expected: 2) = %d\n", Count_If(someOccurrences, 3));
        printf("\tCount from a non-empty list with only entries of node to search for (expected: 4) = %d\n", Count_If(allOccurrences, 3));

    // Testing Delete
        printf("\n\n  Delete\n");
        LINKED_LIST multipleOcc = Create_List();
        Push_Front(&multipleOcc, 3);
        Push_Front(&multipleOcc, 4);
        Push_Front(&multipleOcc, 3);
        Push_Front(&multipleOcc, 2);
        Push_Front(&multipleOcc, 1);

        printf("\n\tDelete from an empty list: ");
        if (Delete(&emptyList, 3))
            printf("Error\n");
        else
            printf("No errors\n");

        printf("\tDelete node not in list: ");
        if (Delete(&noOccurrences, 5))
            printf("Error\n");
        else
            printf("No errors\n");

        printf("\tDelete only instance of node: ");
        if (Delete(&noOccurrences, 3)) {
            printf("Printing the list (expected: 4 -> 2 -> 1 -> 0) = ");
            Print_List(stdout, noOccurrences);
        } else {
            printf("Error\n");
        }

        printf("\tDelete head of list: ");
        if (Delete(&noOccurrences, 4)) {
            printf("Printing the list (expected: 2 -> 1 -> 0) = ");
            Print_List(stdout, noOccurrences);
        } else {
            printf("Error\n");
        }

        printf("\tDelete one of multiple instances of node: ");
        if (Delete(&multipleOcc, 3)) {
            printf("Printing the list (expected: 1 -> 2 -> 4 -> 3) = ");
            Print_List(stdout, multipleOcc);
        } else {
            printf("Error\n");
        }


    // Test Is_Empty
        printf("\n\n  Is_Empty\n");
        printf("\n\tTesting empty list: ");
        if (Is_Empty(emptyList)) printf("List is Empty\n"); else printf("List is not empty\n");
        printf("\tTesting non-empty list: ");
        if (Is_Empty(multipleOcc)) printf("List is Empty\n"); else printf("List is not empty\n");

    // Test Clear
        printf("\n\n  Clear\n");
        printf("\n\tClear empty list: ");
        Clear(&emptyList);
        if (Is_Empty(emptyList)) printf("List is Empty\n"); else printf("List is not empty\n");
        printf("\tClear list with one node: ");
        Push_Front(&emptyList, 3);
        Clear(&emptyList);
        if (Is_Empty(emptyList)) printf("List is Empty\n"); else printf("List is not empty\n");
        printf("\tClear list with multiple nodes: ");
        Clear(&multipleOcc);
        if (Is_Empty(multipleOcc)) printf("List is Empty\n"); else printf("List is not empty\n");

    // Test Remove_Duplicates
        printf("\n\n  Remove_Duplicates\n");
        Remove_Duplicates(&emptyList);
        printf("\n\tDuplicates removed from empty list (expected: ) = ");
        Print_List(stdout, emptyList);

        LINKED_LIST noDup = Create_List();
        for (int i = 0; i < 4; ++i)
            Push_Back(&noDup, i);
        Remove_Duplicates(&noDup);
        printf("\tDuplicates removed from list without duplicates (expected: 0 -> 1 -> 2 -> 3) = ");
        Print_List(stdout, noDup);

        for (int i = 0; i < 4; ++i)
            Push_Back(&emptyList, 3);
        Remove_Duplicates(&emptyList);
        printf("\tDuplicates removed from list with only one unique value (expected: 3) = ");
        Print_List(stdout, emptyList);

        Clear (&emptyList);
        int vals[] = {1,2,1,3,1};
        for (int i = 0; i < 5; ++i)
            Push_Back(&emptyList, vals[i]);
        Remove_Duplicates(&emptyList);
        printf("\tDuplicates removed from list with one set of scrambled duplicates (expected: 1 -> 2 -> 3) = ");
        Print_List(stdout, emptyList);

        Clear (&emptyList);
        int moreVals[] = {1,2,1,2,3,2,1,4,3};
        for (int i = 0; i < 9; ++i)
            Push_Back(&emptyList, moreVals[i]);
        Remove_Duplicates(&emptyList);
        printf("\tDuplicates removed from list with multiple sets scrambled duplicates (expected: 1 -> 2 -> 3 -> 4) = ");
        Print_List(stdout, emptyList);

        Clear (&emptyList);
        for (int i = 0; i < 12; ++i)
            Push_Back(&emptyList, i % 4); // 0 1 2 3 0 1 2 3 0 1 2 3 -> simplified to 0 1 2 3
        Remove_Duplicates(&emptyList);
        printf("\tDuplicates from from list with multiple duplicates out of order (expected: 0 -> 1 -> 2 -> 3) = ");
        Print_List(stdout, emptyList);

        printf("\n\n");
    return 0;
}
