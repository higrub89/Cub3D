
// ¡¡Incluimos el .h de NUESTRO módulo!!
#include "../include/cube3D.h"



int main(void)
{
    t_grl  grl; // ¡Usamos t_grl!

    // Inicializar la estructura a cero
    ft_bzero(&grl, sizeof(t_grl));

    // 1. Rellenar la estructura con datos falsos (de mock_init.c)
    ft_init_mock_data(&grl);

    // 2. Imprimir el mapa para verificar
    printf("\n--- Mapa Falso Cargado ---\n");
    // ¡Esto ahora funcionará porque t_grl SÍ tiene .map.grid!
    for (int i = 0; grl.map.grid[i]; i++)
        printf("%s\n", grl.map.grid[i]);
    printf("------------------------\n");
    
    // (PRÓXIMO PASO: ft_init_motor(&grl);)

    // 3. Limpiar
    ft_ctrl_cleanUp(&grl, NULL, 0);
    return (0);
}