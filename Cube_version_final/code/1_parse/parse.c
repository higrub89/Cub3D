#include "../../include/cub3D.h"

// Controlador PARSEO - Recolecta Responsabilidades.
void    ft_ctrl_parse(t_grl *grl, const char *map_file) 
{
	ft_map_array(grl,  map_file); 
	ft_headers(grl);
	ft_normalize_assets(grl);
	ft_prepare_map_block(grl);
	ft_test_parser(grl);
}

void	ft_test_parser(t_grl *grl)
{
	int	i;

	printf("\n=== PARSER TEST ===\n");
	printf("Texturas normalizadas:\n");
	i = 0;
	while (i < 4)
	{
		if (grl->assets.textures_path[i])
			printf("  [%d]: %s\n", i, grl->assets.textures_path[i]);
		i++;
	}
	printf("Colores RGB:\n");
	printf("  Floor: 0x%06X\n", grl->assets.colors_rgb[0]);
	printf("  Ceiling: 0x%06X\n", grl->assets.colors_rgb[1]);
	printf("Mapa bloque:\n");
	printf("  Dimensiones: %dx%d\n", grl->map_height, grl->map_width);
	printf("  Indices: start=%d, end=%d\n", grl->map_start, grl->map_end);
	if (grl->map_block)
	{
		i = 0;
		while (grl->map_block[i])
		{
			printf("  [%d]: %s\n", i, grl->map_block[i]);
			i++;
		}
	}
	printf("==================\n\n");
}
