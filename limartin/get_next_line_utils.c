/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/08 19:03:23 by limartin      #+#    #+#                 */
/*   Updated: 2021/12/14 20:12:05 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_malloc_expander(char **str, int size, int grow)
{
	int		i;
	char	*cpy;

	i = 0;
	cpy = (char *)malloc(sizeof(char) * (size + 1));
	if (cpy == 0)
		return (0);
	while (i < size)
	{
		cpy[i] = (*str)[i];
		i++;
	}
	free(*str);
	*str = (char *)malloc(sizeof(char) * (size + grow + 1));
	while ((i > 0) && !(*str == 0))
	{
		i--;
		(*str)[i] = cpy[i];
	}
	free(cpy);
	if (*str == 0)
		return (0);
	(*str)[size + grow] = '\0';
	return (size + grow + 1);
}

size_t	ft_linelen(const char *s, char n)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0' && s[len] != n)
		len++;
	return (len);
}