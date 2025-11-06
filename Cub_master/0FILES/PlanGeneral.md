# Plan de arquitectura para cub3D (parte obligatoria, Linux/MLX)

### Objetivo

Implementar cub3D cumpliendo el subject (raycasting, parsing `.cub`, controles WASD/←→, texturas NESO, colores techo/suelo) en Linux usando MiniLibX y `libft` propia.

### Capas y responsabilidades

- **app/** (orquestación)
- `main.c`: valida args, inicializa `context`, arranca `game_loop`, salida limpia.
- `context.h/.c`: estructura raíz con punteros a `mlx`, `window`, `image`, `scene`, `player`, `textures`, `input`.
- **platform/** (abstracción MLX para Linux)
- `mlx_platform.h/.c`: init/destroy, create_image, put_image, hooks, time.
- `keys_linux.h`: keycodes Linux (W/A/S/D, arrows, ESC), masks X11.
- `window.h/.c`: create/destroy, loop hook, close events.
- **config/** (parsing `.cub`)
- `parser.h/.c`: `parse_scene(path, Scene*)` con validación.
- `lexer.h/.c`: tokeniza líneas para identificadores `NO/SO/WE/EA`, `F`, `C`, y mapa.
- `map.h/.c`: almacenamiento del mapa (matriz de chars), normalización de filas, chequeo cerrado.
- `colors.h/.c`: parse RGB `F`/`C` a `uint32_t`.
- `paths.h/.c`: rutas de texturas.
- `errors.h/.c`: tipos de error, mensajes, salida "Error\n<detalle>".
- **assets/** (carga de texturas)
- `textures.h/.c`: carga XPM con MLX, valida dimensiones, ownership y liberación.
- **math/**
- `vec2.h/.c`: operaciones 2D (add, sub, dot, norm, rot).
- `angles.h/.c`: rad/deg, normalize_angle.
- **game/**
- `player.h/.c`: posición, dirección, plano cámara; movimiento/rotación con colisión básica.
- `input.h/.c`: estado de teclas, on_key_down/up.
- `loop.h/.c`: `update(ctx, dt)`, `render(ctx)`; integración con MLX loop.
- **render/** (raycasting)
- `raycaster.h/.c`: DDA por rayo, distancia corregida por fish-eye.
- `projection.h/.c`: altura de muro por columna, selección NESO, cálculo de offset X para textura.
- `draw.h/.c`: muros texturizados, techo/suelo en color sólido.
- `image.h/.c`: buffer intermedio (mlx_image), `put_pixel`, lock/unlock si aplica.
- **utils/**
- `str.h`, `mem.h` (pueden envolver `libft`), `safe_alloc.h/.c`.

### Árbol de directorios

- `include/` (headers públicos por capa)
- `src/app/`
- `src/platform/`
- `src/config/`
- `src/assets/`
- `src/math/`
- `src/game/`
- `src/render/`
- `src/utils/`
- `libs/libft/` (tu repo clonado)
- `libs/minilibx-linux/` (MLX Linux)
- `assets/textures/` (NESO.xpm)
- `maps/` (escenas `.cub` de prueba)
- `Makefile`

### Contratos clave (interfaces)

- `parse_scene(const char* path, Scene* out)` retorna `bool` y llena:
- `Scene.textures[4]` rutas; `Scene.floor_color`, `Scene.ceiling_color`; `Scene.map` rectangular y cerrado; `Scene.spawn_pos`, `Scene.spawn_dir` (N/S/E/W).
- `platform_init(Context*)` crea `mlx`, `win`, `image`; `platform_destroy(Context*)` libera todo en orden.
- `textures_load(Context*, Scene*)` carga XPM en `Texture[4]` (NESO) y valida.
- `game_init(Context*, Scene*)` posiciona jugador y plano cámara.
- `loop_update(Context*, float dt)` aplica input/movimiento con colisión (contra '1').
- `render_frame(Context*)` rasteriza columnas y hace `mlx_put_image_to_window`.

### Parsing `.cub` (reglas del subject)

- Aceptar líneas vacías entre elementos (excepto mapa, que es el último bloque).
- Elementos en cualquier orden: `NO/SO/WE/EA`, `F`, `C`; exactamente uno de cada.
- `F/C`: `R,G,B` en [0..255], rechazar fuera de rango o formatos extra.
- Mapa:
- Conservar espacios; normalizar a ancho máximo rellenando con espacios.
- Validar un único spawn `N|S|E|W`.
- Comprobar cerrado: BFS/DFS sobre celdas no-espacio; bordes no deben ser abiertos ni tocar espacios "fuera".

### Raycasting (DDA) resumido

- Por cada columna `x`:
- `camera_x = 2*x/w - 1`, `ray_dir = dir + plane*camera_x`.
- DDA hasta golpear celda '1' (o fin seguro por límites del mapa).
- Distancia perpendicular: `perp = (side == x ? (map_x - pos_x + (1-step_x)/2)/ray_dir_x : ...)`.
- Altura: `line_h = (int)(h / perp)`; `draw_start/end` recortados al viewport.
- Selección textura por `side` y signo del paso; `tex_x` por punto de impacto.
- Muros texturizados; techo/suelo con `C`/`F` sólidos.

### Entradas y eventos (Linux/MLX)

- Keycodes Linux (X11): `W=119, A=97, S=115, D=100, ESC=65307, Left=65361, Right=65363`.
- Hooks: `mlx_hook(win, KeyPress/KeyRelease)`, `mlx_hook(win, DestroyNotify)`; `mlx_loop_hook` para `update+render`.

### Gestión de memoria y errores

- Toda asignación vía `safe_alloc` o verificada; liberar en orden inverso.
- Ruta de salida única `shutdown(Context*, code)`.
- Mensajes de error: `Error\n<detalle>` estrictamente (stdout/stderr según preferencia, pero consistente).

### Build (Linux)

- `CC=cc`, `CFLAGS=-Wall -Wextra -Werror -O2 -g`.
- `INCLUDES=-Iinclude -Ilibs/minilibx-linux -Ilibs/libft`.
- `LDFLAGS=-Llibs/minilibx-linux -lmlx -Llibs/libft -lft -lXext -lX11 -lm`.
- Reglas: `all`, `clean`, `fclean`, `re`, `bonus`, `run`, `valgrind` (opcional si permitido).
- Objetivo: binario `cub3D`.

### Portabilidad (nota rápida)

- Si en macOS en local: cambiar `-lmlx -framework OpenGL -framework AppKit` y keycodes. Mantener capa `platform/` para aislar diferencias.

### Pruebas mínimas

- `maps/valid_simple.cub` (del subject), `maps/open_edge.cub` (debe fallar), `maps/invalid_color.cub`, `maps/dup_tex.cub`.
- Verificar: carga texturas, movimiento, rotación, cierre con ESC y con X.