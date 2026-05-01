#include <chrono>
#include <iostream>
#include <cstdlib>
using namespace std;


#define DEBUG 1

unsigned long long calc_time( void (*foo)(void* arg_struct), void* args ){
	using namespace std::chrono;

	int id = rand() & (0xFF);
	int verbose = 0;


	auto start = high_resolution_clock::now();

	#ifdef DEBUG
		if(DEBUG & verbose){
			cout << "calc_time(" << id <<"): Iniciando Operación costosa de tiempo" << endl;
		}
	#endif

	foo(args);


	auto end = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(end-start);

	#ifdef DEBUG
		if(DEBUG & verbose){
			cout << "calc_time(" << id <<"): Operación terminada en " << duration.count() << "ns." << endl;
		}
	#endif

	return (unsigned long long)duration.count();
}