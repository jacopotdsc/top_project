//#pragma once
//#pragma message "compiling: general_stats.h "

#include "general_stats.h"


// leggo parametri da /proc/stats che mi servono e li scrivo su param
void read_stats_cpu(float* param){	
	FILE* my_file = fopen("/proc/stat", "r"); 	//apro il file in lettura
	
	// controlla se è stato aperto correttamente, in caso stampa il msg di errore e termina
	handle_error(my_file, "general_stats.c -> read_stats_cpu: file not opened");	
			
	fscanf(my_file,"%*s %f %f %f %f %f %f %f %f %f %f", &param[0], &param[1], &param[2], &param[3], &param[4], &param[5], &param[6], &param[7], &param[8], &param[9] );
	
	//printf("%f %f %f %f\n",param[0], param[1], param[2], param[3]);
	
	handle_error_fclose( fclose( my_file), "read_stats_cpu, error closing");
}


// https://rosettacode.org/wiki/Linux_CPU_utilization
float general_cpu_usage(){
	
	float param[10];
	read_stats_cpu(param);
	
	float user_time		= param[0]; 
	float nice_time		= param[1]; 
	float system_time	= param[2]; 
	float idle_time		= param[3]; 
	float iowait_time 	= param[4];
	float irq_time	 	= param[5];
	float softirq_time 	= param[6];
	float steal_time 	= param[7];
	float guest_time 	= param[8];
	float guest_nice_time 	= param[9];
	
	
	//printf("ut: %.2f, nt: %.2f, st: %.2f, id: %.2f\n", user_time, nice_time, system_time, idle_time);
	
	float hertz = sysconf(_SC_CLK_TCK); // frequenza della CPU
	
	
	float total_time = 0;
	
	for( int i=0; i < sizeof(param)/sizeof(float); i++){ 
		total_time += param[i]; 
	}
	
	//float total_time = user_time + nice_time + system_time + idle_time;
	
	float idle_time_percentage	= idle_time / total_time;
	float cpu_usage_percentage = 100*( ( 1.0 - idle_time_percentage ) );
	//float cpu_usage_percentage = ( ( total_time - idle_time ) ) / total_time;
	
	//printf("total time: %f, idle_time: %f, cpu_usage: %f, sum: %f \n \n", total_time, idle_time_percentage, cpu_usage_percentage, (1-idle_time_percentage));
	
	return cpu_usage_percentage;
}



void read_stats_memory(float* param){
	FILE* my_file = fopen("/proc/meminfo", "r"); 	//apro il file in lettura
	
	handle_error(my_file, "general_stats.c -> read_stats_memory: file not opened");	
	
	
	// total memory, free, avaible, buffers, chached
	//printf("size *param: %d, size param: %d, float: %d\n", sizeof(*param), sizeof(param), sizeof(float));
	for( int i=0; i < sizeof(param) / sizeof(float); i++) fscanf(my_file,"%*s %f %*s", &param[i] );

	handle_error_fclose( fclose( my_file), "read_stats_memory, error closing");
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
	
	//printf("tf: %.2f, fm: %.2f, bm: %.2f, cm: %.2f\n", total_memory, free_memory, buffer_memory, cached_memory);
	
	float total_memory_usage = total_memory - ( free_memory + buffer_memory + cached_memory );
	
	float total_memory_usage_percentage = 100*(total_memory_usage / total_memory);
	
	return total_memory_usage_percentage;
}
