/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 20:08:00 by limartin      #+#    #+#                 */
/*   Updated: 2021/12/15 12:55:57 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ColdRace.h"

int write_values(t_ht *ht)
{
	int ret = 1;
	char *query_key;
	char *query_value;
	int query_len = 0;
	int val_len = 0;

	while(ret)
	{
		ret = get_next_line(0, &query_key);
		query_len = ft_strlen(query_key);
		if (query_len == 0)
			break;
		query_value = ht_retrieve(ht, query_key, &val_len);
		if (query_value == NULL)
		{
			write(1, query_key, query_len);
			write(1, ": Not found.\n", 13);
		}
		else
		{
			write(1, query_value, val_len);
			write(1, "\n", 1);
		}
	}
	return (0);
}

int main(void)
{
	t_ht *ht = hash_table_create();

	// ht_insert(ht, "key", "value", 3, 5);
	// ht_visualise(ht);
	ft_set_kvps(ht);
	// write_values(ht);
	resolve_queries(ht);
	return (0);
}