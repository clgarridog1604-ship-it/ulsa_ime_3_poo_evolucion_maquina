# Práctica Unidad IV: La evolución de una máquina

Programación Orientada a Objetos · Ingeniería Mecatrónica · Tercer semestre

## Sobre esta práctica

**El problema.** La planta de manufactura que conoces del segundo parcial necesita un programa para controlar su línea. Varias máquinas (torno, fresadora, pulidora, estación de inspección y banda transportadora) procesan piezas en ciclos. Cada máquina tiene un nombre, cuenta las piezas que procesa y el tiempo que trabaja, y sabe cuánto tarda un ciclo. La línea ejecuta turnos y genera un reporte con las piezas, el tiempo y la capacidad por hora de cada máquina. Varios equipos de la planta escriben máquinas nuevas, y todos parten de la clase base `Maquina` que tú escribes.

La primera versión de `Maquina` se escribió "rápido": funciona, pero no tiene reglas. Tu trabajo es hacerla evolucionar, etapa por etapa, hasta que el propio diseño impida los errores en lugar de esperar a que alguien los cometa.

**Qué se practica.** Diseño de clases, invariantes y encapsulamiento, constructores `explicit`, enlace estático y dinámico, `virtual` y `override`, slicing, destructor virtual y `= default`, clases abstractas y métodos virtuales puros, contratos entre la clase base y sus derivadas, empleo correcto e incorrecto de la herencia, composición y agregación, espacios de nombres, compilación separada y librerías.

**Idea central.** Cada restricción que agregas a una clase convierte un error silencioso en un error que el compilador o el propio programa detectan. Programar orientado a objetos es escribir clases; diseñar orientado a objetos es decidir qué **no** se puede hacer con ellas.

**Repositorio base.** `ulsa_ime_3_poo_evolucion_maquina`. Harás un fork y trabajarás en tu copia. El repositorio base no trae código: tú creas las carpetas, los archivos y todas las clases.

**Entregable.** El enlace a tu fork en Google Classroom, con el código final en `include/` y `src/`, el `README.md` completo, `diseno_inicial.png`, `diseno_solucion.png` y un historial de commits con al menos un commit por etapa.

**Ritmo.** Es una sola práctica. Iníciala en clase y avanza a tu ritmo. Lo que no termines en clase, lo completas como tarea.

| Fase | Qué haces | Secciones del README |
|---|---|---|
| 0 | Preparar el entorno | Ninguna |
| 1 | Entender el problema | 1.1, 1.2, 1.3 |
| 2 | Diseñar la solución | 2.1 (2.2 y 2.3 al terminar la Fase 3) |
| 3 | Implementar: la evolución en 10 etapas | 3.0 a 3.10 |
| 4 | Probar y mejorar | 4.1, 4.2 |
| 5 | Publicar en GitHub | 5.1 |
| Cierre | Reflexión | 6.1 a 6.4 |

## Fase 0. Preparar el entorno

En esta práctica tú construyes el proyecto desde cero. Si algo falla en esta fase, pregunta en clase de inmediato: es el mejor momento para resolver cualquier problema con tu entorno.

1. Entra al repositorio base y presiona **Fork** para crear tu copia.
2. Clona tu fork en tu computadora.
   - Con terminal: `git clone <url-de-tu-fork>`
   - Con GitHub Desktop: *File > Clone repository*, elige tu fork y una carpeta local.
3. Abre la carpeta en VS Code. Al inicio solo contiene:

```
ulsa_ime_3_poo_evolucion_maquina/
├── .gitignore
├── PRACTICA.md
└── README.md
```

4. Crea las carpetas `include/` y `src/`. Dentro de `src/` crea un `main.cpp` mínimo:

```cpp
#include <iostream>

int main() {
    std::cout << "Planta lista\n";
    return 0;
}
```

5. Desde la raíz del repositorio, compila y ejecuta:

```
g++ -Wall -Wextra -std=c++17 -Iinclude src/*.cpp -o evolucion_maquina
./evolucion_maquina
```

6. Ejecuta `git status`. Debe aparecer `src/main.cpp`, pero no el ejecutable `evolucion_maquina`. Haz tu primer commit con el mensaje `Etapa inicial: estructura del proyecto`.
   - Con terminal: `git add .`, `git commit -m "Etapa inicial: estructura del proyecto"` y `git push`
   - Con GitHub Desktop: escribe el mensaje, presiona **Commit to main** y luego **Push origin**.

Al terminar la práctica tu proyecto se verá así:

```
ulsa_ime_3_poo_evolucion_maquina/
├── include/
│   ├── BandaTransportadora.h
│   ├── ControlDeLinea.h
│   ├── Cortadora.h
│   ├── Fresadora.h
│   ├── InspeccionVisual.h
│   ├── Maquina.h
│   ├── Motor.h
│   ├── Pulidora.h
│   └── Torno.h
├── src/
│   ├── BandaTransportadora.cpp
│   ├── ControlDeLinea.cpp
│   ├── Cortadora.cpp
│   ├── Fresadora.cpp
│   ├── InspeccionVisual.cpp
│   ├── Maquina.cpp
│   ├── Motor.cpp
│   ├── Pulidora.cpp
│   ├── Torno.cpp
│   └── main.cpp
├── .gitignore
├── PRACTICA.md
├── README.md
├── diseno_inicial.png
└── diseno_solucion.png
```

> **Nota técnica.** `-Iinclude` le indica al compilador en qué carpeta buscar los archivos `.h`, y `src/*.cpp` compila todas las implementaciones juntas. `-Wall -Wextra` activa las advertencias. En esta práctica las advertencias son parte del aprendizaje: léelas siempre, aunque el programa compile.

> **Nota técnica.** Git no guarda carpetas vacías. Mientras `include/` no tenga archivos no aparecerá en `git status`; es normal.

> **Nota técnica.** En esta práctica cada etapa termina con un commit. Al final, tu historial de GitHub contará la evolución completa de tu diseño. Haz push después de cada commit para tener siempre un respaldo.

## Fase 1. Entender el problema

Lee el problema de "Sobre esta práctica" dos veces y llena el README.

- **1.1** Explica el problema con tus propias palabras.
- **1.2** Escribe al menos tres reglas que siempre deben cumplirse en cualquier máquina. Por ejemplo, piensa qué valores nunca deberían ser negativos.
- **1.3** Responde: ¿quién más usa la clase `Maquina`? ¿Qué podría salir mal si otro equipo crea una máquina nueva sin conocer tus reglas?

> **Nota conceptual.** Una regla que un objeto debe cumplir siempre, desde que se construye hasta que se destruye, se llama **invariante**. Las reglas de la sección 1.2 son los invariantes de `Maquina`. A lo largo de la práctica verás quién es responsable de hacerlas cumplir.

## Fase 2. Diseñar la solución

En esta práctica dibujarás **dos** diagramas de clases: uno antes de escribir código y otro al terminar. Compararlos te mostrará cuánto cambió el diseño.

**Diagrama inicial.** Antes de empezar la Fase 3, lee la Etapa 0 y dibuja sus tres clases (`Maquina`, `Torno` y `Fresadora`) con sus atributos, sus métodos, su visibilidad y la relación de herencia.

