#include"map.h"

size_t hash(MapKey key, size_t size) {
    return key % size;
}

size_t hash2(MapKey key, size_t size) {

    return (33 + key) % size;
}

Map * create_map(size_t size) {
    Map * m = malloc(sizeof(Map));
    m->arr = (MapPair**)malloc(size * sizeof(MapPair*));
    m->shouldProbe = malloc(size * sizeof(bool));
    for (size_t i = 0; i < size; i++) {
        m->arr[i] = NULL;
        m->shouldProbe[i] = false;
    }
    m->maxSize = size;
    m->numElems = 0;
    return m;
}
void map_insert(Map * m, MapKey key, MapValue val) {
    if (map_shouldResize(m))
        map_resize(m);
    m->numElems += 1;
    size_t idx = hash(key, m->maxSize);
    while (m->shouldProbe[idx % m->maxSize])
        idx += hash2(key, m->maxSize);
    if (idx != -1) {
        m->arr[idx] = malloc(sizeof(MapPair));
        m->arr[idx]->key = key;
        m->arr[idx]->value = val;
        m->shouldProbe[idx] = true;
    }
}
size_t map_findIndex(Map * m, MapKey key) {
    size_t idx = hash(key, m->maxSize);
    size_t start = idx; // For keeping track of if key has been found

    while(m->shouldProbe[idx]) {
        if (m->arr[idx] != NULL && m->arr[idx]->key == key)
            return idx;
        idx = (idx + hash2(key, m->maxSize)) % m->maxSize;
        if (idx == start)
            break;
    }
    return -1;
}
void map_erase(Map * m, MapKey key) {
    size_t idx = map_findIndex(m, key);
    if (idx != -1) {
        free(m->arr[idx]);
        m->arr[idx] = NULL;
        m->numElems -= 1;
    }
}
// Returns null if not found
MapValue* map_find(Map * m, MapKey key) {
    size_t idx = hash(key, m->maxSize);
    if (idx != -1)
        return &(m->arr[idx]->value);
    return NULL;
}
bool map_shouldResize(Map * m) {
    return ((double)m->numElems) / m->maxSize >= LOADFACTOR;
}
void map_destroy(Map * m) {
    if (m != NULL) {
        for (size_t i = 0; i < m->maxSize; i++) {
            if (m->arr[i] != NULL) free(m->arr[i]);
        }
        free(m->arr);
        free(m->shouldProbe);
    }
    free(m);
}
size_t map_findPrime(size_t num) {
	  size_t len = sizeof( primes ) / sizeof( size_t );
    size_t prime = 0;
    for (prime = 0; prime < len; prime++) {
        if (primes[prime] > num) {
            return primes[prime];
        }
    }

    return primes[prime - 1];
}
void map_resize(Map * m) {
    size_t newSize = map_findPrime(2 * m->maxSize);
    MapPair ** newArr = (MapPair **) malloc(sizeof(MapPair*) * newSize);
    free(m->shouldProbe);
    m->shouldProbe = (bool*) malloc(sizeof(bool) * newSize);
    for (int i = 0; i < newSize; i++) {
        m->shouldProbe[i] = false;
        newArr[i] = NULL;
    }
    MapPair ** oldArr = m->arr;
    m->arr = newArr;
    size_t oldSize = m->maxSize;
    m->maxSize = newSize;
    m->numElems = 0;
    for (int i = 0; i < oldSize; i++) {
        if (oldArr[i] != NULL) {
            map_insert(m, oldArr[i]->key, oldArr[i]->value);
            free(oldArr[i]);
        }
    }
    free(oldArr);
}
size_t map_size(Map * m) {
    return m->numElems;
}
