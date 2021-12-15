/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hashtable.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/15 09:36:54 by limartin      #+#    #+#                 */
/*   Updated: 2021/12/15 09:56:51 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ColdRace.h"

// hash function
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

// function to create the hashtable
t_ht *hash_table_create(void)
{
	t_ht *hashtable = (t_ht *)malloc(sizeof(t_ht) * 1);
	hashtable->entries = (t_pair **)malloc(sizeof(t_pair *) * TABLE_SIZE);

	int i = 0;
	while (i < TABLE_SIZE)
	{
		hashtable->entries[i] = NULL;
		i++;
	}
	return (hashtable);
}

t_pair *ht_pair(const char *key, const char *value, int keylen, int vallen)
{
	int i = 0;
	t_pair *entry = (t_pair *)malloc(sizeof(t_pair) * 1);
	entry->key = (char *)malloc(keylen + 1);
	
	entry->value = (char *)malloc(vallen + 1);
	strcpy(entry->value, value)
	entry->keyLength = keylen;
	entry->valueLength = vallen;
	entry->next = NULL;


}


// function to insert kvp into hashtable
void ht_insert(t_ht *table, const char *key, const char *value, int keylen, int vallen)
{
	unsigned int row = ft_hash(key);
	t_pair *entry = table->entries[row];

	if (entry == NULL)
	{
		table->entries[row] = ht_pair(key, value, keylen, vallen);
		return ();
	}

	t_pair *prev;
	while (entry != NULL)
	{

	}
}
