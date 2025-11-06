#include "../../include/cub3D.h"

void ft_ctrl_cleanUp(t_grl *grl, char *sterror , int exit_code)
{
    if (exit_code == 1)
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
    (void)grl;
    // futuras estructuras por liberar 
}




