#include <stdio.h>

/* Bubble sort: Ptr version */
void bubble_b(int *data, int count) {
  int *i, *last;
  for (last = data + count - 1; last > data; last--) {
    for (i = data; i < last; i++)
      if (*(i+1) < *i) {
        /* Swap adjacent elements */
        int t = *(i+1);
        *(i+1) = *i;
        *i = t;
      }
  }
}

int main(int argc, char *argv[]) {
    int data[5] = {
        3, 1, 5, 2, 4
    };

    bubble_b(data, 5);

    int i = 0;
    for (i = 0; i < 5; ++i) {
        printf("data[%d]=%d\n", i, data[i]);
    }

    return 0;
}