Se sugiere usar **draw.io** (https://app.diagrams.net), que es gratuito, funciona en el navegador sin crear cuenta y también tiene versión de escritorio.

1. Crea un diagrama en blanco y activa la biblioteca de figuras **UML** en el panel izquierdo (*Más figuras > UML*).
2. Usa la figura **Clase** para cada clase, con sus tres secciones: nombre, atributos y métodos.
3. Marca la visibilidad con `+` (público), `-` (privado) y `#` (protegido).
4. Conecta las clases con las flechas de herencia, composición y agregación que correspondan.
5. Exporta con *Archivo > Exportar como > PNG* y guarda el archivo como `diseno_inicial.png` en la raíz del repositorio.

**Diagrama final.** Al terminar la Etapa 9, dibuja el diseño completo y expórtalo como `diseno_solucion.png`, también en la raíz.

Si prefieres otra herramienta o hacerlo a mano y fotografiarlo, también es válido, siempre que los archivos tengan esos nombres y sean legibles.

- **2.1** Verifica que el diagrama inicial se vea en el README.
- **2.2** Al terminar la Fase 3, verifica que el diagrama final se vea en el README.
- **2.3** Al terminar la Fase 3, completa la tabla que compara ambos diagramas.

> **Nota técnica.** En UML, una clase abstracta se escribe con su nombre en *cursiva* o con la etiqueta `«abstract»`, y sus métodos virtuales puros también van en cursiva. La herencia es una flecha con triángulo vacío hacia la base, la composición lleva un rombo relleno y la agregación un rombo vacío, ambos del lado del contenedor.

> **Nota técnica.** Guarda el archivo editable de draw.io (`.drawio`) en tu computadora. Tu diagrama final partirá del inicial, y así no tendrás que dibujarlo de nuevo.

## Fase 3. Implementar: la evolución en 10 etapas

Cada etapa sigue la misma estructura:

1. **Situación.** Qué está pasando en la planta.
2. **Código.** Lo que escribes o cambias. Cuando la guía te da el código de un error, escríbelo tal cual: el error tiene que aparecer para poder estudiarlo.
3. **Ejecuta y observa.** Compila, ejecuta y compara con lo que muestra la guía.
4. **Acertijo.** Responde en el README por qué pasa lo que observaste.
5. **Corrección.** Modifica el diseño. La guía te da las interfaces (`.h`) y tú escribes las implementaciones (`.cpp`).
6. **Commit.** Cierra la etapa con un commit `Etapa N: <descripción>`.

En cada clase, primero declara en el `.h` y después implementa en el `.cpp`. Compila después de cada cambio.

| Etapa | Título | README |
|---|---|---|
| 0 | Una máquina sin reglas | 3.0 |
| 1 | Invariantes y constructores explicit | 3.1 |
| 2 | Virtual y override | 3.2 |
| 3 | La línea de producción | 3.3 |
| 4 | Destructores | 3.4 |
| 5 | La clase abstracta | 3.5 |
| 6 | El contrato que el compilador no ve | 3.6 |
| 7 | La base hace cumplir el contrato | 3.7 |
| 8 | Herencia mal usada | 3.8 |
| 9 | La librería y la prueba final | 3.9 |

Durante toda la fase, registra en la sección **3.10** cada duda que surja, cómo la resolviste y qué fuente consultaste.

---

### Etapa 0. Una máquina sin reglas

**Situación.** Esta es la primera versión del programa. Todo es público, todo "funciona" y nadie pensó en reglas. Escríbela tal cual.

`include/Maquina.h`:

```cpp
#ifndef MAQUINA_H
#define MAQUINA_H

#include <string>

class Maquina {
public:
    std::string nombre;
    int piezasProcesadas;
    int tiempoTrabajadoSeg;

    Maquina(const std::string& nombre);

    void procesar();
    void mostrarEstado() const;
};

#endif
```

`src/Maquina.cpp`:

```cpp
#include "Maquina.h"

#include <iostream>

Maquina::Maquina(const std::string& nombre)
    : nombre(nombre), piezasProcesadas(0), tiempoTrabajadoSeg(0) {}

void Maquina::procesar() {
    std::cout << nombre << ": procesamiento generico\n";
    piezasProcesadas++;
    tiempoTrabajadoSeg += 10;
}

void Maquina::mostrarEstado() const {
    std::cout << nombre << " | piezas: " << piezasProcesadas
              << " | tiempo: " << tiempoTrabajadoSeg << " s\n";
}
```

`include/Torno.h`:

```cpp
#ifndef TORNO_H
#define TORNO_H

#include "Maquina.h"

class Torno : public Maquina {
public:
    Torno(const std::string& nombre);

    void procesar();
};

#endif
```

`src/Torno.cpp`:

```cpp
#include "Torno.h"

#include <iostream>

Torno::Torno(const std::string& nombre) : Maquina(nombre) {}

void Torno::procesar() {
    std::cout << nombre << ": torneando pieza\n";
    piezasProcesadas++;
    tiempoTrabajadoSeg += 45;
}
```

Crea `Fresadora.h` y `Fresadora.cpp` siguiendo el mismo modelo del torno: su `procesar()` imprime `fresando pieza` y suma 60 segundos.

`src/main.cpp`:

```cpp
#include "Fresadora.h"
#include "Maquina.h"
#include "Torno.h"

#include <iostream>

// Ejecuta varios ciclos de cualquier maquina de la planta.
void ejecutarTurno(Maquina& m, int ciclos) {
    for (int i = 0; i < ciclos; i++) {
        m.procesar();
    }
}

int main() {
    Torno torno("Torno T-01");
    Fresadora fresadora("Fresadora F-01");

    std::cout << "--- Llamada directa ---\n";
    torno.procesar();
    fresadora.procesar();

    std::cout << "--- Turno de 2 ciclos ---\n";
    ejecutarTurno(torno, 2);
    ejecutarTurno(fresadora, 2);

    std::cout << "--- Estado ---\n";
    torno.mostrarEstado();
    fresadora.mostrarEstado();

    return 0;
}
```

**Ejecuta y observa.** Compila sin advertencias. Deberías ver:

```
--- Llamada directa ---
Torno T-01: torneando pieza
Fresadora F-01: fresando pieza
--- Turno de 2 ciclos ---
Torno T-01: procesamiento generico
Torno T-01: procesamiento generico
Fresadora F-01: procesamiento generico
Fresadora F-01: procesamiento generico
--- Estado ---
Torno T-01 | piezas: 3 | tiempo: 65 s
Fresadora F-01 | piezas: 3 | tiempo: 80 s
```

**Acertijo (README 3.0).** Llamado directamente, el torno tornea. Dentro de `ejecutarTurno()`, el mismo objeto hace un "procesamiento generico".

- a) ¿Por qué no imprime "torneando" ni "fresando" dentro de `ejecutarTurno()`?
- b) ¿Por qué el torno acumula 65 s y no 135 s?

**Corrección.** En esta etapa no corriges nada: solo entiendes qué pasa. La corrección llega en la Etapa 2.

> **Nota conceptual.** `ejecutarTurno()` recibe un `Maquina&`. Sin `virtual`, el compilador decide qué método llamar según el **tipo declarado** de la variable (`Maquina`), no según el **tipo real** del objeto (`Torno`). Esto se llama **enlace estático**: la decisión se toma al compilar.

> **Nota de C++.** `Torno::procesar()` no sobrescribe a `Maquina::procesar()`: lo **oculta**. Un método con el mismo nombre en la derivada solo "gana" cuando llamas desde una variable del tipo derivado.

**Commit:** `Etapa 0: maquina sin reglas`

---

### Etapa 1. Invariantes y constructores explicit

**Situación.** Un compañero encontró dos formas de obtener reportes absurdos sin que el compilador se quejara.

Agrega esta función a `main.cpp`, antes de `main`:

```cpp
void imprimirFicha(const Maquina& m) {
    std::cout << "Ficha -> ";
    m.mostrarEstado();
}
```

Y reemplaza el contenido de `main` por:

```cpp
    Torno torno("Torno T-01");
    Fresadora fresadora("Fresadora F-01");

    ejecutarTurno(torno, 2);
    torno.piezasProcesadas = -5;
    imprimirFicha(torno);

    std::string codigo = "Fantasma";
    imprimirFicha(codigo);

    return 0;
```

