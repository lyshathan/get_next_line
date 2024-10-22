#include <stdio.h>
#include <stdlib.h>

void	safe_free(char **tobefreed)
{
    if (tobefreed && *tobefreed) // Vérifie que tobefreed n'est pas NULL
    {
        printf("Freeing: %s\n", *tobefreed);
        free(*tobefreed);
        *tobefreed = NULL; // Nullifie le pointeur après la libération
    }
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

void	ft_strdup(char **s, const char *str) // Utilise const char* pour str
{
    size_t	i;
    size_t	len;

    if (!str) // Vérifie que str n'est pas NULL
        return;
    len = ft_strlen(str, '\0');
    safe_free(s); // Libère l'ancien contenu de s
    *s = malloc((len + 1) * sizeof(char)); // Alloue de la mémoire
    if (!*s) // Vérifie si l'allocation a échoué
        return;
    printf("Allocated %zu bytes for strdup\n", len + 1);
    
    // Copie la chaîne dans le nouveau buffer
    for (i = 0; i < len; i++)
    {
        (*s)[i] = str[i];
    }
    (*s)[i] = '\0'; // Null termine la chaîne
}

void	ft_strjoin(char **s1, const char *s2) // Utilise const char* pour s2
{
    size_t	i;
    size_t	j;
    char	*temp;

    if (!s1 || !s2) // Vérifie que les pointeurs ne sont pas NULL
        return;
    if (!*s1) // Si s1 est vide, on fait un strdup de s2
    {
        ft_strdup(s1, s2);
        return;
    }

    ft_strdup(&temp, *s1); // Copie s1 dans temp
    safe_free(s1); // Libère s1 avant de le réallouer

    // Alloue de la nouvelle mémoire pour s1
    *s1 = malloc((ft_strlen(temp, '\0') + ft_strlen(s2, '\n') + 1) * sizeof(char));
    if (!*s1) // Vérifie si l'allocation a échoué
    {
        safe_free(&temp); // Libère temp en cas d'échec
        return;
    }
    printf("Allocated *s1: %zu bytes\n", ft_strlen(temp, '\0') + ft_strlen(s2, '\n') + 1);

    // Copie le contenu de temp dans s1
    for (i = 0; temp[i]; i++)
    {
        (*s1)[i] = temp[i];
    }
    safe_free(&temp); // Libère temp après usage

    // Copie le contenu de s2 dans s1
    for (j = 0; s2[j] && s2[j] != '\n'; j++)
    {
        (*s1)[i] = s2[j];
        i++;
    }
    if (s2[j] == '\n')
        (*s1)[i++] = '\n';

    (*s1)[i] = '\0'; // Null termine la nouvelle chaîne
}

int main()
{
    char *copy = NULL;
    char *line = NULL;

    ft_strdup(&copy, "cop\ny");
    ft_strdup(&line, "helloooooo");

    printf("Initial line: %s\n", line);
    ft_strjoin(&line, copy); // Joint copy à line
    printf("Final line: %s\n", line);

    safe_free(&line); // Libère la ligne finale
    safe_free(&copy); // Libère copy après usage

    return 0;
}
