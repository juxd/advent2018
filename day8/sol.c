#include <stdio.h>
#include <stdlib.h>

int sum;
FILE* fp;

typedef struct node {
  struct node *children;
  int *meta_info;
  int value;
} node;

node* parse_node()
{
  int ch, meta;
  int i, tmp;
  int metasum = 0;
  fscanf(fp, "%d %d ", &ch, &meta);
  node* newnode = malloc(sizeof(node));
  newnode->children = calloc(ch + 1, sizeof(node));
  newnode->meta_info = calloc(meta, sizeof(int));

  for (i = 0; i < ch; i++) {
    newnode->children[i + 1] = *(parse_node());
  }

  for (i = 0; i < meta; i++) {
    fscanf(fp, "%d", &tmp);
    newnode->meta_info[i] = tmp;
    metasum += tmp;
  }

  if (ch > 0) {
    newnode->value = 0;
    for (i = 0; i < meta; i++) {
      int idx = newnode->meta_info[i];
      if (idx > ch) continue;
      newnode->value += (newnode->children[idx]).value;
    }
  } else {
    newnode->value = metasum;
  }

  sum += metasum;
  return newnode;
}

int main()
{
  fp = fopen("input.in", "r");
  sum = 0;
  node* root = parse_node();
  fclose(fp);
  printf("%d\n", sum);
  printf("%d\n", root->value);
  return 0;
}
