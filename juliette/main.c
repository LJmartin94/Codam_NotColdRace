#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "Libft1/libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	int	i;

	i = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (dstsize - 1 > 0 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
		dstsize--;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

static int	clean( char **out, int word_count)
{
	int	i;

	i = 0;
	while (i < word_count)
	{
		free(out[i]);
		i++;
	}
	free(out);
	return (-1);
}

static int	word_len(char const *s, char c, char **out, int count)
{
	int	i;
	int	word_len;
	int	word_count;
	int	save;

	i = 0;
	word_count = 0;
	while (s[i] && word_count < count)
	{
		word_len = 0;
		while (s[i] == c)
			i++;
		save = i;
		while (s[i] != c && s[i] != '\0')
		{
			word_len++;
			i++;
		}
		out[word_count] = malloc (word_len + 1);
		if (!out[word_count])
			return (clean(out, word_count));
		ft_strlcpy(out[word_count], &s[save], word_len + 1);
		word_count++;
	}
	return (0);
}

static int	word_counter(char const *s, char c)
{	
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			count++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{	
	char	**out;
	int		word_count;

	if (!s)
		return (NULL);
	word_count = word_counter(s, c);
	out = malloc (sizeof(char *) * (word_count + 1));
	if (!out)
		return (NULL);
	if (word_len(s, c, out, word_count) == -1)
		return (NULL);
	out[word_count] = 0;
	return (out);
}

int main()
{
	// int	fd1;
	//int	fd;
	// char 	*input;
	char input[1000];
	int ret = read(0, input, 1000);
	input[ret + 1] = '\0';
	write(1, input, ret + 1);
	// int ret;
	// // input = malloc(sizeof(char) * 11001);
	// // fd1 = open("test.txt", O_RDONLY);
	// //fd = open("output.txt", O_WRONLY);
	// ret = read(fd1, input, 11000);
	// input[ret + 1] = '\0';
	
	// //write(1, input, ret + 1);
	// printf("%s", input);
	// // char	**splitty;
	// splitty= ft_split(input,'\n');
	// //ft_putstr(input, fd);
	// printf("%s", splitty[0]);
	// printf("%s", splitty[1]);
	// printf("%s", splitty[2]);

	//close(0);
	// close(fd1);
}