Agrega también `#include <string>` en `main.cpp`.

**Ejecuta y observa.**

```
Torno T-01: procesamiento generico
Torno T-01: procesamiento generico
Ficha -> Torno T-01 | piezas: -5 | tiempo: 20 s
Ficha -> Fantasma | piezas: 0 | tiempo: 0 s
```

**Acertijo (README 3.1).**

- a) ¿Qué regla de tu sección 1.2 rompió `torno.piezasProcesadas = -5;`?
- b) Nunca escribiste `Maquina("Fantasma")`. ¿De dónde salió esa máquina?

**Corrección.** Protege el estado de la máquina. Esta es la nueva interfaz:

`include/Maquina.h`:

```cpp
#ifndef MAQUINA_H
#define MAQUINA_H

#include <string>

class Maquina {
private:
    std::string nombre;
    int piezasProcesadas;
    int tiempoTrabajadoSeg;

protected:
    // Solo las clases derivadas avisan a la base lo que ocurrio en un ciclo.
    void registrarPieza();
    void agregarTiempo(int segundos);

public:
    explicit Maquina(const std::string& nombre);

    void procesar();

    const std::string& getNombre() const;
    int getPiezasProcesadas() const;
    int getTiempoTrabajadoSeg() const;
    void mostrarEstado() const;
};

#endif
```

En `src/Maquina.cpp`:

1. El constructor lanza `std::invalid_argument` si el nombre está vacío (incluye `<stdexcept>`).
2. `registrarPieza()` suma una pieza.
3. `agregarTiempo()` lanza `std::invalid_argument` si los segundos no son mayores que cero; si son válidos, los acumula.
4. `procesar()` usa `registrarPieza()` y `agregarTiempo(10)` en lugar de modificar los atributos directamente.
5. Implementa los tres accedentes.

Compila. Ahora aparecen errores en `Torno.cpp`, `Fresadora.cpp` y `main.cpp`:

```
src/Torno.cpp:8:18: error: 'std::string Maquina::nombre' is private within this context
src/Torno.cpp:9:5: error: 'int Maquina::piezasProcesadas' is private within this context
src/main.cpp:24:11: error: 'int Maquina::piezasProcesadas' is private within this context
src/main.cpp:28:19: error: invalid initialization of reference of type 'const Maquina&' from expression of type 'std::string'
```

Estos errores son buenos: el compilador ahora protege tus reglas. Corrígelos así:

- En `Torno` y `Fresadora`, usa `getNombre()`, `registrarPieza()` y `agregarTiempo()`. Declara también sus constructores como `explicit`.
- Deja `main.cpp` como estaba en la Etapa 0: borra `imprimirFicha()` y las líneas del experimento.

Responde en el README:

- c) ¿Qué tuviste que cambiar en `Torno` y `Fresadora` y por qué?

> **Nota conceptual.** Un **invariante** solo se puede garantizar si nadie fuera de la clase puede modificar el estado directamente. Con los atributos `private`, la única forma de cambiar las piezas o el tiempo es a través de métodos que validan. El cambio en la base obligó a cambiar las derivadas: ese es el costo de no haber diseñado las reglas desde el principio.

> **Nota de C++.** `protected` significa "accesible para las clases derivadas, pero no para el resto del programa". `registrarPieza()` y `agregarTiempo()` son la interfaz que la base ofrece a sus derivadas, no al público.

> **Nota de C++.** Un constructor de un solo parámetro también funciona como **conversión automática**. Sin `explicit`, el compilador convirtió `codigo` en una `Maquina` temporal para poder llamar a `imprimirFicha()`. Con `explicit`, esa conversión ya no está permitida. Declara `explicit` todo constructor de un parámetro, salvo que quieras la conversión a propósito.

**Commit:** `Etapa 1: invariantes y constructor explicit`

---

### Etapa 2. Virtual y override

**Situación.** Ya es momento de que `ejecutarTurno()` respete el tipo real de cada máquina. Además, cada máquina debe informar su tiempo de ciclo y la planta quiere saber su capacidad por hora.

Cambia la sección pública de `include/Maquina.h`:

```cpp
public:
    explicit Maquina(const std::string& nombre);

    virtual void procesar();
    virtual int tiempoCicloSeg() const;
    double capacidadPorHora() const;

    const std::string& getNombre() const;
    int getPiezasProcesadas() const;
    int getTiempoTrabajadoSeg() const;
    void mostrarEstado() const;
```

En `src/Maquina.cpp`:

1. `tiempoCicloSeg()` devuelve 10.
2. `procesar()` llama a `agregarTiempo(tiempoCicloSeg())` en lugar de usar el 10 fijo.
3. `capacidadPorHora()` devuelve `3600.0 / tiempoCicloSeg()`.
4. `mostrarEstado()` agrega al final `" | capacidad: " << capacidadPorHora() << " pzas/h"`.

Ahora actualiza las derivadas **exactamente** así. Observa con atención las diferencias entre ambas:

`include/Torno.h` (sección pública):

```cpp
public:
    explicit Torno(const std::string& nombre);

    void procesar();
    int tiempoCicloSeg() const;
```

`include/Fresadora.h` (sección pública):

```cpp
public:
    explicit Fresadora(const std::string& nombre);

    void procesar();
    int tiempoCicloSeg();
```

En los `.cpp`, `Torno::tiempoCicloSeg()` devuelve 45 y `Fresadora::tiempoCicloSeg()` devuelve 60, cada una con la misma firma que su `.h`. Los dos `procesar()` llaman a `agregarTiempo(tiempoCicloSeg())`.

**Ejecuta y observa.** Ahora `ejecutarTurno()` sí tornea y fresa. Pero mira el estado de la fresadora:

```
Torno T-01 | piezas: 3 | tiempo: 135 s | capacidad: 80 pzas/h
Fresadora F-01 | piezas: 3 | tiempo: 180 s | capacidad: 360 pzas/h
```

Una fresadora de 60 s por ciclo produce 60 piezas por hora, no 360.

**Acertijo (README 3.2).**

- a) El tiempo acumulado (180 s) usó 60 s por ciclo, pero la capacidad (360 pzas/h) usó 10 s. ¿Por qué el mismo objeto usó dos tiempos distintos?
- b) Revisa la salida del compilador. ¿Apareció alguna advertencia? Según la versión de tu compilador, puede o no aparecer.

**Corrección.** Agrega `override` a todos los métodos que pretenden sobrescribir en `Torno` y `Fresadora`. Primero hazlo sin corregir el `const` de la fresadora:

```cpp
    void procesar() override;
    int tiempoCicloSeg() override;
```

El compilador ahora se niega:

```
include/Fresadora.h:11:9: error: 'int Fresadora::tiempoCicloSeg()' marked 'override', but does not override
```

Corrige la firma (`int tiempoCicloSeg() const override;`, también en el `.cpp`) y verifica que la fresadora reporte 60 pzas/h.

> **Nota conceptual.** Con `virtual`, la decisión de qué método ejecutar se toma **en ejecución**, según el tipo real del objeto: es el **enlace dinámico**. Por eso `ejecutarTurno()` ya funciona, y el acertijo de la Etapa 0 queda resuelto.

> **Nota de C++.** El `const` es parte de la firma de un método. `int tiempoCicloSeg()` y `int tiempoCicloSeg() const` son dos métodos distintos. `mostrarEstado()` es `const`, así que solo puede llamar a la versión `const`, y la fresadora no tenía una: se usó la de la base.

> **Nota de C++.** `override` no cambia lo que hace tu código: le pide al compilador que **verifique** que de verdad sobrescribes un método virtual de la base. Úsalo siempre. Convierte un error silencioso en un error de compilación.

