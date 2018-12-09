#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  struct node *next;
  struct node *prev;
  int val;
} node;

void insert_after(node* target, node* src)
{
  node* newnext = target->next;

  target->next = src;
  src->prev = target;

  src->next = newnext;
  newnext->prev = src;
}

node* handle_x(node* cur, int player, unsigned int* scores) {
  int i;
  node* ptr = cur;
  for (i = 0; i < 7; i++) {
    ptr = ptr->prev;
  }
  scores[player] += ptr->val;
  (ptr->prev)->next = ptr->next;
  (ptr->next)->prev = ptr->prev;
  node* ret = ptr->next;
  free(ptr);
  return ret;
}

int main()
{
  int n_players, last;
  int i, p;
  node *cur, *newnode;

  cur = NULL;
  scanf("%d players; last marble is worth %d points", &n_players, &last);

  unsigned int scores[n_players];
  for (i = 0; i < n_players; i++) {
    scores[i] = 0;
  }

  // initialise first (0th) node
  cur = (node*)malloc(sizeof(node));
  cur->next = cur;
  cur->prev = cur;
  cur->val = 0;
  
  p = 0;
  for (i = 1; i <= last; i++) {
    if (i % 23 == 0) {
      scores[p] += i;
      cur = handle_x(cur, p, scores);
    } else {
      newnode = (node*)malloc(sizeof(node));
      newnode->val = i;
      insert_after(cur->next, newnode);
      cur = newnode;
    }
    p = (p + 1) % n_players;
  }

  unsigned int tmp = 0;
  for (i = 0; i < n_players; i++) {
    if (scores[i] > tmp)
      tmp = scores[i];
  }

  printf("%u\n", tmp);

  // FREE!!!
  (cur->prev)->next = NULL;
  while(cur != NULL) {
    newnode = cur;
    cur = cur->next;
    free(newnode);
  }
  return 0;
}
