# Plan: Implementación Modular del Parser cub3D

## Metodología de Trabajo

- Implementar función por función con pausas para entender
- Entregar código en `buffer.c` temporal
- Usuario reorganiza en su estructura de carpetas
- Validar y comentar antes de avanzar

## Arquitectura General

```
main.c
  └─> ft_controller(t_grl *grl)
       └─> ft_ctrl_parse(t_grl *grl)
            └─> funciones de parsing específicas
```

## Fases de Implementación

### **FASE 1: Apertura y Validación Básica**

- Validar extensión `.cub`
- Abrir archivo
- Leer contenido línea por línea
- Estructura básica de `t_grl` con puntero al archivo

**Funciones:**

- `validate_file_extension(char *filename)`
- `open_file(char *filename)`
- `read_file_lines(int fd)` → retorna array de strings

---

### **FASE 2: Parsing de Texturas**

- Identificar líneas con NO, SO, WE, EA
- Extraer rutas de texturas
- Validar existencia de archivos
- Estructura `t_config` con texturas

**Funciones:**

- `is_texture_line(char *line)`
- `parse_texture(char *line, char **texture_path)`
- `validate_texture_path(char *path)`
- `parse_all_textures(char **lines, t_config *config)`

---

### **FASE 3: Parsing de Colores**

- Identificar líneas F y C
- Parsear formato RGB (R,G,B)
- Validar rangos 0-255
- Convertir a formato utilizable (int hex)

**Funciones:**

- `is_color_line(char *line)`
- `parse_rgb(char *line, int *r, int *g, int *b)`
- `validate_rgb_range(int r, int g, int b)`
- `rgb_to_hex(int r, int g, int b)`
- `parse_colors(char **lines, t_config *config)`

---

### **FASE 4: Parsing del Mapa (Lectura)**

- Identificar dónde empieza el mapa
- Leer todas las líneas del mapa
- Validar caracteres permitidos (0,1,N,S,E,W,espacio)
- Crear array 2D del mapa

**Funciones:**

- `find_map_start(char **lines)`
- `is_valid_map_char(char c)`
- `validate_map_chars(char **map_lines)`
- `create_map_grid(char **map_lines, t_map *map)`

---

### **FASE 5: Validación del Jugador**

- Encontrar posición del jugador (N/S/E/W)
- Validar que haya exactamente 1 jugador
- Guardar posición y orientación
- Estructura `t_player`

**Funciones:**

- `is_player_char(char c)`
- `find_player_position(char **grid, t_player *player)`
- `validate_single_player(char **grid)`
- `set_player_orientation(char c, t_player *player)`

---

### **FASE 6: Validación del Mapa (Cerrado)**

- Verificar que el mapa esté rodeado de paredes
- Implementar flood fill para detectar huecos
- Validar espacios dentro del mapa
- Validar bordes del mapa

**Funciones:**

- `validate_map_borders(char **grid, int width, int height)`
- `flood_fill(char **grid_copy, int x, int y)`
- `validate_map_closed(t_map *map)`

---

### **FASE 7: Integración y Controlador**

- Función `ft_ctrl_parse` que orquesta todo
- Manejo centralizado de errores
- Función de liberación de memoria
- Integración con `ft_controller`

**Funciones:**

- `ft_ctrl_parse(t_grl *grl, char *filename)`
- `print_error(char *msg)`
- `free_parse_data(t_grl *grl)`
- Actualizar `ft_controller` en main.c

---

## Estructuras de Datos (se crean conforme se necesiten)

```c
// Se implementarán una por una según la fase:
typedef struct s_config  // Fase 2-3
typedef struct s_map     // Fase 4
typedef struct s_player  // Fase 5
typedef struct s_grl     // Integra todo
```

## Orden de Archivos a Crear/Modificar

1. `buffer.c` - archivo temporal para entregar funciones
2. `includes/cube3d.h` - agregar estructuras y prototipos
3. Usuario organiza funciones en `code/parse/` según prefiera
4. Actualizar `code/main.c` con la integración final