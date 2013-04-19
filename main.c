#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_X 16
#define SIZE_Y 16
#define SIZE( x ) (sizeof(x)/sizeof(*x))

typedef struct {
    int present;
    int next;
} map_t;

map_t **filling_map(int *);
int free_memory(map_t **, int);
int display_map(map_t **);
int change_generation(map_t **);
int check_cell(map_t **, int, int);
int copy_map(map_t **);

int main()
{
    int i, gen_num = 0;
    map_t **map;
    map = filling_map(&gen_num);
    for (i = 0; i < gen_num; i++) {
        change_generation(map);
    }
    display_map(map);
    free_memory(map, SIZE_Y);
    return 0;
}

map_t **filling_map(int *gen_num)
{
    int i, j;
    char input_buffer[128];
    map_t **map;
    FILE *fp = fopen("input.in", "r");

    fgets(input_buffer, SIZE(input_buffer), fp);
    *gen_num = strtol(input_buffer, NULL, 10);

    printf("sizeX = %d, sizeY = %d, generation number = %d\n", SIZE_X,
           SIZE_Y, *gen_num);

    if (!(map = (map_t **) calloc(SIZE_Y, sizeof(**map)))) {
        printf("Memory isn't allocated at the first calloc\n");
        exit(1);
    }
    for (i = 0; i < SIZE_Y; i++) {
        if (!(map[i] = (map_t *) calloc(SIZE_X, sizeof(*map)))) {
            printf("Memory isn't allocated\n");
            exit(1);
        }
    }
    for (i = 0; i < SIZE_Y; i++) {
        for (j = 0; j < SIZE_X; j++) {
            map[i][j].present = getc(fp) - '0';
        }
        getc(fp);
    }

    fclose(fp);
    return map;
}

int free_memory(map_t ** array, int size)
{
    int i;
    for (i = 0; i < size; i++) {
        free(array[i]);
    }
    free(array);
    return 0;
}

int display_map(map_t ** map)
{
    int i, j;
    for (i = 0; i < SIZE_Y; i++) {
        for (j = 0; j < SIZE_X; j++) {
            printf("%d", map[i][j].present);
        }
        puts("");
    }

    return 0;
}

int change_generation(map_t ** map)
{
    int i, j;

    for (i = 0; i < SIZE_Y; i++) {
        for (j = 0; j < SIZE_X; j++) {
            map[i][j].next = check_cell(map, i, j);
        }
    }

    copy_map(map);
    return 0;
}

int check_cell(map_t ** map, int i, int j)
{
    int left = j - 1, right = j + 1, top = i - 1, bottom = i + 1, amount;
    if(i == 0) {
        top = SIZE_Y;
        bottom = 1;
    }
    else if(i == SIZE_Y) {
        top = SIZE_Y - 1;
        bottom = 0;
    }

   if(j == 0) {
        left = SIZE_X;
        right = 1;
    }
    else if (j == SIZE_X) {
        left = SIZE_X - 1;
        right = 0;
    }

    amount =
        map[top][left].present + map[top][j].present +
        map[top][right].present + map[i][left].present +
        map[i][right].present + map[bottom][left].present +
        map[bottom][j].present + map[bottom][right].present;
    if (!map[i][j].present && amount == 3) {
        return 1;
    } else {
        if (amount > 3 || amount < 2) {
            return 0;
        }
    }


    return 1;
}

int copy_map(map_t ** map)
{
    int i, j;
    for (i = 0; i < SIZE_Y; i++) {
        for (j = 0; j < SIZE_X; j++) {
            map[i][j].present = map[i][j].next;
        }
    }

    return 0;
}
