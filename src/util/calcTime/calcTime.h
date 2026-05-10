#ifndef HPTIMERER
#define HPTIMERER
/**
 * Calculates the execution time of a given function, returning the time it took in nanoseconds
 * @param foo A poniter to a the funtcion to measure time from, which returns void and takes any pointer as arg.
 * @param args A pointer to the functions arguments.
 * 
 * @returns An unsigned long long with the exectuion time in nanoseconds.
 */
unsigned long long calc_time( void (*foo)(void* arg_struct), void* args );

#include <chrono>

/**
 * Clase que funciona como una interfaz más amigable de calc_time, permitiendo
 * medir tiempo mediante una función de start() y end().
 */
struct HPTimer{
private:
	/// Identificador del proceso que está realizando este temporizador, principalmente para debug.
	int id;
	/// Instancia de tiempo en la que se inició el temporizador.
	std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
	/// Utilizado para decidir cuánta información enviar a consola. @deprecated
	bool verbose = 0;
public:
	/// Inicia el temporizador guardando la instancia de tiempo actual en startTime.
	void start();

	/**
	 * Termina el tiempo medido, entregando la diferencia entre el tiempo actual y el guardado
	 * al llamar startTime().
	 * @return Diferencia de tiempo del high_resolution_clock desde startTime hasta la instancia actual.
	 */
	unsigned long long end();
};
#endif