#include "get_next_line.h"

size_t	ft_strlen_until(const char *s, char stop)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != stop)
	{
		i++;
	}
	return (i);
}

void	copy_until(char **dest, char *src, char stop)
{
	size_t	len;
	size_t	i;

	if (!src || !*src)
		return ;
	safe_free(dest);
	len = ft_strlen_until(src, stop);
	if (src[len] == '\n')
		len++;
	*dest = malloc((len + 1) * sizeof(char));
	if (!*dest)
		return;
	i = 0;
	while (src[i] && src[i] != stop)
	{
		(*dest)[i] = src[i];
		i++;
	}
	if (src[i] == '\n')
		(*dest)[i++] = '\n';
	(*dest)[i] = '\0';
}

void	join_until(char **dest, char *src, char stop)
{
	size_t	i;
	size_t	k;
	char	*temp;

	if (!src || !*src)
		return ;
	if (!*dest || !**dest)
	{
		copy_until(dest, src, stop);
		return ;
	}
	k = ft_strlen_until(*dest, '\0') + ft_strlen_until(src, stop);
	if (src[ft_strlen_until(src, stop)] == '\n')
		k++;
	temp = NULL;
	copy_until(&temp, *dest, '\0');
	safe_free(dest);
	*dest = malloc((k + 1) * sizeof(char));
	if (!*dest)
		return ;
	i = 0;
	while(temp[i])
	{
		(*dest)[i] = temp[i];
		i++;
	}
	safe_free(&temp);
	k = 0;
	while (src[k] && src[k] != stop)
		(*dest)[i++] = src[k++];
	if (src[k] == '\n')
		(*dest)[i++] = '\n';
	(*dest)[i] = '\0';
}

char	*ft_strchr(char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return (++s);
		s++;
	}
	if (*s == '\0' && c == '\0')
		return (s);
	return (NULL);
}

void	clear_string(char	**string)
{
	size_t	i;

	if (!*string)
		return ;
	i = 0;
	while ((*string)[i])
	{
		(*string)[i] = '\0';
		i++;
	}
	return;
}

// int	main()
// {
// 	char *line = strdup("bonjour");
// 	char *buffer = strdup("hel\nlo.");

// 	join_until(&line, buffer, '\n');
// 	printf("line = #%s#\n", line);
// 	safe_free(&line);
// 	safe_free(&buffer);

// 	return (0);
// }
