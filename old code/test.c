#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	safe_free(char **tobefreed)
{
    if (*tobefreed && **tobefreed)
    {
        free(*tobefreed);
        *tobefreed = NULL;
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

void	ft_strdup(char **s, char *str) //free and change s, doesn't impact str
{
    size_t	i;
    size_t	len;

    if (!str)
        return;
    len = ft_strlen(str, '\0');
    safe_free(s);
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
    
    // Allocation de temp pour sauvegarder l'ancien contenu de s1
    temp = malloc(ft_strlen(*s1, '\0') + 1);
    if (!temp)
        return;
    strcpy(temp, *s1);  // On copie le contenu de s1 dans temp
    safe_free(s1);  // On libère s1 avant de le réallouer

    // Nouvelle allocation pour s1
    *s1 = malloc((ft_strlen(temp, '\0') + ft_strlen(s2, '\n') + 1) * sizeof(char));
    if (!*s1)
    {
        safe_free(&temp);  // Si allocation échoue, libérer temp
        return;
    }

    // Copie du contenu de temp dans s1
    i = 0;
    while (temp[i])
    {
        (*s1)[i] = temp[i];
        i++;
    }
    safe_free(&temp);  // On libère temp après utilisation

    // Copie du contenu de s2 dans s1
    j = 0;
    while (s2[j] && s2[j] != '\n')
    {
        (*s1)[i] = s2[j];
        i++;
        j++;
    }
    if (s2[j] == '\n')
        (*s1)[i++] = '\n';

    (*s1)[i] = '\0';  // Terminer la nouvelle chaîne s1
}

int main()
{
    char *copy = strdup("cop\ny");
    char *line = strdup("helloooooo");

    printf("Initial line: %s\n", line);
    ft_strjoin(&line, copy);  // Join copy to line
    printf("Final line: %s\n", line);

    safe_free(&line);  // Free the final line
    safe_free(&copy);  // Free copy after usage

    return 0;
}
