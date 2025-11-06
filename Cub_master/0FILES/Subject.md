**cub3D**
#### Mi primer RayCaster con miniLibX

**Resumen:** Este proyecto está inspirado en el mundialmente famoso juego Wolfenstein 3D, el cual es considerado el primer FPS jamás creado. Te permitirá explorar el trazado de rayos (*ray-casting*). Tu objetivo será crear una vista dinámica dentro de un laberinto, donde tendrás que encontrar tu camino.
**Versión:** 11.0

### Contenidos
I Prólogo 2
II Objetivos 4
III Instrucciones Comunes 5
IV Instrucciones de IA 7
V Parte obligatoria - cub3D 9
VI Parte Bonus 14
VII Ejemplos 15
VIII Presentación y evaluación por pares 18
1
### Capítulo I

### Prólogo
Desarrollado por Id Software, liderado por los mundialmente conocidos John Carmack y John Romero, y publicado en 1992 por Apogee Software, Wolfenstein 3D es el primer verdadero "First Person Shooter" (Juego de Disparos en Primera Persona) en la historia de los videojuegos.
Figura I.1: John Romero (izquierda) y John Carmack (derecha) posando para la posteridad.
Wolfenstein 3D es el ancestro de juegos como Doom (Id Software, 1993), Doom II (Id Software, 1994), Duke Nukem 3D (3D Realm, 1996) y Quake (Id Software, 1996), que son hitos eternos adicionales en el mundo de los videojuegos.

Ahora, es tu turno de revivir la Historia...
2
cub3D Mi primer RayCaster con miniLibX
El juego Wolfenstein 3D tiene lugar originalmente en la Alemania nazi, lo que podría ser potencialmente inquietante. Las imágenes y la historia de este juego se presentan aquí solo por razones técnicas y por razones de cultura pop/geek, ya que el juego fue considerado una obra maestra por ambas.
3

### Capítulo II
### Objetivos
Los objetivos de este proyecto son similares a todos los objetivos de este primer año: rigor, uso de C, algoritmos básicos, investigación de información, etc..
Como proyecto de diseño gráfico, cub3D te permitirá mejorar tus habilidades en estas áreas: ventanas, colores, eventos, relleno de formas, etc..
En conclusión, **cub3D es un campo de juego notable para explorar las aplicaciones prácticas lúdicas de las matemáticas sin tener que comprender los detalles específicos**.
Con la ayuda de numerosos documentos disponibles en internet, utilizarás las matemáticas como una herramienta para crear algoritmos elegantes y eficientes.
Si esto te conviene, puedes probar el juego original antes de comenzar este proyecto: http://users.atw.hu/wolf3d/.
4

### Capítulo III
### Instrucciones Comunes
*   Tu proyecto debe estar escrito en **C**.
*   Tu proyecto debe estar escrito de acuerdo con la **Norma**. Si tienes archivos/funciones *bonus*, se incluyen en la verificación de la norma, y **recibirás un 0 si hay un error de norma**.
*   Tus funciones **no deben cerrarse inesperadamente** (fallo de segmentación, error de bus, doble liberación de memoria, etc.) excepto por comportamiento indefinido. Si esto ocurre, tu proyecto será considerado no funcional y recibirá un **0 durante la evaluación**.
*   Toda la memoria asignada en el *heap* debe liberarse correctamente cuando sea necesario. Las fugas de memoria (*memory leaks*) no serán toleradas.
*   Si el *subject* lo requiere, debes entregar un **Makefile** que compile tus archivos fuente a la salida requerida con los *flags* **-Wall, -Wextra, y -Werror, usando cc**. Además, tu Makefile no debe realizar enlaces innecesarios (*unnecessary relinking*).
*   Tu Makefile debe contener al menos las reglas **$(NAME), all, clean, fclean y re**.
*   Para entregar *bonus* para tu proyecto, debes incluir una regla *bonus* en tu Makefile, que agregará todos los diversos encabezados, librerías o funciones que no están permitidos en la parte principal del proyecto. Los *bonus* deben colocarse en archivos `_bonus.{c/h}`, a menos que el *subject* especifique lo contrario. La evaluación de las partes obligatoria y *bonus* se lleva a cabo por separado.
*   Si tu proyecto te permite usar tu libft, debes copiar sus fuentes y su Makefile asociado en una carpeta `libft`. El Makefile de tu proyecto debe compilar la librería usando su Makefile, y luego compilar el proyecto.
*   Te animamos a crear programas de prueba para tu proyecto, aunque este trabajo no necesita ser entregado y no será calificado. Te dará la oportunidad de probar fácilmente tu trabajo y el trabajo de tus compañeros. Encontrarás estas pruebas especialmente útiles durante tu defensa. De hecho, durante la defensa, tienes la libertad de usar tus pruebas y/o las pruebas del compañero que estás evaluando.
*   Entrega tu trabajo al repositorio Git asignado. **Solo el trabajo en el repositorio Git será calificado**. Si Deepthought es asignado para calificar tu trabajo, esto ocurrirá después de tus evaluaciones por pares. Si ocurre un error en cualquier sección de tu trabajo durante la calificación de Deepthought, la evaluación se detendrá.
5
cub3D Mi primer RayCaster con miniLibX
6

