#include "process_stats.h"



void read_file_stat(FILE* f, float* aux){	// legge il file /proc/[pid]/stat
	
	int index = 0;
	fscanf(f, " %f ", &aux[index++]);
	fscanf(f, " %*s ", &aux[index++]);
	while( index < 25){
		fscanf(f, "%f ", &aux[index]);
		index += 1;
	}
	
}

void read_stats_process(char* path, float* param){	// legge i parametri utili per il calcolo di cpu_usage
	
	FILE* my_file = fopen(path, "r"); 	//apro il file in lettura
	
	// controlla se è stato aperto correttamente, in caso stampa il msg di errore e termina
	handle_error(my_file, "general_stats.c -> general_cpu_usage: file not opened");	
			
	
	// leggo tutto il file e lo metto in param
	
	float aux[25];
    read_file_stat(my_file, aux);
    
	param[0] = aux[13];
	param[1] = aux[14];
	param[2] = aux[15];
	param[3] = aux[16];
	param[4] = aux[21];
	
	close( (int) my_file);
	
	// prendo il parametro uptime ( del del sistema in secondi )
	
	my_file = fopen("/proc/uptime", "r"); 	
	
	handle_error(my_file, "general_stats.c -> general_cpu_usage: file not opened");	
	
	fscanf(my_file, "%f %f", &param[5], &aux[1]);	// aux[1] serve per scaricare da qualche parte la scanf
	
	
	// stampo
	printf("%f %f %f %f %f %f\n",param[0], param[1], param[2], param[3], param[4], param[5]);
	
	
}


// https://stackoverflow.com/questions/16726779/how-do-i-get-the-total-cpu-usage-of-an-application-from-proc-pid-stat
float process_cpu_usage(char* path){
	
	float param[6];
	read_stats_process(path, param);
	
	
    float utime 	= param[0];		// CPU time spent in user code, measured in clock ticks
    float stime 	= param[1];		// CPU time spent in kernel code, measured in clock ticks
    float cutime 	= param[2];		// Waited-for children's CPU time spent in user code (in clock ticks)
    float cstime 	= param[3];		// Waited-for children's CPU time spent in kernel code (in clock ticks)
    float starttime = param[4];		// Time when the process started, measured in clock ticks
    
    float uptime 	= param[5];		// tempo trascorso del sistema

	
	float hertz = sysconf(_SC_CLK_TCK); // frequenza della CPU
	
	float total_time = utime + cutime;	// tempo speso dal processo
	float seconds = uptime - (starttime / hertz);	// tempo totale trascorso
	float cpu_usage = 100 * ((total_time / hertz) / seconds);	// % di uso della cpu
	
	return cpu_usage;

}

float process_memory_usage(int pid){
	return 0.0;
}
