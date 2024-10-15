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
	/* *memory = malloc(sizeof(char));
	if (!*memory)
	{
		free(*buffer);
		free(*line);
		*buffer = NULL;
		line = NULL;
		return ;
	}
	**memory = '\0'; */
}

void	ft_copy_memory_into_line(char **memory, char **line)
{
	ft_strdup(line, *memory);							//set line with memory
	if (*memory)
		free(*memory);
}

char	*ft_in_case_memory(char **memory, char **line, int red, char **buffer)
{
	if (ft_strchr(*memory, '\n'))						//if newline found in memory
	{
		ft_strjoin(line, *memory);						//concatenate memory until newline into line
		ft_strdup(memory, ft_strchr(*memory, '\n'));	//reset memory, erasing everything before '\n'
		free(*buffer);
		return (*line);
	}
	if (red != BUFFER_SIZE)
	{
		ft_strdup(line, *memory);
		free(*memory);
		free(*buffer);
		return (*line);
	}
	return (*line);
}

char	*get_next_line(int fd)
{
	static int	red;
	char		*buffer;
	char		*line;
	static char	*memory;

	if (fd == -1)
		return NULL;
	// printf("first memory =	%s\n", memory);
	ft_set_buffer_and_line(&buffer, &line);		//Set buffer with BUFFER_SIZE and allocate line
	if (memory && (ft_strchr(memory, '\n') || red != BUFFER_SIZE))	//if newline in memory or end of file reached
		return (ft_in_case_memory(&memory, &line, red, &buffer));
	if (memory)														//if no newline in memory
		ft_copy_memory_into_line(&memory, &line);
	// printf("line =		#%s#\n", line);
	// printf("memory =	#%s#\n\n", memory);
	red = BUFFER_SIZE;
	// printf("initial red =	%d\n\n", red);
	while (red == BUFFER_SIZE)								//while not end of file
	{
		red = read(fd, buffer, BUFFER_SIZE);
		// printf("red =		%d\n", red);
		// printf("buffer =	#%s#\n", buffer);
		if (red == 0 && !line)
		{
			if (buffer)
				free(buffer);
			if (memory)
				free(memory);
			return (NULL);
		}
		ft_strjoin(&line, buffer);							//concatenate buffer until newline into line
		// printf("line =		#%s#\n", line);
		if (ft_strchr(buffer, '\n'))						//if newline is found --> keep the end of the line in memory --> BREAK (return line)
		{
			// printf("Found newspace in buffer\n");
			ft_strdup(&memory, ft_strchr(buffer, '\n'));
			// printf("memory =	#%s#\n\n", memory);
			break ;
		}
		// printf("memory =	#%s#\n\n", memory);
		ft_bzero(buffer, BUFFER_SIZE);						//if no newline found --> buffer reset
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

	// int i = 1;
	line = get_next_line(fd);
	// printf("\n\nline : ");
	printf("%s\n", line);
	// free(line);

	// line = get_next_line(fd);
	// printf("\n\nline : ");
	// printf("%s\n", line);
	free(line);

	close(fd);
	// free(filename);
	return (0);


	// while ((line = get_next_line(fd)) != NULL)
	// {
		// printf("line n°%d = '%s'", i, line);
	// 	i++;
	// }

	

	// //////////////////////////////////////////////////////////////
	// //TEST WITH STANDARD INPUT

    // printf("Entrez plusieurs lignes (Ctrl+D pour finir) :\n");

    // while ((line = get_next_line(STDIN_FILENO)) != NULL) {
        // printf("%s", line);
    //     free(line);
    // }

    // printf("Fin de la saisie.\n");

    // return 0;
}
