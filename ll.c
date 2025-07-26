#include "ll.h"
#include <stdlib.h>

typedef struct LinkedList_t {
    LinkedList_Node_t *head;
    LinkedList_Node_t *tail;
    uint16_t num_nodes;
} LinkedList_t;

/*
** For the node, we store the size of the data contained in `void *data`, then
** the pointer to the next node, then the data itself.
** NOTE: We set data last cause it can be of any size, depending on the type
** 	contained within
*/
typedef struct LinkedList_Node_t {
    size_t size;
    LinkedList_Node_t *next;
    void *data;
} LinkedList_Node_t;

LinkedList_Node_t *LL_NodeCreate(size_t data_size) {
    /*
     ** We make sure to malloc enough memory for whatever size is passed into
     ** `size_t data_size`, then whatever else is needed for the members of the
     ** node struct. We use `char *` just to get the size of the systems
     ** pointer.
     ** On 32-bit systems, the pointer is 4 bytes, on 64-bit systems, it's 8
     ** bytes. Since a byte is 8-bits, you can easily derive the pointer size
     ** of any bit-width by just dividing the bits by 8.
     */
    LinkedList_Node_t *node = (LinkedList_Node_t *)malloc(
        data_size + sizeof(char *) + sizeof(size_t));
    node->next = NULL;
    return node;
}
size_t LL_NodeGetSize(LinkedList_Node_t *node) {
    return node->size + sizeof(char *) + sizeof(size_t);
}
void *LL_NodeGetDataField(LinkedList_Node_t *node) {
    /*
    ** Ideally we'd have a function to set the linked list's data without
    ** relying on the user to use either memcpy or dereference a pointer
    ** directly. Alas, I can't think of any way to do that right now.
    */
    return &node->data;
}

LinkedList_t *LL_Create(LinkedList_Node_t *node) {
    node->next = NULL;
    LinkedList_t *ll = (LinkedList_t *)malloc(sizeof(LinkedList_t));
    ll->head = node;
    ll->tail = node;
    ll->num_nodes = 0;
    return ll;
}

/*
** We assume the node we're inserting has already been initialized with the
** correct data, this is a bad assumption to make.
*/
void LL_InsertNode(LinkedList_t *list, LinkedList_Node_t *node_to_insert,
                   uint16_t index) {
    LinkedList_Node_t *current_node = list->head;
    LinkedList_Node_t *next_node = NULL;

    // base cases that can allow the linked list to *sometimes* be performant
    if (index == 0) {
        list->head = node_to_insert;
        node_to_insert->next = current_node;
        list->num_nodes++;
        return;
    }
    if (index >= list->num_nodes) {
        // We're inserting at the end of the list, therefore we don't need to
        // iterate over the elements of the list.
        list->tail->next = node_to_insert;
        list->tail = node_to_insert;
        node_to_insert->next = NULL;
        list->num_nodes++;
        return;
    }

    // Iterate through the list, if no other method of insertion was successful.
    // we do (index - 1), because when inserting between elements we insert
    // AFTER the current element we're processing, this is a hacky solution for
    // that bug.
    for (int i = 0; i < (index - 1); i++) {
        /*
        ** if we find the end of the list before the specified index, we just
        ** set the node at the end of the list.
        ** Due to the base cases above, this if statement SHOULD NOT ever be
        ** run. It only exists to account for unforeseen consequences.
        */
        if (current_node->next == NULL) {
            current_node->next = node_to_insert;
            list->tail = node_to_insert;
            node_to_insert->next = NULL;
            list->num_nodes++;
            return;
        }
        // if no node was inserted this loop, set the current node to the next
        // node before the next iteration.
        current_node = current_node->next;
    }

    // we are at the index we want, and can insert the node, moving around the
    // other nodes beforehand.
    next_node = current_node->next;
    current_node->next = node_to_insert;
    node_to_insert->next = next_node;
    list->num_nodes++;
    return;
}

void *LL_GetNodeData(LinkedList_t *list, uint16_t index) {
    LinkedList_Node_t *current_node = list->head;
    // same base cases as above function
    if (index == 0) {
        return &list->head->data;
    }
    if (index >= list->num_nodes) {
        return &list->tail->data;
    }
    for (int i = 0; i < index; i++) {
        if (current_node->next == NULL) {
            // we are at end of list, just return this current index
            return &current_node->data;
        }
        current_node = current_node->next;
    }
    return &current_node->data;
}

LinkedList_Node_t *LL_GetHead(LinkedList_t *list) { return list->head; }

LinkedList_Node_t *LL_GetTail(LinkedList_t *list) { return list->tail; }

uint16_t LL_GetNumNodes(LinkedList_t *list) { return list->num_nodes; }

void LL_DeleteNode(LinkedList_t *list, uint16_t index) {
    // TODO implement
}

/*
** If this node exists, we already have the size of the data from the size
** member of the struct, so we shouldn't need any more arguments other than the
** pointer to the node itself.
*/
// void LL_NodeDelete(LinkedList_Node_t *node) {
//     /*
//     ** very surprised free doesn't force us to specify a size, does malloc
//     keep
//     ** track of the size of allocations for us? Certainly something to
//     ** investigate later.
//     */
//     free(node);
// }
