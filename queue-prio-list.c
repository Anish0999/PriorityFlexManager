#include "queue-prio-datastructure.h"
#include "queue-prio-list-datastructure.h"
#include <stdlib.h>
#include <string.h>

short initializeQueueList(Queue_prio_list *const queue_prio_list) {
  if(queue_prio_list == NULL)
    return 0;

  queue_prio_list->head = NULL;

  return 1;
}

short addPriorityQueue(Queue_prio_list *const queue_prio_list, const char new_queue_name[]) {
  Queue_prio *ptr = NULL;
  node_list *temp = NULL;
  node_list *new_node = NULL;
  node_list *last = NULL;
  
  if(queue_prio_list == NULL || new_queue_name == NULL)
    return 0;

  temp = queue_prio_list->head;
  
  while(temp != NULL) {
    if(strcmp(temp->name, new_queue_name) == 0)
      return 0;

    temp = temp->next;
  }
  
  ptr = malloc(sizeof(Queue_prio));
  
  if(!ptr)
    return 0;
  
  ptr->head = NULL;

  new_node = malloc(sizeof(node_list));

  new_node->name = malloc(strlen(new_queue_name) + 1);
  strcpy(new_node->name, new_queue_name);

  new_node->qp = ptr;
  new_node->next = NULL;

  if(queue_prio_list->head == NULL) {
    queue_prio_list->head = new_node;
  }
  else { 
    last = queue_prio_list->head;
    while(last->next != NULL)
      last = last->next;

    last->next = new_node;
  }
  
  return 1;
}

short countQueues(const Queue_prio_list *const queue_prio_list) {
  node_list *ptr = NULL;
  short count;
  
  if(queue_prio_list == NULL)
    return -1;

  count = 0;
  ptr = queue_prio_list->head;

  while(ptr != NULL) {
    if(ptr->qp != NULL)
      count++;
    
    ptr = ptr->next;
  }

  return count;
}

Queue_prio *fetchQueue(const Queue_prio_list *const queue_prio_list, const char queue_name[]) {
  Queue_prio *queue_ptr = NULL;
  node_list *ptr = NULL;
  
  if(queue_prio_list == NULL || queue_name == NULL)
    return NULL;

  ptr = queue_prio_list->head;
  
  while(ptr != NULL) {
    if(strcmp(ptr->name, queue_name) == 0) {
      return queue_ptr = ptr-> qp;
    }
    ptr = ptr->next;
  }
  
  return NULL;
}

short deleteQueue(Queue_prio_list *const queue_prio_list, const char queue_to_remove[]) {
  node_list *curr = NULL;
  node_list *prev = NULL;

  if (queue_prio_list == NULL || queue_to_remove == NULL) {
    return -1;
  }

  curr = queue_prio_list->head;

  while (curr != NULL) {
    if (strcmp(curr->name, queue_to_remove) == 0) {
      clear_queue_prio(curr->qp);
      free(curr->qp);
      free(curr->name);

      if (prev == NULL) {
	queue_prio_list->head = curr->next;
      } else {
	prev->next = curr->next;
      }
      
      free(curr);
      return 1;
    }

    prev = curr;
    curr = curr->next;
  }

  return 0;
}

unsigned short emptyQueueList(Queue_prio_list *const queue_prio_list) {
  node_list *curr = NULL;
  node_list *prev = NULL;

  if (queue_prio_list == NULL) {
    return 0;
  }

  curr = queue_prio_list->head;

  while (curr != NULL) {
    prev = curr;
    curr = curr->next;

    clear_queue_prio(prev->qp);
    free(prev->qp);
    if (prev->name != NULL) {
      free(prev->name);
    }
    free(prev);
  }

  queue_prio_list->head = NULL;

  return 1;
}