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
 * FUNCIÓN 8: ft_is_line_empty
 * ================================================================
 * ¿Qué hace?
 * Determina si una línea está vacía o solo contiene espacios/tabuladores.
 * 
 * ¿Por qué es necesaria?
 * Facilita saltar líneas en blanco cuando separamos cabeceras del bloque
 * del mapa.
 * 
 * ¿Cómo funciona?
 * 1. Si la línea es NULL, se considera vacía.
 * 2. Recorre cada carácter y, si encuentra algo distinto a espacio o tab,
 *    retorna 0.
 * 3. Si finaliza el recorrido sin hallar contenido, retorna 1.
 * ================================================================
 */

int ft_is_line_empty(char *line)
{
	int i;

	if (!line)
		return (1);
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (0); // Caracter encontrado 
		i++;
	}
	return (1); // Si es vacia 
}

/*
 * ================================================================
 * FUNCIÓN 9: ft_is_map_line
 * ================================================================
 * ¿Qué hace?
 * Comprueba si una línea contiene caracteres válidos de mapa (`0`, `1`,
 * `N`, `S`, `E`, `W`), ignorando espacios y tabuladores.
 * 
 * ¿Por qué es necesaria?
 * Permite diferenciar las líneas topológicas de las cabeceras u otros
 * datos antes de delimitar el bloque de mapa.
 * 
 * ¿Cómo funciona?
 * 1. Recorre la línea caracter por caracter.
 * 2. Si encuentra un símbolo de mapa, marca que la línea es candidata.
 * 3. Si aparece un carácter no permitido (distinto de espacio/tab), la
 *    descarta devolviendo 0.
 * 4. Al terminar, retorna 1 sólo si se detectó al menos un símbolo válido.
 * ================================================================
 */

int ft_is_map_line(char *line)
{
	int i;
	int has_tile;

	if (!line)
		return (0);
	i = 0;
	has_tile = 0;
	while (line[i] != '\0')
	{
		if (ft_strchr("01NSEW", line[i]))
			has_tile = 1;
		else if (line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	return (has_tile);
}

/*
 * ================================================================
 * FUNCIÓN 10: ft_find_map_start_index
 * ================================================================
 * ¿Qué hace?
 * Busca en el array de líneas el índice donde comienza el bloque de mapa.
 * 
 * ¿Por qué es necesaria?
 * Para separar cabeceras y mapa, necesitamos saber cuál es la primera
 * línea topológica válida.
 * 
 * ¿Cómo funciona?
 * 1. Avanza saltando líneas vacías con `ft_is_line_empty`.
 * 2. Continúa recorriendo hasta encontrar una línea que `ft_is_map_line`
 *    considere válida.
 * 3. Si no encuentra mapa, invoca `ft_ctrl_cleanUp`.
 * ================================================================
 */

int ft_find_map_start_index(t_grl *grl, char **lines)
{
	int i;

	if (!lines)
		ft_ctrl_cleanUp(grl, "Lines array missing", 1);
	i = 0;
	while (lines[i] && ft_is_line_empty(lines[i]))
		i++;
	while (lines[i])
	{
		if (ft_is_map_line(lines[i]))
			return (i);
		i++;
	}
	ft_ctrl_cleanUp(grl, "Map block not found", 1);
	return (-1);
}

/*
 * ================================================================
 * FUNCIÓN 11: ft_guard_against_map_gap
 * ================================================================
 * ¿Qué hace?
 * Recorre las líneas vacías posteriores al mapa y verifica que no existan
 * celdas válidas tras el hueco.
 * 
 * ¿Por qué es necesaria?
 * Garantiza que el mapa sea un bloque continuo sin segmentos separados
 * por líneas vacías.
 * 
 * ¿Cómo funciona?
 * 1. Avanza mientras encuentre líneas vacías.
 * 2. Si descubre otra línea de mapa tras el hueco, aborta.
 * ================================================================
 */

void ft_guard_against_map_gap(t_grl *grl, char **lines, int idx)
{
	if (!lines)
		ft_ctrl_cleanUp(grl, "Lines array missing", 1);
	while (lines[idx] && ft_is_line_empty(lines[idx]))
		idx++;
	if (lines[idx] && ft_is_map_line(lines[idx]))
		ft_ctrl_cleanUp(grl, "Map has gaps", 1);
}

/*
 * ================================================================
 * FUNCIÓN 12: ft_find_map_end_index
 * ================================================================
 * ¿Qué hace?
 * Determina el último índice del bloque de mapa asegurando continuidad.
 * 
 * ¿Por qué es necesaria?
 * Evita que existan huecos o contenido extraño dentro de la región del
 * mapa crudo antes de pasarlo al módulo siguiente.
 * 
 * ¿Cómo funciona?
 * 1. Valida que `map_start` apunte a una línea de mapa.
 * 2. Avanza desde `map_start` guardando el último índice con datos válidos.
 * 3. Si aparece una línea vacía, delega en `ft_guard_against_map_gap`.
 * ================================================================
 */

int ft_find_map_end_index(t_grl *grl, char **lines, int map_start)
{
	int i;
	int last_map;

	if (!lines || map_start < 0 || !lines[map_start])
		ft_ctrl_cleanUp(grl, "Invalid map start index", 1);
	i = map_start;
	last_map = map_start;
	while (lines[i])
	{
		if (ft_is_map_line(lines[i]))
			last_map = i;
		else if (ft_is_line_empty(lines[i]))
		{
			ft_guard_against_map_gap(grl, lines, i + 1);
			return (last_map);
		}
		else
			ft_ctrl_cleanUp(grl, "Invalid content inside map", 1);
		i++;
	}
	return (last_map);
}
