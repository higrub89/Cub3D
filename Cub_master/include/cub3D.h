#ifndef CUBE3D_H
# define CUBE3D_H

# include "../libft/include/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>

typedef struct s_grl
{
    // Estructura general que contendrá TODO lo que se reserve en memoria
    // Se irá completando conforme avancemos
}   t_grl;

// // MAIN // // 
void    ft_controller(t_grl *grl, const char *map_file);

// PARSE
void    ft_ctrl_parse(t_grl *grl, const char *map_file);
void    ft_validate_file_extension(t_grl *grl, const char *map_file);
int     ft_open_file(t_grl *grl, const char *map_file);
char    *ft_read_file_content(t_grl *grl, int fd);
int     ft_count_lines(char *buffer);
char    **ft_allocate_lines_array(t_grl *grl, int line_count);
void    ft_split_buffer_lines(char *buffer, char **lines);
void    ft_close_file(t_grl *grl, int fd);

// CLEANUP
void    ft_ctrl_cleanUp(t_grl *grl, char *sterror, int exit_code);
void    ft_print_error(char *sterror);
void    ft_free(t_grl *grl);

// EXTRAS 
void imprimir_vector(char **v);

#endif