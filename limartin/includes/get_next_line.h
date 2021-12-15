/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/17 03:35:00 by limartin      #+#    #+#                 */
/*   Updated: 2021/12/14 20:24:27 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>

int		get_next_line(int fd, char **line);
int		ft_fill_remainder(char *remainder, int fd, int *nl);
int		ft_handle_remainder(char **line, char *rmn, int *i, int *nl);
void	ft_clear_remainder(char *remainder, int j);
int		ft_error(char *remainder, char **line);

int		ft_malloc_expander(char **str, int size, int grow);
size_t	ft_linelen(const char *s, char n);

#endif