### Capítulo IV
### Instrucciones de IA

##### * ##### Contexto
Durante tu recorrido de aprendizaje, la IA puede ayudar con muchas tareas diferentes. Tómate el tiempo para explorar las diversas capacidades de las herramientas de IA y cómo pueden apoyar tu trabajo. Sin embargo, siempre abórdalas con precaución y evalúa críticamente los resultados. Ya sea código, documentación, ideas o explicaciones técnicas, nunca puedes estar completamente seguro de que tu pregunta fue bien formulada o de que el contenido generado es preciso. Tus compañeros son un recurso valioso para ayudarte a evitar errores y puntos ciegos.

##### * ##### Mensaje principal
☛ Usa la IA para reducir tareas repetitivas o tediosas.
☛ Desarrolla habilidades de *prompting* —tanto de codificación como no de codificación— que beneficiarán tu futura carrera.
☛ Aprende cómo funcionan los sistemas de IA para anticipar y evitar mejor los riesgos, sesgos y problemas éticos comunes.
☛ Continúa desarrollando habilidades técnicas y habilidades blandas (*power skills*) trabajando con tus compañeros.
☛ **Solo utiliza contenido generado por IA que comprendas completamente y del que puedas asumir la responsabilidad**.

##### * ##### Reglas del estudiante:
*   Debes tomarte el tiempo para explorar las herramientas de IA y comprender cómo funcionan, para que puedas usarlas éticamente y reducir posibles sesgos.
*   Debes reflexionar sobre tu problema antes de hacer el *prompting* — esto te ayuda a escribir *prompts* más claros, detallados y relevantes utilizando vocabulario preciso.
*   Debes desarrollar el hábito de sistemáticamente verificar, revisar, cuestionar y probar cualquier cosa generada por la IA.
*   Siempre debes buscar la revisión de pares — no confíes únicamente en tu propia validación.
7
cub3D Mi primer RayCaster con miniLibX

##### * ##### Resultados de la fase:
*   Desarrollar habilidades de *prompting* tanto de propósito general como específicas del dominio.
*   Aumentar tu productividad con el uso efectivo de herramientas de IA.
*   Continuar fortaleciendo el pensamiento computacional, la resolución de problemas, la adaptabilidad y la colaboración.

##### * ##### Comentarios y ejemplos:
*   Encontrarás regularmente situaciones —exámenes, evaluaciones y más— donde debes demostrar una comprensión real. Prepárate, sigue desarrollando tanto tus habilidades técnicas como interpersonales.
*   Explicar tu razonamiento y debatir con compañeros a menudo revela lagunas en tu comprensión. Haz del aprendizaje entre pares una prioridad.
*   Las herramientas de IA a menudo carecen de tu contexto específico y tienden a proporcionar respuestas genéricas. Tus compañeros, que comparten tu entorno, pueden ofrecer *insights* más relevantes y precisos.
*   Donde la IA tiende a generar la respuesta más probable, tus compañeros pueden proporcionar perspectivas alternativas y matices valiosos. Confía en ellos como un punto de control de calidad.
✓ Buena práctica: Pregunto a la IA: "¿Cómo pruebo una función de ordenamiento?" Me da algunas ideas. Las pruebo y reviso los resultados con un compañero. Refinamos el enfoque juntos.
✗ Mala práctica: Le pido a la IA que escriba una función completa, la copio y pego en mi proyecto. Durante la evaluación por pares, no puedo explicar qué hace ni por qué. Pierdo credibilidad — y suspendo mi proyecto.
✓ Buena práctica: Utilizo la IA para ayudar a diseñar un *parser*. Luego reviso la lógica con un compañero. Detectamos dos *bugs* y lo reescribimos juntos — mejor, más limpio y completamente entendido.
✗ Mala práctica: Dejo que Copilot genere mi código para una parte clave de mi proyecto. Compila, pero no puedo explicar cómo maneja las *pipes*. Durante la evaluación, fallo en justificar y suspendo mi proyecto.
8

