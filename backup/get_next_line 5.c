#include "get_next_line.h"

void	ft_set_buffer_and_line(char **buffer, char **line)
{
	*buffer = malloc(BUFFER_SIZE * sizeof(char));
	if (!*buffer)
		return ;
	*line = malloc(sizeof(char));
	if (!*line)
	{
		free(*buffer);
		*buffer = NULL;
		return ;
	}
	**line = '\0';
}

void	ft_copy_memory_into_line(char **memory, char **line)
{
	if (*line)
		free(*line);
	*line = ft_strdup(*memory);
	if (*memory)
		free(*memory);
	*memory = NULL;
}

char	*ft_in_case_memory(char **memory, char **line, int red, char **buffer)
{
	char	*temp;

	if (ft_strchr(*memory, '\n'))
	{
		ft_strjoin(line, *memory);
		temp = ft_strdup(ft_strchr(*memory, '\n'));
		free(*memory);
		*memory = ft_strdup(temp);
		free(temp);
		free(*buffer);
		return (*line);
	}
	if (red != BUFFER_SIZE)
	{
		if (*line)
			free(*line);
		*line = ft_strdup(*memory);
		free(*memory);
		*memory = NULL;
		free(buffer);
		return (*line);
	}
	return (*line);
}

void	ft_in_case_no_memory(char **line, char **buffer)
{
	ft_strjoin(line, *buffer);
}

char	*get_next_line(int fd)
{
	static int	red;
	char		*buffer;
	char		*line;
	static char	*memory;

	ft_set_buffer_and_line(&buffer, &line);
	if (memory && (ft_strchr(memory, '\n') || red != BUFFER_SIZE))
		return (ft_in_case_memory(&memory, &line, red, &buffer));
	if (memory)
		ft_copy_memory_into_line(&memory, &line);
	while ((red = read(fd, buffer, BUFFER_SIZE))  == BUFFER_SIZE)
	{
		if (red == 0 && !line)
		{
			free(buffer);
			return (NULL);
		}
		ft_in_case_no_memory(&line, &buffer);
		if (ft_strchr(buffer, '\n'))
		{
			memory = ft_strdup(ft_strchr(buffer, '\n'));
			break ;
		}
		ft_bzero(buffer, BUFFER_SIZE);
	}
	free(buffer);
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
	printf("%s\n", line = get_next_line(fd));
	free(line);
	/* printf("%s\n", line = get_next_line(fd));
	free(line);
	printf("%s\n", line = get_next_line(fd));
	free(line);
	printf("%s\n", line = get_next_line(fd));
	free(line); */
	close(fd);

	return (0);


	while ((line = get_next_line(fd)) != NULL)
	{
		printf("line n°%d = '%s'", i, line);
		i++;
	}

	

	//////////////////////////////////////////////////////////////
	//TEST WITH STANDARD INPUT

    printf("Entrez plusieurs lignes (Ctrl+D pour finir) :\n");

    while ((line = get_next_line(STDIN_FILENO)) != NULL) {
        printf("%s", line);
        free(line);
    }

    printf("Fin de la saisie.\n");

    return 0;
}
