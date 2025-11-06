# 42Project

**🧱 Cub3D (raycasting):**

* Simula 3D desde un mapa 2D.
* Usa **raycasting**: lanza rayos en 2D para detectar paredes y proyectarlas en pantalla.
* Menor carga matemática: trigonometría básica (sen, cos).
* Se centra en **movimiento del jugador**, **colisiones**, **texturas** y **render en tiempo real**.
* Enfocado en **lógica de juego y optimización del bucle principal**.

**🌇 MiniRT (raytracing):**

* Renderiza escenas 3D reales: cada píxel calcula un rayo 3D que choca con objetos.
* Requiere **álgebra vectorial y geométrica** (productos escalar y vectorial, normales, reflexión, luz).
* Sin movimiento: escena estática, pero **alta precisión visual**.
* Se enfoca en **modelado matemático**, **física de la luz** y **estructura de datos para escenas**.
* Mucho más **abstracto y matemático**, menos interactivo.


**🎯 Raycasting:**

* **Qué es:** Técnica rápida para simular 3D usando un mapa 2D (como *Wolfenstein 3D*).
* **Cómo funciona:**

1. Desde la posición del jugador se lanzan **rayos en distintas direcciones**.
2. Cada rayo avanza hasta chocar con una pared en el mapa 2D.
3. Se calcula la **distancia al impacto** → la pared se dibuja más alta o más baja según esa distancia (efecto de profundidad).
4. Se repite para cada columna de la pantalla → ilusión de entorno 3D.
* 🔹 Rápido, simple, en tiempo real.
* 🔹 Basado en **ángulos y trigonometría** (sin coordenadas 3D reales).

**🌇 Raytracing:**

* **Qué es:** Simulación física de cómo viaja la luz en un entorno 3D.
* **Cómo funciona:**

1. Cada píxel de la cámara lanza un **rayo 3D** hacia la escena.
2. Se calcula **qué objeto toca primero** (intersección con esferas, planos, cilindros).
3. Se evalúa **la luz**, **sombra**, **reflexión** o **refracción** según materiales.
4. El color final del píxel es el resultado de esas interacciones.
* 🔹 Preciso, realista, pero **lento**.
* 🔹 Requiere **álgebra vectorial** y **geometría espacial**.




Tiempo estimado:
* Cub3D ≈ 2–3 semanas.
* MiniRT ≈ 4–6 semanas (más matemático).


🧱 Cub3D — Flujo general:
1. Carga del mapa → se lee el archivo .cub con texturas y layout 2D.
2. Inicialización → posición del jugador, plano de cámara, MLX.
3. Raycasting → en cada frame se lanzan rayos desde la cámara; se detectan paredes y distancias.
4. Proyección → cada pared se dibuja con su textura y altura proporcional a la distancia.
5. Render loop → el bucle MLX actualiza la imagen y maneja eventos (teclas, movimiento, rotación).

🌇 MiniRT — Flujo general:
1. Carga de escena → se parsea un .rt con luces, cámaras y objetos 3D.
2. Inicialización → cámara, vectores de dirección, luz ambiental.
3. Cálculo de rayos → para cada píxel se lanza un rayo; se busca la intersección más cercana.
4. Cálculo de luz → se determina color según materiales, sombras, reflexión, etc.
5. Render final → se guarda la imagen (BMP) o se muestra en ventana.