#include "get_next_line.h"

void	ft_set_buffer_and_line(char **buffer, char **line)
{
	*buffer = malloc(BUFFER_SIZE * sizeof(char));
	if (!*buffer)
		return ;
	*line = NULL;
}

void	ft_copy_memory_into_line(char **memory, char **line)
{
	*line = ft_strdup(*memory);
	*memory = NULL;
}

char	*ft_in_case_memory(char **memory, char **line, int red)
{
	char	*temp;

	if (ft_strchr(*memory, '\n'))
	{
		temp = ft_strjoin(*line, *memory);
		*line = ft_strdup(temp);
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

void	ft_in_case_no_memory(char **line, char **buffer)
{
	char	*temp;

	temp = ft_strjoin(*line, *buffer);
	*line = ft_strdup(temp);
	free(temp);
}

char	*get_next_line(int fd)
{
	static int	red;
	char		*buffer;
	char		*line;
	static char	*memory;

	ft_set_buffer_and_line(&buffer, &line);
	if (memory && (ft_strchr(memory, '\n') || red != BUFFER_SIZE))
		return (ft_in_case_memory(&memory, &line, red));
	if (memory)
		ft_copy_memory_into_line(&memory, &line);
	red = BUFFER_SIZE;
	while (red == BUFFER_SIZE)
	{
		ft_bzero(buffer, BUFFER_SIZE);
		red = read(fd, buffer, BUFFER_SIZE);
		if (red == 0 && !line)
			return (NULL);
		ft_in_case_no_memory(&line, &buffer);
		if (ft_strchr(buffer, '\n'))
		{
			memory = ft_strdup(ft_strchr(buffer, '\n'));
			break ;
		}
	}
	return (line);
}

int	main()
{
	//////////////////////////////////////////////////////////////
	//TEST WITH A GIVEN FILE
	char	*filename = "text.txt";
	char	*line;
	int		fd = open(filename, O_RDWR);

	if(fd == -1)
		exit(1);

	int i = 1;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("line n°%d = '%s'", i, line);
		i++;
	}

	close(fd);

	return (0);

	//////////////////////////////////////////////////////////////
	//TEST WITH STANDARD INPUT

	/* char *line;

    printf("Entrez plusieurs lignes (Ctrl+D pour finir) :\n");

    while ((line = get_next_line(STDIN_FILENO)) != NULL) {
        printf("%s", line);
        free(line);
    }

    printf("Fin de la saisie.\n");

    return 0; */
}
