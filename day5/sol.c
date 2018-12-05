#include <stdio.h>
#include <stdlib.h>

int complementOf(int first, int second)
{
  return (first - second) == 32
    || (second - first) == 32;
}

int part1()
{
  FILE *fp;
  int tmp, cur;
  int stack[50000];

  fp = fopen("input.in", "r");
  cur = 0;
  tmp = fgetc(fp);
  while (tmp > 64) {
    stack[cur] = tmp;
    tmp = fgetc(fp);
    cur++;
    if (cur == 1) {
      continue;
    }
    if (complementOf(stack[cur - 1], stack[cur - 2])) {
      cur -= 2;
    }
  }
  fclose(fp);
  return cur;
}

int part1_without_char(int ch)
{
  FILE *fp;
  int tmp, cur;
  int stack[50000];

  fp = fopen("input.in", "r");
  cur = 0;
  tmp = fgetc(fp);
  while (tmp > 64) {
    if (tmp == ch || tmp == ch + 32) {
      tmp = fgetc(fp);
      continue;
    }
    stack[cur] = tmp;
    tmp = fgetc(fp);
    cur++;
    if (cur == 1) {
      continue;
    }
    if (complementOf(stack[cur - 1], stack[cur - 2])) {
      cur -= 2;
    }
  }
  fclose(fp);
  return cur;
}

int part2()
{
  int m, i, tmp;
  
  m = 50000;
  for (i = 65; i < 90; i++) {
    tmp = part1_without_char(i);
    if (tmp < m) m = tmp;
  }
  return m;
}

int main()
{
  printf("%d\n", part1());
  printf("%d\n", part2());
  return 0;
}