> **Nota técnica.** Algunos compiladores advierten "hides overloaded virtual function" o "was hidden" en el caso de la fresadora. Si lo viste, el compilador ya te estaba diciendo el problema. Una advertencia ignorada es un error que todavía no ha ocurrido.

**Commit:** `Etapa 2: metodos virtuales y override`

---

### Etapa 3. La línea de producción

**Situación.** La planta necesita una clase que coordine las máquinas de la línea. Esta es la primera versión.

`include/ControlDeLinea.h`:

```cpp
#ifndef CONTROLDELINEA_H
#define CONTROLDELINEA_H

#include "Maquina.h"

#include <vector>

class ControlDeLinea {
private:
    std::vector<Maquina> maquinas;

public:
    void agregar(const Maquina& maquina);
    void ejecutarTurno(int ciclos);
    void imprimirReporte() const;
};

#endif
```

`src/ControlDeLinea.cpp`:

```cpp
#include "ControlDeLinea.h"

#include <iostream>

void ControlDeLinea::agregar(const Maquina& maquina) {
    maquinas.push_back(maquina);
}

void ControlDeLinea::ejecutarTurno(int ciclos) {
    for (Maquina& m : maquinas) {
        for (int i = 0; i < ciclos; i++) {
            m.procesar();
        }
    }
}

void ControlDeLinea::imprimirReporte() const {
    std::cout << "--- Reporte de la linea ---\n";
    for (const Maquina& m : maquinas) {
        m.mostrarEstado();
    }
}
```

`src/main.cpp` (la función `ejecutarTurno()` ya no se necesita, bórrala):

```cpp
#include "ControlDeLinea.h"
#include "Fresadora.h"
#include "Torno.h"

#include <iostream>

int main() {
    Torno torno("Torno T-01");
    Fresadora fresadora("Fresadora F-01");

    ControlDeLinea linea;
    linea.agregar(torno);
    linea.agregar(fresadora);

    linea.ejecutarTurno(2);
    linea.imprimirReporte();

    std::cout << "--- Objetos originales ---\n";
    torno.mostrarEstado();
    fresadora.mostrarEstado();

    return 0;
}
```

**Ejecuta y observa.**

```
Torno T-01: procesamiento generico
Torno T-01: procesamiento generico
Fresadora F-01: procesamiento generico
Fresadora F-01: procesamiento generico
--- Reporte de la linea ---
Torno T-01 | piezas: 2 | tiempo: 20 s | capacidad: 360 pzas/h
Fresadora F-01 | piezas: 2 | tiempo: 20 s | capacidad: 360 pzas/h
--- Objetos originales ---
Torno T-01 | piezas: 0 | tiempo: 0 s | capacidad: 80 pzas/h
Fresadora F-01 | piezas: 0 | tiempo: 0 s | capacidad: 60 pzas/h
```

**Acertijo (README 3.3).**

- a) `procesar()` ya es virtual. ¿Por qué la línea procesó todo como "generico"?
- b) ¿Por qué el torno y la fresadora originales quedaron con 0 piezas?

**Corrección.** La línea no debe guardar copias, sino conocer las máquinas que ya existen en la planta.

`include/ControlDeLinea.h`:

```cpp
#ifndef CONTROLDELINEA_H
#define CONTROLDELINEA_H

#include "Maquina.h"

#include <vector>

// Coordina las maquinas de la linea. Las maquinas existen fuera de la linea:
// la linea solo las conoce (agregacion) y nunca las destruye.
class ControlDeLinea {
private:
    std::vector<Maquina*> maquinas;

public:
    bool agregar(Maquina* maquina);
    void ejecutarTurno(int ciclos);
    void imprimirReporte() const;
};

#endif
```

En `src/ControlDeLinea.cpp`:

1. `agregar()` devuelve `false` si recibe `nullptr`; si no, guarda el puntero y devuelve `true`.
2. `ejecutarTurno()` recorre los punteros y llama a `m->procesar()`.
3. `imprimirReporte()` muestra "La linea no tiene maquinas" si está vacía; si no, muestra el estado de cada máquina y al final el total de piezas.

En `main.cpp`, agrega las máquinas con `linea.agregar(&torno);`. Verifica que ahora la línea tornee y fresee, y que los objetos originales tengan las mismas piezas que el reporte.

Responde en el README:

- c) La relación entre `ControlDeLinea` y `Maquina`, ¿es composición o agregación? ¿Por qué?

> **Nota conceptual.** Guardar un `Torno` en un `std::vector<Maquina>` copia solo la parte `Maquina` del objeto; la parte `Torno` se pierde. A esto se le llama **slicing** (rebanado). El enlace dinámico solo funciona a través de **punteros o referencias** a la base.

> **Nota de C++.** Para que haya enlace dinámico se necesitan dos cosas: un método `virtual` y una llamada a través de un puntero o una referencia a la base. Pasa los objetos de una jerarquía como `Base&`, `const Base&` o `Base*`, nunca por valor.

> **Nota conceptual.** La línea no crea las máquinas ni las destruye: solo las conoce. Por eso nunca hace `delete` sobre sus punteros. Si la línea desaparece, las máquinas siguen existiendo en la planta.

**Commit:** `Etapa 3: linea de produccion con agregacion`

---

### Etapa 4. Destructores

**Situación.** El torno ahora tiene un motor de husillo (composición). La planta también quiere crear máquinas de forma dinámica, con `new`, y destruirlas cuando ya no se necesitan.

`include/Motor.h`:

```cpp
#ifndef MOTOR_H
#define MOTOR_H

class Motor {
private:
    double velocidadMaxRpm;
    double velocidadActualRpm;

public:
    explicit Motor(double velocidadMaxRpm);
    ~Motor();

    void fijarVelocidad(double rpm);
    double getVelocidad() const;
};

#endif
```

En `src/Motor.cpp`, implementa el `Motor` que viste en la teoría: el constructor lanza `std::invalid_argument` si la velocidad máxima no es positiva y `fijarVelocidad()` limita la velocidad entre 0 y la máxima. El destructor solo imprime `"  Destruyendo Motor\n"`.

Modifica `include/Torno.h`:

```cpp
#ifndef TORNO_H
#define TORNO_H

#include "Maquina.h"
#include "Motor.h"

class Torno : public Maquina {
private:
    Motor husillo;

public:
    explicit Torno(const std::string& nombre);
    ~Torno();

    void procesar() override;
    int tiempoCicloSeg() const override;
};

#endif
```

En `src/Torno.cpp`:

1. El constructor inicializa `husillo(3000.0)` en la lista de inicialización, después de `Maquina(nombre)`.
2. `procesar()` fija el husillo a 1200 rpm e imprime `torneando pieza a 1200 rpm` usando `husillo.getVelocidad()`.
3. El destructor imprime `"  Destruyendo Torno\n"`.

En `Maquina`, declara `~Maquina();` en la sección pública e implementa un destructor que imprima `"  Destruyendo Maquina\n"`.

Al final de `main`, en lugar de las líneas de "Objetos originales", agrega:

```cpp
    std::cout << "--- Experimento: destruir a traves de la base ---\n";
    Maquina* temporal = new Torno("Torno T-99");
    delete temporal;

    std::cout << "--- Fin de main ---\n";
```

**Ejecuta y observa.** Primero mira la salida del **compilador**:

```
src/main.cpp:20:5: warning: deleting object of polymorphic class type 'Maquina' which has non-virtual destructor might cause undefined behavior [-Wdelete-non-virtual-dtor]
```

El programa compila de todos modos. Ejecútalo:

