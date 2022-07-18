#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "error_handler.h"
#include "process_stats.h"

#define FILE_STAT 	"/stat"
#define FILE_STATUS "/status"

void get_process();	// plotta statistiche generale { tot_cpu_usage, tot_mem_usage } e quelle dei processi { pid, cpu_usage, mem_usage, state }


