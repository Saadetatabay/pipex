/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satabay <satabay@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 13:39:57 by satabay           #+#    #+#             */
/*   Updated: 2025/10/08 13:41:20 by satabay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	word_count(char const *s, char c)
{
	int	word_count;
	int	i;

	i = 1;
	word_count = 0;
	if (*(s) != c)
		word_count++;
	while (*(s + i))
	{
		if (*(s + i) != c && *(s + i - 1) == c)
			word_count++;
		i++;
	}
	return (word_count);
}

static void	free_splitted(char **splitted, int j)
{
	while (j--)
		free(splitted[j]);
	free(splitted);
}

static char	**filling(char **splitted, const char *s, char c, int word_con)
{
	int	len;
	int	j;

	j = 0;
	while (j < word_con)
	{
		while (*s == c)
			s++;
		len = 0;
		while (*(s + len) != c && *(s + len) != '\0')
			len++;
		splitted[j] = malloc(sizeof(char) * (len + 1));
		if (!splitted[j])
		{
			free_splitted(splitted, j);
			return (NULL);
		}
		ft_memcpy(splitted[j], s, len);
		splitted[j][len] = '\0';
		s = s + len;
		j++;
	}
	splitted[j] = NULL;
	return (splitted);
}

char	**ft_split(char const *s, char c)
{
	int		word_c;
	char	**splitted;

	if (s[0] == '\0')
		word_c = 0;
	else
		word_c = word_count(s, c);
	splitted = malloc(sizeof(char *) * (word_c + 1));
	if (!splitted)
		return (NULL);
	return (filling(splitted, s, c, word_c));
}

char	*ft_strdup(const char *s)
{
	size_t	i;
	size_t	len;
	char	*copy;

	len = ft_strlen(s);
	copy = malloc(sizeof(char) * (len + 1));
	if (!copy)
		return (0);
	i = 0;
	while (i < len)
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
