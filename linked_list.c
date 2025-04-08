#include "linked_list.h"

#include <stdlib.h>

struct list_node *new_node(size_t value) { 
  struct list_node *malNode = malloc(sizeof(struct list_node));
  malNode->value = value;
  malNode->next = NULL;
  
  return malNode;
}

void insert_at_head(struct linked_list *list, size_t value) {

struct list_node *newHead = new_node(value);
newHead->next = list->head;
list->head = newHead;
}

void insert_at_tail(struct linked_list *list, size_t value) {
  // struct list_node *newNode = new_node(value);
  
  struct list_node *currentNode = list->head; 
  if (list->head == NULL) {
    
  }
  while (currentNode->next != NULL) {
    currentNode = currentNode->next;
  }
  currentNode->next = new_node(value);
}

size_t remove_from_head(struct linked_list *list) { 
  size_t retVal = list->head->value;
  struct list_node *temp = list->head->next;
  free(list->head);
  list->head = temp;

  return retVal;
}

size_t remove_from_tail(struct linked_list *list) {
  struct list_node *current = list->head;
  size_t retVal = 0;
  struct list_node *previous = NULL;
  if (current == NULL) {
    return retVal;
  }
  else if (current->next == NULL) {
    retVal = current->value;
    return retVal;
  }
  while (current->next != NULL)
  {
    previous = current;
    current = current->next;
  }
  retVal = current->value;
  previous->next = NULL;
  free(current);
  
  return retVal;
}

void free_list(struct linked_list list) {
struct list_node *current = list.head;
struct list_node *next = NULL;

while (current != NULL)
{
  next = current->next;
  free(current);
  current = next;
}

}

// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
  fprintf(fp, "[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
    fprintf(fp, "%zu ", cur->value);
  }
  fprintf(fp, "]\n");
}
