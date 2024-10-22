#include "get_next_line.h"

void	safe_free(char *tobefreed)
{
	if (tobefreed && *tobefreed)
	{
		free(tobefreed);
		tobefreed = NULL;
	}
	return;
}

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

// void 	ft_strjoin(char **s1, char *s2) //free and change s1, doesn't impact s2
// {
// 	size_t	i;
// 	size_t	j;
// 	char	*temp;

// 	if (!s1 || !s2)
// 		return;
// 	if (!*s1)
// 	{
// 		ft_strdup(s1, s2);
// 		return;
// 	}
// 	temp = malloc(ft_strlen(*s1, '\0') + 1);
// 	if (!temp)
// 		return ;
// 	ft_strdup(&temp, *s1);
// 	safe_free(s1);
// 	*s1 = malloc((ft_strlen(temp, '\0') + ft_strlen(s2, '\n') + 1) * sizeof(char));
// 	if (!*s1)
// 	{
// 		safe_free(&temp);
// 		return ;
// 	}
// 	i = 0;
// 	while (temp && temp[i])
// 	{
// 		(*s1)[i] = temp[i];
// 		i++;
// 	}
// 	safe_free(&temp);
// 	//printf("temp = %s\n", temp);
// 	j = 0;
// 	while (s2[j] && s2[j] != '\n')
// 	{
// 		(*s1)[i] = s2[j];
// 		i++;
// 		j++;
// 	}
// 	if (s2[j] == '\n')
// 		(*s1)[i] = '\n';
// 	(*s1)[++i] = '\0';
// 	//need to free s2 after calling the function;
// }

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
	safe_free(*s);
	printf ("len = %zu\n", len);
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
	//need to free str after calling the function;
}

void	ft_strjoin(char **s1, char *s2) //free and change s1, doesn't impact s2
{
    size_t	i;
    size_t	j;
    char	*temp;

    if (!s1 || !s2)
        return;
    if (!*s1)
    {
        ft_strdup(s1, s2);
        return;
    }
	temp = NULL;
    ft_strdup(&temp, *s1); // Copie de *s1 dans temp
    safe_free(*s1);         // Libération de l'ancienne s1
    
    // Nouvelle allocation pour s1, avec suffisamment d'espace pour temp + s2
    *s1 = malloc((ft_strlen(temp, '\0') + ft_strlen(s2, '\n') + 1) * sizeof(char));
    if (!*s1)
    {
        safe_free(temp);  // Libération de temp en cas d'échec
        return;
    }
    
    // Copie de temp dans *s1
    i = 0;
    while (temp && temp[i])
    {
        (*s1)[i] = temp[i];
        i++;
    }
    safe_free(temp); // Libération de temp après utilisation

    // Copie de s2 dans *s1 jusqu'à \n ou la fin
    j = 0;
    while (s2[j] && s2[j] != '\n')
    {
        (*s1)[i] = s2[j];
        i++;
        j++;
    }
    // Ajout du caractère '\n' si présent
    if (s2[j] == '\n')
        (*s1)[i++] = '\n';
    
    (*s1)[i] = '\0'; // Terminaison de la chaîne
}


// int main()
// {
//     char *copy = strdup("cop\ny");
//     char *line = strdup("helloooooo");

//     printf("Initial line: %s\n", line);
//     ft_strjoin(&line, copy);  // Join copy to line
//     printf("Final line: %s\n", line);

//     safe_free(&line);  // Free the final line
//     safe_free(&copy);  // Free copy after usage

//     return 0;
// }
