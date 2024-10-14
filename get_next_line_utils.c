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

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*str;

	len = ft_strlen(s1, '\0') + ft_strlen(s2, '\n');
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] && s2[j] != '\n')
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	if (s2[j] == '\n')
		str[i] = '\n';
	str[++i] = '\0';
	return (str);
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

char	*ft_strdup(const char *s)
{
	size_t	i;
	size_t	len;
	char	*str;

	len = ft_strlen(s, '\0');
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

/* int main()
{
	char *line;
	line = NULL;

	char *str = ft_strjoin("12345", "67\n89\n");
	printf("%s\n", str);

	int i = 0;
	while (str[i])
	{
		write (1, &str[i], 1);
		write (1, "\n", 1);
		i++;
	}
	printf("printed i = %d", i);
	return 0;
} */