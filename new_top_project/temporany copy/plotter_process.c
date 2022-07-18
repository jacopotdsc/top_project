#include "plotter_process.h"


char* create_path_pid(char* pid){	// mi crea la stringa "/proc/[pid]"
	char string_proc[10] = "/proc/";
	return strcat(string_proc,pid);
}

char* create_path(char* actual_path, char* file){
	printf("create_path: %s\n", actual_path);
	return strcat(actual_path, file);
}

char* create_plot_string(char path[]){	// mi restituisce una stringa con le statistiche del processo
	
	//char path_stat[100]   = "/stat";
	//char path_status[100] = "/status";
	
	printf("path: %s \n", path );
	
	//printf("path: %s -> path_status: %s, len: %d, sizeof: %d\n", path, path_status, strlen(path_status), sizeof(path_status) );
	
	//char* new_path_stat = (char*)malloc(sizeof(char)*100); 
	//new_path_stat = strcat(*path, path_stat);
	//printf("new_path_stat: %s\n", new_path_stat);
	
	/*char* new_path_status= (char*)malloc(sizeof(char)*100); 
	new_path_status = strcat(path, path_status);
	printf("new_path_status: %s\n", new_path_status);*/
	
	return "-- ok --";
	
}

void get_process(){
	
	DIR* my_dir = opendir("/proc");
	
	handle_error(my_dir, "plotter_process.c -> get_process: failed opendir\n");

	struct dirent* my_struct;
	char* name;
	
	float p_cpu_usage;
	float p_mem_usage;
	int p_id;
	char* p_state;
	
	printf("total_cpu_usage: %f,\ttotal_memory_usage: %f\n", general_cpu_usage(), general_memory_usage() );
	while( (my_struct = readdir(my_dir) ) ){	// cicla per tutte le cartelle e si ferma quando le ha fatte tutte
			
		name = my_struct->d_name;
		
		if( atoi(name) == 0) continue; // atoi restituisce 0 se non è un numero ed i processi sono numerati a partire da 1
			
		//printf("dir: %s\n", name);
		
		char string_proc[10] = "/proc/";
		char* path = strcat(string_proc, name);
		//printf("0 -> path: %s \n", path);
		
		
		// da questo punto, mi creo la stringa finale che contiene tutte le statistiche del processo
		
		char* path1 = (char*)malloc(sizeof(char)*20);
		char* path2 = (char*)malloc(sizeof(char)*20);
		
		char file1[6] = "/stat";
		char file2[8] = "/status";

		strcpy(path1, path);
		strcpy(path2, path);
		
		//printf("path1: %s \n", path1);
		//printf("path2: %s \n", path2);

		char* path_stat   = strcat(path1, file1);
		//printf("1.2-> path_stat: %s \n", path_stat);
		char* path_status = strcat(path2, file2);
		//printf("2.2 -> path_status: %s \n", path_status);
		

		p_cpu_usage = process_cpu_usage(path_stat);	
		p_mem_usage = process_memory_usage(path_status);
		p_id = process_id(path_status);
		p_state = process_state(path_status);
		
		printf("pid: %d,\tcpu_usage: %f,\tmem_usage: %f,\tstate: %s\n", p_id, p_cpu_usage, p_mem_usage, p_state);
		
		//sleep(1);
	}
	
	free(my_dir);
	//int ret = closedir( my_dir );
	//if( ret == 0) printf("errore\n");
	
	printf("---- plot terminated ----\n");
}