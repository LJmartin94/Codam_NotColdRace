/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   general_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/15 09:07:40 by limartin      #+#    #+#                 */
/*   Updated: 2021/12/15 09:13:29 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
	if (ft_strcmp(s1, s2))
		return (0);
	return (1);
}