#include "process_stats.h"

void read_file_stat(const char* path, float* param){	// legge il file /proc/[pid]/stat
	
	FILE* my_file = fopen(path, "r"); 	//apro il file in lettura
	
	handle_error(my_file, "process_stats.c -> read_file_stat, f1: file path not opened");	
	
	char* line;
	size_t linesize = 0;
	while( getline(&line, &linesize, my_file) != -1 ){
		//printf("%s",line);
	}
	
    handle_error_fclose( fclose( my_file), "read_file_stat f1, error closing");
    
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
	
	handle_error(my_file2, "general_stats.c -> read_file_stat, f2: file uptime not opened");	
	
	char aux;
	fscanf(my_file2, "%f %f", &param[5], &aux);	// aux[1] serve per scaricare da qualche parte la scanf
	
	handle_error_fclose( fclose( my_file2), "read_file_stat f2, error closing");
	
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
	
	//printf("--ret: %f--\n", cpu_usage_percentage);
	
	return cpu_usage_percentage;

}

// https://stackoverflow.com/questions/16726779/how-do-i-get-the-total-cpu-usage-of-an-application-from-proc-pid-stat
float process_cpu_usage(const char* path){ // wrapper per sopra
	return calculate_cpu_usage(path);
}


void read_file_status(const char* path, float* param){	// legge il file /proc/[pid]/stat
	
	FILE* my_file = fopen(path, "r"); 	
	
	handle_error(my_file, "process_stats.c -> read_file_status, f1: file not opened");	
	
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
	
	handle_error_fclose( fclose( my_file), "read_file_status f1, error closing");

	
	FILE* my_file2 = fopen("/proc/meminfo", "r"); 	
	
	handle_error(my_file2, "process_stat.c -> read_file_status, f1: file not opened");	
	
	char aux;
	fscanf(my_file2, "%*s %f", &param[3]);	// aux[1] serve per scaricare da qualche parte la scanf
	
	handle_error_fclose( fclose( my_file2), "read_file_status f2, error closing");
	
	//printf("%f %f %f %f \n",param[0], param[1], param[2], param[3]);
	//sleep(3);
	
}

float process_memory_usage(const char* path){	// calcola l'uso della memoria
	/*
	float param[4];
	read_file_status(path, param);
	
	/*float RssAnon 	= param[0];
	float RssFile 	= param[1];
	float RssShmem 	= param[2];
	float tot_mem 	= param[3];
	
	printf("\nmra: %f, rf: %f, rs: %f, tm: %f\n", RssAnon, RssFile, RssShmem, tot_mem);
	printf("path: %s\n", path);
	
	float memory_usage = ( RssAnon + RssFile + RssShmem ) / tot_mem;*/
	
	float param[7];
	
	/*FILE* my_file = fopen(path, "r"); 	//apro il file in lettura
	
	handle_error(my_file, "process_stats.c -> process_memory_usage, f1: file not opened");
	
	//fscanf(my_file, "%f %f %f %f %f %f %f", &param[0], &param[1], &param[2], &param[3], &param[4], &param[5], &param[6] );
	fscanf(my_file, "%f %f %f %f %f %f %f", &param[0]);
	
	handle_error_fclose( fclose( my_file), "process_memory_usage f1, error closing");
	
	// ram, text, data
	//float memory_usage = ( param[0] / general_memory_usage() );
	//printf("0: %f, 1: %f, 3: %f, 5: %f\, mem_usage: %f \n", param[0], param[1], param[3], param[5], general_memory_usage() );
	
	
	*/
	
	FILE* my_file2 = fopen(path, "r"); 	//apro il file in lettura
	
	handle_error(my_file2, "process_stats.c -> process_memory_usage, f1: file not opened");
	
	//fscanf(my_file, "%f %f %f %f %f %f %f", &param[0], &param[1], &param[2], &param[3], &param[4], &param[5], &param[6] );
	fscanf(my_file2, "%f %f %f %f %f %f %f", &param[0], &param[1], &param[2], &param[3], &param[4], &param[5], &param[6]);
	
	handle_error_fclose( fclose( my_file2), "process_memory_usage f1, error closing");
	
	//+printf("p[0]: %f, p[1]: %f, p[3]: %f, p[5]: %f\n", param[0], param[1], param[3], param[5]);
	
	
	// calcolo la ram totale
	
	FILE* my_file3 = fopen("/proc/meminfo","r");
	handle_error(my_file3, "process_stats.c -> process_memory_usage, f3: file not opened");
	
	float tot_mem;
	
	char* line;
	size_t linesize = 0;
	int i = 0;
	while( getline(&line, &linesize, my_file3) != -1 ){
		char* token = strtok(line, " ");
		//printf("token: %s\n",token);
		if( strcmp(token, &"MemTotal:") == 0 )
			tot_mem = atoi( strtok(NULL, " ") );
	}
	
	//printf("tot_mem: %.2f\n", tot_mem);
	
	handle_error_fclose( fclose( my_file3), "process_memory_usage f3, error closing");
	
	//float memory_usage = ( param[0] + param[1] + param[3] + param[5] ) / 4032888 ;
	//float memory_usage = ( param[5] * getpagesize()) / 4032888000 ;
	float memory_usage = ( param[5] * getpagesize()) / (tot_mem*1000) ;
	 
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
	
	handle_error(my_file, "process_stats.c -> process_state: file not opened");	
	
	char* line;
	size_t linesize = 0;
	int i = 0;
	while( getline(&line, &linesize, my_file) != -1 ){

		char* token = strtok(line, "\t");
		
		if( strcmp(token, &"State:") == 0 )
			return strtok(NULL, " ");
	}
	
	handle_error_fclose( fclose( my_file), "process_state, error closing");
}

