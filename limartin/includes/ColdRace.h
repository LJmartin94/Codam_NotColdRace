// INCLUDES
#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>
#include "get_next_line.h"

// DEFINES

# ifndef ARRAY_SIZE
#  define ARRAY_SIZE 2
# endif

// STRUCTS
typedef struct s_pair {
    char *key;
    char *value;
    int valueLength;
}   t_pair;

typedef struct s_link {
    t_pair **subArray;
    struct s_link *next;
}   t_link;

// PROTOTYPES
int ft_strlen(const char *str);
int	are_strs_eq(const char *s1, const char *s2);
t_link *ft_get_kvps(int *kvps_total);