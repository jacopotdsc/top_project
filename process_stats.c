#include "process_stats.h"

void read_file_stat(const char* path, float* param){	// legge il file /proc/[pid]/stat
	
	printf("rfs, path: %s\n", path);
	FILE* my_file = fopen(path, "r"); 	//apro il file in lettura
	printf("path: %s\n", path);
	
	// controlla se è stato aperto correttamente, in caso stampa il msg di errore e termina
	handle_error(my_file, "process_stats.c -> read_stats_process: file path not opened");	
	
	char* line;
	size_t linesize = 0;
	while( getline(&line, &linesize, my_file) != -1 ){
		//printf("%s",line);
	}
	
    close( (int) my_file);
    
    char* token = strtok(line, " ");
    
    int index = 0;
    for( int i=0; token != NULL; i++ ){
		
		if( MASK ){
			param[index] = atoi(token);
			//printf("token: %s, param[%d]: %f\n", token, index, param[index]);
			//sleep(1);
			index += 1;
		}
		
		token = strtok(NULL, " ");
	}
	
	FILE* my_file2 = fopen("/proc/uptime", "r"); 	
	
	handle_error(my_file2, "general_stats.c -> read_stats_process: file uptime not opened");	
	
	char aux;
	fscanf(my_file2, "%f %f", &param[5], &aux);	// aux[1] serve per scaricare da qualche parte la scanf
	
	close( (int) my_file2);
	
	//printf("%f %f %f %f %f %f\n",param[0], param[1], param[2], param[3], param[4], param[5]);
	//sleep(3);
	
}

float calculate_cpu_usage(const char* path){	// calcola l'utilizzo della cpu
	
	//printf("path: %s\n", path);
	float param[6];
	read_file_stat(path, param);
	
	
    float utime 	= param[0];		// CPU time spent in user code, measured in clock ticks
    float stime 	= param[1];		// CPU time spent in kernel code, measured in clock ticks
    float cutime 	= param[2];		// Waited-for children's CPU time spent in user code (in clock ticks)
    float cstime 	= param[3];		// Waited-for children's CPU time spent in kernel code (in clock ticks)
    float starttime = param[4];		// Time when the process started, measured in clock ticks
    
    float uptime 	= param[5];		// tempo trascorso del sistema

	//printf("%f %f %f %f %f %f\n",param[0], param[1], param[2], param[3], param[4], param[5]);
	
	float hertz = sysconf(_SC_CLK_TCK); // frequenza della CPU
	//printf("hertz: %f\n", hertz);
	
	float total_time = utime + stime + cutime + cstime;	// tempo speso dal processo
	float seconds 	 = uptime - (starttime / hertz);	// tempo totale trascorso
	float cpu_usage  = ((total_time / hertz) / seconds);	// % di uso della cpu
	
	float cpu_usage_percentage = 100*cpu_usage;
	
	printf("--ret: %f--\n", cpu_usage_percentage);
	
	return cpu_usage_percentage;

}

// https://stackoverflow.com/questions/16726779/how-do-i-get-the-total-cpu-usage-of-an-application-from-proc-pid-stat
float process_cpu_usage(const char* path){ // wrapper per sopra
	return calculate_cpu_usage(path);
}


void read_file_status(const char* path, float* param){	// legge il file /proc/[pid]/stat
	
	FILE* my_file = fopen(path, "r"); 	//apro il file in lettura
	
	// controlla se è stato aperto correttamente, in caso stampa il msg di errore e termina
	handle_error(my_file, "process_stats.c -> read_file_status: file not opened");	
	
	char* line;
	size_t linesize = 0;
	int i = 0;
	while( getline(&line, &linesize, my_file) != -1 ){
		
		//printf("\nline: %s", line);
		char* token = strtok(line, "\t");
		//printf("token: %s\n", token);
		
		if( TOKEN_MASK ){
			param[i] = atoi( strtok(NULL, " ") );
			//printf("token: %s, param[%d]: %f\n", token, i, param[i]);
			i++;
		}
	}
	
    close( (int) my_file);
	
	FILE* my_file2 = fopen("/proc/meminfo", "r"); 	
	
	handle_error(my_file2, "process_stat.c -> read_file_status: file not opened");	
	
	char aux;
	fscanf(my_file2, "%*s %f", &param[3]);	// aux[1] serve per scaricare da qualche parte la scanf
	
	close( (int) my_file2);
	
	//printf("%f %f %f %f \n",param[0], param[1], param[2], param[3]);
	//sleep(3);
	
}

float process_memory_usage(const char* path){	// calcola l'uso della memoria
	float param[4];
	read_file_status(path, param);
	
	float RssAnon 	= param[0];
	float RssFile 	= param[1];
	float RssShmem 	= param[2];
	float tot_mem 	= param[3];
	
	//printf("ra: %f, rf: %f, rs: %f, tm: %f\n", RssAnon, RssFile, RssShmem, tot_mem);
	
	float memory_usage = ( RssAnon + RssFile + RssShmem ) / tot_mem;
	
	return 100 * memory_usage;
}

int process_id(char* path){	// mi restituisce id del processo
	
	char buff[80];
	strcpy(buff,path);
	
	char* token = strtok(buff,"/");
	token = strtok(NULL,"/");
	
	return atoi(token);
	
}

char* process_state(char* path){	// mi restituisce lo stato del processo
	FILE* my_file = fopen(path, "r"); 	//apro il file in lettura
	
	// controlla se è stato aperto correttamente, in caso stampa il msg di errore e termina
	handle_error(my_file, "process_stats.c -> read_file_status: file not opened");	
	
	char* line;
	size_t linesize = 0;
	int i = 0;
	while( getline(&line, &linesize, my_file) != -1 ){

		char* token = strtok(line, "\t");
		
		if( strcmp(token, &"State:") == 0 )
			return strtok(NULL, " ");
	}
}

