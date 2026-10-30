#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

/* =========================================================
 * static_assert: comprobaciones en tiempo de compilación
 * ========================================================= */

struct packed{
	int i;
	char *p;
};

/**
 * Esta static_assert no falla para sistemas de 32 bits ya que
 * tanto int como char * ocupan 4 bytes cada uno, en cambio, en
 * sistemas de 64 bits char * ocupa 8 bytes por lo que el compilador
 * añade 4 bytes de relleno al struct.
 *
 * Solo se compila con `make fail` (define DEMO_FALLO) para ver el error.
 */
#ifdef DEMO_FALLO
static_assert(
	sizeof(struct packed) == sizeof(int) + sizeof(char *),
	"struct packed no debe tener bytes de relleno"
);
#endif

/**
 * Versión portable: comprobar que el campo p está alineado, que es
 * lo que de verdad nos importa, en vez de suponer que no hay relleno
 */
static_assert(
	offsetof(struct packed, p) % alignof(char *) == 0,
	"el campo p debe estar alineado"
);

/* En C23 el mensaje es opcional */
static_assert(CHAR_BIT == 8);

/**
 * Buffer con prefijo: constexpr (C23) permite usar size en una
 * static_assert y como tamaño de un array que no es VLA
 */
static const char prefix[] = "Error No: ";
constexpr int size = 14;
static char str[size];

static_assert(
	sizeof(str) > sizeof(prefix),
	"str debe ser mayor que prefix"
);


/**
 * Verifica que no se dan falsos positivos al detectar el EOF
 * y que el bucle no termine así antes de tiempo
 */
void clear_stdin(){
	int c;

	do {
		c = getchar();
		static_assert(
			sizeof(unsigned char) < sizeof(int),
			"FIO34-C violation"
		);
	} while (c != EOF);
}


/* =========================================================
 * assert: comprobaciones en tiempo de ejecución
 * Se desactivan compilando con -DNDEBUG (`make release`)
 * ========================================================= */

/**
 * Escribe "Error No: <errnum>" en str.
 * Precondición: errnum no negativo
 */
const char *format_error(int errnum){
	assert(errnum >= 0 && "errnum debe ser no negativo");

	/* [[maybe_unused]] (C23): con NDEBUG el assert desaparece y n no se usa */
	[[maybe_unused]] int n = snprintf(str, sizeof(str), "%s%d", prefix, errnum);

	/* Postcondición: el resultado no se ha truncado */
	assert(n >= 0 && (size_t)n < sizeof(str));
	return str;
}

/**
 * Divide a entre b.
 * Precondición: b distinto de 0
 */
int dividir(int a, int b){
	assert(b != 0);
	return a / b;
}


/* =========================================================
 * Tests
 * ========================================================= */

static void test_format_error(){
	assert(strcmp(format_error(0), "Error No: 0") == 0);
	assert(strcmp(format_error(42), "Error No: 42") == 0);
	assert(strcmp(format_error(999), "Error No: 999") == 0);
	printf("test_format_error: OK\n");
}

static void test_dividir(){
	assert(dividir(10, 2) == 5);
	assert(dividir(-9, 3) == -3);
	assert(dividir(7, 2) == 3);
	printf("test_dividir: OK\n");
}

int main(int argc, char *argv[]){
	(void)argv;

	test_format_error();
	test_dividir();

	/*
	 * Pasar cualquier argumento fuerza un assert fallido
	 * (útil para ver el abort desde gdb: `run x` y luego `bt`)
	 */
	if (argc > 1) {
		printf("Forzando assert fallido...\n");
		dividir(1, 0);
	}

	printf("Todos los tests pasaron\n");
	return 0;
}
