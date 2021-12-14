# ifndef ARRAY_SIZE
#  define ARRAY_SIZE 1
# endif

typedef struct s_pair {
    char *key;
    char *value;
    int valueLength;
}   t_pair;

typedef struct s_link {
    t_pair *subArray[ARRAY_SIZE];
    struct s_link *next;
}   t_link;

#include <unistd.h>
#include <stdlib.h>