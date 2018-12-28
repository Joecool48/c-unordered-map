#ifndef MAP_H
#define MAP_H

#include<stdlib.h>

typedef int MapKey;
typedef int MapValue;
size_t hash (MapKey key, size_t size);
size_t hash2 (MapKey key, size_t size);

#define LOADFACTOR .7

typedef char bool;
#define false 0
#define true 1

typedef struct {
    MapKey key;
    MapValue value;
} MapPair;

typedef struct {
    MapPair ** arr;
    bool * shouldProbe;
    size_t maxSize;
    size_t numElems;

} Map;

static const size_t primes[] = {
    17ul, 29ul, 37ul, 53ul, 67ul, 79ul, 97ul, 131ul, 193ul, 257ul, 389ul,
    521ul, 769ul, 1031ul, 1543ul, 2053ul, 3079ul, 6151ul, 12289ul, 24593ul,
    49157ul, 98317ul, 196613ul, 393241ul, 786433ul, 1572869ul, 3145739ul,
    6291469ul, 12582917ul, 25165843ul, 50331653ul, 100663319ul,
    201326611ul, 402653189ul, 805306457ul, 1610612741ul, 3221225473ul,
    4294967291ul
};

Map* create_map(size_t size);
void map_insert(Map * m, MapKey key, MapValue value);
void map_erase(Map * m, MapKey elem);
void map_resize(Map * m);
void map_destroy(Map * m);
size_t map_findIndex(Map * m, MapKey key);
MapValue* map_find(Map * m, MapKey key);
bool map_shouldResize(Map * m);
size_t map_findPrime(size_t num);
size_t map_size(Map * m);
#endif /*MAP_H*/