```
--- Experimento: destruir a traves de la base ---
  Destruyendo Maquina
--- Fin de main ---
  Destruyendo Maquina
  Destruyendo Torno
  Destruyendo Motor
  Destruyendo Maquina
```

**Acertijo (README 3.4).** Llena la tabla de destructores del README.

- a) ¿Qué advertencia mostró el compilador? ¿Por qué decimos que ya te estaba avisando del problema?
- b) Después de "Fin de main" el torno sí se destruyó completo. ¿Por qué ahí sí y con `delete temporal` no? ¿A qué máquina corresponde el primer "Destruyendo Maquina" después de "Fin de main"?

**Corrección.** Declara el destructor de `Maquina` como `virtual`. Compila (la advertencia desaparece) y ejecuta:

```
--- Experimento: destruir a traves de la base ---
  Destruyendo Torno
  Destruyendo Motor
  Destruyendo Maquina
```

Completa la tabla del README. Después **limpia** el código, porque en una clase real los destructores no imprimen mensajes:

1. Borra los destructores de `Torno` y `Motor` (su declaración y su implementación).
2. En `Maquina`, borra la implementación y deja solo `virtual ~Maquina() = default;` en el `.h`.
3. Borra de `main` el experimento de destrucción.

> **Nota conceptual.** Si una clase tiene al menos un método `virtual`, su destructor también debe ser `virtual`. Sin él, al destruir un objeto derivado a través de un puntero a la base solo se ejecuta el destructor de la base: la parte derivada y sus componentes (el motor) nunca se destruyen. Es comportamiento indefinido y una fuga de recursos.

> **Nota de C++.** El orden de destrucción es el inverso al de construcción: primero el cuerpo del destructor de la derivada, después sus atributos (el `Motor`) y al final la base. Los objetos locales de `main` se destruyen en orden inverso a su creación.

> **Nota de C++.** `= default` le pide al compilador el destructor estándar. Lo declaramos solo para poder marcarlo `virtual`. `virtual ~Maquina() = default;` comunica "el destructor normal, pero virtual".

> **Nota técnica.** Esta es la segunda vez que una advertencia te anticipa un error. Compilar sin advertencias no es una cuestión de estética: es parte del diseño.

**Commit:** `Etapa 4: destructor virtual`

---

### Etapa 5. La clase abstracta

**Situación.** Pasan dos cosas en la planta. Alguien agrega a la línea una "máquina sin tipo", que en la vida real no existe. Y otro equipo crea la `Pulidora` (30 s por ciclo), pero olvida implementar `procesar()`.

`include/Pulidora.h`:

```cpp
#ifndef PULIDORA_H
#define PULIDORA_H

#include "Maquina.h"

class Pulidora : public Maquina {
public:
    explicit Pulidora(const std::string& nombre);

    int tiempoCicloSeg() const override;
};

#endif
```

En `src/Pulidora.cpp`, implementa el constructor y `tiempoCicloSeg()`, que devuelve 30.

En `main.cpp`, incluye `Pulidora.h` y crea dos máquinas más:

```cpp
    Pulidora pulidora("Pulidora P-01");
    Maquina generica("Maquina sin tipo");
```

Agrégalas a la línea con `linea.agregar(&pulidora);` y `linea.agregar(&generica);`.

**Ejecuta y observa.** Compila sin errores ni advertencias.

```
Pulidora P-01: procesamiento generico
Pulidora P-01: procesamiento generico
Maquina sin tipo: procesamiento generico
Maquina sin tipo: procesamiento generico
--- Reporte de la linea ---
...
Pulidora P-01 | piezas: 2 | tiempo: 60 s | capacidad: 120 pzas/h
Maquina sin tipo | piezas: 2 | tiempo: 20 s | capacidad: 360 pzas/h
```

La pulidora no pule y una máquina que no existe produjo piezas. El reporte de la planta está mal y nadie se dio cuenta.

**Corrección.** Una "máquina genérica" no tiene sentido: cada máquina real debe decir qué hace y cuánto tarda. Convierte esos dos métodos en **virtuales puros** en `include/Maquina.h`:

```cpp
    virtual void procesar() = 0;
    virtual int tiempoCicloSeg() const = 0;
```

Borra de `src/Maquina.cpp` las implementaciones de `Maquina::procesar()` y `Maquina::tiempoCicloSeg()`: ya no existe un comportamiento genérico. Compila:

```
src/main.cpp:10:14: error: cannot declare variable 'pulidora' to be of abstract type 'Pulidora'
include/Pulidora.h:6:7: note:   because the following virtual functions are pure within 'Pulidora':
include/Maquina.h:21:18: note:     'virtual void Maquina::procesar()'
src/main.cpp:11:13: error: cannot declare variable 'generica' to be of abstract type 'Maquina'
include/Maquina.h:6:7: note:   because the following virtual functions are pure within 'Maquina':
include/Maquina.h:21:18: note:     'virtual void Maquina::procesar()'
include/Maquina.h:22:17: note:     'virtual int Maquina::tiempoCicloSeg() const'
```

**Acertijo (README 3.5).**

- a) Copia los mensajes de error y explica con tus palabras qué dice cada uno.
- b) ¿Por qué es mejor este error de compilación que el comportamiento "generico" de antes?

Ahora resuelve los errores:

1. Borra de `main` la máquina genérica.
2. Implementa `Pulidora::procesar()`: imprime `puliendo pieza`, registra la pieza y agrega su tiempo de ciclo.

> **Nota conceptual.** Una **clase abstracta** define **qué** debe hacer toda máquina, sin decir **cómo**. Un método virtual puro (`= 0`) es una obligación: toda clase derivada concreta debe implementarlo, o tampoco se podrán crear objetos de ella. El compilador hace cumplir esa obligación por ti.

> **Nota conceptual.** Si en la Etapa 3 no hubieras corregido el `std::vector<Maquina>`, ahora no compilaría: no se pueden crear copias de una clase abstracta. El diseño abstracto también te protege del slicing.

> **Nota técnica.** Los mensajes de error de C++ son largos, pero tienen estructura: la línea con `error:` dice qué falló y las líneas con `note:` dicen por qué. Con clang el texto cambia ("variable type 'Pulidora' is an abstract class"), pero la información es la misma.

**Commit:** `Etapa 5: Maquina como clase abstracta`

---

### Etapa 6. El contrato que el compilador no ve

**Situación.** Hay reglas que el compilador no puede verificar. Escríbelas en la interfaz para que todos los equipos las conozcan. En `include/Maquina.h`, reemplaza las dos declaraciones virtuales puras por:

```cpp
    // CONTRATO de procesar(): cada llamada procesa exactamente UNA pieza.
    // Toda clase derivada debe llamar una vez a registrarPieza() y una vez
    // a agregarTiempo(tiempoCicloSeg()).
    virtual void procesar() = 0;

    // CONTRATO de tiempoCicloSeg(): devuelve los segundos que tarda un
    // ciclo. Siempre es mayor que cero.
    virtual int tiempoCicloSeg() const = 0;
```

Llega una estación de inspección escrita por otro equipo.

`include/InspeccionVisual.h`:

```cpp
#ifndef INSPECCIONVISUAL_H
#define INSPECCIONVISUAL_H

#include "Maquina.h"

class InspeccionVisual : public Maquina {
public:
    explicit InspeccionVisual(const std::string& nombre);

    void procesar() override;
    int tiempoCicloSeg() const override;
};

#endif
```

`src/InspeccionVisual.cpp`:

```cpp
#include "InspeccionVisual.h"

#include <iostream>

InspeccionVisual::InspeccionVisual(const std::string& nombre) : Maquina(nombre) {}

void InspeccionVisual::procesar() {
    std::cout << getNombre() << ": inspeccionando pieza con camara\n";
}

int InspeccionVisual::tiempoCicloSeg() const {
    return 0;
}
```

