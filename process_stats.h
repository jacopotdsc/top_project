#include "error_handler.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>

#define MASK ( i == 13 || i == 14 || i == 15 || i == 16 || i == 21 ) // posizione dei parametri della CPU da leggere

#define TOKEN_MASK strcmp(token, &"RssAnon:") == 0 || strcmp(token,&"RssFile:") == 0 || strcmp(token, &"RssShmem:") == 0 // mi serve per il file status del processo

#define DELIM "\t"

float process_cpu_usage(const char* path);		// calcola la % di utilizzo della CPU del processo PID
float process_memory_usage(const char* path);	// calcola la % di utilizzo della memoria del processo PID
int process_id(char* path);						// ritorna l'id
char* process_state(char* path);				// calcola lo stato del processo PID