### Capítulo V
### Parte obligatoria - cub3D
| Nombre del programa | cub3D |
|---|---|
| Archivos a entregar | Todos tus archivos Makefile all, clean, fclean, re, bonus |
| Argumentos | un mapa en formato *.cub |
| Funciones externas | * open, close, read, write, printf, malloc, free, perror, strerror, exit, gettimeofday. |
| | * Todas las funciones de la librería matemática (-lm man man 3 math). |
| | * gettimeofday(). |
| | * Todas las funciones de la librería MinilibX. |
| Libft autorizada | Sí |
| Descripción | Debes crear una representación gráfica 3D "realista" del interior de un laberinto desde una perspectiva en primera persona. Tienes que crear esta representación utilizando los principios de trazado de rayos (*ray-casting*) mencionados anteriormente. |

Las restricciones son las siguientes:
*   Debes usar la **miniLibX**. Ya sea la versión que está disponible en el sistema operativo, o desde sus fuentes. Si eliges trabajar con las fuentes, deberás aplicar las mismas reglas para tu libft que las escritas anteriormente en la parte de Instrucciones Comunes.
*   La gestión de tu ventana debe seguir siendo **fluida**: cambiar a otra ventana, minimizar, etc..
9
cub3D Mi primer RayCaster con miniLibX
*   Muestra diferentes texturas de pared (la elección es tuya) que varían dependiendo del lado al que se enfrente la pared (**Norte, Sur, Este, Oeste**).
10
cub3D Mi primer RayCaster con miniLibX
*   Tu programa debe poder establecer los colores del **suelo y del techo a dos colores diferentes**.
*   El programa muestra la imagen en una ventana y respeta las siguientes reglas:
    *   Las teclas de flecha izquierda y derecha del teclado deben permitirte mirar a la izquierda y a la derecha en el laberinto.
    *   Las teclas **W, A, S y D** deben permitirte mover el punto de vista a través del laberinto.
    *   Presionar **ESC** debe cerrar la ventana y salir del programa de forma limpia.
    *   Hacer clic en la cruz roja del marco de la ventana debe cerrar la ventana y salir del programa de forma limpia.
*   El uso de imágenes de la librería miniLibX es fuertemente recomendado.
*   Tu programa debe tomar como primer argumento un archivo de descripción de escena con la extensión **.cub**.
*   El mapa debe estar compuesto por solo **6 posibles caracteres**: **0** para un espacio vacío, **1** para una pared, y **N, S, E o W** para la posición inicial del jugador y la orientación de aparición (*spawning*). Este es un mapa válido simple: `111111 100101 101001 1100N1 111111`.
*   **El mapa debe estar cerrado/rodeado por paredes**, si no, el programa debe devolver un error.
*   Excepto por el contenido del mapa, cada tipo de elemento puede estar separado por una o más líneas vacías.
*   Excepto por el contenido del mapa que **siempre debe ser el último**, cada tipo de elemento puede establecerse en cualquier orden en el archivo.
*   Excepto por el mapa, cada tipo de información de un elemento puede separarse por uno o más espacios.
*   El mapa debe ser *parseado* tal como aparece en el archivo. Los espacios son una parte válida del mapa y depende de ti cómo manejarlos. Debes ser capaz de *parsear* cualquier tipo de mapa, siempre y cuando respete las reglas del mapa.
11
cub3D Mi primer RayCaster con miniLibX
*   Excepto por el mapa, cada elemento debe comenzar con su identificador de tipo (compuesto por uno o dos caracteres), seguido de su información específica en un orden estricto:.

*   Textura Norte: NO ./ruta_a_la_textura_norte
    *   identificador: NO
    *   ruta a la textura norte
*   Textura Sur: SO ./ruta_a_la_textura_sur
    *   identificador: SO
    *   ruta a la textura sur
