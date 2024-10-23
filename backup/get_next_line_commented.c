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

char	*in_case_memory(char **memory, char **line, char **buffer, size_t red)
{
	char	*temp;

	temp = NULL;
	if (ft_strchr(*memory, '\n'))
		{
			copy_until(line, *memory, '\n');
			printf("line = #%s#\n", *line);
			copy_until(&temp, ft_strchr(*memory, '\n'), '\0');
			printf("temp = #%s#\n", temp);
			copy_until(memory, temp, '\0');
			safe_free(&temp);

			//*memory = ft_strchr(*memory, '\n');
			free(*buffer);
			return (*line);
		}
	else
	{
		copy_until(line, *memory, '\n');
		if (red != BUFFER_SIZE)
		{
		free(*buffer);
			safe_free(memory);
			return (*line);
		}
	}
	safe_free(line);
	return (NULL);
}

void	f_check(char **line, char **buffer, char **memory)
{
	join_until(line, *buffer, '\n');
	////printf("line = #%s#\n", line);
	//printf("leaks check memory = #%s#\n", *memory);
	//clear_string(memory);
	copy_until(memory, ft_strchr(*buffer, '\n'), '\0');
	////printf("memory = #%s#\n", memory);
}

char	*get_next_line(int fd)
{
	static char		*memory;
	static size_t	red;
	char			*line;
	char			*buffer;

	// printf("> Initial memory = #%s#\n", memory);
	// printf("> Red = %zu\n", red);
	if (fd < 0)
		return (NULL);
	set_buffer_and_line(&buffer, &line);
	// printf("> Line = #%s#\n", line);
	// printf("> Buffer = #%s#\n", buffer);
	if (memory && *memory)
	{
		// if (ft_strchr(memory, '\n'))
		// {
		// 	printf("== NEWLINE IN MEMORY==\n\n");
		// 	return (in_case_memory(&memory, &line, &buffer, red));
		// }
		// copy_until(&line, memory, '\n');

		if (ft_strchr(memory, '\n') && *ft_strchr(memory, '\n'))
		{
			// printf("==NEWSPACE FOUND IN MEMORY\n");
			char	*temp = NULL;
			copy_until(&line, memory, '\n');
			// printf("line = #%s#\n", line);
			// printf("ft_strchr = #%s#\n", ft_strchr(memory, '\n'));
			copy_until(&temp, ft_strchr(memory, '\n'), '\0');
			// printf("temp = #%s#\n", temp);
			copy_until(&memory, temp, '\0');
			// printf("memory = #%s#\n", memory);
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
		//printf("line = #%s#\n", line);
	}
	////printf("> Line after 1st part = #%s#\n", line);
	red = BUFFER_SIZE;
	while (red == BUFFER_SIZE)
	{
		red = read(fd, buffer, BUFFER_SIZE);
		////printf("red = %zu\n", red);
		////printf("buffer = #%s#\n", buffer);
		////printf("line = #%s#\n", line);
		if (red <= 0 && !line)
		{
			free(buffer);
			safe_free(&line);
			return (NULL);
		}
		if (ft_strchr(buffer, '\n'))
		{
			f_check(&line, &buffer, &memory);
			/* join_until(&line, buffer, '\n');
			////printf("line = #%s#\n", line);
			memory = NULL;
			copy_until(&memory, ft_strchr(buffer, '\n'), '\0');
			////printf("memory = #%s#\n", memory); */
			break;
		}
		else
		{
			join_until(&line, buffer, '\0');
			////printf("line = #%s#\n", line);
			if (red != BUFFER_SIZE)
			{
				free(buffer);
				clear_string(&memory);
				return (line);
			}
		}
		clear_string(&buffer);
	}
	//printf("Left memory = #%s#\n", memory);
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

