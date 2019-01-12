#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdio.h>
#include <math.h>

#define MAX_WORD_LENGTH 20

struct llnode {
        char* word;
        int d1_count;
	int d2_count;
	int d3_count;
        struct llnode* next;
};

struct hashmap {
        struct llnode** map;
        int num_buckets;
        int num_elements;
};

// hashmap.c
struct hashmap* hm_create(int num_buckets);
struct llnode* hm_get(struct hashmap* hm, char* word);
void hm_put(struct hashmap* hm, char* word, int d1_count, int d2_count, int d3_count);
void hm_remove(struct hashmap* hm, char* word);
void hm_destroy(struct hashmap* hm);
int hash(struct hashmap* hm, char* word);

// training.c
void train(struct hashmap* hm, char* file1, char* file2, char* file3);
void add_file_contents(struct hashmap* hm, char* input_file_name);
char* get_next_word (FILE* in);
void stop_word(struct hashmap* hm);
void print(struct hashmap* hm);

// search.c
int read_query(struct hashmap* hm);
void show_results();
char* get_query_word(char* query, char* word);
void rank(struct hashmap* hm, char* word);
double tf_idf(struct llnode* node, char* file_name);
double get_idf(struct llnode* node);

#endif
