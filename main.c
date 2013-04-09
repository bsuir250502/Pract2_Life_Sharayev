#include <stdafx.h>
#include <stdlib.h>



int main() {
  int i, j, size_x, size_y, *map;
  char input_buffer[128], *endptr;
  FILE *fp = fopen("input.in", "r");
  fgets(input_buffer, strlen(input_buffer), fp);
  size_x = strtol(input_buffer, &endptr, 10);
  fgets(input_buffer, strlen(input_buffer), fp);
  size_y = strtol(input_buffer, &endptr, 10);
  map = (int *)malloc(size_x * size_y * 2 * sizeof(int));


  fclose(fp);
  return 0;
}
