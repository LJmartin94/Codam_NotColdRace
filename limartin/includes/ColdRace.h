// INCLUDES
#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>
#include "get_next_line.h"

// DEFINES

#ifndef TABLE_SIZE
# define TABLE_SIZE 20000
#endif

// STRUCTS
typedef struct s_pair 
{
    char *key;
    char *value;
	int keyLength;
    int valueLength;
	struct s_pair *next;
}   t_pair;

typedef struct s_link 
{
    t_pair **subArray;
    struct s_link *next;
}   t_link;

typedef struct s_hash_table
{
	t_pair **entries;
} t_ht;

// PROTOTYPES
int ft_strlen(const char *str);
int	are_strs_eq(const char *s1, const char *s2);
int ft_set_kvps(t_ht *ht);
t_ht *hash_table_create(void);
void ht_insert(t_ht *table, char *key, char *value, int keylen, int vallen);
void ht_visualise(t_ht *hashtable);
char *ht_retrieve(t_ht *table, char *key, int *val_len);
void resolve_queries(t_ht *ht);