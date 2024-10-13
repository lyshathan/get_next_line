#include "get_next_line.h"

void	ft_set_buffer_and_line(char **buffer, char **line)
{
	*buffer  = malloc(BUFFER_SIZE * sizeof(char));
	if (!*buffer)
		return;
	*line = "";
}

char	*ft_in_case_memory(char **memory, char **line, int red)
{
	char	*temp;

	if (ft_strchr(*memory, '\n'))
	{
		temp = ft_strjoin(*line, *memory);
		*line = strdup(temp);
		temp = ft_strdup(ft_strchr(*memory, '\n'));
		*memory = ft_strdup(temp);
		free(temp);
		return (*line);
	}
	if (red != BUFFER_SIZE)
	{
		*line = ft_strdup(*memory);
		free (*memory);
		*memory = NULL;
		return (*line);
	}
	return (*line);
}

void	ft_in_case_no_memory(char **line, char **buffer, char **memory)
{
	char	*temp;

//	*memory = ft_strdup(ft_strchr(*buffer, '\n'));
	temp = ft_strjoin(*line, *buffer);
	*line = strdup(temp);
	free(temp);
}


char	*get_next_line(int fd)
{
	static int	red;
	char 		*buffer;
	char 		*line;
	static char	*memory;

	ft_set_buffer_and_line(&buffer, &line);
//	printf("memory = #%s#\n\n", memory);
	if (memory)
	{
		if (ft_strchr(memory, '\n') || red != BUFFER_SIZE)
			return (ft_in_case_memory(&memory, &line, red));
		line = ft_strdup(memory);
		memory = NULL;
	}
	red = BUFFER_SIZE;
	while (red == BUFFER_SIZE)
	{
		ft_bzero(buffer, BUFFER_SIZE);
		red = read(fd, buffer, BUFFER_SIZE);
//		printf("red = %d | buffer = %s\n\n", red, buffer);
		if (red == 0 && !line)
			return (NULL);
		ft_in_case_no_memory(&line, &buffer, &memory);
		if (ft_strchr(buffer, '\n'))
		{
			memory = ft_strdup(ft_strchr(buffer, '\n'));
			break;
		}
	}
	return (line);
}

int	main(int arc, char **arv)
{
	(void)arc;
	char *filename = "text.txt";
	char *line;
	int fd = open(filename, O_RDWR);

	if(fd == -1)
		exit(1);

	int i = 0;

	printf("Line n°%d\n", ++i);
	printf("'%s'\n\n", get_next_line(fd));
	printf("Line n°%d\n", ++i);
	printf("'%s'\n\n", get_next_line(fd));
	printf("Line n°%d\n", ++i);
	printf("'%s'\n\n", get_next_line(fd));
	printf("Line n°%d\n", ++i);
	printf("'%s'\n\n", get_next_line(fd));
	printf("Line n°%d\n", ++i);
	printf("'%s'\n\n", get_next_line(fd));
	printf("Line n°%d\n", ++i);
	printf("'%s'\n\n", get_next_line(fd));

	close(fd);

    return 0;
}

/* 	if (memory)
	{
		if (ft_strchr(memory, '\n'))
		{
			temp = ft_strjoin(line, memory);
			line = strdup(temp);
			temp = ft_strdup(ft_strchr(memory, '\n'));
			memory = ft_strdup(temp);
			free(temp);
			return (line);
		}
		if (red != BUFFER_SIZE)
		{
			line = ft_strdup(memory);
			free (memory);
			memory = NULL;
			return (line);
		}
		line = ft_strdup(memory);
		memory = NULL;
	} */

	/* while (bytes_read == BUFFER_SIZE)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		red = bytes_read;
		if (red == 0)
			return (NULL);
		if (ft_strchr(buffer, '\n'))
		{
			memory = ft_strdup(ft_strchr(buffer, '\n'));
			temp = ft_strjoin(line, buffer);
			line = strdup(temp);
			free(temp);
			break;
		}
		else
		{
			temp = ft_strjoin(line, buffer);
			line = strdup(temp);
		}
		ft_bzero(buffer, BUFFER_SIZE);
	} */