#include <stdio.h>

static int heap[100];
static int size = 0;

int heapDelete()
{
  if (size == 0) {
    fprintf(stderr, "Error: heap is empty\n");
    return -1;
  }

  int maxValue = heap[0];

  size--;
  heap[0] = heap[size];

  int i = 0;
  while (1) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int largest = i;

    if (left < size && heap[left] > heap[largest])
      largest = left;

    if (right < size && heap[right] > heap[largest])
      largest = right;

    if (largest == i)
      break;

    int temp = heap[i];
    heap[i] = heap[largest];
    heap[largest] = temp;

    i = largest;
  }

  return maxValue;
}

void heapAdd(int thing2add)
{
  if (size >= 100) {
    fprintf(stderr, "Error: heap is full\n");
    return;
  }

  heap[size] = thing2add;
  int i = size;
  size++;

  while (i > 0) {
    int parent = (i - 1) / 2;

    if (heap[parent] >= heap[i])
      break;

    int temp = heap[parent];
    heap[parent] = heap[i];
    heap[i] = temp;

    i = parent;
  }
}

int heapSize()
{
  return size;
}

int heapItem(int index)
{
  return heap[index];
}
