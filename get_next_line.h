#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

size_t	ft_strlen(const char *s, char c);
char	*ft_strchr(const char *s, int c);
void	ft_strjoin(char **s1, char *s2);
void	ft_bzero(void *s, size_t n);
void	ft_strdup(char **s, char *str);
//char	*ft_strdup(char *s);
char	*get_next_line(int fd);

#endif