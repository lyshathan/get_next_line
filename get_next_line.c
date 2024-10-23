#include "get_next_line.h"

void	safe_free(char **tobefreed)
{
	if (*tobefreed && **tobefreed)
	{
		free(*tobefreed);
		*tobefreed = NULL;
	}
}

void	set_buffer_and_line(char **buffer, char **line)
{
	*buffer = NULL;
	*buffer = malloc(BUFFER_SIZE * sizeof(char));
	if (!*buffer)
		return ;
	clear_string(buffer);
	*line = NULL;
}

char	*get_next_line(int fd)
{
	static char		*memory;
	static size_t	red;
	char			*line;
	char			*buffer;

	if (fd < 0)
		return (NULL);
	set_buffer_and_line(&buffer, &line);
	if (memory && *memory)
	{
		if (ft_strchr(memory, '\n') && *ft_strchr(memory, '\n'))
		{
			char	*temp = NULL;
			copy_until(&line, memory, '\n');
			copy_until(&temp, ft_strchr(memory, '\n'), '\0');
			copy_until(&memory, temp, '\0');
			safe_free(&temp);
			free(buffer);
			return (line);
		}
		else
		{
			copy_until(&line, memory, '\n');
			if (red != BUFFER_SIZE)
			{
				free(buffer);
				safe_free(&memory);
				return (line);
			}
		}
	}
	red = BUFFER_SIZE;
	while (red == BUFFER_SIZE)
	{
		red = read(fd, buffer, BUFFER_SIZE);
		if (red <= 0 && !line)
		{
			free(buffer);
			safe_free(&line);
			return (NULL);
		}
		if (ft_strchr(buffer, '\n'))
		{
			join_until(&line, buffer, '\n');
			copy_until(&memory, ft_strchr(buffer, '\n'), '\0');
			break;
		}
		else
		{
			join_until(&line, buffer, '\0');
			if (red != BUFFER_SIZE)
			{
				free(buffer);
				clear_string(&memory);
				return (line);
			}
		}
		clear_string(&buffer);
	}
	free(buffer);
	return (line);
}

int main(int arc, char ** arv)
{
	(void)arc;
	char	*filename = arv[1];
	char	*line;
	int fd = open(filename, O_RDWR);

	if(fd == -1)
		exit(1);

	int i = 1;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("line %d ------> ", i);
		printf("#%s#\n\n", line);
		safe_free(&line);
		i++;
	}
	line = get_next_line(fd);
	printf("line %d ------> ", i);
	printf("#%s#\n\n", line);
	safe_free(&line);

	line = get_next_line(fd);
	printf("line %d ------> ", i);
	printf("#%s#\n\n", line);
	safe_free(&line);

	close(fd);
	return (0);
}

