#include "get_next_line.h"

size_t	ft_strlen(const char *s, char c)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] && s[i] != c)
	{
		i++;
	}
	if (s[i] == '\n')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	char	*temp;

	if (!s)
		return (NULL);
	temp = (char *)s;
	while (*temp)
	{
		if (*temp == (char)c)
			return (++temp);
		temp++;
	}
	if (*temp == '\0' && (char)c == '\0')
		return (temp);
	return (NULL);
}

void 	ft_strjoin(char **s1, char *s2) //free and change s1, doesn't impact s2
{
	size_t	i;
	size_t	j;
	char	*temp;

	temp = malloc(sizeof(char));
	if (!temp)
		return ;
	ft_strdup(&temp, *s1);
	if (*s1)
		free(*s1);
	*s1 = malloc(((ft_strlen(temp, '\0') + ft_strlen(s2, '\n')) + 1) * sizeof(char));
	if (!*s1)
		return ;
	i = 0;
	while (temp && temp[i])
	{
		(*s1)[i] = temp[i];
		i++;
	}
	free(temp);
	j = 0;
	while (s2[j] && s2[j] != '\n')
	{
		(*s1)[i] = s2[j];
		i++;
		j++;
	}
	if (s2[j] == '\n')
		(*s1)[i] = '\n';
	(*s1)[++i] = '\0';
}

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*str;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

void	ft_strdup(char **s, char *str) //free and change s, doesn't impact str
{
	size_t	i;
	size_t	len;

	if (!str)
		return;
	len = ft_strlen(str, '\0');
	if (*s)
		free(*s);
	*s = malloc((len + 1) * sizeof(char));
	if (!*s)
		return;
	i = 0;
	while (str[i])
	{
		(*s)[i] = str[i];
		i++;
	}
	(*s)[i] = '\0';
	//free (str);
}

/* int main()
{
	char *copy = strdup("12345");
	char *line = strdup("helloooooo");

	printf("%s\n", line);
	ft_strdup(&line, copy);
	printf("%s\n", line);
	return 0;
} */