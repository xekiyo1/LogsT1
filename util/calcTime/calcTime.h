

/**
 * Calculates the execution time of a given function, returning the time it took in nanoseconds
 * @param foo A poniter to a the funtcion to measure time from, which returns void and takes any pointer as arg.
 * @param args A pointer to the functions arguments.
 * 
 * @returns An unsigned long long with the exectuion time in nanoseconds.
 */
unsigned long long calc_time( void (*foo)(void* arg_struct), void* args );