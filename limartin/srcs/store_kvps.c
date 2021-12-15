/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   store_kvps.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/15 09:15:31 by limartin      #+#    #+#                 */
/*   Updated: 2021/12/15 11:17:59 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "ColdRace.h"

int ft_set_kvps(t_ht *ht)
{
	int ret = 1;
	char *key;
	int keylen = 0;
	char *value;
	int vallen = 0;

	while(ret == 1)
	{
		ret = get_next_line(0, &key);
		keylen = ft_strlen(key);
		if (ret == 0 || keylen == 0)
			break;
		ret = get_next_line(0, &value);
		vallen = ft_strlen(value);
		if (ret == 0 || vallen == 0)
			break;
		ht_insert(ht, key, value, keylen, vallen);
	}
	return (0);
}