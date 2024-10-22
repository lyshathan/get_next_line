#include "get_next_line.h"

void	ft_set_buffer_and_line(char **buffer, char **line)
{
	*buffer = malloc(BUFFER_SIZE * sizeof(char));
	if (!*buffer)
		return ;
	*line = NULL;
	// *line = malloc(sizeof(char));
	// if (!*line)
	// {
	// 	safe_free(buffer);
	// 	return ;
	// }
	// **line = '\0';
}

void	ft_copy_memory_into_line(char **memory, char **line)
{
	printf("==ft copy memory into line==\n");
	ft_strdup(line, *memory);							//set line with memory
	safe_free(*memory);
}

char	*ft_in_case_memory(char **memory, char **line, int red, char **buffer)
{
	printf("==ft in case memory==\n");
	char	*temp;
	temp = NULL;
	if (ft_strchr(*memory, '\n'))						//if newline found in memory
	{
		ft_strjoin(line, *memory);						//concatenate memory until newline into line
		printf("to be memorized = #%s#\n", ft_strchr(*memory, '\n'));
		ft_strdup(&temp, ft_strchr(*memory, '\n'));
		ft_strdup(memory, temp);
		safe_free(temp);
		printf("modified memory = #%s#\n", *memory);
		safe_free(*buffer);
		return (*line);
	}
	if (red != BUFFER_SIZE)
	{
		ft_strdup(line, *memory);
		safe_free(temp);
		safe_free(*memory);
		safe_free(*buffer);
		return (*line);
	}
	safe_free(temp);
	safe_free(*buffer);
	return (*line);
}

char	*get_next_line(int fd)
{
	static int	red;
	char		*buffer;
	char		*line;
	static char	*memory;

	if (fd == -1)
		return (NULL);
	printf("first memory =	#%s#\n", memory);
	ft_set_buffer_and_line(&buffer, &line);		//Set buffer with BUFFER_SIZE and allocate line
	if (memory && *memory && (ft_strchr(memory, '\n') || red != BUFFER_SIZE))	//if newline in memory or end of file reached
		return (ft_in_case_memory(&memory, &line, red, &buffer));
	if (memory && *memory)														//if no newline in memory
		ft_copy_memory_into_line(&memory, &line);

	printf("line =		#%s#\n", line);
	printf("memory =	#%s#\n\n", memory);
	red = BUFFER_SIZE;
	printf("initial red =	%d\n\n", red);
	while (red == BUFFER_SIZE)								//while not end of file
	{
		printf("==CASE NO MEMORY==\n");
		red = read(fd, buffer, BUFFER_SIZE);
		printf("red =		%d\n", red);
		printf("buffer =	#%s#\n", buffer);
		if (red == 0 && !line)
		{
			printf("==End of file reached==");
			safe_free(buffer);
			return (NULL);
		}
		ft_strjoin(&line, buffer);							//concatenate buffer until newline into line  
		printf("line =		#%s#\n", line);
		if (ft_strchr(buffer, '\n'))						//if newline is found --> keep the end of the line in memory --> BREAK (return line)
		{
			printf("==Found newspace in buffer==\n");
			ft_strdup(&memory, ft_strchr(buffer, '\n')); //++++
			printf("memory =	#%s#\n\n", memory);
			break ;
		}
		printf("memory =	#%s#\n\n", memory);
		ft_bzero(buffer, BUFFER_SIZE);						//if no newline found --> buffer reset
	}
	safe_free(buffer);
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

	// int i = 0;
	// line = get_next_line(fd);
	// printf("-->line %d : ", ++i);
	// printf("%s\n", line);
	// printf("++++++++++++++++++\n\n");
	// safe_free(&line);

	// line = get_next_line(fd);
	// printf("-->line %d : ", ++i);
	// printf("%s\n", line);
	// printf("++++++++++++++++++\n\n");
	// free(line);


	int i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("-->line %d : ", ++i);
		printf("%s\n", line);
		safe_free(line);
		printf("++++++++++++++++++\n\n");
	}
	printf("-->line %d : ", ++i);
	printf("%s\n", line);
	safe_free(line);
	printf("++++++++++++++++++\n\n");

	


	close(fd);
	return (0);

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
