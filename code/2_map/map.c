#include "../../include/cub3D.h"

static void	ft_test_map(t_grl *grl);
static void	ft_print_map_dimensions(t_grl *grl);
static void	ft_print_player_info(t_grl *grl);
static void	ft_print_normalized_map(t_grl *grl);
static void	ft_print_solid_map(t_grl *grl);
static void	ft_print_player_direction(int dir);

// Controlador MAP - Recolecta Responsabilidades.
void ft_ctrl_map(t_grl *grl)
{											// Validaciones.
	ft_validate_map_closure(grl); // Valida los bordes 
	ft_validate_player_start(grl); // Posicion de las validaciones 
	ft_validate_map_characters(grl); // Valida caracteres validos
	ft_validate_exterior_access(grl); // Valida acceso desde exterior
	ft_normalize_map_dimensions(grl); // Normaliza dimensiones
	ft_build_navigable_map(grl); // Construye mapa navegable
	ft_store_player_start(grl); // Almacena posicion jugador
	ft_calculate_final_dimensions(grl); // Calcula dimensiones finales
	ft_test_map(grl);
}

void	ft_test_map(t_grl *grl)
{
	printf("\n=== MAP TEST ===\n");
	ft_print_map_dimensions(grl);
	ft_print_player_info(grl);
	ft_print_normalized_map(grl);
	ft_print_solid_map(grl);
	printf("==================\n\n");
}

void	ft_print_map_dimensions(t_grl *grl)
{
	printf("Dimensiones normalizadas:\n");
	printf("  Altura: %d\n", grl->map_height);
	printf("  Ancho: %d\n", grl->map_width);
}

void	ft_print_player_info(t_grl *grl)
{
	printf("Posicion jugador:\n");
	printf("  Fila: %d, Columna: %d\n", grl->player_row, grl->player_col);
	ft_print_player_direction(grl->player_dir);
}

void	ft_print_normalized_map(t_grl *grl)
{
	int	row;

	printf("Mapa normalizado:\n");
	row = 0;
	while (row < grl->map_height)
	{
		if (grl->map_block[row])
			printf("  [%2d]: %s\n", row, grl->map_block[row]);
		row++;
	}
}

void	ft_print_solid_map(t_grl *grl)
{
	int	row;
	int	col;

	printf("Mapa de solidez (1=solido, 0=navegable):\n");
	row = 0;
	while (row < grl->map_height)
	{
		printf("  [%2d]: ", row);
		col = 0;
		while (col < grl->map_width)
		{
			if (grl->solid_map && grl->solid_map[row])
				printf("%d", grl->solid_map[row][col]);
			col++;
		}
		printf("\n");
		row++;
	}
}

void	ft_print_player_direction(int dir)
{
	printf("  Direccion: ");
	if (dir == 0)
		printf("Norte (N)\n");
	else if (dir == 1)
		printf("Sur (S)\n");
	else if (dir == 2)
		printf("Este (E)\n");
	else if (dir == 3)
		printf("Oeste (W)\n");
	else
		printf("Desconocida\n");
}