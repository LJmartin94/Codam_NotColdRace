/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 20:08:00 by limartin      #+#    #+#                 */
/*   Updated: 2021/12/15 09:19:17 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ColdRace.h"

int write_values(t_link *head, int kvps)
{
	int ret = 1;
	int i = 0;
	int j = 0;
	char *query;
	t_link *array_link = head;

	while(ret)
	{
		ret = get_next_line(0, &query);
		if (ft_strlen(query) == 0)
			break;
		i = 0;
		j = 0;
		array_link = head;
		while (j < kvps)
		{
			if (are_strs_eq(query, ((array_link->subArray)[i])->key))
			{
				write(1, ((array_link->subArray)[i])->value, ((array_link->subArray)[i])->valueLength);
				write(1, "\n", 1);
				break;
			}
			i++;
			if (i % ARRAY_SIZE == 0)
			{
				array_link = array_link->next;
				i = 0;
			}
			j++;
		}
		if (j == kvps)
		{
			write(1, query, ft_strlen(query));
			write(1, ": Not found.\n", 13);
		}
	}
	return (0);
}

int main(void)
{
	int kvps = 0;

	t_link *list_array_kvp = ft_get_kvps(&kvps);
	write_values(list_array_kvp, kvps);
	return (0);
}