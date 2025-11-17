#include "../include/cube3D.h"

/**
 * @brief Inicializa el buffer de pantalla (screen_buff) para renderizado.
 * Esta función debe ser llamada desde ft_init_motor() después de crear la ventana.
 */
void	ft_init_screen_buffer(t_grl *grl)
{
	// Crear la imagen que servirá como buffer de pantalla
	grl->engine.screen_buff.img_ptr = mlx_new_image(grl->engine.mlx, 
													WIN_WIDTH, WIN_HEIGHT);
	if (!grl->engine.screen_buff.img_ptr)
		ft_ctrl_cleanUp(grl, "Error: mlx_new_image() falló", 1);
	
	// Obtener la dirección de memoria del buffer y sus propiedades
	grl->engine.screen_buff.addr = mlx_get_data_addr(
		grl->engine.screen_buff.img_ptr,
		&grl->engine.screen_buff.bpp,
		&grl->engine.screen_buff.line_len,
		&grl->engine.screen_buff.endian);
	
	grl->engine.screen_buff.width = WIN_WIDTH;
	grl->engine.screen_buff.height = WIN_HEIGHT;
	
	printf("✅ RENDER: Buffer de pantalla inicializado (%dx%d).\n", 
			WIN_WIDTH, WIN_HEIGHT);
}

/**
 * @brief Pinta un píxel en el buffer de pantalla en la posición (x, y).
 * @param grl Estructura principal del juego
 * @param x Coordenada X (0 a WIN_WIDTH-1)
 * @param y Coordenada Y (0 a WIN_HEIGHT-1)
 * @param color Color en formato RGB (0xRRGGBB)
 */
static void	ft_put_pixel(t_grl *grl, int x, int y, int color)
{
	char	*dst;
	
	// Validar coordenadas
	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return;
	
	// Calcular la posición del píxel en el buffer
	dst = grl->engine.screen_buff.addr + 
		  (y * grl->engine.screen_buff.line_len + 
		   x * (grl->engine.screen_buff.bpp / 8));
	
	// Escribir el color (asumiendo formato ARGB o RGB según endian)
	*(unsigned int*)dst = color;
}

/**
 * @brief Renderiza el techo y el suelo usando los colores del mapa mock.
 * Divide la pantalla en dos mitades: techo arriba y suelo abajo.
 */
static void	ft_render_floor_ceiling(t_grl *grl)
{
	int	x;
	int	y;
	int	half_height;
	
	half_height = WIN_HEIGHT / 2;
	
	// Renderizar techo (mitad superior)
	for (y = 0; y < half_height; y++)
	{
		for (x = 0; x < WIN_WIDTH; x++)
		{
			ft_put_pixel(grl, x, y, grl->map.ceiling_color);
		}
	}
	
	// Renderizar suelo (mitad inferior)
	for (y = half_height; y < WIN_HEIGHT; y++)
	{
		for (x = 0; x < WIN_WIDTH; x++)
		{
			ft_put_pixel(grl, x, y, grl->map.floor_color);
		}
	}
}

/**
 * @brief (FASE 3) Loop principal de renderizado.
 * Esta función se llama en cada frame por mlx_loop_hook.
 * Por ahora solo renderiza techo y suelo. Más adelante añadiremos las paredes.
 * 
 * @param grl Estructura principal del juego
 * @return 0 (siempre, requerido por mlx_loop_hook)
 */
int	ft_game_loop(t_grl *grl)
{
	// 1. Renderizar techo y suelo
	ft_render_floor_ceiling(grl);
	
	// 2. (Próximo paso: aquí irá el raycasting de paredes)
	
	// 3. Copiar el buffer a la ventana
	mlx_put_image_to_window(grl->engine.mlx, 
							grl->engine.win, 
							grl->engine.screen_buff.img_ptr, 
							0, 0);
	
	return (0);
}

