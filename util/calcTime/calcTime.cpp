#include "../../config.hp"
#include "calcTime.h"

#include <chrono>
#include <iostream>
#include <cstdlib>
using namespace std;
using namespace std::chrono;

void HPTimer::start(){
	id = rand() & (0xFF);

	startTime = high_resolution_clock::now();
	
	#ifdef LOGLEVEL
		if(LOGLEVEL > 1)
			cout << "calc_time(" << id <<"): Iniciando Operación costosa de tiempo" << endl;
	#endif
}

unsigned long long HPTimer::end(){
	auto endTime = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(endTime-startTime);

	#ifdef LOGLEVEL
		if(LOGLEVEL){
			cout << "calc_time(" << id <<"): Operación terminada en " << duration.count() << "ns." << endl;
		}
	#endif

	return (unsigned long long)duration.count();
}

unsigned long long calc_time( void (*foo)(void* arg_struct), void* args ){
	using namespace std::chrono;

	int id = rand() & (0xFF);
	int verbose = 0;


	auto start = high_resolution_clock::now();

	

	foo(args);


	auto end = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(end-start);

	#ifdef LOGLEVEL
		if(LOGLEVEL)
			cout << "calc_time(" << id <<"): Operación terminada en " << duration.count() << "ns." << endl;
	#endif

	return (unsigned long long)duration.count();
}