*   Textura Oeste: WE ./ruta_a_la_textura_oeste
    *   identificador: WE
    *   ruta a la textura oeste
*   Textura Este: EA ./ruta_a_la_textura_este
    *   identificador: EA
    *   ruta a la textura este
*   Color del Suelo: F 220,100,0
    *   identificador: F
    *   colores R, G, B en el rango : 0, 255, 255
12
cub3D Mi primer RayCaster con miniLibX
*   Color del Techo: C 225,30,0
    *   identificador: C
    *   colores R, G, B en el rango : 0, 255, 255

*   Ejemplo de la parte obligatoria con una escena .cub minimalista:
```
NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture
F 220,100,0
C 225,30,0
1111111111111111111111111
1000000000110000000000001
1011000001110000000000001
1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

*   Si se encuentra cualquier tipo de mala configuración en el archivo, **el programa debe salir correctamente y devolver "Error\n" seguido de un mensaje de error explícito de tu elección**.
13

### Capítulo VI
### Parte Bonus
Los *bonus* serán evaluados solo si tu parte obligatoria es **perfecta**. Por perfecta, naturalmente, queremos decir que debe estar completo, que no puede fallar, incluso en casos de errores desagradables como uso incorrecto, etc.. Significa que si tu parte obligatoria no obtiene TODOS los puntos durante la calificación, **tus *bonus* serán completamente IGNORADOS**.

Lista de Bonus:
*   Colisiones de pared.
*   Un sistema de minimapa.
*   Puertas que pueden abrirse y cerrarse.
*   *Sprites* animados.
*   Rotar el punto de vista con el ratón.
¡Podrás crear mejores juegos más tarde, no pierdas demasiado tiempo!
Se te permite usar otras funciones o añadir símbolos en el mapa para completar la parte *bonus* siempre y cuando su uso esté justificado durante tu evaluación. También se te permite modificar el formato esperado del archivo de escena para adaptarlo a tus necesidades.
¡Sé inteligente!
14

### Capítulo VII
### Ejemplos
Figura VII.1: Réplica del diseño original de Wolfeinstein3D, usando RayCasting.
Figura VII.2: Ejemplo de cómo podría verse tu proyecto según la parte obligatoria.
15
cub3D Mi primer RayCaster con miniLibX
Figura VII.3: Ejemplo de la parte *bonus* con un minimapa, texturas de suelo y techo, y un *sprite* animado de un famoso erizo.
Figura VII.4: Otro ejemplo de un *bonus* con un HUD, barra de salud, efecto de sombra y un arma que puede disparar.
16
cub3D Mi primer RayCaster con miniLibX
Figura VII.5: Otro ejemplo de un juego *bonus* con un arma de tu elección y el jugador mirando al techo.

Nota: Este documento puede contener imágenes con derechos de autor. Consideramos que este *subject*, creado con fines educativos, está bajo las directrices de Uso Justo (*Fair Use*).
17

### Capítulo VIII
### Presentación y evaluación por pares
Entrega tu tarea a tu repositorio Git como de costumbre. Solo el trabajo dentro de tu repositorio será evaluado durante la defensa. No dudes en verificar dos veces los nombres de tus archivos para asegurarte de que sean correctos.
Durante la evaluación, ocasionalmente se puede solicitar una breve modificación del proyecto. Esto podría involucrar un cambio menor de comportamiento, unas pocas líneas de código para escribir o reescribir, o una característica fácil de añadir.
Si bien este paso puede no ser aplicable a todos los proyectos, debes estar preparado para ello si se menciona en las pautas de evaluación. Este paso tiene como objetivo verificar tu comprensión real de una parte específica del proyecto.
La modificación se puede realizar en cualquier entorno de desarrollo que elijas (por ejemplo, tu configuración habitual), y debería ser factible en unos pocos minutos — a menos que se defina un plazo de tiempo específico como parte de la evaluación. Puedes, por ejemplo, ser solicitado para hacer una pequeña actualización a una función o script, modificar una visualización, o ajustar una estructura de datos para almacenar nueva información, etc..
Los detalles (alcance, objetivo, etc.) se especificarán en las pautas de evaluación y pueden variar de una evaluación a otra para el mismo proyecto.
???????????? XXXXXXXXXX = $3$$796ba5a53df1352e06cc7b0f3ad2a41d
18