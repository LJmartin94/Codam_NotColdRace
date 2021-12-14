/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 20:08:00 by limartin      #+#    #+#                 */
/*   Updated: 2021/12/14 22:49:16 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "ColdRace.h"

int ft_strlen(const char *str)
{
	int i = 0;
	while(str[i] != '\0')
		i++;
	return(i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	int				res;
	unsigned char	c1;
	unsigned char	c2;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i])
	{
		if (((s1[i] == '\0') && (s2[i] == '\0')) || (i == n - 1))
			return (0);
		i++;
	}
	c1 = (unsigned char)s1[i];
	c2 = (unsigned char)s2[i];
	res = (c1 - c2);
	return (res);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	n;

	n = ft_strlen(s1);
	return (ft_strncmp(s1, s2, n + 1));
}

int	are_strs_eq(const char *s1, const char *s2)
{
	if (ft_strcmp(s1, s2) != 0)
		return (0);
	else
		return (1);
}

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
		// write(1, key, ft_strlen(key));
		// write(1, "\n", 1);
		// write(1, value, ((array_link->subArray)[i])->valueLength);
		// write(1, "\n", 1);
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