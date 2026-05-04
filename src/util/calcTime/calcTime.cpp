#include "../../config.hp"
#include "calcTime.h"

#include <chrono>
#include <iostream>
#include <cstdlib>
using namespace std;
using namespace std::chrono;

void HPTimer::start(){
	static int next_id = 0;
	id = next_id++;

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

	static int next_id = 0;
	int id = next_id++;


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