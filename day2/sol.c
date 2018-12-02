#include <stdio.h>
#include <stdlib.h>

int main()
{
  FILE *fp;
  int *counts;
  char *string;
  int twos, threes;

  fp = fopen("input.in", "r");
  twos = 0;
  threes = 0;

  while(fscanf(fp, "%s", string) == 1) {
    int i;

    counts = (int*)calloc(26, sizeof(int));

    for(i = 0; i < 26; i++) {
      counts[(int)string[i] - 97]++;
    }

    for(i = 0; i < 26; i++) {
      if (counts[i] == 2) {
        twos++;
        break;
      }
    }

    for(i = 0; i < 26; i++) {
      if (counts[i] == 3) {
        threes++;
        break;
      }
    }
    free(counts);
  }
  printf("%d\n", twos * threes);
  fclose(fp);
}
