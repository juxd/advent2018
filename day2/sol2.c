#include <stdio.h>
#include <stdlib.h>

char *string;

char get_char(char *string, int index, int offset) {
  return *(string + index * 30 + offset);
}

int main()
{
  FILE *fp;
  int i;

  string = (char*)malloc(250 * 30 * sizeof(char));
  // pre-processing file
  fp = fopen("input.in", "r");
  i = 0;
  while (fscanf(fp, "%s", string + i * 30) == 1) {
    i++;
  }
  fclose(fp);

  for (i = 0; i < 250; i++) {
    int j;
    int *dup;

    for (j = i; j < 250; j++) {
      int k;
      int count = 0;
      dup = (int*)calloc(26, sizeof(int));
      for (k = 0; k < 26; k++) {
        if (get_char(string, i, k) == get_char(string, j, k)) {
          dup[k] = 1;
          count++;
        }
      }
      if (count == 25) {
        for (k = 0; k < 26; k++) {
          if (dup[k]) printf("%c", get_char(string, i, k));
        }
        printf("\n");
      }
      free(dup);
    }
  }
  free(string);

  return 0;
}
