# Plan: Implementación del Motor Gráfico (Engine) de cub3D

## 1. Objetivo y Metodología

El objetivo de este módulo es implementar toda la lógica de renderizado gráfico y control del jugador.

La metodología será el **desarrollo aislado (mocking)**. Se creará una función `ft_init_mock_data` que rellenará la estructura `t_game` con un mapa y datos de jugador "falsos" (hardcodeados). Esto permite desarrollar y probar el motor gráfico (`raycasting`, texturas, movimiento) de forma independiente, sin depender de que el módulo de *parsing* esté terminado.

## 2. Estructuras de Datos Clave

Este módulo será el "dueño" (creador y gestor) de las estructuras relacionadas con `miniLibX` y el principal "consumidor" (lector) de las estructuras de `t_mapdata` y `t_player`.

- **`t_engine`**: Contendrá las variables de `miniLibX` (`mlx_ptr`, `win_ptr`), la imagen principal que actúa como *buffer* de pantalla (`t_img screen_buff`), y las 4 imágenes de textura (`t_img textures[4]`).
- **`t_player`**: Leeremos la posición inicial, pero seremos los únicos en **modificar** `pos_x`, `pos_y`, `dir_x`, `dir_y` durante el bucle de juego.
- **`t_mapdata`**: Leeremos `grid`, `floor_color`, `ceiling_color` y las rutas de las texturas.

## 3. Fases de Implementación del Motor

### FASE 1: Conexión y Ventana ("Hola, Mundo" Gráfico)

- **Objetivo:** Abrir una ventana funcional con `miniLibX`.
- **Funciones:** `ft_init_motor(t_game *game)`
- **Pasos:**
    1.  `mlx_init()`: Establecer la conexión con el servidor gráfico.
    2.  `mlx_new_window()`: Crear la ventana con las dimensiones `WIN_WIDTH` y `WIN_HEIGHT`.
    3.  Manejar fallos si `mlx_init` o `mlx_new_window` devuelven `NULL`.
- **Resultado:** Una ventana negra vacía en la pantalla.

### FASE 2: Bucle de Juego y Eventos (Movimiento Básico)

- **Objetivo:** Capturar las entradas del teclado (WASD, Flechas, ESC) y hacer que el programa se cierre limpiamente.
- **Funciones:** `ft_setup_hooks(t_game *game)`, `ft_handle_keypress(int keycode, t_game *game)`, `ft_close_game(t_game *game)`
- **Pasos:**
    1.  `mlx_key_hook()`: Registrar la función `ft_handle_keypress`.
    2.  `mlx_hook(DestroyNotify)`: Registrar `ft_close_game` para la 'X' de la ventana.
    3.  `ft_handle_keypress`: Implementar la lógica para `ESC` (que llama a `ft_close_game`).
    4.  `ft_close_game`: Debe liberar toda la memoria (`free_map`, `mlx_destroy_window`, etc.) y llamar a `exit(0)`.
    5.  `mlx_loop()`: Poner el `main` en espera.
- **Resultado:** Una ventana que se cierra correctamente con `ESC` o la 'X'.

### FASE 3: Renderizado Básico (Techo, Suelo y Movimiento)

- **Objetivo:** Dibujar el cielo y el suelo, y mover al jugador (aún sin muros).
- **Funciones:** `ft_game_loop(t_game *game)`, `ft_update_player(t_game *game)`, `ft_render_background(t_game *game)`
- **Pasos:**
    1.  Crear una imagen (`t_img screen_buff`) que sirva de *buffer* (`mlx_new_image`).
    2.  Implementar `ft_game_loop` y registrarla con `mlx_loop_hook`.
    3.  **En `ft_game_loop`:**
        a.  Llamar a `ft_update_player()` (que actualiza `player.pos_x`, `pos_y`, etc., según las teclas pulsadas).
        b.  Llamar a `ft_render_background()` (que dibuja el color del techo en la mitad superior de `screen_buff` y el del suelo en la mitad inferior).
        c.  Llamar a `mlx_put_image_to_window()` para volcar el *buffer* a la ventana.
- **Resultado:** Una pantalla dividida en dos colores. Al pulsar `W/A/S/D`, el jugador (aún invisible) debería moverse.

### FASE 4: El Núcleo del Raycasting (Muros de Colores)

- **Objetivo:** Lanzar los rayos (Raycasting) y dibujar los muros como líneas verticales de un solo color.
- **Funciones:** `ft_raycast_walls(t_game *game)`, `ft_draw_column(t_game *game, int x, ...)`
- **Pasos:**
    1.  Dentro de `ft_game_loop` (antes de `mlx_put_image_to_window`), llamar a `ft_raycast_walls`.
    2.  **Lógica de `ft_raycast_walls`:**
        a.  Iniciar un bucle `for (x = 0; x < WIN_WIDTH; x++)`.
        b.  **Paso 1 (Cálculo del Rayo):** Calcular la posición y dirección del rayo para la columna `x`.
        c.  **Paso 2 (Algoritmo DDA):** "Caminar" el rayo por la matriz `game->map.grid` hasta que golpee un muro (`'1'`).
        d.  **Paso 3 (Cálculo de Distancia):** Calcular la distancia perpendicular al muro (para evitar el efecto "ojo de pez").
        e.  **Paso 4 (Cálculo de Altura):** Calcular la altura de la línea a dibujar (`line_height = WIN_HEIGHT / perp_dist`).
        f.  **Paso 5 (Dibujo):** Llamar a `ft_draw_column` con los datos calculados.
    3.  **Lógica de `ft_draw_column`:** Dibujar una línea vertical en `screen_buff` en la `x` actual, desde `draw_start` hasta `draw_end`, usando un color diferente según el lado del muro (NO, SO, WE, EA).
- **Resultado:** ¡Un laberinto 3D!  Hecho de muros de colores sólidos.

### FASE 5: Renderizado de Texturas

- **Objetivo:** Reemplazar los muros de colores sólidos con las texturas correctas.
- **Funciones:** `ft_load_textures(t_game *game)`, actualizar `ft_draw_column`.
- **Pasos:**
    1.  Crear `ft_load_textures` que use `mlx_xpm_file_to_image` para cargar las 4 rutas (NO, SO, WE, EA) en `game->engine.textures[4]`.
    2.  Actualizar `ft_draw_column` para que, en lugar de un color, calcule:
        a.  `tex_x`: La coordenada X de la textura (basada en dónde golpeó el rayo).
        b.  `tex_y`: Iterar por la altura del muro, escalando la coordenada Y de la textura.
        c.  Copiar el píxel de la textura al `screen_buff`.
- [cite_start]**Resultado:** El juego completo como se ve en el *subject*[cite: 261].

### FASE 6: Integración y Limpieza Final

- **Objetivo:** Unir el motor con el *parser* de Álex.
- **Pasos:**
    1.  Eliminar la llamada a `ft_init_mock_data()`.
    2.  El `main.c` oficial llamará a `ft_ctrl_parse(game)` (de Álex) y luego a `ft_init_motor(game)` (tuyo).
    3.  Asegurarse de que `ft_ctrl_cleanUp` libera toda la memoria (texturas, imágenes MLX, ventana, `map.grid`, etc.).
    4.  Probar con mapas reales.




