/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   store_kvps.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/15 09:15:31 by limartin      #+#    #+#                 */
/*   Updated: 2021/12/15 09:15:52 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "ColdRace.h"

t_pair *ft_newkvp(char *key, char *value, int val_len)
{
	t_pair *res;
	res = (t_pair *)malloc(sizeof(t_pair));
	if (res)
	{
		res->key = key;
		res->value = value;
		res->valueLength = val_len;
	}
	return (res);
}

t_link *ft_newlst()
{
	t_link *res;
	res = (t_link *)malloc(sizeof(t_link));
	res->subArray = (t_pair **)malloc(sizeof(t_pair *) * ARRAY_SIZE);
	res->next = NULL;
	return (res);
}


void ft_lstadd_back(t_link **alst, t_link *new)
{
	t_link	*res;

	if (!(alst) || !(new))
		return ;
	if (!(*alst))
		*alst = new;
	else
	{
		res = *alst;
		while (res->next)
			res = res->next;
		res->next = new;
	}
}

t_link *ft_get_kvps(int *kvps_total)
{
	int ret = 1;
	int len = 0;
	int kvps = 0;
	int i = 0;
	int j = 0;
	char *key;
	char *value;

	t_link *head_link = ft_newlst();
	t_link *array_link = head_link;
	t_pair *new;

	while(ret == 1)
	{
		ret = get_next_line(0, &key);
		len = ft_strlen(key);
		if (ret == 0 || len == 0)
			break;
		ret = get_next_line(0, &value);
		len = ft_strlen(value);
		if (ret == 0 || len == 0)
			break;
		if (kvps % ARRAY_SIZE == 0 && kvps != 0)
		{
			array_link = ft_newlst();
			ft_lstadd_back(&head_link, array_link);
			i = 0;
		}
		new = (t_pair *)malloc(sizeof(t_pair));
		new->key = key;
		new->value = value;
		new->valueLength = ft_strlen(value);
		(array_link->subArray)[i] = new;
		i++;
		kvps++;
	}

	i = 0;
	array_link = head_link;
	while (j < kvps)
	{
		key = ((array_link->subArray)[i])->key;
		value = ((array_link->subArray)[i])->value;
		i++;
		if (i % ARRAY_SIZE == 0)
		{
			array_link = array_link->next;
			i = 0;
		}
		j++;
	}
	*kvps_total = kvps;
	return (head_link);
}