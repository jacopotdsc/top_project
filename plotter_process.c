#include "plotter_process.h"

void get_process(){
	
	DIR* my_dir = opendir("/proc");
	
	handle_error(my_dir, "plotter_process.c -> get_process: failed opendir\n");

	struct dirent* my_struct;
	char* name;
	
	float p_cpu_usage;
	float p_mem_usage;
	int p_id;
	char* p_state;
	
	/*float total_cpu_usage = general_cpu_usage();
	float total_mem_usage = general_memory_usage();
	
	printf("total_cpu_usage: %f,\ttotal_memory_usage: %f\n", total_cpu_usage, total_mem_usage );
	*/
	while( (my_struct = readdir(my_dir) ) ){	// cicla per tutte le cartelle e si ferma quando le ha fatte tutte
			
		name = my_struct->d_name;
		
		if( atoi(name) == 0) continue; // atoi restituisce 0 se non è un numero ed i processi sono numerati a partire da 1
			
		//printf("dir: %s\n", name);
		
		char string_proc[200] = "/proc/";
		char* path = strcat(string_proc, name);
		//printf("0 -> path: %s \n", path);
		
		
		// da questo punto, mi creo la stringa finale che contiene tutte le statistiche del processo
		
		char* path1 = (char*)malloc(sizeof(char)*20);
		char* path2 = (char*)malloc(sizeof(char)*20);
		char* path3 = (char*)malloc(sizeof(char)*20);
		
		char file1[6] = "/stat";
		char file2[8] = "/status";
		char file3[7] = "/statm";

		strcpy(path1, path);
		strcpy(path2, path);
		strcpy(path3, path);
		
		//printf("path1: %s \n", path1);
		//printf("path2: %s \n", path2);

		char* path_stat   = strcat(path1, file1);
		//printf("1.2-> path_stat: %s \n", path_stat);
		char* path_status = strcat(path2, file2);
		//printf("2.2 -> path_status: %s \n", path_status);
		char* path_statm  = strcat(path3, file3);
		//printf("3.1 -> path_statm: %s \n", path_statm);
		

		p_cpu_usage = process_cpu_usage(path_stat);	
		p_mem_usage = process_memory_usage(path_statm);
		p_id = process_id(path_status);
		p_state = process_state(path_status);
		
		printf("pid: %d,  \tcpu_usage: %.2f,  mem_usage: %.2f,  state: %s\n", p_id, p_cpu_usage, p_mem_usage, p_state);
		
		//sleep(1);
		free(path1);
		free(path2);
		free(path3);
	}
	
	free(my_struct);
	int ret = closedir( my_dir );
	if( ret != 0) printf("errore, ret: %d\n", ret);
	
	printf("---- plot terminated ----\n");
}
