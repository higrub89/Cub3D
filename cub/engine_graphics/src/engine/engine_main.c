#include "../include/cub3D.h"

/*
** Mock de la función de limpieza (temporal)
** Usamos el prototipo real de cleanUp.c
*/
void	ft_ctrl_cleanUp(t_grl *grl, char *sterror, int exit_code)
{
	if (sterror)
	{
		write(2, "Error\n", 6);
		write(2, sterror, ft_strlen(sterror));
		write(2, "\n", 1);
	}
	// (Aquí liberarías la memoria del mock map, etc.)
	printf("--- Limpieza simulada ---\n");
	if (grl) // Para que no dé error de 'unused variable'
		exit(exit_code);
	exit(exit_code);
}

int	main(void)
{
	t_grl	grl;

	// Inicializar la estructura a cero (importante)
	ft_bzero(&grl, sizeof(t_grl));
	// 1. Rellenar la estructura con datos falsos (tu mock)
	ft_init_mock_data(&grl);
	// 2. Imprimir el mapa para verificar
	printf("\n--- Mapa Falso Cargado ---\n");
	for (int i = 0; grl.map.grid[i]; i++)
		printf("%s\n", grl.map.grid[i]);
	printf("------------------------\n");
	// (PRÓXIMO PASO: ft_init_motor(&grl );)
	// 3. Limpiar (temporal)
	ft_ctrl_cleanUp(&grl, NULL, 0);
	return (0);
}

/*
#include <errno.h>

typedef struct s_grl
{
	// Estructura general que contendrá TODO lo que se reserve en memoria
	// Se irá completando conforme avancemos
}		t_grl;

// // MAIN // //
void	ft_controller(t_grl *grl, const char *map_file);

// PARSE
void	ft_ctrl_parse(t_grl *grl, const char *map_file);
void	ft_validate_file_extension(t_grl *grl, const char *map_file);
int		ft_open_file(t_grl *grl, const char *map_file);
char	*ft_read_file_content(t_grl *grl, int fd);
int		ft_count_lines(char *buffer);
char	**ft_allocate_lines_array(t_grl *grl, int line_count);
void	ft_split_buffer_lines(char *buffer, char **lines);
void	ft_close_file(t_grl *grl, int fd);

// CLEANUP
void	ft_ctrl_cleanUp(t_grl *grl, char *sterror, int exit_code);
void	ft_print_error(char *sterror);
void	ft_free(t_grl *grl);

// EXTRAS
void	imprimir_vector(char **v);

#endif
*/