#ifndef GNL_H
# define GNL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>

char	*get_next_line(int fd);
size_t	ft_strlen_until(const char *s, char stop);
void	copy_until(char **dest, char *src, char stop);
void	join_until(char **dest, char *src, char stop);
char	*ft_strchr(char *s, char c);
void	safe_free(char **tobefreed);
void	clear_string(char	*string);

# endif
