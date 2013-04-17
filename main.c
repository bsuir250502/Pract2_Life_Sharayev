#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE( x ) (sizeof(x)/sizeof(*x))

typedef struct {
    int present;
    int next;
} map_t;

map_t **filling_map(int *, int *, int *);
int free_memory(map_t **, int);
int display_map(map_t **, int, int);

int main()
{
    int i, sizeX = 0, sizeY = 0, gen_num = 0;
    map_t **map;
    map = filling_map(&sizeX, &sizeY, &gen_num);
    display_map(map, sizeX, sizeY);
    for(i = 0; i < gen_num; i++) {
        printf("something")
    }

    free_memory(map, sizeY);
    if (!map) {
        printf("Memory free\n");
        exit(1);
    }
    return 0;
}

map_t **filling_map(int *sizeX, int *sizeY, int *gen_num)
{
    int i, j;
    char input_buffer[128];
    map_t **map;
    FILE *fp = fopen("input.in", "r");

    fgets(input_buffer, SIZE(input_buffer), fp);
    *sizeX = strtol(input_buffer, NULL, 10);
    fgets(input_buffer, SIZE(input_buffer), fp);
    *sizeY = strtol(input_buffer, NULL, 10);
    fgets(input_buffer, SIZE(input_buffer), fp);
    *gen_num = *sizeY = strtol(input_buffer, NULL, 10);

    if (!(map = (map_t **) calloc(*sizeY, sizeof(**map)) )) {
        printf("Memory isn't allocated at the first calloc\n");
        exit(1);
    }
    for(i = 0; i < *sizeY; i++) { 
        if (!(map[i] = (map_t *) calloc(*sizeX, sizeof(*map)) )) {
            printf("Memory isn't allocated\n");
            exit(1);
        }
    }
    for (i = 0; i < *sizeY; i++) {
        for (j = 0; j < *sizeX; j++) {
            map[i][j].present = getc(fp) - '0';
        }
        getc(fp);
    }

    fclose(fp);
    return map;
}

int free_memory(map_t **map, int sizeY)
{
    int i;
    for(i = 0; i < sizeY; i++) {
        free(map[i]);
    }
    free(map);
    return 0;
}

int display_map(map_t **map, int sizeX, int sizeY)
{
    int i, j;
    for (i = 0; i < sizeY; i++) {
        for (j = 0; j < sizeX; j++) {
            printf("%d", map[i][j].present);
        }
        puts("");
    }

    return 0;
}
