#include "process_stats.h"



void read_file_stat(FILE* f, float* aux){	// legge il file /proc/[pid]/stat
	
	int index = 0;
	fscanf(f, " %f", &aux[index++]);
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

void read_file_status(char* path, float* param){	// legge il file /proc/[pid]/stat
	
	FILE* my_file = fopen(path, "r"); 	//apro il file in lettura
	
	// controlla se è stato aperto correttamente, in caso stampa il msg di errore e termina
	handle_error(my_file, "general_stats.c -> general_cpu_usage: file not opened");
	
	int index = 0;
	
	char string[20];
	float my_float;
	
	while( index < 6){
		
		fscanf(my_file, "%s:", string);
	
		//printf("scanning -> %s, %f\n",string, my_float);
		//if(index != 0 ) sleep(1);
		
		// se ho trovato un parametro che mi serve, lo metto in param
		if( strcmp(string, "VmPeak:") == 0 || strcmp(string, "VmSize:") == 0 || strcmp(string, "VmLck:") == 0 || strcmp(string, "VmPin:") == 0 || strcmp(string, "VmHWM:") == 0 || strcmp(string, "VmRSS:") == 0 ){
			
			fscanf(my_file, "%f ", &my_float);
			param[index] = my_float;
			index += 1;
		}
		
	}
	
	close( (int) my_file);
	
}

void read_total_memory(float* param){	// legge il file /proc/[pid]/stat
	
	FILE* my_file = fopen("/proc/meminfo", "r"); 	//apro il file in lettura
	
	// controlla se è stato aperto correttamente, in caso stampa il msg di errore e termina
	handle_error(my_file, "general_stats.c -> general_cpu_usage: file not opened");
	
	float my_float;
	char string[20];
	
	while( 1 ){
		fscanf(my_file, "%s:", string);
	
		// ho trovato il parametro che mi serve
		if( strcmp(string, "MemTotal:") == 0 ){
			
			fscanf(my_file, "%f ", &my_float);
			*param = my_float;
			break;
		}
	}
	
	close( (int) my_file);
}

float process_memory_usage(char* path){
	float param[6];
	read_file_status(path, param);
	
	float VmPeak	= param[0];	
	float VmSize	= param[1];
	float VmLck		= param[2];
	float VmPin		= param[3];
	float VmHWM		= param[4];
	float VmRSS		= param[5];
	
	float tot_memory;
	read_total_memory(&tot_memory);
	
	//printf("vp: %.2f, vs: %.2f, vl: %.2f, vp: %.2f, vh: %.2f, vr: %.2f, tm: %.2f\n", VmPeak, VmSize, VmLck, VmPin, VmHWM, VmRSS, tot_memory);
	
	float total_memory_process = VmPeak + VmSize + VmLck + VmPin + VmHWM + VmRSS;	// uso totale della memoria
	float memory_usage = 100 * ( total_memory_process / tot_memory );
	
	//printf("tot_m_p: %f, tot_mem: %f, mem_usage: %f\n", total_memory_process, tot_memory, memory_usage);
	
	return memory_usage;
	
}



