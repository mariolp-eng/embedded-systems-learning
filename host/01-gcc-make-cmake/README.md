# 01 — GCC, Make and CMake

Fixed-size ring buffer (FIFO queue) in C with unit tests, used to practise building a multi-file C project with GCC by hand, Make and CMake.

The ring buffer stores `int` values in a static array with no dynamic memory, the same approach used later for UART reception on the STM32. Writing to a full buffer or reading from an empty one is rejected with an error code.

## Structure

```
01-gcc-make-cmake/
├── include/
│   └── ring_buffer.h       # Public interface
├── src/
│   ├── main.c              # Usage example
│   └── ring_buffer.c       # Implementation
└── tests/
    └── test_ring_buffer.c  # Unit tests (assert-based)
```

## Building with GCC by hand

Compile each source file to an object file:

```bash
gcc -std=c11 -Wall -Wextra -Werror -g -Iinclude -c src/ring_buffer.c -o ring_buffer.o
gcc -std=c11 -Wall -Wextra -Werror -g -Iinclude -c src/main.c -o main.o
gcc -std=c11 -Wall -Wextra -Werror -g -Iinclude -c tests/test_ring_buffer.c -o test_ring_buffer.o
```

Link the demo and the test executables (both reuse `ring_buffer.o`):

```bash
gcc main.o ring_buffer.o -o ring_buffer_demo
gcc test_ring_buffer.o ring_buffer.o -o test_ring_buffer
```

Run them:

```bash
./test_ring_buffer
./ring_buffer_demo
```

To inspect the intermediate compilation stages:

```bash
gcc -std=c11 -Iinclude -E src/ring_buffer.c -o ring_buffer.i   # preprocessed code
gcc -std=c11 -Iinclude -S src/ring_buffer.c -o ring_buffer.s   # generated assembly
```

## Tests

The tests use only the public interface of the module (black-box testing) and cover:

- Initial state after `rb_init`
- Writing and reading a single value
- FIFO order when filling the buffer to capacity
- Rejected write when the buffer is full
- Rejected read when the buffer is empty
- Index wrap-around, with data crossing the end of the array

---

# 01 — GCC, Make y CMake (español)

Buffer circular de tamaño fijo (cola FIFO) en C con tests unitarios, usado para practicar la compilación de un proyecto en C de varios archivos con GCC a mano, Make y CMake.

El buffer guarda valores `int` en un array estático, sin memoria dinámica, igual que se usará después para la recepción por UART en el STM32. Escribir con el buffer lleno o leer con el buffer vacío se rechaza con un código de error.

## Estructura

```
01-gcc-make-cmake/
├── include/
│   └── ring_buffer.h       # Interfaz pública
├── src/
│   ├── main.c              # Ejemplo de uso
│   └── ring_buffer.c       # Implementación
└── tests/
    └── test_ring_buffer.c  # Tests unitarios (con assert)
```

## Compilación con GCC a mano

Compilar cada archivo fuente a un archivo objeto:

```bash
gcc -std=c11 -Wall -Wextra -Werror -g -Iinclude -c src/ring_buffer.c -o ring_buffer.o
gcc -std=c11 -Wall -Wextra -Werror -g -Iinclude -c src/main.c -o main.o
gcc -std=c11 -Wall -Wextra -Werror -g -Iinclude -c tests/test_ring_buffer.c -o test_ring_buffer.o
```

Enlazar la demo y el test (los dos reutilizan `ring_buffer.o`):

```bash
gcc main.o ring_buffer.o -o ring_buffer_demo
gcc test_ring_buffer.o ring_buffer.o -o test_ring_buffer
```

Ejecutarlos:

```bash
./test_ring_buffer
./ring_buffer_demo
```

Para ver las etapas intermedias de la compilación:

```bash
gcc -std=c11 -Iinclude -E src/ring_buffer.c -o ring_buffer.i   # código preprocesado
gcc -std=c11 -Iinclude -S src/ring_buffer.c -o ring_buffer.s   # ensamblador generado
```

## Tests

Los tests usan solo la interfaz pública del módulo (pruebas de caja negra) y cubren:

- El estado inicial tras `rb_init`
- Escribir y leer un único valor
- El orden FIFO al llenar el buffer hasta su capacidad
- El rechazo de una escritura con el buffer lleno
- El rechazo de una lectura con el buffer vacío
- El giro de los índices, con datos que cruzan el final del array