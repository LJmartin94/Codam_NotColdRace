/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/14 17:01:50 by limartin      #+#    #+#                 */
/*   Updated: 2021/12/14 20:01:35 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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

int get_till_newline(char *input, int *i, char **str, int *len_val, char mode)
{
	int len = 0;

	while (input[*i + len] != '\n' && input[*i + len])
		len++;
	if ((mode == 'k' && input[*i + len] == '\0') || len == 0)
		return (1);
	printf("%c\n", mode);
	*str = (char *)malloc(sizeof(char) * (len + 1));
	len = 0;
	while (input[*i] != '\n')
	{
		(*str)[len] = input[*i];
		len++;
		(*i)++;
	}
	(*str)[len] = '\0';
	(*i)++;
	// if (mode == 'v')
	// 	*len_val = len;
	return (0);
}

t_link *str_to_kvp(char *input)
{
	int i = 0; //input index
	int k = 0; //number of KVPs
	t_link **all_kvps = NULL; //linked list of arrays of key value pairs.
	t_link *new_kvpArray = NULL; // a single link in the above list
	t_pair *new_kvp = NULL; // a single entry in the content array of the above link
	char **key;
	char **value;
	int len = 0;

	while(input[i] != '\0')
	{
		if (k % ARRAY_SIZE == 0)
		{
			new_kvpArray = ft_newlst();
			ft_lstadd_back(all_kvps, new_kvpArray);
		}
		
		if (get_till_newline(input, &i, key, &len, 'k'))
			break;
		write(1, "test\n", 5);
		if (get_till_newline(input, &i, value, &len, 'v'))
			break;
		while(new_kvpArray->next)
			new_kvpArray = new_kvpArray->next;
		(new_kvpArray->subArray)[k] = ft_newkvp(*key, *value, len);
	}
	return (*all_kvps);
}

int main(int argc, char **argv)
{
	if (argc <= 1)
		return(write(1, "give 1 arg\n", 11));
	
	t_link *head = NULL;
	head = str_to_kvp((argv[1]));
	int k = 0;
	while(head)
	{
		while (k < ARRAY_SIZE)
		{
			
			write(1, head->subArray[k]->value, head->subArray[k]->valueLength);
			k++;
		}
		head = head->next;
	}

}