#include "general_stats.h"

int main(){
	
	while(1){
		printf("\ncpu_usage:\t %f %\n", general_cpu_usage() );	// rivedi i valori che restituisce
		printf("memory_usage:\t %f %\n", general_memory_usage() );
		sleep(1);
	}
}
