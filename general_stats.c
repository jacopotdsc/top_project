//#pragma once
//#pragma message "compiling: general_stats.h "

#include "general_stats.h"


// leggo parametri da /proc/stats che mi servono e li scrivo su param
void read_stats_cpu(float* param){	
	FILE* my_file = fopen("/proc/stat", "r"); 	//apro il file in lettura
	
	// controlla se è stato aperto correttamente, in caso stampa il msg di errore e termina
	handle_error(my_file, "general_stats.c -> general_cpu_usage: file not opened");	
			
	fscanf(my_file,"%*s %f %f %f %f", &param[0], &param[1], &param[2], &param[3] );
	
	//printf("%f %f %f %f\n",param[0], param[1], param[2], param[3]);
	
	close( (int) my_file);
}


// https://rosettacode.org/wiki/Linux_CPU_utilization
float general_cpu_usage(){
	
	float old_param[4];
	read_stats_cpu(old_param);
	
	/* sleep(1);	// gli permetto di aggiornarsi
	
	long double new_param[4];
	read_stats(new_param); */
	
	//float hertz = sysconf(_SC_CLK_TCK); // frequenza della CPU
	
	// per calcolare l'utilizzo totale,
	// normalizzo la differenza tra i due sample
	
	float total_time 	= old_param[0] + old_param[1] + old_param[2] + old_param[3];
	float idle_time 	= old_param[3] / total_time;
	float cpu_usage 	= 100* ( 1 - idle_time );
	
	return cpu_usage;
}


void read_stats_memory(float* param){
	FILE* my_file = fopen("/proc/meminfo", "r"); 	//apro il file in lettura
	
	// controlla se è stato aperto correttamente, in caso stampa il msg di errore e termina
	handle_error(my_file, "general_stats.c -> general_cpu_usage: file not opened");	
	
	
	// total memory, free, avaible, buffers, chached
	for( int i=0; i < 5; i++) fscanf(my_file,"%*s %f %*s", &param[i] );

	close( (int) my_file);
}

// https://sites.google.com/a/thetnaing.com/therunningone/how-to-calculate-systems-memory-utilization
float general_memory_usage(){
	
	// leggo i parametri
	float param[5];
	read_stats_memory(param);
	
	// li prendo tutti tranne quelo della memoria disponibile
	float total_memory 	= param[0];
	float free_memory	= param[1];
	float buffer_memory = param[3];
	float cached_memory = param[4];
	
	//printf("tf: %f.2, fm: %f.2, bm: %f.2, cm: %f.2\n", total_memory, free_memory, buffer_memory, cached_memory);
	
	float total_memory_usage = total_memory - ( free_memory + buffer_memory + cached_memory );
	
	float total_memory_usage_percentuage = 100*(total_memory_usage / total_memory);
	
	return total_memory_usage_percentuage;
}
