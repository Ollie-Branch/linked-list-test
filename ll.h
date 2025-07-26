#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stddef.h>
#include <stdint.h>

/*
** We use opaque data types so we have the freedom to change backend
** implementation without breaking client code.
*/
typedef struct LinkedList_t LinkedList_t;
typedef struct LinkedList_Node_t LinkedList_Node_t;

// it makes more sense to have node functions above the list functions, because
// the nodes are the atomic components of a list.
LinkedList_Node_t *LL_NodeCreate(size_t data_size);
size_t LL_NodeGetSize(LinkedList_Node_t *node);
void *LL_NodeGetDataField(LinkedList_Node_t *node);
void LL_NodeDelete(LinkedList_Node_t *node);

/*
** I don't yet know a way to make this safer, ideally we'd check types of insert
** elements to ensure they're the same as other elements in the list. We can
** insert arbitrarily-sized and typed data into a list (since nodes just take an
** arbitrary type and its size), but there's no sane use-case for that imo, and
** will probably cause more mistakes in user-side implementation.
**
** I'm thinking, perhaps a better client-facing API could exist by using macro
** magic to create unique node-types for whatever we want to contain in the
** node, but that would be hard to debug for a toy project. If we did this, we'd
** probably have to make most of the LinkedList functions macros as well, idk.
**
** If we were to do that, we'd need to keep the void* for node datatypes
** probably.
*/
void LL_InsertNode(LinkedList_t *list, LinkedList_Node_t *node_to_insert,
                   uint16_t index);
LinkedList_t *LL_Create(LinkedList_Node_t *head);
void LL_Delete(LinkedList_t *list);
void *LL_GetNodeData(LinkedList_t *list, uint16_t index);
uint16_t LL_GetNumNodes(LinkedList_t *list);
void LL_DeleteNode(LinkedList_t *list, uint16_t index);
LinkedList_Node_t *LL_GetTail(LinkedList_t *list);
LinkedList_Node_t *LL_GetHead(LinkedList_t *list);

#endif
