Planteamiento de modulos por responsabilidades divididas.

Parser.

Descripción.
Interpreta el archivo `.cub`, separa texturas, colores y mapa crudo, y entrega estructuras intermedias listas para validarse.

Responsabilidades a gran escala sobre ese módulo.
- Leer el fichero de escena y segmentar cada bloque de información.
- Normalizar rutas, números y strings para consumo posterior.


Map.

Descripción. 
Garantiza que el mapa cumpla las reglas topológicas y lo transforma en una malla navegable uniforme.

Responsabilidades a gran escala sobre ese módulo.
- Verificar cierre del mapa, caracteres permitidos y posición inicial única.
- Rellenar huecos o padding necesario para indexación segura.
- Construir estructuras que describen solidez y dimensiones del entorno básico.


Assets. // activos Recursos?

Descripción.
Centraliza texturas y colores, asegurando su carga, acceso y vida útil para el muestreo.

Responsabilidades a gran escala sobre ese módulo.
- Validar y cargar las rutas a texturas definidas en el `.cub`.
- Gestionar formatos de color de suelo y techo.
- Exponer interfaces de lectura de texels para el motor de rayos.


Engine.

Descripción.
Orquesta la simulación núcleo: lanza rayos, calcula intersecciones y compone el frame final en memoria.

Responsabilidades a gran escala sobre ese módulo.
- Ejecutar el algoritmo de raycasting columna por columna sobre la grilla.
- Muestrear texturas y aplicar correcciones de distancia e iluminación básica.
- Ensamblar el buffer completo de imagen que luego consumirá la capa de render.


Input.

Descripción.
Convierte eventos de usuario en acciones de movimiento y rotación, controlando que el jugador permanezca en espacios válidos.

Responsabilidades a gran escala sobre ese módulo.
- Mapear teclas o señales externas a comandos de movimiento/rotación normalizados.
- Aplicar integración cinemática con resolución de colisiones contra el mapa.
- Actualizar el estado del jugador antes de cada ciclo del engine.


Render.

Descripción.
Toma el buffer producido por el engine y lo presenta en pantalla usando la librería gráfica elegida.

Responsabilidades a gran escala sobre ese módulo.
- Gestionar la ventana (apertura, cierre limpiamente, refresco).
- Transferir el frame buffer a la superficie de dibujo (por ejemplo, MiniLibX image).
- Coordinar la sincronización del bucle principal con eventos del sistema.


Math.

Descripción.
Proporciona utilidades matemáticas y de álgebra que sostienen cálculos de raycasting y movimiento.

Responsabilidades a gran escala sobre ese módulo.
- Implementar funciones trigonométricas, normalización de vectores y manejo de ángulos.
- Ofrecer operaciones de matrices/vectores ligeras para rotaciones y proyecciones.
- Garantizar precisión y estabilidad numérica en cálculos repetitivos.

Clean_up.

Descripcion: 
Capa de sistema de limpieza para todas las salidas. 
Uso general:
Salida directa desde cualquier punto del programa, sin propagar errores hacia atras. 

Prototipo : void ft_ctrl_cleanUp(t_grl *grl, char *sterror , int exit_code)
Recibe una estructura general para liberar informacion , 
un string con error por si falla una funcion local o NULL si falla una funcion del sistema y 
un Exit_Code para determinar si imprimir un mensaje de error o salimos con 0