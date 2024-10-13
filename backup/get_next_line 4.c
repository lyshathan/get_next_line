#include "get_next_line.h"

char 	*ft_in_case_memory(char **memory, char **line, int red)
{
	char	*temp;

	if (ft_strchr(*memory, '\n'))
	{
		temp = ft_strjoin(*line, *memory);
		*line = strdup(temp);
		temp = ft_strdup(ft_strchr(*memory, '\n'));
		*memory = ft_strdup(temp);
		free(temp);
	}
	if (red != BUFFER_SIZE)
	{
		*line = ft_strdup(*memory);
		free (*memory);
		*memory = NULL;
	}
	return (*line);
}

char	*get_next_line(int fd)
{
	int	bytes_read;
	static int red;
	char *buffer;
	char *line;
	char *temp;
	static char	*memory;

	buffer  = malloc(BUFFER_SIZE * sizeof(char));
	if (!buffer)
		return NULL;

	
	bytes_read = BUFFER_SIZE;

	line = "";

	if (memory)
	{
		if (ft_strchr(memory, '\n') || red != BUFFER_SIZE)
		{
			line = ft_in_case_memory(&memory, &line, red);
			return (line);
		}
		line = ft_strdup(memory);
		memory = NULL;
	}

	//while not OEF -> read the next BUFFER_SIZE char
	while (bytes_read == BUFFER_SIZE)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		red = bytes_read;
		//if everything has been read && the is no more memory -> return NULL
		if (red == 0)
			return NULL;
		temp = ft_strjoin(line, buffer);
		line = strdup(temp);
		free (temp);
		if (ft_strchr(buffer, '\n'))
		{
			memory = ft_strdup(ft_strchr(buffer, '\n'));
			break;
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