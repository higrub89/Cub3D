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
    if (exit_code != 0 && sterror) // CAMBIO MIO === SI ES ERROR IMPRIMIMOS
        ft_print_error(sterror);
    ft_free(grl);
    exit(exit_code);
}

void ft_print_error(char *sterror)
{
    if (sterror) // errores propios 
    {
        write(2, "Error\n", 6);
        write(2, sterror, ft_strlen(sterror));
    }
    else    // errores sistema
    {
        write(2, "Error\n", 6);
        perror(NULL); 
    }
}

void ft_free(t_grl *grl)
{
    //FUNCION QUE DEBE IMPLEMENTAR ALEX PARA EL PARSER
    // NOTA: Cuando Alex teNGA EL parser, aquí iría ft_free_map_data(&grl->map);
    ft_free_mock_data(grl); 

    // 2. Liberamos el motor gráfico
    ft_free_engine(grl);
}



