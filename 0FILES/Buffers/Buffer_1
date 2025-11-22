/*
 * ================================================================
 * FUNCIÓN 1: validate_file_extension
 * ================================================================
 * ¿Qué hace?
 * Valida que el archivo tenga extensión .cub
 * 
 * ¿Por qué es necesaria?
 * Cub3D solo debe aceptar archivos .cub según el subject
 * 
 * ¿Cómo funciona?
 * 1. Verifica que el filename no sea NULL
 * 2. Cuenta la longitud del string
 * 3. Verifica que tenga al menos 4 caracteres (".cub")
 * 4. Compara los últimos 4 caracteres con ".cub"
 * 5. Si algo falla, llama ft_ctrl_cleanUp y sale del programa
 * 
 * IMPORTANTE: 
 * - Esta función NO retorna, si es válida simplemente termina
 * - Si falla, ft_ctrl_cleanUp llama a exit(1)
 * ================================================================
 */

void ft_validate_file_extension(t_grl *grl, char *map_file)
{
	int	len;

	// Si no hay filename, error
	if (!map_file)
		ft_ctrl_cleanUp(grl, "File does not exist", 0);
	
	// Calcular longitud del string
	len = ft_strlen(map_file);
	
	// Si tiene menos de 4 caracteres, no puede ser ".cub"
	if (len < 4)
		ft_ctrl_cleanUp(grl, "File name wrong", 0);
	
	// Comparar los últimos 4 caracteres con ".cub"
	// map_file + len - 4 apunta a donde empieza ".cub"
	if (ft_strncmp(map_file + len - 4, ".cub", 4) != 0)
		ft_ctrl_cleanUp(grl, "Wrong Extension", 0);
	
}

/*
 * ================================================================
 * INSTRUCCIONES:
 * 1. Copia esta función a tu archivo code/parse/parse.c
 * 2. Agrega el prototipo a include/cub3D.h:
 *    void    validate_file_extension(t_grl *grl, char *filename);
 * ================================================================
 */

/*
 * ================================================================
 * FUNCIÓN 2: ft_open_file
 * ================================================================
 * ¿Qué hace?
 * Abre el archivo .cub en modo lectura
 * 
 * ¿Por qué es necesaria?
 * Necesitamos abrir el archivo antes de leerlo
 * 
 * ¿Cómo funciona?
 * 1. Llama a open() con O_RDONLY
 * 2. Retorna el file descriptor (fd)
 * 3. Si falla, llama ft_ctrl_cleanUp
 * 
 * IMPORTANTE: 
 * - Retorna fd >= 0 si éxito
 * - Cierra el programa si falla
 * ================================================================
 */

int ft_open_file(t_grl *grl, char *map_file)
{
	int fd;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		ft_ctrl_cleanUp(grl, NULL, 1);
	return (fd);
}

/*
 * ================================================================
 * INSTRUCCIONES:
 * 1. Copia esta función a tu archivo code/parse/parse.c
 * 2. Agrega el prototipo a include/cub3D.h:
 *    int     ft_open_file(t_grl *grl, char *map_file);
 * ================================================================
 */

/*
 * ================================================================
 * FUNCIÓN 3: ft_read_file_content
 * ================================================================
 * ¿Qué hace?
 * Lee TODO el contenido del archivo en un buffer estático
 * 
 * ¿Por qué es necesaria?
 * Necesitamos leer todo el archivo para procesarlo línea por línea
 * 
 * ¿Cómo funciona?
 * 1. Llama a read() con buffer grande estático
 * 2. Cuenta cuántos bytes leyó
 * 3. Retorna el buffer
 * 4. Si falla, llama ft_ctrl_cleanUp
 * 
 * IMPORTANTE: 
 * - Retorna buffer estático, NO liberarlo
 * - Si archivo vacío, llama cleanUp
 * ================================================================
 */

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

/*
 * ================================================================
 * INSTRUCCIONES:
 * 1. Copia esta función a tu archivo code/parse/parse.c
 * 2. Agrega el prototipo a include/cub3D.h:
 *    char    *ft_read_file_content(t_grl *grl, int fd);
 * ================================================================
 */

