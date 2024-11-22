#include "get_next_line.h"

char *get_next_line(int fd)
{
	static char buf[BUFFER_SIZE];
	static int start = 0;
	static int end = 0;
	char *line;
	int len = 0;
	int m = 1;

	line = malloc(sizeof(char));
	if (!line)
		return (NULL);
	line[0] = '\0';
	while (1)
	{
		if (start == end)
		{
			end = read(fd, buf, BUFFER_SIZE);
			start = 0;
			if (end == 0)
			{
				if (line[0] == '\0')
				{
					return (free(line),NULL);
				}
				else
					return (line);
			}
			if (end < 0)
				return (free(line), NULL);
		}
		while (start < end && buf[start] != '\n')
		{
			if (len + 1 >= m)
			{
				m *= 2;
				char *new_line = malloc(m * sizeof(char));
				if (!new_line)
					return (free(line), NULL);
				for (int i = 0; i < len; i++)
					new_line[i] = line[i];
				free(line);
				line = new_line;
			}
			line[len++] = buf[start++];
			line[len] = '\0';
		}

		if (start < end && buf[start] == '\n')
		{
			line[len++] = '\n';
			start++;
			break;
		}
	}
	line[len] = '\0';
	return (line);
}
/*
#include <fcntl.h>
#include <stdio.h>
int main()
{
	int fd = open("test", O_RDONLY);
	char *line;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}*/
