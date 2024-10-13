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

	if (memory)
	{
//		printf("--> memory = %s\n", memory);
		if (ft_strchr(memory, '\n'))
		{
			copy2 = ft_strjoin(line, memory);
			line = strdup(copy2);
			copy2 = ft_strdup(ft_strchr(memory, '\n'));
			memory = ft_strdup(copy2);
//			printf("--> memory = %s\n", memory);
			free(copy2);
//			printf("**********\n'%s'\n**********\n\n\n", line);
			return (line);
		}
		if (red != BUFFER_SIZE)
		{
			line = ft_strdup(memory);
//			printf("**********\n'%s'\n**********\n\n\n", line);
			free (memory);
			memory = NULL;
			return (line);
		}
		line = ft_strdup(memory);
		memory = NULL;
	}

	while (bytes_read == BUFFER_SIZE)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		red = bytes_read;
//		printf("bytes_read = %d\n", bytes_read);
		if (red == 0)
		{
//			printf("NO MORE LINE\n");
			return (NULL);
		}
//		printf("buffer = %s\n", buffer);
		if (ft_strchr(buffer, '\n'))
		{
			memory = ft_strdup(ft_strchr(buffer, '\n'));
			copy2 = ft_strjoin(line, buffer);
			line = strdup(copy2);
			free(copy2);
//			printf("--> memory = %s\n\n", memory);
			break;
		}
		else
		{
			copy2 = ft_strjoin(line, buffer);
			line = strdup(copy2);
//			printf("> copy = %s\n\n", line);
		}
		ft_bzero(buffer, BUFFER_SIZE);
	}
//	printf("**********\n'%s'\n**********\n\n\n", line);
	return (line);
}

int	main(int arc, char **arv)
{
	(void)arc;
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