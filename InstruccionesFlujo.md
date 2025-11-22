FLUJO DE TRABAJO : 

25 lineas por funcion maximo. 
Si hay responsabilidades mas grandes dividir 

Controlar y manipular la estructura del programa yo, el gpt solo podra escribir en buffer.c 

Creacion de funciones en un archivo llamado buffer.c por modulo siguiendo el plan anteriormente creado.
En la cual se añade informacion como en el siguiente ejemplo

/*
 * ================================================================
 * FUNCIÓN 1: validate_file_extension
 * ================================================================
 * ¿Qué hace?
 * Valida que el archivo tenga extensión .cub
 * 
 * ¿Por qué es necesaria?
 * Cub3D solo debe aceptar archivos .cub según el subject
 * 
 * ¿Cómo funciona?
 * 1. Verifica que el filename no sea NULL
 * 2. Cuenta la longitud del string
 * 3. Verifica que tenga al menos 4 caracteres (".cub")
 * 4. Compara los últimos 4 caracteres con ".cub"
 * 5. Si algo falla, llama ft_ctrl_cleanUp y sale del programa
 * 
 * IMPORTANTE: 
 * - Esta función NO retorna, si es válida simplemente termina
 * - Si falla, ft_ctrl_cleanUp llama a exit(1)
 * ================================================================
 */

void ft_validate_file_extension(t_grl *grl, char *map_file)
{
    int len;

    // Si no hay filename, error
    if (!map_file)
        ft_ctrl_cleanUp(grl, "File does not exist", 0);
    
    // Calcular longitud del string
    len = ft_strlen(map_file);
    
    // Si tiene menos de 4 caracteres, no puede ser ".cub"
    if (len < 4)
        ft_ctrl_cleanUp(grl, "File name wrong", 0);
    
    // Comparar los últimos 4 caracteres con ".cub"
    // map_file + len - 4 apunta a donde empieza ".cub"
    if (ft_strncmp(map_file + len - 4, ".cub", 4) != 0)
        ft_ctrl_cleanUp(grl, "Wrong Extension", 0);
    
}

/*
 * ================================================================
 * INSTRUCCIONES:
 * 1. Copia esta función a tu archivo code/parse/parse.c
 * 2. Agrega el prototipo a include/cub3D.h:
 *    void    validate_file_extension(t_grl *grl, char *filename);
 * ================================================================
 */
---
