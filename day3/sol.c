#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

// I figured it would be more efficient is grid is just a global var.
// Turned out no biggie I guess.
int *grid;

/**
 * Reads file line by line to parse and store value into the destination table.
 * I think this can be more modularised for future use.
 */
int process_file(int dest[][5], regex_t *regex)
{
  FILE *fp;
  regmatch_t matches[6];
  char buf[30], tmp[5];
  int ctr, i;

  fp = fopen("input.in", "r");
  ctr = 0;
  while (!feof(fp)) {
    fgets(buf, 30, fp);
    if (regexec(regex, buf, 6, matches, 0) == REG_NOMATCH) {
      break;
    }
    for (i = 1; i < 6; i++) {
      memset(tmp, '\0', sizeof(tmp));
      strncpy(tmp, buf + matches[i].rm_so, matches[i].rm_eo - matches[i].rm_so);
      dest[ctr][i - 1] = atoi(tmp);
    }
    ctr++;
  }
  fclose(fp);
  return ctr;
}

/**
 * `fill_grid` and `check_grid` are the main solving functions for this AOC.
 * 
 * fill_grid basically just fills and adds count to overlapping grids.
 *
 * check_grid returns 1 when an entry's squares are all only filled once, else returns 0.
 */

void fill_grid(int entries[][5], int no_entry)
{
  int i, x, y, w, h;
  for (i = 0; i < no_entry; i++) {
    x = entries[i][1];
    y = entries[i][2];
    w = entries[i][3];
    h = entries[i][4];
    int j, k;
    for (j = 0; j < h; j++) {
      for (k = 0; k < w; k++) {
        grid[1000 * (y + j) + (x + k)]++;
      }
    }
  }
}

int check_grid(int entries[][5], int id)
{
  int x, y, w, h;
  x = entries[id][1];
  y = entries[id][2];
  w = entries[id][3];
  h = entries[id][4];
  int j, k;
  for (j = 0; j < h; j++) {
    for (k = 0; k < w; k++) {
      if (grid[1000 * (y + j) + (x + k)] > 1) return 0;
    }
  }
  return 1;
}

int main()
{
  regex_t regex;
  int entries[1350][5];
  int no_entry;

  if (regcomp(&regex, "#([0-9]+) @ ([0-9]+),([0-9]+): ([0-9]+)x([0-9]+)", REG_EXTENDED) != 0) {
    printf("fail to compile regex\n");
    return 1;
  }

  no_entry = process_file(entries, &regex);

  grid = calloc(1000 * 1000, sizeof(int));
  fill_grid(entries, no_entry);

  /**
   * Here comes the main solving code. 
   * 
   * For part 1: 
   * Just iterate through grid space and count those > 1.
   *
   * For part 2:
   * I go through the filling process again, only this time checking that my grid is only filled once.
   */

  int i, amt;

  // simple loop for part 1
  amt = 0;
  for (i = 0; i < 1000000; i++) {
    if (grid[i] > 1) amt++;
  }
  printf("%d\n", amt);

  // reset and perform part 2
  amt = 0;
  for (i = 0; i < no_entry && !amt; i++) {
    amt = check_grid(entries, i);
  }
  printf("%d\n", i);

  free(grid);
  return 0;
}
