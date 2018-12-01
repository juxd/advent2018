#include <stdio.h>
#include <stdlib.h>

int search_for(int* head, int i)
{
  if (head[i]) return 1;
  head[i] = 1;
  return 0;
}

int main()
{
  FILE *fp;
  int i = 0;
  int doing = 1;
  int d;
  int* track;
  int* head;

  fp = fopen("input.in", "r");
  head = (int*)malloc(sizeof(int) * 400000);

  while(doing) {
    while(fscanf(fp, "%d", &d) == 1) {
      i += d;
      if (search_for(head, i + 200000)) {
        doing = 0;
        break;
      }
    }
    fseek(fp, 0, SEEK_SET);
  }
  printf("%d\n", i);
  fclose(fp);
  return 0;
}
