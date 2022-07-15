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

char* get_process(){
	
	DIR* my_dir = opendir("/proc");
	
	handle_error(my_dir, "plotter_process.c -> get_process: failed opendir\n");

	struct dirent* my_struct;
	char* name;
	
	float p_cpu_usage;
	float p_mem_usage;
	int p_id;
	char* p_state;
	
	printf("entro nel while\n");
	while( (my_struct = readdir(my_dir) ) ){	// cicla per tutte le cartelle e si ferma quando le ha fatte tutte
			
		name = my_struct->d_name;
		
		if( atoi(name) == 0) continue; // atoi restituisce 0 se non è un numero ed i processi sono numerati a partire da 1
			
		printf("dir: %s\n", name);
		
		char* path = create_path_pid(name);
		printf("path: %s \n", path);
		
		
		// da questo punto, mi creo la stringa finale che contiene tutte le statistiche del processo
		
		char* path_stat = strcat(path, "/stat");
		printf("path_stat: %s\n", path_stat);
		
		p_cpu_usage = process_cpu_usage(path_stat);
		
		char* path_status = strcat(path, "us");
		printf("path_status: %s\n", path_status);
		
		p_mem_usage = process_memory_usage(path_status);
		p_id = process_id(path_status);
		p_state = process_state(path_status);
		
		printf("cpu: %f, mem: %f, id: %d, state: %s\n", p_cpu_usage, p_mem_usage, p_id, p_state);
		
		sleep(1);
		
	}
	
	sleep(1);
	printf("----finito----\n");
	return "bene";
}
