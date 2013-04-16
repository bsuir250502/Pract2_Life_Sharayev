#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int present;
    int next;
} map_t;



map_t **filling_map(int *, int *);

int main()
{
    int size_x = 0, size_y = 0;
    map_t **map;
    map = filling_map(&size_x, &size_y);

    return 0;
}

map_t **filling_map(int *size_x, int *size_y)
{
    int i, j;
    char input_buffer[128], *endptr;
    map_t **map;
    FILE *fp = fopen("input.in", "r");

    fgets(input_buffer, strlen(input_buffer), fp);
    *size_x = strtol(input_buffer, &endptr, 10);
    fgets(input_buffer, strlen(input_buffer), fp);
    *size_y = strtol(input_buffer, &endptr, 10);
    map = (map_t **) malloc((*size_x) * (*size_y) * sizeof(**map));
    if (!map) {
        printf("Memory isn't allocated");
        exit(1);
    }
    for(i = 0; i < *size_y; i++) {
        map[i] = (map_t *) malloc(sizeof(*map));
        if (!map[i]) {
            printf("Memory isn't allocated");
            exit(1);
        }
    }
    for (i = 0; i < *size_y; i++) {
        for (j = 0; j < *size_x; j++) {
            map[i][j].present = getc(fp) - '0';
        }
        getc(fp);
    }

    fclose(fp);
    return map;
}
