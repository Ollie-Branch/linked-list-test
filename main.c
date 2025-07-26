#include "ll.h"
#include <stdio.h>
#include <stdlib.h>

const int num_linked_list_elems = 20;

void SetupLinkedListWithInt(LinkedList_t *list) {
    // the list already has an element in the first member
    int *element = (int *)LL_GetNodeData(list, 0);
    *element = 50;
    for (int i = 1; i < num_linked_list_elems; i++) {
        LinkedList_Node_t *node = LL_NodeCreate(sizeof(int));
        element = (int *)LL_NodeGetDataField(node);
        *element = (rand() % 100) + 1;
        LL_InsertNode(list, node, i);
    }
    return;
}

int main(int argv, char **argc) {
    LinkedList_t *int_list = LL_Create(LL_NodeCreate(sizeof(int)));
    SetupLinkedListWithInt(int_list);

    printf("%i", *(int *)LL_GetNodeData(int_list, 0));
    for (int i = 1; i < num_linked_list_elems; i++) {
        printf(" -> %i", *(int *)LL_GetNodeData(int_list, i));
    }

    printf("\n\nNumber of nodes in list: %i \n",
           (LL_GetNumNodes(int_list) + 1)); // convert 0 index to 1-index
    printf("List Head: %i \n",
           *(int *)LL_NodeGetDataField(LL_GetHead(int_list)));
    printf("List Tail: %i \n",
           *(int *)LL_NodeGetDataField(LL_GetTail(int_list)));

    printf("\n\ninserting the number 5 at position #5, to make sure the "
           "other items in the list are preserved \n \n"); // 1-indexed

    LinkedList_Node_t *node = LL_NodeCreate(sizeof(int));
    int *element = (int *)LL_NodeGetDataField(node);
    *element = 5;
    LL_InsertNode(int_list, node, 4); // 0-indexed

    printf("%i", *(int *)LL_GetNodeData(int_list, 0));
    for (int i = 1; i < num_linked_list_elems + 1; i++) {
        printf(" -> %i", *(int *)LL_GetNodeData(int_list, i));
    }
    printf("\n\nNumber of nodes in list: %i \n",
           (LL_GetNumNodes(int_list) + 1)); // convert 0-index to 1-index
    printf("List Head: %i \n",
           *(int *)LL_NodeGetDataField(LL_GetHead(int_list)));
    printf("List Tail: %i \n",
           *(int *)LL_NodeGetDataField(LL_GetTail(int_list)));

    printf("\n\ninserting the number 20 at position #21, to make sure the "
           "other items in the list are preserved \n \n"); // 1-indexed

    node = LL_NodeCreate(sizeof(int));
    element = (int *)LL_NodeGetDataField(node);
    *element = 20;
    LL_InsertNode(int_list, node, 20); // 0-indexed

    printf("%i", *(int *)LL_GetNodeData(int_list, 0));
    for (int i = 1; i < LL_GetNumNodes(int_list) + 1; i++) {
        printf(" -> %i", *(int *)LL_GetNodeData(int_list, i));
    }
    printf("\n \n Number of nodes in list: %i \n",
           (LL_GetNumNodes(int_list) + 1)); // convert 0-index to 1-index
    printf("List Head: %i \n",
           *(int *)LL_NodeGetDataField(LL_GetHead(int_list)));
    printf("List Tail: %i \n",
           *(int *)LL_NodeGetDataField(LL_GetTail(int_list)));

    return 0;
}
