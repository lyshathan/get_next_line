#include "get_next_line.h"

char	*get_next_line(int fd)
{
	int	i;
	int	bytes_read;
	static int red;
	char *buffer;
	char *line;
	char *copy;
	static char	*memory;

	buffer  = malloc(BUFFER_SIZE * sizeof(char));
	if (!buffer)
		return NULL;

	
	bytes_read = BUFFER_SIZE;

	line = "";

	if (memory)
	{
		if (ft_strchr(memory, '\n'))
		{
			copy = ft_strjoin(line, memory);
			line = strdup(copy);
			copy = ft_strdup(ft_strchr(memory, '\n'));
			memory = ft_strdup(copy);
			free(copy);
			return (line);
		}
		if (red != BUFFER_SIZE)
		{
			line = ft_strdup(memory);
			free (memory);
			return (line);
		}
		line = ft_strdup(memory);
		free (memory);
	}

	while (bytes_read == BUFFER_SIZE)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		red = bytes_read;
		if (red == 0)
			return (NULL);
		if (ft_strchr(buffer, '\n'))
		{
			memory = ft_strdup(ft_strchr(buffer, '\n'));
			copy = ft_strjoin(line, buffer);
			line = strdup(copy);
			free(copy);
			break;
		}
		else
		{
			copy = ft_strjoin(line, buffer);
			line = strdup(copy);
			free(copy);
		}
		ft_bzero(buffer, BUFFER_SIZE);
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
	
	printf("Line n°%d =", ++i);
	printf("'%s'\n\n", get_next_line(fd));
	printf("Line n°%d =", ++i);
	printf("'%s'\n\n", get_next_line(fd));
	printf("Line n°%d =", ++i);
	printf("'%s'\n\n", get_next_line(fd));
	printf("Line n°%d =", ++i);
	printf("'%s'\n\n", get_next_line(fd));
	printf("Line n°%d =", ++i);
	printf("'%s'\n\n", get_next_line(fd));
	printf("Line n°%d =", ++i);
	printf("'%s'\n\n", get_next_line(fd));

	close(fd);

    return 0;
}