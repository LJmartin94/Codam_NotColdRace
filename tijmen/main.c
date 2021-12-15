#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "get_next_line.h"

#define TABLE_SIZE 20000

typedef struct entry_t {
    char *key;
    char *value;
    struct entry_t *next;
} entry_t;

typedef struct {
    entry_t **entries;
} ht_t;

unsigned int hash(char *key) {
    unsigned long int value = 0;
    unsigned int i = 0;
    unsigned int key_len = strlen(key);

    // do several rounds of multiplication
    for (; i < key_len; ++i) {
        value = value * 37 + key[i];
    }

    // make sure value is 0 <= value < TABLE_SIZE
    value = value % TABLE_SIZE;

    return value;
}

entry_t *ht_pair(char *key, char *value) {
    // allocate the entry
    entry_t *entry = malloc(sizeof(entry_t) * 1);
    entry->key = key;
    entry->value = value;

    // next starts out null but may be set later on
    entry->next = NULL;

    return entry;
}

ht_t *ht_create(void) {
    // allocate table
    ht_t *hashtable = malloc(sizeof(ht_t) * 1);

    // allocate table entries
    hashtable->entries = malloc(sizeof(entry_t*) * TABLE_SIZE);

    // set each to null (needed for proper operation)
    int i = 0;
    for (; i < TABLE_SIZE; ++i) {
        hashtable->entries[i] = NULL;
    }

    return hashtable;
}

void ht_set(ht_t *hashtable, char *key, char *value) {
    unsigned int slot = hash(key);

    // try to look up an entry set
    entry_t *entry = hashtable->entries[slot];

    // no entry means slot empty, insert immediately
    if (entry == NULL) {
        hashtable->entries[slot] = ht_pair(key, value);
        return;
    }

    entry_t *prev;

    // walk through each entry until either the end is
    // reached or a matching key is found
    while (entry != NULL) {
        // check key
        if (strcmp(entry->key, key) == 0) {
            // match found, replace value
            free(entry->value);
            entry->value = malloc(strlen(value) + 1);
            strcpy(entry->value, value);
            return;
        }

        // walk to next
        prev = entry;
        entry = prev->next;
    }

    // end of chain reached without a match, add new
    prev->next = ht_pair(key, value);
}

char *ht_get(ht_t *hashtable, char *key) {
    unsigned int slot = hash(key);

    // try to find a valid slot
    entry_t *entry = hashtable->entries[slot];

    // no slot means no entry
    if (entry == NULL) {
        return NULL;
    }

    // walk through each entry in the slot, which could just be a single thing
    while (entry != NULL) {
        // return value if found
        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }

        // proceed to next key if available
        entry = entry->next;
    }

    // reaching here means there were >= 1 entries but no key match
    return NULL;
}

void ht_del(ht_t *hashtable, char *key) {
    unsigned int bucket = hash(key);

    // try to find a valid bucket
    entry_t *entry = hashtable->entries[bucket];

    // no bucket means no entry
    if (entry == NULL) {
        return;
    }

    entry_t *prev;
    int idx = 0;

    // walk through each entry until either the end is reached or a matching key is found
    while (entry != NULL) {
        // check key
        if (strcmp(entry->key, key) == 0) {
            // first item and no next entry
            if (entry->next == NULL && idx == 0) {
                hashtable->entries[bucket] = NULL;
            }

            // first item with a next entry
            if (entry->next != NULL && idx == 0) {
                hashtable->entries[bucket] = entry->next;
            }

            // last item
            if (entry->next == NULL && idx != 0) {
                prev->next = NULL;
            }

            // middle item
            if (entry->next != NULL && idx != 0) {
                prev->next = entry->next;
            }

            // free the deleted entry
            free(entry->key);
            free(entry->value);
            free(entry);

            return;
        }

        // walk to next
        prev = entry;
        entry = prev->next;

        ++idx;
    }
}

void ht_dump(ht_t *hashtable) {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        entry_t *entry = hashtable->entries[i];

        if (entry == NULL) {
            continue;
        }

        printf("slot[%4d]: ", i);

        for(;;) {
            printf("%s=%s ", entry->key, entry->value);

            if (entry->next == NULL) {
                break;
            }

            entry = entry->next;
        }

        printf("\n");
    }
}

typedef struct s_substr
{
    char *str;
    size_t len;
    struct s_substr *next;
}   t_substr;


t_substr *lst_add(char *str, size_t len)
{
    t_substr *link;

    link = malloc(sizeof(t_substr));
    if (!link)
        return NULL;
    link->str = str;
    link->len = len;
    return (link);
}

size_t ft_strlennn(char *str)
{
    size_t i = 0;

    while (str[i])
        i++;
    return(i);
}

void writeOutput(t_substr *root, size_t strLen)
{
    char *output;
    t_substr *link;
    size_t outputIndex = 0;
    size_t substringIndex;

    output = malloc(sizeof(char) * (strLen + 1));
    if (!output)
        return;
    link = root;
    while (link)
    {
        substringIndex = 0;
        while (substringIndex < link->len)
        {
            output[outputIndex + substringIndex] = link->str[substringIndex];
            substringIndex++;
        }
        outputIndex += substringIndex;
        link = link->next;
    }
    write(1, output, strLen);
}

void resolve_queries(ht_t *ht)
{
    char *value;
    char *line = 0;
    t_substr root;
    t_substr *link;
    char nl[] = "\n";
    char notfound[] = ": Not found.\n";
    size_t strLen = 0;

    link = &root;
    while (get_next_line(0, &line))
    {
        if (strcmp("", line) == 0)
            break;
        value = ht_get(ht, line);
        if (value == NULL)
        {
            link->next = lst_add(line, ft_strlennn(line));
            link = link->next;
            link->next = lst_add(notfound, 13);
            link = link->next;
            strLen += ft_strlennn(line) + 13;
        }
        else
        {
            link->next = lst_add(value, ft_strlennn(value));
            link = link->next;
            link->next = lst_add(nl, 1);
            link = link->next;
            strLen += ft_strlennn(value) + 1;
        }
    }
    link->next = NULL;
    writeOutput((root.next), strLen);
}

int main(void) {
    ht_t *ht = ht_create();
    char *line = NULL;
    char *key;
    char *value;
    int count;

    count = 0;

    while (get_next_line(0, &line))
    {
        if (strcmp("", line) == 0)
        {
            resolve_queries(ht);
            break ;
        }
        if (count % 2 == 0)
        {
            key = line;
            line = NULL;
            // value = 0;
        }
        else
        {
            value = line;
            ht_set(ht, key, value);
            line = NULL;
            // key = 0;
        }
        count++;
	}
    
    return 0;
}
