#include "../include/cub3D.h"

void ft_controller(t_grl *grl, const char *map_file)
{
    ft_ctrl_parse(grl, map_file);
}

int main (int ac, char **av)
{
    t_grl  grl; // Estructuras unificadas
    
    (void)ac;
    ft_controller(&grl, av[1]);
    return (0);
}