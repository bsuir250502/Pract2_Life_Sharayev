#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE( x ) (sizeof(x)/sizeof(*x))

typedef struct {
    int present;
    int next;
} map_t;

typedef struct {
    int x;
    int y;
} msize_t;

map_t **filling_map(int *, msize_t *);
int free_memory(map_t **, msize_t);
int display_map(map_t **, msize_t);
int change_generation(map_t **, msize_t);
int check_cell(map_t **,msize_t, int, int);
int copy_map(map_t **, msize_t);

int main()
{
    int i, gen_num = 0;
    map_t **map;
    msize_t size;
    map = filling_map(&gen_num, &size);
    display_map(map, size);
    for (i = 0; i < gen_num; i++) {
        change_generation(map, size);
    }
    display_map(map, size);
    free_memory(map, size);
    return 0;
}

map_t **filling_map(int *gen_num, msize_t *size)
{
    int i, j;
    char input_buffer[128];
    map_t **map;
    FILE *fp = fopen("input.in", "r");

    fgets(input_buffer, SIZE(input_buffer), fp);
    size->x = strtol(input_buffer, NULL, 10);
    fgets(input_buffer, SIZE(input_buffer), fp);
    size->y = strtol(input_buffer, NULL, 10);
    fgets(input_buffer, SIZE(input_buffer), fp);
    *gen_num = strtol(input_buffer, NULL, 10);

    printf("sizeX = %d, sizeY = %d, generation number = %d\n", size->x,
           size->y, *gen_num);

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

int free_memory(map_t ** array, msize_t size)
{
    int i;
    for (i = 0; i < size.y; i++) {
        free(array[i]);
    }
    free(array);
    return 0;
}

int display_map(map_t ** map, msize_t size)
{
    int i, j;
    for (i = 0; i < size.y; i++) {
        for (j = 0; j < size.x; j++) {
            printf("%d", map[i][j].present);
        }
        puts("");
    }

    return 0;
}

int change_generation(map_t ** map, msize_t size)
{
    int i, j;

    for (i = 0; i < size.y; i++) {
        for (j = 0; j < size.x; j++) {
            map[i][j].next = check_cell(map, size, i, j);
        }
    }

    copy_map(map, size);
    return 0;
}

int check_cell(map_t ** map, msize_t size, int i, int j)
{
    int left = j - 1, right = j + 1, top = i - 1, bottom = i + 1, amount;
    if(i == 0) {
        top = size.y;
        bottom = 1;
    }
    else if(i == size.y) {
        top = size.y - 1;
        bottom = 0;
    }

   if(j == 0) {
        left = size.x;
        right = 1;
    }
    else if (j == size.x) {
        left = size.x - 1;
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

int copy_map(map_t ** map, msize_t size)
{
    int i, j;
    for (i = 0; i < size.y; i++) {
        for (j = 0; j < size.x; j++) {
            map[i][j].present = map[i][j].next;
        }
    }

    return 0;
}
