#include <stdio.h>
#include <stdlib.h>

void init(int **mat)
{
  FILE *fp;
  char buf[5];
  int source, dest;

  fp = fopen("input.in", "r");
  while(!feof(fp)) {
    fgets(buf, 5, fp);
    source = buf[0] - 65;
    dest = buf[2] - 65;
    mat[source][dest] = 1;
  }
  fclose(fp);
}

void printMat(int **adjMat)
{
  int i, j;
  for (i = 0; i < 26; i++) {
    for (j = 0; j < 26; j++) {
      printf("%d ", adjMat[i][j]);
    }
    printf("\n");
  }
}

int findNext(int **adjMat, int *taken, int n)
{
  int i, j;
  int invalid;
  for (i = 0; i < 26; i++) {
    invalid = 0;
    for (j = 0; j < 26; j++) {
      if (adjMat[j][i]) {
        invalid = 1;
        break;
      }
    }
    for (j = 0; j < n; j++) {
      if (taken[j] == i) {
        invalid = 1;
        break;
      }
    }
    if (!invalid) break;
  }
  if (i >= 26) {
    return -1;
  }
  taken[n] = i;
  return i;
}

void clearNext(int **adjMat, int target)
{
  int i;
  for (i = 0; i < 26; i++) {
    adjMat[target][i] = 0;
  }
}

// checks if a work is completed in this step so the adjacency matrix can be updated
void check_if_done(
    int **workDone,
    int *to_free,
    int *ctr,
    int worker,
    int time)
{
  if (workDone[worker][time + 1] < 0) {
    to_free[worker] = workDone[worker][time];
    *ctr = *ctr + 1;
  }
}

void free_after_time(int **adj_mat, int to_free[5]) {
  int i, j;
  for (i = 0; i < 5; i++) {
    if (to_free[i] >= 0) {
      clearNext(adj_mat, to_free[i]);
    }
    to_free[i] = -1;
  }
}

// assigns work to a free worker
void assign_work(
    int **work_done,
    int **adj_mat,
    int *jobs_taken,
    int *taken_amt, 
    int worker, 
    int time)
{
  int i, job;
  job = findNext(adj_mat, jobs_taken, *taken_amt);
  if (job < 0) return;
  for (i = 0; i < time + job + 61; i++)
    work_done[worker][i] = job;
  *taken_amt += 1;
}

int main()
{
  int *adjMat[26];
  int *taken;
  int i, j, k;
  int next;

  taken = calloc(26, sizeof(int));
  for (i = 0; i < 26; i++) {
    adjMat[i] = calloc(26, sizeof(int));
  }

  //part 1
  init(adjMat);

#ifdef DEBUG
  printMat(adjMat);
#endif

  for (i = 0; i < 26; i++) {
    next = findNext(adjMat, taken, i);
    clearNext(adjMat, next);
    printf("%c", next + 65);
#ifdef DEBUG
    printMat(adjMat);
#endif
  }

  printf("\n");
  free(taken);

  // part 2
  taken = calloc(26, sizeof(int));
  init(adjMat);
  int *workDone[5], tasks_assigned, all_done, to_free[5];
  for (i = 0; i < 5; i++) {
    to_free[i] = -1;
    workDone[i] = calloc(2000, sizeof(int));
    for (j = 0; j < 2000; j++) {
      workDone[i][j] = -1;
    }
  }

  tasks_assigned = 0;
  all_done = 0;
  for (i = 0; i < 1000; i++) { 
    if (all_done >= 26) {
      printf("%d\n", i);
      break;
    }
    for (j = 0; j < 5; j++) {
      if (workDone[j][i] >= 0) {
        check_if_done(workDone, to_free, &all_done, j, i);
      } else {
        assign_work(workDone, adjMat, taken, &tasks_assigned, j, i);
      }
    }
#ifdef DEBUG
    for (j = 0; j < 5; j++) {
      printf("%d ", workDone[j][i]);
    }
    printf("\n");
#endif
    free_after_time(adjMat, to_free);
  }
  
  free(taken);
  for (i = 0; i < 26; i++) {
    free(adjMat[i]);
  }

  return 0;
}

