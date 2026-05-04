#include <cstring>
#include <iostream>
#include <string>
#include "../RTreeConstructors/RTreeConstructor.h"
using namespace std;

#define SHOW_USAGE cout << "Usage: " << argv[0] << " [filename on bin/data)] [NX | STR] [N (2^N blocks will be used)]" << endl

/**
 * Este archivo (Accesado a través del comando del CLI)
 * se ocupa de armar árboles R según especificaciones.
 *
 * El resultado es luego enviado a bin/trees/custom.bin
 */
int main(const int argc, char** argv){
	if (constexpr int expected_arguments = 3; argc != expected_arguments + 1){
		cout << "Wrong number of arguments, received: " << argc - 1 << endl;
		SHOW_USAGE;
		return 0;
	}

	const int N =  1 << stoi(argv[3]);

	if (strcmp(argv[2], "NX") == 0) {
		NearestXConstructor NX;
		NX.CreateRTree(argv[1], "custom.bin", N);
	}
	else if (strcmp(argv[2], "STR") == 0) {
		STRConstructor STR;
		STR.CreateRTree(argv[1], "custom.bin", N);
	}
	else {
		cout << "NX (NearestX) or STR needs to be specified." << endl;
		SHOW_USAGE;
		return 0;
	}

	return 0;
}