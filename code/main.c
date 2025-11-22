
#include "../include/cub3D.h"

/**
 * @brief Controlador Principal.
 * Orquesta la secuencia lógica del programa:
 * 1. Parseo (Alex) -> Lee fichero y llena estructuras básicas.
 * 2. Validación Mapa (Alex) -> Asegura que el mapa es cerrado y jugable.
 * 3. Integración (Puente) -> Convierte datos de Alex a datos de Rubén.
 * 4. Motor (Rubén) -> Inicia gráficos y bucle de juego.
 */
void ft_controller(t_grl *grl, const char *map_file)
{
    // 0. Limpieza preventiva
    ft_bzero(grl, sizeof(t_grl));

    // 1. Fase de Parseo y Mapa (Alex)
    printf("🔹 INICIO: Parseando mapa...\n");
    ft_ctrl_parse(grl, map_file);
    ft_ctrl_map(grl);
    printf("✅ PARSE: Mapa validado correctamente.\n");

    // 2. Fase de Integración (Puente)
    printf("🔹 PUENTE: Convirtiendo datos...\n");
    ft_convert_data(grl);
    
    // 3. Fase de Motor (Rubén)
    printf("🔹 MOTOR: Arrancando sistemas gráficos...\n");
    ft_init_motor(grl);       // Inicia MLX y Ventana
    // (ft_load_textures ya se llama dentro de ft_init_motor en tu versión actual)
    
    ft_setup_hooks(grl);      // Configura teclado y cierre
    
    printf("🏁 READY: Iniciando Loop del Juego.\n");
    mlx_loop(grl->engine.mlx);
}

int main (int ac, char **av)
{
    t_grl  grl;
    
    if (ac != 2)
    {
        ft_print_error("Uso: ./cub3D <mapa.cub>");
        return (1);
    }
    ft_controller(&grl, av[1]);
    return (0);
}