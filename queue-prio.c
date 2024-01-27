/* #include "queue-prio.h" */
#include "queue-prio-datastructure.h"
#include "queue-prio-list-datastructure.h"

#include <stdlib.h>
#include <string.h>

unsigned short init_queue(Queue_prio *const queue_prio) { 
  if(queue_prio == NULL)
    return 0;
  
  queue_prio->head = NULL;
  
  return 1;
}

unsigned short en_queue(Queue_prio *const queue_prio, const
			char new_element[], unsigned int priority) {

  Node *ptr = NULL;
  Node *spaceNode = NULL;
  Node *prev = NULL;
  char *e = NULL;
  int insertFound = 0;

  if(queue_prio == NULL)
    return 0;

  e = malloc(strlen(new_element) + 1);

  if (e == NULL) {
    return 0;
  }
  
  strcpy(e, new_element);

  spaceNode = malloc(sizeof(Node));

  if (spaceNode == NULL) { 
    free(e);
    return 0;
  }
  
  spaceNode->name = e;
  spaceNode->priority = priority;
  spaceNode->next = NULL;

  if(queue_prio->head == NULL) {
    queue_prio->head = spaceNode;
    return 1;
  }

  ptr = queue_prio->head;

  while (ptr != NULL && !insertFound) {

    if (ptr->priority == priority) {

      free(e);
      free(spaceNode);

      
      return 0;  
    } 
    if (ptr->priority < priority) {
      insertFound = 1;
    } else {
      prev = ptr;
      ptr = ptr->next;
    }
  }

  if (prev == NULL) {
    spaceNode->next = queue_prio->head;
    queue_prio->head = spaceNode;
  } else {
    spaceNode->next = ptr;
    prev->next = spaceNode;
  }
  
  return 1;
}

short has_no_elements(const Queue_prio *const queue_prio) {

  if(queue_prio == NULL)
    return -1;

  if(queue_prio->head == NULL)
    return 1;

  return 0;
}

short size(const Queue_prio *const queue_prio) {

  short count = 0;
  Node *ptr = NULL;
  
  if(queue_prio == NULL)
    return -1;

  if(queue_prio->head == NULL) {
    return 0;
  }

  ptr = queue_prio->head;

  while(ptr != NULL) {
    
    count++;
    ptr = ptr-> next;
  }
  
  return count;
}

char *peek(const Queue_prio *const queue_prio) {

  Node *ptr = NULL;
  char *nameCopy = NULL;
  
  if(queue_prio == NULL)
    return NULL;

  if(queue_prio->head == NULL) {
    return NULL;
  }

  ptr = queue_prio->head;
  
  nameCopy = malloc(strlen(ptr->name) + 1);
  strcpy(nameCopy, ptr->name);

  return nameCopy;
}

char *de_queue(Queue_prio *const queue_prio) {
  Node *ptr = NULL;
  char *name = NULL;

  if(queue_prio == NULL)
    return NULL;

  if(queue_prio->head == NULL)
    return NULL;

  ptr = queue_prio->head;
  name = ptr->name;  
  queue_prio->head = ptr->next; 

  free(ptr);
  
  return name; 
}

char **all_element_names(const Queue_prio *queue_prio) {

  Node *ptr = NULL;

  int index = NULL;

  char **arrNames = NULL;

  if(queue_prio == NULL)
    return NULL;

  arrNames  = malloc(sizeof(char *) * (size(queue_prio) + 1));

  arrNames[size(queue_prio)] = NULL;

  if(size(queue_prio) == 0)
    return arrNames;

  index = 0;

  ptr = queue_prio -> head;

  while(ptr != NULL) {

    arrNames[index] = malloc(strlen(ptr->name) + 1);
    strcpy(arrNames[index], ptr->name);

    index++;

    ptr = ptr->next;
  }

  return arrNames;
}

unsigned short free_name_list(char *name_list[]) {
  int ind = 0;
    
  if (name_list == NULL) {
    return 0;
  }

  while (name_list[ind] != NULL) {
    free(name_list[ind]);
    ind++;
  }

  free(name_list);

  return 1;
}

unsigned short clear_queue_prio(Queue_prio *const queue_prio) {
  Node *prev = NULL;
  Node *curr = NULL;

  if (queue_prio == NULL) {
    return 0;
  }

  curr = queue_prio->head;

  while (curr != NULL) {
    if (curr->name != NULL) {
      free(curr->name);
    }

    prev = curr;
    curr = curr->next;

    free(prev);
  }

  prev = NULL;
  curr = NULL;

  queue_prio->head = NULL;

  return 1;
}

int get_priority(const Queue_prio *const queue_prio, const char element[]) {
  Node *curr = NULL;
  int max = -1;
  
  if(queue_prio == NULL || element == NULL)
    return -1;

  curr = queue_prio->head;

  while(curr != NULL) {
    if(strcmp(curr->name, element) == 0) {
      if(curr->priority > max) {
        max = curr->priority;
      }
    }

    curr = curr->next;
  }

  return max;
}

unsigned int remove_elements_between(Queue_prio *const queue_prio, unsigned int low, unsigned int high) {
  Node *prev = NULL;
  Node *curr = queue_prio->head;
  unsigned int count = 0;

  if (queue_prio == NULL) {
    return 0;
  }

  while (curr != NULL) {
    if (curr->priority >= low && curr->priority <= high) {
      Node *temp = curr;
      
      if (prev == NULL) {
        queue_prio->head = curr->next;
      } else {
        prev->next = curr->next;
      }

      curr = curr->next;

      free(temp->name);
      free(temp);

      count++;
    } else {
      prev = curr;
      curr = curr->next;
    }
  }

  return count;
}

unsigned int change_priority(Queue_prio *const queue_prio, const char element[], unsigned int new_priority) {
  Node *curr = NULL;
  unsigned int found = 0;
  
  if (queue_prio == NULL || element == NULL) {
    return 0;
  }

  curr = queue_prio->head;
  while (curr != NULL) {
    if (curr->priority == new_priority) {
      return 0;
    }
    curr = curr->next;
  }

  curr = queue_prio->head;
  while (curr != NULL) {
    if (strcmp(curr->name, element) == 0) {
      if (found) {
        return 0;
      } else {
        found = 1;
      }
    }
    curr = curr->next;
  }

  if (found) {
    curr = queue_prio->head;
    while (curr != NULL) {
      if (strcmp(curr->name, element) == 0) {
        curr->priority = new_priority;
        return 1;
      }
      curr = curr->next;
    }
  }

  return 0;
}