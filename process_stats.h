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

#define MASK ( i == 13 || i == 14 || i == 15 || i == 16 || i == 21 ) // posizione dei parametri della CPU da leggere

#define TOKEN_MASK ( token == "RssAnon:" || token == "RssFile:" || token == "RssShmem:" ) // mi serve per il file status del processo

float process_cpu_usage(const char* path);		// calcola la % di utilizzo della CPU del processo PID
float process_memory_usage(const char* path);		// calcola la % di utilizzo della memoria del processo PID
//char* process_user(int pid);				// ritorna il norme dell'user del processo PID
//char* process_state(int pid);				// calcola lo stato del processo PID
