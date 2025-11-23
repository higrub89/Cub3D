#include "../../include/cub3D.h"

// ** para comentarios de estructura. 
// ** Recolector Responsabilidades.
void ft_map_array(t_grl *grl, const char *map_file)  // (0xFF.cub) -> (map(array mapeo buffstatic))
{
    // ** Variables internas. 
    int 	fd;
	char 	*buffer;
	int 	line_count;

    // ** Responsabilidad de 5-10 funciones 
    ft_validate_file_extension(grl, map_file);              // Validar extension .cub
    fd = ft_open_file(grl, map_file);                       // Abrir archivo
	buffer = ft_read_file_content(grl, fd);                 // Leer contenido a buff static
	line_count = ft_count_lines(buffer);                    // contar lineas -> 
	grl->map = ft_allocate_lines_array(grl, line_count);    // Reservamos array
	ft_split_buffer_lines(buffer, grl->map);                // Mapear array 
	ft_close_file(grl, fd);                                 // Cerrar archivo 
    // imprimir_vector(grl->map);         // Prueba provisional antes de sacar lines. 
}

void ft_validate_file_extension(t_grl *grl, const char *map_file)
{
	int	len;
	
	if (!map_file) // Exista valor en 0XFF (map_file)
		ft_ctrl_cleanUp(grl, "File does not exist", 1);
	len = ft_strlen(map_file); 
	if (len < 4) // Si tiene menos de 4 caracteres, no puede ser ".cub"
		ft_ctrl_cleanUp(grl, "Filename wrong", 1);
	if (ft_strncmp(map_file + len - 4, ".cub", 4) != 0) // Validar extension
		ft_ctrl_cleanUp(grl, "Wrong Extension", 1);
}

int ft_open_file(t_grl *grl, const char *map_file)
{
	int fd;

	fd = open(map_file, O_RDONLY);	// Abrimos archivo 
	if (fd < 0)
		ft_ctrl_cleanUp(grl, NULL, 1);
	return (fd);
}

char *ft_read_file_content(t_grl *grl, int fd)
{
	static char	buffer[100000]; // creamos buffer estatico 100,000 bytes
	ssize_t		bytes_read;

	bytes_read = read(fd, buffer, 100000); // Rellenamos el mapa de forma lineal. 
	if (bytes_read < 0)
		ft_ctrl_cleanUp(grl, NULL, 1);
	if (bytes_read == 0)
		ft_ctrl_cleanUp(grl, "File is empty", 1);
	buffer[bytes_read] = '\0';
	return (buffer);	// devolvemos buffer con los datos del .cub
}

int	ft_count_lines(char *buffer)
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