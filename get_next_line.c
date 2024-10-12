#include "get_next_line.h"

char	*get_next_line(int fd)
{
	int	i;
	int	bytes_read;
	char *buffer;
	char *copy;

	buffer  = malloc(BUFFER_SIZE * sizeof(char));
	if (!buffer)
		return NULL;

	bytes_read = BUFFER_SIZE;

	while (bytes_read == BUFFER_SIZE)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		printf("buffer = %s\n", buffer);
		printf("bytes_read = %d\n\n", bytes_read);
		ft_bzero(buffer, 15);
	}
	return (buffer);
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

	close(fd);

    return 0;
}