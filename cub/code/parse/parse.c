#include "../../include/cub3D.h"

void imprimir_vector(char **v)
{
    if (!v)
		printf("FAllo");
    for (size_t i = 0; v[i] != NULL; i++)
        printf("%s\n", v[i]);
}

void    ft_ctrl_parse(t_grl *grl, const char *map_file)
{
    int 	fd;
	char 	*buffer;
	int 	line_count;
	char	**lines;

    ft_validate_file_extension(grl, map_file);
    fd = ft_open_file(grl, map_file);
	buffer = ft_read_file_content(grl, fd);
	line_count = ft_count_lines(buffer);
	lines = ft_allocate_lines_array(grl, line_count);
	ft_split_buffer_lines(buffer, lines);
	ft_close_file(grl, fd);
	// Pruebas fase 1. 
	imprimir_vector(lines);
}

void ft_validate_file_extension(t_grl *grl, const char *map_file)
{
	int	len;
	
	if (!map_file)
		ft_ctrl_cleanUp(grl, "File does not exist", 1);
	len = ft_strlen(map_file); 
	if (len < 4) // Si tiene menos de 4 caracteres, no puede ser ".cub"
		ft_ctrl_cleanUp(grl, "Filename wrong", 1);
	if (ft_strncmp(map_file + len - 4, ".cub", 4) != 0) 
		ft_ctrl_cleanUp(grl, "Wrong Extension", 1);
}

int ft_open_file(t_grl *grl, const char *map_file)
{
	int fd;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		ft_ctrl_cleanUp(grl, NULL, 1);
	return (fd);
}

char *ft_read_file_content(t_grl *grl, int fd)
{
	static char	buffer[100000];
	ssize_t		bytes_read;

	bytes_read = read(fd, buffer, 100000);
	if (bytes_read < 0)
		ft_ctrl_cleanUp(grl, NULL, 1);
	if (bytes_read == 0)
		ft_ctrl_cleanUp(grl, "File is empty", 0);
	buffer[bytes_read] = '\0';
	return (buffer);
}

int ft_count_lines(char *buffer)
{
	int	i;
	int	line_count;

	i = 0;
	line_count = 0;
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
			line_count++;
		i++;
	}
	if (i > 0 && buffer[i - 1] != '\n')
		line_count++;
	return (line_count);
}

char **ft_allocate_lines_array(t_grl *grl, int line_count)
{
	char	**lines;

	lines = (char **)malloc(sizeof(char *) * (line_count + 1));
	if (!lines)
		ft_ctrl_cleanUp(grl, "Malloc failed", 0);
	return (lines);
}

void ft_split_buffer_lines(char *buffer, char **lines)
{
	int	i;
	int	start;
	int	line_idx;

	i = 0;
	start = 0;
	line_idx = 0;
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
		{
			buffer[i] = '\0';
            lines[line_idx] = &buffer[start];
			start = i + 1;
			line_idx++;
		}
		i++;
	}
	if (start < i)
		lines[line_idx++] = &buffer[start];
	lines[line_idx] = NULL;
}

void ft_close_file(t_grl *grl, int fd)
{
	if (close(fd) < 0)
		ft_ctrl_cleanUp(grl, NULL, 1);
}