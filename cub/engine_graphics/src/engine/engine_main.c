#include "../include/cub3D.h"

/*
** Mock de la función de limpieza (temporal)
** Usamos el prototipo real de cleanUp.c
*/
void    ft_ctrl_cleanUp(t_game *game, char *sterror, int exit_code)
{
    if (sterror)
    {
        write(2, "Error\n", 6);
        write(2, sterror, ft_strlen(sterror));
        write(2, "\n", 1);
    }
    // (Aquí liberarías la memoria del mock map, etc.)
    printf("--- Limpieza simulada ---\n");
    if (game) // Para que no dé error de 'unused variable'
        exit(exit_code);
    exit(exit_code);
}

int main(void)
{
    t_game  game;

    // Inicializar la estructura a cero (importante)
    ft_bzero(&game, sizeof(t_game));

    // 1. Rellenar la estructura con datos falsos (tu mock)
    ft_init_mock_data(&game);

    // 2. Imprimir el mapa para verificar
    printf("\n--- Mapa Falso Cargado ---\n");
    for (int i = 0; game.map.grid[i]; i++)
        printf("%s\n", game.map.grid[i]);
    printf("------------------------\n");
    
    // (PRÓXIMO PASO: ft_init_motor(&game);)

    // 3. Limpiar (temporal)
    ft_ctrl_cleanUp(&game, NULL, 0);
    return (0);
}