#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

extern int pop();
extern void push(int);
extern int isEmpty();

extern void heapAdd(int);
extern int heapDelete();
extern int heapSize();
extern int heapItem(int);

void printXML(int index, int size)
{
  if (index >= size)
    return;

  printf("<node id=\"%d\">", heapItem(index));

  if (2 * index + 1 < size)
    printXML(2 * index + 1, size);

  if (2 * index + 2 < size)
    printXML(2 * index + 2, size);

  printf("</node>");
}

int main(int argc, char * argv[])
{
  int value;

  while (scanf("%d", &value) != EOF) {
    fprintf(stderr, "READING INPUT: %d\n", value);
    heapAdd(value);
  }

  printXML(0, heapSize());
  printf("\n");

  while (heapSize() > 0) {
    value = heapDelete();
    printf("%d\n", value);
    push(value);
  }

  while (!isEmpty()) {
    printf("%d\n", pop());
  }

  exit(0);
}
