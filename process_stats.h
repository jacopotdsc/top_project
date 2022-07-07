/* - process_stats.h:	scrivo dichiarazioni funzione che devo plottare per ogni processo
							- CPU usage
							- memory usage
							- pid
							- user
							- stato processo
*/


#include "error_handler.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>

float process_cpu_usage(char* path);		// calcola la % di utilizzo della CPU del processo PID
float process_memory_usage(int pid);		// calcola la % di utilizzo della memoria del processo PID
//char* process_user(int pid);				// ritorna il norme dell'user del processo PID
//char* process_state(int pid);				// calcola lo stato del processo PID
