/* ************************************************************************** */
/* */
/* engine_render.c                                                           */
/* */
/* Funciones de renderizado y bucle principal.                               */
/* ************************************************************************** */

#include "../../include/cube3D.h"

/**
 * @brief Inicializa el buffer de pantalla (screen_buff) para renderizado.
 */
void    ft_init_screen_buffer(t_grl *grl)
{
    grl->engine.screen_buff.img_ptr = mlx_new_image(grl->engine.mlx, 
                                                    WIN_WIDTH, WIN_HEIGHT);
    if (!grl->engine.screen_buff.img_ptr)
        ft_ctrl_cleanUp(grl, "Error: mlx_new_image() falló", 1);
    
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
 * @brief Pinta un píxel en el buffer de pantalla.
 * No es static porque ft_raycast_walls la necesita.
 */
void    ft_put_pixel(t_grl *grl, int x, int y, int color)
{
    char    *dst;

    if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
        return;
    
    dst = grl->engine.screen_buff.addr + 
          (y * grl->engine.screen_buff.line_len + 
           x * (grl->engine.screen_buff.bpp / 8));
    
    *(unsigned int*)dst = color;
}

/**
 * @brief Renderiza el techo y el suelo (mitad y mitad).
 * Definida como static y ANTES de su uso en ft_game_loop.
 */
static void ft_render_floor_ceiling(t_grl *grl)
{
    int x;
    int y;
    int half_height;
    
    half_height = WIN_HEIGHT / 2;
    
    // Renderizar techo (mitad superior)
    y = 0;
    while (y < half_height)
    {
        x = 0;
        while (x < WIN_WIDTH)
        {
            ft_put_pixel(grl, x, y, grl->map.ceiling_color);
            x++;
        }
        y++;
    }
    
    // Renderizar suelo (mitad inferior)
    while (y < WIN_HEIGHT)
    {
        x = 0;
        while (x < WIN_WIDTH)
        {
            ft_put_pixel(grl, x, y, grl->map.floor_color);
            x++;
        }
        y++;
    }
}

/**
 * @brief Orquestador del Raycasting.
 * Itera cada columna x, calcula el rayo y dibuja la línea vertical.
 */
void    ft_raycast_walls(t_grl *grl)
{
    t_ray   ray;
    int     x;
    int     y;

    x = 0;
    while (x < WIN_WIDTH)
    {
        // 1. Inicializar y calcular pasos (en engine_raycast.c)
        ft_init_ray(&ray, grl, x);
        ft_calc_step(&ray, grl);
        
        // 2. Ejecutar DDA para encontrar pared
        ft_perform_dda(&ray, grl);
        
        // 3. Calcular alturas y colores
        ft_calc_wall_height(&ray);
        ft_get_wall_color(&ray);
        
        // 4. Dibujar la línea vertical
        y = ray.draw_start;
        while (y < ray.draw_end)
        {
            ft_put_pixel(grl, x, y, ray.color);
            y++;
        }
        x++;
    }
}

/**
 * @brief Loop principal llamado por mlx_loop_hook.
 */
int ft_game_loop(t_grl *grl)
{
    // 1. Pintar fondo (borra el frame anterior)
    ft_render_floor_ceiling(grl);
    
    // 2. Pintar muros (sobre el fondo)
    ft_raycast_walls(grl);
    
    // 3. Volcar buffer a la ventana
    mlx_put_image_to_window(grl->engine.mlx, 
                            grl->engine.win, 
                            grl->engine.screen_buff.img_ptr, 
                            0, 0);
    return (0);
}