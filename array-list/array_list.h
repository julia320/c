#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#define INITIAL_SIZE 10

struct array_list {
        int* array;
        int size;
        int capacity;
};

struct array_list* al_create(void);
void al_add(struct array_list* list, int value);
int al_get(struct array_list* list, int index);
void al_set(struct array_list* list, int index, int value);
void al_remove(struct array_list* list, int index);
int al_size(struct array_list* list);
void al_destroy(struct array_list* list);

#endif