Agrégala a la línea en `main` como `InspeccionVisual inspeccion("Inspeccion I-01");`.

**Ejecuta y observa.** Compila sin errores ni advertencias. Pero el reporte dice:

```
Inspeccion I-01 | piezas: 0 | tiempo: 0 s | capacidad: inf pzas/h
```

Capacidad **infinita** y cero piezas, aunque la cámara inspeccionó dos.

**Acertijo (README 3.6).**

- a) ¿Qué partes del contrato violó `InspeccionVisual`?
- b) Todas las firmas son correctas y el compilador no se quejó. ¿Por qué no lo detectó?
- c) Corriges esta clase, pero mañana llega otra máquina de otro equipo que tampoco lee el comentario. ¿Qué pasaría?

**Corrección.** Haz que `InspeccionVisual` cumpla el contrato: su ciclo dura 15 s y su `procesar()` registra la pieza y el tiempo. Verifica que reporte 2 piezas, 30 s y 240 pzas/h.

> **Nota conceptual.** El compilador verifica la **forma** del contrato (nombres, parámetros, tipos), pero no su **significado**. Una derivada puede tener todas las firmas correctas y aun así romper lo que la base promete. Es el mismo problema del Cuadrado y el Rectángulo: una derivada que no se comporta como se espera de la base no es sustituible.

> **Nota conceptual.** Documentar el contrato en el `.h` es necesario, pero no suficiente: depende de que cada equipo lo lea y lo respete. La siguiente etapa responde a la pregunta c.

> **Nota de C++.** Dividir un `double` entre cero no detiene el programa: el resultado es `inf` (infinito) o `nan` (no es un número). Por eso un error así puede llegar hasta un reporte sin que nadie lo note.

**Commit:** `Etapa 6: contrato documentado`

---

### Etapa 7. La base hace cumplir el contrato

**Situación.** Si cada derivada es responsable de registrar sus piezas y su tiempo, cada derivada es una oportunidad de equivocarse. La solución es que la base controle el ciclo completo y solo le pida a cada máquina la parte que de verdad cambia: el trabajo físico de un ciclo.

`include/Maquina.h`:

```cpp
#ifndef MAQUINA_H
#define MAQUINA_H

#include <string>

// Clase base abstracta de todas las maquinas de la planta.
//
// CONTRATO para toda clase derivada:
//   1. ejecutarCiclo() realiza el trabajo fisico de UN ciclo.
//   2. tiempoCicloSeg() devuelve los segundos de un ciclo; siempre es
//      mayor que cero.
// La base es quien registra la pieza y el tiempo de cada ciclo, y quien
// verifica que el tiempo sea valido.
class Maquina {
private:
    std::string nombre;
    int piezasProcesadas;
    int tiempoTrabajadoSeg;

    void registrarPieza();
    void agregarTiempo(int segundos);
    int tiempoCicloValidado() const;

    // Lo que cada maquina hace en un ciclo. Solo la base lo llama.
    virtual void ejecutarCiclo() = 0;

public:
    explicit Maquina(const std::string& nombre);
    virtual ~Maquina() = default;

    // Procesa exactamente una pieza. No es virtual: ninguna derivada
    // puede cambiar las reglas del ciclo.
    void procesar();

    virtual int tiempoCicloSeg() const = 0;
    double capacidadPorHora() const;

    const std::string& getNombre() const;
    int getPiezasProcesadas() const;
    int getTiempoTrabajadoSeg() const;
    void mostrarEstado() const;
};

#endif
```

Observa los cambios: `registrarPieza()` y `agregarTiempo()` pasaron de `protected` a `private`, `procesar()` ya no es virtual y apareció `ejecutarCiclo()`, que es **privado** y virtual puro.

En `src/Maquina.cpp`:

1. `tiempoCicloValidado()` obtiene `tiempoCicloSeg()`. Si no es mayor que cero, lanza `std::logic_error` con el mensaje `nombre + ": tiempoCicloSeg() debe ser mayor que cero"`. Si es válido, lo devuelve.
2. `procesar()` hace, en este orden: obtener el tiempo validado, llamar a `ejecutarCiclo()`, registrar la pieza y agregar el tiempo.
3. `capacidadPorHora()` usa `tiempoCicloValidado()`.

En cada derivada (`Torno`, `Fresadora`, `Pulidora` e `InspeccionVisual`):

1. Cambia `procesar()` por `ejecutarCiclo()` y decláralo en una sección `private:` con `override`. `tiempoCicloSeg()` sigue siendo público.
2. Deja en `ejecutarCiclo()` solo el trabajo de la máquina: el mensaje y, en el torno, el husillo. Ya no registra piezas ni tiempo.

En `main`, envuelve todo el contenido en un bloque `try` y atrapa los errores para mostrarlos (incluye `<exception>`):

```cpp
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << '\n';
        return 1;
    }
```

Compila y verifica que el reporte sea el mismo que en la Etapa 6.

**Ejecuta y observa.** Haz tres experimentos y regresa cada uno a su estado correcto antes del siguiente.

1. **Tiempo inválido.** Cambia temporalmente `InspeccionVisual::tiempoCicloSeg()` para que devuelva 0:

```
Pulidora P-01: puliendo pieza
Error: Inspeccion I-01: tiempoCicloSeg() debe ser mayor que cero
```

2. **¿Quién puede llamar a qué?** Escribe `torno.ejecutarCiclo();` en `main` y compila. Después intenta llamar a `registrarPieza()` desde `Pulidora::ejecutarCiclo()`:

```
src/main.cpp:23:28: error: 'virtual void Torno::ejecutarCiclo()' is private within this context
src/Pulidora.cpp:9:5: error: 'void Maquina::registrarPieza()' is private within this context
```

3. **El atajo.** Un compañero agrega a `Torno` un método público propio:

```cpp
// En include/Torno.h, seccion publica
    void procesar();

// En src/Torno.cpp
void Torno::procesar() {
    std::cout << getNombre() << ": atajo, ciclo rapido\n";
    ejecutarCiclo();
}
```

En `main`, antes de ejecutar el turno, agrega `torno.procesar();` y `torno.mostrarEstado();`:

```
Torno T-01: atajo, ciclo rapido
Torno T-01: torneando pieza a 1200 rpm
Torno T-01 | piezas: 0 | tiempo: 0 s | capacidad: 80 pzas/h
```

Sin embargo, en el turno de la línea el torno registra sus piezas correctamente.

**Acertijo (README 3.7).**

- a) `ejecutarCiclo()` es privado en `Maquina`, y aun así cada derivada lo sobrescribe y la base lo llama. ¿Cómo es posible?
- b) ¿Qué ocurre ahora con un tiempo de ciclo igual a 0? Compáralo con la Etapa 6.
- c) ¿Por qué la línea ignoró el atajo del torno, pero la llamada directa no? ¿Qué cambio corrige el diseño?

**Corrección.** Borra el atajo del torno y las llamadas de prueba de `main`. Verifica que el programa vuelva a compilar sin advertencias.

> **Nota conceptual.** Este diseño se llama **interfaz no virtual** (NVI, por sus siglas en inglés). El método público `procesar()` no es virtual y contiene las reglas del ciclo; el método privado y virtual `ejecutarCiclo()` es el único punto que cada derivada personaliza. El contrato vive en **un solo lugar**, la base, y ninguna derivada lo puede saltar.

> **Nota de C++.** El acceso (`private`) y la sobrescritura (`virtual`) son independientes. `private` controla **quién puede llamar** a un método; `virtual` controla **qué versión se ejecuta**. Una derivada puede dar su propia versión de un método privado aunque no pueda llamar a la versión de la base.

