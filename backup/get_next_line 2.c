#include "get_next_line.h"

char	*get_next_line(int fd)
{
	int	i;
	int	bytes_read;
	static int red;
	char *buffer;
	char *line;
	char *copy2;
	static char	*memory;

	buffer  = malloc(BUFFER_SIZE * sizeof(char));
	if (!buffer)
		return NULL;

	
	bytes_read = BUFFER_SIZE;

	line = "";

	printf("=====================================\nNEW FUNCTION CALL\n=====================================\n\n");

	if (memory)
	{
		printf("--> memory = %s\n\n", memory);
		if (ft_strchr(memory, '\n'))
		{
			copy2 = ft_strjoin(line, memory);
			line = strdup(copy2);
			copy2 = ft_strdup(ft_strchr(memory, '\n'));
			memory = ft_strdup(copy2);
			printf("--> memory = %s\n\n", memory);
			free(copy2);
			printf("**********\nline = %s\n**********\n\n\n", line);
			return (line);
		}
		if (red != BUFFER_SIZE)
		{
			printf("red = %d\n", red);
			printf("--> memory = %s\n\n", memory);
			printf("**********\nline = %s\n**********\n\n\n", memory);
			return (memory);
		}
		line = ft_strdup(memory);
		memory = NULL;
	}

	while (bytes_read == BUFFER_SIZE)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		red = bytes_read;
		printf("bytes_read = %d\n", bytes_read);
		printf("buffer = %s\n", buffer);
		if (ft_strchr(buffer, '\n'))
		{
			memory = ft_strdup(ft_strchr(buffer, '\n'));
			copy2 = ft_strjoin(line, buffer);
			line = strdup(copy2);
			free(copy2);
			printf("--> memory = %s\n\n", memory);
			break;
		}
		else
		{
		//	printf("buffer = %s	-->	", buffer);
			copy2 = ft_strjoin(line, buffer);
			line = strdup(copy2);
			printf("> copy = %s\n\n", line);
		}
		ft_bzero(buffer, BUFFER_SIZE);
	}
	printf("**********\nline = %s\n**********\n\n\n", line);
	return (line);
}

int	main()
{
	char *filename = "text.txt";
	char *line;
	int fd = open(filename, O_RDWR);

	if(fd == -1)
	{
		printf("\nError Opening File!!\n");
		exit(1);
	}
	else
		printf("File %s opened sucessfully!\n\n", filename);

	get_next_line(fd);
	get_next_line(fd);
	get_next_line(fd);

	close(fd);

    return 0;
}