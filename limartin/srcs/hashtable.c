/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hashtable.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/15 09:36:54 by limartin      #+#    #+#                 */
/*   Updated: 2021/12/15 12:12:55 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ColdRace.h"

// funciton to hash a key
unsigned int ft_hash(const char *key)
{
	unsigned long int value = 0;
	unsigned int i = 0;
	unsigned int key_len = ft_strlen(key);

	while (i < key_len)
	{
		value = value * 37 + key[i];
		i++;
	}

	value = value % TABLE_SIZE;
	return (value);
}

// Djb2 hash function
unsigned long Djb2_hash(char *str) 
{
        unsigned long hash = 5381;
        int c;
        while ((c = *str++))
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
        return hash % TABLE_SIZE;
}

// function to create the hashtable
t_ht *hash_table_create(void)
{
	t_ht *hashtable = (t_ht *)malloc(sizeof(t_ht) * 1);
	hashtable->entries = (t_pair **)malloc(sizeof(t_pair *) * TABLE_SIZE);

	// TODO: if static, may not need to null?
	int i = 0;
	while (i < TABLE_SIZE)
	{
		hashtable->entries[i] = NULL;
		i++;
	}
	return (hashtable);
}

// function to make & populate new kvp
t_pair *ht_pair(char *key, char *value, int keylen, int vallen)
{
	t_pair *entry = (t_pair *)malloc(sizeof(t_pair) * 1);
	
	entry->key = key;
	entry->value = value;
	entry->keyLength = keylen;
	entry->valueLength = vallen;
	entry->next = NULL;
	return (entry);
}


// function to insert kvp into hashtable
void ht_insert(t_ht *table, char *key, char *value, int keylen, int vallen)
{
	unsigned int row = Djb2_hash(key);
	t_pair *entry = table->entries[row];

	if (entry == NULL)
	{
		table->entries[row] = ht_pair(key, value, keylen, vallen);
		return ;
	}

	t_pair *prev;
	while (entry != NULL)
	{
		// Overwrite existing value if existing key matches current key
		if (are_strs_eq(entry->key, key))
		{
			free(entry->value);
			entry->value = (char *)malloc(vallen + 1);
			for (int i = 0; i <= vallen; i++)
				entry->value[i] = value[i];
			return ;
		}
		prev = entry;
		entry = prev->next;
	}
	prev->next = ht_pair(key, value, keylen, vallen);
	return ;
}

// function to look up value by key
char *ht_retrieve(t_ht *table, char *key, int *val_len)
{
	unsigned int row = Djb2_hash(key);
	t_pair *entry = table->entries[row];

	*val_len = 0;
	if (entry == NULL)
		return (NULL);
	while (entry != NULL)
	{
		if (are_strs_eq(entry->key, key))
		{
			*val_len = entry->valueLength;
			return (entry->value);
		}
		entry = entry->next;
	}
	return (NULL);
}

// function for debugging that prints entire hashtable
#include <stdio.h>
void ht_visualise(t_ht *hashtable)
{
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		t_pair *entry = hashtable->entries[i];
		if (entry == NULL)
			continue ;
		printf("slot[%4d]: ", i);

		while(1)
		{
			printf("%s = %s ", entry->key, entry->value);
			if (entry->next == NULL)
				break ;
			entry = entry->next;
		}
		write(1, "\n", 1);
	}
	return ;
}