> **Nota conceptual.** El atajo del torno **oculta** a `procesar()`, igual que en la Etapa 0. Como `procesar()` no es virtual, todo código que use una `Maquina&` o una `Maquina*` (como la línea) siempre ejecuta la versión de la base, con sus reglas. Ocultar un método no virtual de la base es un error de diseño.

> **Nota técnica.** Ahora un error de contrato no llega al reporte como `inf`: el programa se detiene con un mensaje que dice qué máquina falló y qué regla rompió. Un error que se detecta pronto y con un mensaje claro es mucho más barato de corregir.

**Commit:** `Etapa 7: la base hace cumplir el contrato`

---

### Etapa 8. Herencia mal usada

**Situación.** La planta necesita una banda transportadora. Un compañero propone lo siguiente: "la banda usa un motor, así que heredo de `Motor` y tengo `fijarVelocidad()` gratis".

`include/BandaTransportadora.h`:

```cpp
#ifndef BANDATRANSPORTADORA_H
#define BANDATRANSPORTADORA_H

#include "Motor.h"

class BandaTransportadora : public Motor {
public:
    BandaTransportadora();

    void moverPieza();
};

#endif
```

`src/BandaTransportadora.cpp`:

```cpp
#include "BandaTransportadora.h"

#include <iostream>

BandaTransportadora::BandaTransportadora() : Motor(1800.0) {}

void BandaTransportadora::moverPieza() {
    fijarVelocidad(900.0);
    std::cout << "Banda: moviendo pieza a " << getVelocidad() << " rpm\n";
}
```

En `main`, crea `BandaTransportadora banda;`, agrégala con `linea.agregar(&banda);` y, en la línea siguiente, escribe `banda.fijarVelocidad(5000.0);`.

**Ejecuta y observa.**

```
src/main.cpp:24:23: error: cannot convert 'BandaTransportadora*' to 'Maquina*'
```

Observa que la línea `banda.fijarVelocidad(5000.0);` **no** produjo error.

**Acertijo (README 3.8).** Usa la guía de decisión de la teoría (es un / tiene un / usa / es de tipo).

- a) Da al menos dos razones por las que `BandaTransportadora : public Motor` es un error de diseño. Piensa en el error de compilación y en quién puede cambiar la velocidad de la banda.
- b) La relación entre `BandaTransportadora` y `Motor`, ¿es composición o agregación? ¿Por qué?

**Corrección.** Una banda **es una** máquina de la planta y **tiene un** motor.

`include/BandaTransportadora.h`:

```cpp
#ifndef BANDATRANSPORTADORA_H
#define BANDATRANSPORTADORA_H

#include "Maquina.h"
#include "Motor.h"

class BandaTransportadora : public Maquina {
private:
    Motor motor;

    void ejecutarCiclo() override;

public:
    explicit BandaTransportadora(const std::string& nombre);

    int tiempoCicloSeg() const override;
};

#endif
```

En `src/BandaTransportadora.cpp`, el motor tiene una velocidad máxima de 1800 rpm; `ejecutarCiclo()` lo fija a 900 rpm e imprime `moviendo pieza a 900 rpm`, y el ciclo dura 20 s. En `main`, crea la banda como `BandaTransportadora banda("Banda B-01");` y borra la llamada a `fijarVelocidad()`. Verifica que la banda reporte 2 piezas, 40 s y 180 pzas/h.

> **Nota conceptual.** La herencia no es una forma de reutilizar código: es una promesa de que la derivada **es un** tipo de la base y se puede usar donde se espera la base. Una banda no es un motor. Al heredar de `Motor`, la banda expuso `fijarVelocidad()` a todo el programa y dejó de ser una `Maquina`.

> **Nota conceptual.** Ante la duda, prefiere la composición: la banda usa su motor por dentro y decide cuándo y cómo cambiar su velocidad. Es la misma relación que tiene el torno con su husillo.

> **Nota de C++.** Podrías pensar en `class BandaTransportadora : public Maquina, public Motor`. Eso es herencia múltiple, un tema de la Unidad V. Aun así, no resolvería el problema de fondo: la banda seguiría sin ser un motor.

**Commit:** `Etapa 8: banda transportadora con composicion`

---

### Etapa 9. La librería y la prueba final

**Situación.** Otros proyectos de la planta quieren reutilizar tus clases. Para eso las conviertes en una librería: un conjunto de clases compiladas, organizadas y protegidas contra choques de nombres.

**Paso 1. Espacio de nombres.** Envuelve el contenido de **todos** los `.h` y `.cpp` (excepto `main.cpp`) en `namespace planta`. Por ejemplo:

`include/Torno.h`:

```cpp
#ifndef TORNO_H
#define TORNO_H

#include "Maquina.h"
#include "Motor.h"

namespace planta {

class Torno : public Maquina {
    // ... misma declaracion ...
};

}  // namespace planta

#endif
```

`src/Torno.cpp`:

```cpp
#include "Torno.h"

#include <iostream>

namespace planta {

Torno::Torno(const std::string& nombre) : Maquina(nombre), husillo(3000.0) {}

// ... resto de las implementaciones ...

}  // namespace planta
```

En `main.cpp`, crea los objetos con su nombre completo: `planta::Torno torno("Torno T-01");`, `planta::ControlDeLinea linea;`, etcétera. Compila con el comando de siempre.

**Paso 2. Compilación separada y librería estática.** Desde la raíz del repositorio, compila cada clase a un archivo objeto (`.o`), sin `main.cpp`:

```
g++ -Wall -Wextra -std=c++17 -Iinclude -c src/Maquina.cpp src/Motor.cpp src/ControlDeLinea.cpp src/Torno.cpp src/Fresadora.cpp src/Pulidora.cpp src/InspeccionVisual.cpp src/BandaTransportadora.cpp
```

Empaqueta los objetos en la librería y enlaza tu programa con ella:

```
ar rcs libplanta.a *.o
g++ -Wall -Wextra -std=c++17 -Iinclude src/main.cpp -L. -lplanta -o evolucion_maquina
./evolucion_maquina
```

El reporte debe ser el mismo de la Etapa 8. Ejecuta `git status`: los `.o`, `libplanta.a` y el ejecutable no deben aparecer.

Ahora prueba el orden de los argumentos, poniendo la librería **antes** de `main.cpp`:

```
g++ -Wall -Wextra -std=c++17 -Iinclude -L. -lplanta src/main.cpp -o evolucion_maquina
```

Verás varios errores `undefined reference`. Regresa al orden correcto.

**Paso 3. La prueba final.** Antes de continuar, haz commit de los pasos 1 y 2 con el mensaje `Etapa 9: libreria planta`. Después, agrega una máquina nueva, la **Cortadora** (50 s por ciclo, imprime `cortando lamina`), con estas reglas:

- Solo puedes **crear** `include/Cortadora.h` y `src/Cortadora.cpp`, y agregar en `main.cpp` el `#include`, el objeto y la llamada a `agregar()`.
- **No puedes modificar** ningún otro archivo de `include/` ni de `src/`, ni recompilar la librería.

Compila solo lo nuevo, enlazándolo con la librería que ya existe:

```
g++ -Wall -Wextra -std=c++17 -Iinclude src/main.cpp src/Cortadora.cpp -L. -lplanta -o evolucion_maquina
./evolucion_maquina
```

Deberías ver:

```
Cortadora C-01: cortando lamina
Cortadora C-01: cortando lamina
...
Cortadora C-01 | piezas: 2 | tiempo: 100 s | capacidad: 72 pzas/h
Total de piezas: 12
```

