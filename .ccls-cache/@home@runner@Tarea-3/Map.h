#ifndef MAP_H
#define MAP_H
#include <stdbool.h>
typedef struct Map Map;

Map * createMap(int (*is_equal)(void* key1, void* key2));

void insertMap(Map * map, void * key, void * value);

void * eraseMap(Map * map, void * key);

void * searchMap(Map * map, void * key);

void * firstMap(Map * map);

void * nextMap(Map * map);

void setSortFunction(Map* map, int (*lower_than)(void* key1, void* key2));

int sizeMap(Map * map);

void **mapToArray(Map * map);

void * clearMap(Map * map);

bool hasKey(Map* map, void* key);

#endif /* MAP_h */

