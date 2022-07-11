#include "general_stats.h"
#include "process_stats.h"


int main(){
	
	while(1){
		sleep(1);
		
		printf("\ncpu_usage:\t %f %\n", general_cpu_usage() );	// rivedi i valori che restituisce
		printf("memory_usage:\t %f %\n", general_memory_usage() );
		
		printf("proc_cpu_usage:\t %f %\n", process_cpu_usage("/proc/2348/stat") );
		printf("proc_memory usage:\t %f %\n", process_memory_usage("/proc/2348/status") );	// sistema, utilizza quella virtuale per il calcolo
		
		sleep(3);
	}
}
