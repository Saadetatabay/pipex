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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	c1;
	unsigned char	c2;
	size_t			i;

	i = 0;
	while (i < n)
	{
		c1 = (unsigned char)*(s1 + i);
		c2 = (unsigned char)*(s2 + i);
		if (c1 != c2)
			return (c1 - c2);
		if (c1 == '\0')
			return (0);
		i++;
	}
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*(s + i) != '\0')
		i++;
	return (i);
}

static void	concatenate(char *cat, const char *s, int *j)
{
	int	i;

	i = 0;
	while (*(s + i))
	{
		*(cat + *j) = *(s + i);
		i++;
		(*j)++;
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*cat;
	int		len;
	int		j;

	if (s1 == NULL)
		return (ft_strdup(s2));
	j = 0;
	len = 0;
	len = ft_strlen(s1);
	len += ft_strlen(s2);
	cat = (char *)malloc(sizeof(char) * (len + 1));
	if (!cat)
		return (0);
	concatenate(cat, s1, &j);
	concatenate(cat, s2, &j);
	*(cat + j) = '\0';
	return (cat);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (!d && !s)
		return (NULL);
	while (n--)
	{
		*d = *s;
		d++;
		s++;
	}
	return (dest);
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