Ejecuta `git status`. Debe mostrar únicamente `src/main.cpp` como modificado y los dos archivos nuevos de la cortadora. Por último, compila con el comando de siempre (`src/*.cpp`) para verificar que el proyecto completo también compila sin advertencias.

**Acertijo (README 3.9).**

- a) ¿Qué archivos mostró `git status`? ¿Cuántos archivos de la librería tuviste que modificar para agregar una máquina nueva?
- b) ¿Qué pasó al escribir `-lplanta` antes de `src/main.cpp`? ¿Por qué?

> **Nota conceptual.** Esta es la gran recompensa del diseño. La cortadora se integró a la línea, respetó el contrato y quedó incluida en el reporte sin que tocaras `Maquina`, `ControlDeLinea` ni ninguna otra clase. El diseño está **abierto a la extensión y cerrado a la modificación**: se agregan comportamientos nuevos sin romper lo que ya funciona.

> **Nota conceptual.** Una librería se comparte con dos partes: los `.h`, que son la **interfaz** (el contrato), y el `.a`, que es el código compilado. Quien usa tu librería no necesita ver tus `.cpp`; le basta con leer los `.h`. Por eso el contrato debe estar escrito ahí.

> **Nota de C++.** `namespace planta` evita choques de nombres: otro proyecto puede tener su propia clase `Motor` sin conflicto. Nunca escribas `using namespace` dentro de un `.h`, porque afectaría a todos los archivos que lo incluyan.

> **Nota de C++.** `-c` compila sin enlazar y produce un `.o` por cada `.cpp`. `ar rcs` empaqueta los `.o` en una librería estática. `-L.` indica en qué carpeta buscar librerías y `-lplanta` cuál usar (el compilador agrega `lib` y `.a`). El enlazador resuelve lo que falta de izquierda a derecha, por eso la librería va después del código que la usa.

> **Nota de C++.** En este curso usamos guardas `#ifndef`. Existe una alternativa más corta, `#pragma once`, que soportan g++, clang y MSVC, aunque no es parte formal del estándar.

> **Nota técnica.** El enlazador (*linker*) une archivos objeto en un ejecutable. No lo confundas con el enlace estático o dinámico de métodos (*binding*): son dos conceptos distintos con nombres parecidos.

**Commit:** `Etapa 9: prueba de extension con Cortadora`

Al terminar esta etapa, dibuja tu diagrama final (Fase 2) y completa las secciones 2.2 y 2.3 del README.

## Fase 4. Probar y mejorar

Ejecuta cada caso desde `main.cpp` y completa la tabla de la sección 4.1 del README. Para los casos que lanzan excepciones, aprovecha el bloque `try` que ya tienes. Para los casos 7 y 8, crea una clase de prueba temporal o modifica temporalmente una existente, y regrésala a su estado correcto al terminar.

| # | Caso | Entrada | Resultado esperado |
|---|---|---|---|
| 1 | Nombre vacío | `planta::Torno t("");` | Excepción con mensaje claro |
| 2 | Línea vacía | `imprimirReporte()` sin máquinas | "La linea no tiene maquinas" |
| 3 | Puntero nulo | `linea.agregar(nullptr)` | Devuelve `false` |
| 4 | Reporte antes del turno | `imprimirReporte()` sin ejecutar ciclos | 0 piezas, 0 s y capacidad calculada |
| 5 | Turno de 0 ciclos | `ejecutarTurno(0)` | Nada cambia |
| 6 | Torno con 3 ciclos | Línea solo con el torno, `ejecutarTurno(3)` | 3 piezas, 135 s, 80 pzas/h |
| 7 | Tiempo de ciclo 0 | `tiempoCicloSeg()` devuelve 0 | Excepción con mensaje claro |
| 8 | Tiempo de ciclo negativo | `tiempoCicloSeg()` devuelve -5 | Excepción con mensaje claro |
| 9 | Máquina duplicada | La misma máquina agregada dos veces | Decide tú qué debería pasar y compáralo con lo que pasa |

- **4.1** Tabla de pruebas con el resultado obtenido en cada caso.
- **4.2** Bitácora de mejoras: qué fallas encontraste, qué cambiaste y por qué.

> **Nota técnica.** El caso 9 no tiene una respuesta única. Antes de ejecutarlo, decide qué debería pasar según el problema de la planta. Si el resultado no coincide, ya tienes una mejora para tu bitácora.

> **Nota técnica.** Vuelve a ejecutar todos los casos después de cada corrección. Un arreglo puede romper algo que ya funcionaba.

### Retos opcionales (insatisfacción positiva)

Tu diseño funciona. ¿Qué más podría hacer? Elige los que te interesen y anótalos en la sección 4.2.

- Haz que `agregar()` rechace una máquina que ya está en la línea.
- Agrega a `ControlDeLinea` un método que muestre la máquina con mayor capacidad por hora.
- Crea una máquina que **comparta** un motor con otra (el motor existe fuera de ambas). ¿Qué relación es? ¿Qué riesgo aparece si el motor se destruye antes que las máquinas?
- Investiga la palabra `final` de C++11 y úsala para que nadie pueda heredar de `Torno`. ¿Cuándo sería útil en la planta?
- Proponer una mejora propia que no esté en esta lista.

## Fase 5. Publicar en GitHub

1. Ejecuta `git status` y verifica que no aparezcan el ejecutable, los `.o` ni `libplanta.a`.
2. Revisa tu historial con `git log --oneline` o en la pestaña *History* de GitHub Desktop. Debe tener el commit de la estructura inicial y al menos un commit por cada etapa, de la 0 a la 9.
3. Sube tus cambios con `git push` o con **Push origin** en GitHub Desktop.
4. Abre tu fork en el navegador y confirma que el README muestra los dos diagramas y todas tus respuestas.

- **5.1** Pega el enlace a tu fork. Es el mismo que entregarás en Google Classroom.

> **Nota técnica.** Tu historial de commits es parte de la entrega. Muestra cómo evolucionó tu diseño, igual que en un proyecto real, donde el historial explica por qué el código es como es.

## Cierre y reflexión

Responde en el README con honestidad. No hay respuestas correctas.

- **6.1** Compara la Etapa 0 con la Etapa 9 y completa la tabla de errores que ya no pueden ocurrir.
- **6.2** ¿Cuál de los errores fue el más peligroso: el de compilación, la advertencia o el que compilaba sin problemas? ¿Por qué?
- **6.3** ¿Qué aprendiste en esta práctica?
- **6.4** ¿Qué cambiarías de tu proceso la próxima vez?

## Lista de verificación

- [ ] El programa compila sin errores ni advertencias con el comando de siempre.
- [ ] Cada clase tiene su interfaz en `include/` y su implementación en `src/`, dentro de `namespace planta`.
- [ ] Todos los atributos son privados y los accedentes son `const`.
- [ ] `Maquina` es abstracta, tiene destructor `virtual ~Maquina() = default;` y su `procesar()` no es virtual.
- [ ] Cada derivada implementa `ejecutarCiclo()` como privado y `tiempoCicloSeg()` como público, ambos con `override`.
- [ ] `ControlDeLinea` guarda punteros y nunca destruye las máquinas.
- [ ] `Torno` y `BandaTransportadora` tienen un `Motor` por composición.
- [ ] La `Cortadora` se agregó sin modificar ningún otro archivo de la librería.
- [ ] Las respuestas de las diez etapas están en el README.
- [ ] Los nueve casos de prueba están documentados.
- [ ] `diseno_inicial.png` y `diseno_solucion.png` están en el repositorio y se ven en el README.
- [ ] El historial tiene al menos un commit por etapa.
- [ ] Ni el ejecutable, ni los `.o`, ni `libplanta.a` están en el repositorio.
- [ ] El enlace al fork está entregado en Google Classroom.
