struct node;

typedef struct Queue_prio {
  struct node *head;
}Queue_prio;

typedef struct node {
  char *name;
  int priority;
  struct node *next;
}Node;