/*
 * ================================================================
 * FUNCIÓN 4: ft_count_lines
 * ================================================================
 * ¿Qué hace?
 * Cuenta cuántas líneas tiene el buffer
 * 
 * ¿Por qué es necesaria?
 * Necesitamos saber cuántas líneas hay antes de crear el array
 * 
 * ¿Cómo funciona?
 * 1. Recorre el buffer carácter por carácter
 * 2. Cuenta cada '\n' que encuentra
 * 3. Si no termina en '\n', cuenta 1 línea extra
 * 4. Retorna el total de líneas
 * 
 * IMPORTANTE: 
 * - Retorna número de líneas
 * - No modifica el buffer
 * ================================================================
 */

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

/*
 * ================================================================
 * INSTRUCCIONES:
 * 1. Copia esta función a tu archivo code/parse/parse.c
 * 2. Agrega el prototipo a include/cub3D.h:
 *    int     ft_count_lines(char *buffer);
 * ================================================================
 */

/*
 * ================================================================
 * FUNCIÓN 5: ft_allocate_lines_array
 * ================================================================
 * ¿Qué hace?
 * Reserva memoria para array de punteros a líneas
 * 
 * ¿Por qué es necesaria?
 * Necesitamos memoria para guardar punteros a cada línea
 * 
 * ¿Cómo funciona?
 * 1. Reserva memoria con malloc para array
 * 2. Retorna array o llama cleanUp si falla
 * 
 * IMPORTANTE: 
 * - Retorna array de punteros
 * - Cierra programa si malloc falla
 * ================================================================
 */

char **ft_allocate_lines_array(t_grl *grl, int line_count)
{
	char	**lines;

	lines = (char **)malloc(sizeof(char *) * (line_count + 1));
	if (!lines)
		ft_ctrl_cleanUp(grl, "Malloc failed", 0);
	return (lines);
}

/*
 * ================================================================
 * INSTRUCCIONES:
 * 1. Copia esta función a tu archivo code/parse/parse.c
 * 2. Agrega el prototipo a include/cub3D.h:
 *    char    **ft_allocate_lines_array(t_grl *grl, int line_count);
 * ================================================================
 */

/*
 * ================================================================
 * FUNCIÓN 6: ft_split_buffer_lines
 * ================================================================
 * ¿Qué hace?
 * Divide el buffer en líneas asignando punteros
 * 
 * ¿Por qué es necesaria?
 * Necesitamos procesar cada línea por separado
 * 
 * ¿Cómo funciona?
 * 1. Recorre buffer reemplazando '\n' por '\0'
 * 2. Guarda punteros a inicio de cada línea en array
 * 3. Retorna array terminado en NULL
 * 
 * IMPORTANTE: 
 * - MODIFICA el buffer original
 * - Asume que 'lines' ya está reservado
 * ================================================================
 */

char **ft_split_buffer_lines(char *buffer, char **lines)
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
	return (lines);
}
/*
 * ================================================================
 * INSTRUCCIONES:
 * 1. Copia esta función a tu archivo code/parse/parse.c
 * 2. Agrega el prototipo a include/cub3D.h:
 *    char    **ft_split_buffer_lines(char *buffer, char **lines);
 * ================================================================
 */

/*
 * ================================================================
 * FUNCIÓN 7: ft_close_file
 * ================================================================
 * ¿Qué hace?
 * Cierra el file descriptor del archivo
 * 
 * ¿Por qué es necesaria?
 * Siempre debemos cerrar archivos después de usarlos
 * 
 * ¿Cómo funciona?
 * 1. Llama a close() con el fd
 * 2. Si falla, llama ft_ctrl_cleanUp
 * 
 * IMPORTANTE: 
 * - Cierra el archivo después de leerlo
 * - Cierra programa si falla
 * ================================================================
 */

void ft_close_file(t_grl *grl, int fd)
{
	if (close(fd) < 0)
		ft_ctrl_cleanUp(grl, NULL, 1);
}

/*
 * ================================================================
 * INSTRUCCIONES:
 * 1. Copia esta función a tu archivo code/parse/parse.c
 * 2. Agrega el prototipo a include/cub3D.h:
 *    void    ft_close_file(t_grl *grl, int fd);
 * ================================================================
 */
