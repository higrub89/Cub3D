#include "../../include/cub3D.h"

// Función auxiliar para destruir el motor gráfico de forma segura
static void ft_free_engine(t_grl *grl)
{
    int i;

    // 1. Limpiar buffer de pantalla
    if (grl->engine.screen_buff.img_ptr)
        mlx_destroy_image(grl->engine.mlx, grl->engine.screen_buff.img_ptr);
    
    // 2. Limpiar texturas (Iteramos las 4)
    i = 0;
    while (i < 4)
    {
        if (grl->engine.textures[i].img_ptr)
            mlx_destroy_image(grl->engine.mlx, grl->engine.textures[i].img_ptr);
        i++;
    }

    // 3. Limpiar ventana
    if (grl->engine.win)
        mlx_destroy_window(grl->engine.mlx, grl->engine.win);

    // 4. Limpiar display y puntero MLX (Crucial en Linux)
    if (grl->engine.mlx)
    {
        mlx_destroy_display(grl->engine.mlx);
        free(grl->engine.mlx);
    }
}

void ft_ctrl_cleanUp(t_grl *grl, char *sterror , int exit_code)
{
    if (exit_code == 1)  // Capa que imprime codigo de error 
        ft_print_error(sterror);
    ft_free(grl);       // Capa que libera memoria. 
    exit(exit_code);    // Salida limpia. 
}

void ft_print_error(char *sterror)
{
    ssize_t bytes_written;
    if (sterror) // errores propios 
    {
        bytes_written = write(2, "Error\n", 6);
        bytes_written = write(2, sterror, ft_strlen(sterror));
    }
    else    // errores sistema
    {
        bytes_written = write(2, "Error\n", 6);
        perror(NULL); 
    }
    (void)bytes_written;
}


void ft_free(t_grl *grl) // futuras estructuras por liberar 
{
    int i;

    if (!grl)
        return ;
    ft_free_engine(grl);
    i = 0;
    while (i < 4)
    {
        if (grl->assets.textures_path[i])
            free(grl->assets.textures_path[i]);
        i++;
    }
    if (grl->map)
        free(grl->map);
    if (grl->map_block)
        ft_free_array(grl->map_block);
    if (grl->solid_map)
    {
        i = 0;
        while (i < grl->map_height)
        {
            if (grl->solid_map[i])
                free(grl->solid_map[i]);
            i++;
        }
        free(grl->solid_map);
    }
}

// Desenpolve propio // Revisar Funcionamienton // 
void ft_free_array(char **array)
{
    char **ptr;    

    ptr = array;
    while(*ptr)
    {
        free(*ptr);
        ptr++;
    }
    free(array);
}
