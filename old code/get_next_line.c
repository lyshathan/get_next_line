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
	ft_strdup(line, *memory);							//set line with memory
	safe_free(*memory);
}

char	*ft_in_case_memory(char **memory, char **line, int red, char *buffer)
{
	char	*temp;
	temp = NULL;

	if (ft_strchr(*memory, '\n'))						//if newline found in memory
	{
		ft_strjoin(line, *memory);						//concatenate memory until newline into line
		ft_strdup(&temp, ft_strchr(*memory, '\n'));
		ft_strdup(memory, temp);
		safe_free(temp);
		safe_free(buffer);
		return (*line);
	}
	if (red != BUFFER_SIZE)
	{
		ft_strdup(line, *memory);
		safe_free(temp);
		safe_free(*memory);
		safe_free(buffer);
		return (*line);
	}
	safe_free(temp);
	safe_free(buffer);
	return (*line);
}

char	*get_next_line(int fd)
{
	static int	red;
	char		*buffer;
	char		*line;
	static char	*memory;

	buffer = NULL;
	line = NULL;
	if (fd == -1)
		return (NULL);

	ft_set_buffer_and_line(&buffer, &line);		//Set buffer with BUFFER_SIZE and allocate line
	if (memory && *memory && (ft_strchr(memory, '\n') || red != BUFFER_SIZE))	//if newline in memory or end of file reached
		return (ft_in_case_memory(&memory, &line, red, buffer));
	if (memory && *memory)														//if no newline in memory
		ft_copy_memory_into_line(&memory, &line);

	red = BUFFER_SIZE;
	while (red == BUFFER_SIZE)								//while not end of file
	{
		red = read(fd, buffer, BUFFER_SIZE);
		if (red == 0 && !line)
		{
			safe_free(buffer);
			return (NULL);
		}
		ft_strjoin(&line, buffer);							//concatenate buffer until newline into line  
		if (ft_strchr(buffer, '\n'))						//if newline is found --> keep the end of the line in memory --> BREAK (return line)
		{
			ft_strdup(&memory, ft_strchr(buffer, '\n')); //++++
			break ;
		}
		//ft_bzero(&buffer, BUFFER_SIZE);						//if no newline found --> buffer reset
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
	// safe_free(&line);

	// line = get_next_line(fd);
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


    // while ((line = get_next_line(STDIN_FILENO)) != NULL) {
    //     free(line);
    // }


    // return 0;
}
