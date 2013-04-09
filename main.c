#include <stdafx.h>
#include <stdlib.h>

int* filling_map(int *, int, int);

int main() {
  int i, j, size_x = 0, size_y = 0, *map;
  map = filling_map(map, &size_x, &size_y);
  


  
  return 0;
}

int* filling_map(int *map, int size_x, int size_y) {
  int i, j;
  char input_buffer[128], *endptr;
  FILE *fp = fopen("input.in", "r");
  fgets(input_buffer, strlen(input_buffer), fp);
  size_x = strtol(input_buffer, &endptr, 10);
  fgets(input_buffer, strlen(input_buffer), fp);
  size_y = strtol(input_buffer, &endptr, 10);
  map = (int *) malloc(size_x * size_y * sizeof(int));
  for(i = 0; i < size_y; i++) {
    for(j = 0; j < size_x; j++) {
      map[i][j]getc(fp)-48;
    }
    getc(fp);
  }

  
  
  fclose(fp);
  return map; 
} 
