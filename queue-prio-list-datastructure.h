struct nodeList;

typedef struct queue_list {
  struct nodeList *head;
}Queue_prio_list;

typedef struct nodeList{
  char *name;
  struct nodeList *next;
  struct Queue_prio *qp;
}node_list;