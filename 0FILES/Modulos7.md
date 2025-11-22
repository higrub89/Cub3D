
### 🧩 **1. parser**

**Objetivo:** leer el archivo `.cub`, validar rutas, colores, y mapa.
**Subtareas y funciones típicas:**

* Abrir y leer archivo línea por línea → 1–2 funciones
* Parsear rutas de texturas (NO, SO, EA, WE) → 1 función
* Parsear colores (F, C) y convertir a RGB → 1–2 funciones
* Parsear mapa (guardar en matriz) → 1–2 funciones
* Validar formato (duplicados, campos faltantes, etc.) → 2–3 funciones

➡️ **Total estimado:** **7–10 funciones**

---

### 🧱 **2. map**

**Objetivo:** validar el mapa y la posición inicial del jugador.
**Subtareas y funciones típicas:**

* Verificar que el mapa esté cerrado por paredes → 2 funciones
* Verificar caracteres válidos → 1 función
* Detectar y guardar posición inicial del jugador → 1–2 funciones
* Validar dimensiones / espacios vacíos → 1 función

➡️ **Total estimado:** **5–6 funciones**

---

### 🖼️ **3. assets**

**Objetivo:** cargar texturas y preparar colores.
**Subtareas y funciones típicas:**

* Cargar textura XPM → 1–2 funciones
* Convertir a estructura interna (buffer de píxeles) → 1 función
* Cargar colores de suelo/cielo → 1 función
* Liberar texturas al salir → 1 función

➡️ **Total estimado:** **4–6 funciones**

---

### ⚙️ **4. engine**

**Objetivo:** bucle principal, raycasting (DDA), proyección.
**Subtareas y funciones típicas:**

* Inicializar motor / estructuras → 1–2 funciones
* Bucle principal (game loop) → 1 función
* Raycasting: cálculo de rayos + DDA → 3–4 funciones
* Cálculo de proyección vertical (altura paredes, offset textura) → 2–3 funciones
* Control de FPS / tiempo → 1 función

➡️ **Total estimado:** **8–12 funciones**

---

### 🎮 **5. input**

**Objetivo:** gestionar teclado y ratón.
**Subtareas y funciones típicas:**

* Capturar eventos de teclado → 1 función
* Actualizar posición/rotación del jugador (WASD, ←→) → 2–3 funciones
* Opcional: ratón (mirar izquierda/derecha) → 1–2 funciones

➡️ **Total estimado:** **4–6 funciones**

---

### 🧵 **6. render**

**Objetivo:** dibujar cielo, suelo, paredes, minimapa.
**Subtareas y funciones típicas:**

* Dibujar fondo (cielo/suelo) → 1 función
* Dibujar paredes texturizadas → 2–3 funciones
* Dibujar minimapa (bonus) → 2 funciones
* Actualizar pantalla → 1 función

➡️ **Total estimado:** **6–8 funciones**

---

### 🔢 **7. math**

**Objetivo:** operaciones vectoriales y geométricas.
**Subtareas y funciones típicas:**

* Normalizar vectores → 1 función
* Rotar vector (cos/sin) → 1 función
* Calcular distancia / longitud → 1 función
* Conversión ángulo/radianes → 1 función

➡️ **Total estimado:** **4–5 funciones**

---

### 🧰 **8. utils**

**Objetivo:** manejo general y limpieza.
**Subtareas y funciones típicas:**

* Gestión de errores (mensajes + salida limpia) → 1–2 funciones
* Liberación de memoria (estructuras, texturas, mapa) → 2–3 funciones
* Logging / debug opcional → 1 función

➡️ **Total estimado:** **4–6 funciones**

---

## 📊 **Resumen general**

| Módulos
| ----------------- 
| parser           
| map              
| assets           
| engine           
| input            
| render           
| math             
| utils            

