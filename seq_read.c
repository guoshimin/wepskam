#include <stdio.h>
#include <stdlib.h>
#include <x86intrin.h>

#define NPAD 0

struct l {
  void *n;
  //long int pad[NPAD];
};

unsigned long long run(struct l* array, int num_passes) {
  struct l* curr;
  unsigned long long i;
  unsigned long long start = __rdtsc(), end;
  for (i = 0; i < num_passes; ++i) {
    for (curr = array; curr; curr = (struct l*)curr->n) {}
  }
  end = __rdtsc();
  return end - start;
}


int main(int argc, char* argv[]) {
  unsigned long long num_entries, i, cycles, wss;
  unsigned long long wss_exponent = atoi(argv[1]);
  unsigned long long struct_size = atoi(argv[2]);
  char* array;
  wss = 1L << wss_exponent;
  num_entries = wss / struct_size;
  array = (char *) malloc(struct_size * num_entries);
  for (i = 0; i < num_entries - 1; ++i) {
    ((struct l*)(array + i * struct_size))->n = array + (i + 1) * struct_size;
  }
  ((struct l*) (array + (num_entries - 1)*struct_size))->n = NULL;
  int num_passes = (1L<<28) / num_entries;
  num_passes = num_passes > 0 ? num_passes : 1;
  cycles = run((struct l*)array, num_passes);
  printf("cycles = %llu, cycles/op = %lf\n", cycles, (double)cycles/(1 << 28));
  return 0;
}
