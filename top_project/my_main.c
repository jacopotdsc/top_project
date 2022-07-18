#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

#include "general_stats.h"
#include "process_stats.h"
#include "plotter_process.h"
#include "error_handler.h"


#define TERMINATE "terminate"
#define KILL 	  "kill"
#define SUSPEND   "suspend"
#define RESUME	  "resume"
#define PLOT	  "plot"
#define STOP	  "stop"
#define HELP	  "help"

#define NOT_IMPLEMENTED(x)	printf("%s, not implemented\n", x);
#define SIG_NOT_IMPLEMENTED(x) printf("Action: %s not implemented\n",x);


void action_process(char* action){
	
	char pid_str[5];
	
	printf("\nInsert a process to %s: ", action);
	scanf(" %s", &pid_str);
	int pid = atoi(pid_str);
	int res;	
	
	if( strcmp(action, TERMINATE) == 0){		// comando ok
		//SIG_NOT_IMPLEMENTED(TERMINATE)
		res = kill(pid, SIGINT);	// di default questo segnale fa terminare
		handle_error_signal(res, "Signal SIGTERM, terminate,  not worked\n");
	}
	else if( strcmp(action, KILL) == 0){		// comando ok
		//SIG_NOT_IMPLEMENTED(KILL)
		res = kill(pid, SIGKILL);	// di default questo segnale fa terminare
		handle_error_signal(res, "Signal KILL, kill, not worked\n");
	}
	else if( strcmp(action, SUSPEND) == 0){		// fa stoppare il processo
		//SIG_NOT_IMPLEMENTED(SUSPEND)
		res = kill(pid, SIGTSTP);	// di default questo segnale fa stoppare il processo
		handle_error_signal(res, "Signal SIGTSTP, suspend, not worked\n");
	}
	else if( strcmp(action, RESUME) == 0){		// vedi meglio
		//SIG_NOT_IMPLEMENTED(RESUME)
		res = kill(pid, SIGCONT);	// di default questo segnale fa continuare il processo se era stato fermato
		handle_error_signal(res, "Signal SIGCONT, resume, not worked\n");
	}
}

int main2(){
	
	while(1){
		sleep(1);
		
		printf("-- chiamo --\n");
		//get_process();

		printf("\ncpu_usage:\t %f %\n", general_cpu_usage() );	// rivedi i valori che restituisce
		printf("memory_usage:\t %f %\n", general_memory_usage() );
		
		//printf("proc_cpu_usage:\t %f %\n", process_cpu_usage("/proc/2348/stat") );
		//printf("proc_memory usage:\t %f %\n", process_memory_usage("/proc/2348/status") );	// sistema, utilizza quella virtuale per il calcolo
		
		//sleep(3);
	}
}

float total_cpu_usage;
float total_mem_usage;

int main(int argc, char* argv[]){
	
	char command[20];
	
	int finished = 0;
	 
	printf("Commands: { terminate, kill, suspend, resume, plot, stop, help}\n");
	 
	//float total_cpu_usage = general_cpu_usage();
	//float total_mem_usage = general_memory_usage();
	
	//printf("total_cpu_usage: %f,\ttotal_memory_usage: %f\n", total_cpu_usage, total_mem_usage ); 
	do{
		
		printf("\nInsert a comand: ");
		scanf(" %s", &command);
		
		if( strcmp(command, TERMINATE) == 0 ){
			//NOT_IMPLEMENTED(TERMINATE);
			action_process(TERMINATE);
		}
		else if( strcmp(command, KILL) == 0 ){
			//NOT_IMPLEMENTED(KILL);
			action_process(KILL);
		}
		else if( strcmp(command, SUSPEND) == 0 ){
			//NOT_IMPLEMENTED(SUSPEND);
			action_process(SUSPEND);
		}
		else if( strcmp(command, RESUME) == 0 ){
			//NOT_IMPLEMENTED(RESUME);
			action_process(RESUME);
		}
		else if( strcmp(command, PLOT) == 0){
			//NOT_IMPLEMENTED(PLOT);
			total_cpu_usage = general_cpu_usage();
			total_mem_usage = general_memory_usage();
	
			printf("total_cpu_usage: %.2f,\ttotal_memory_usage: %.2f\n", total_cpu_usage, total_mem_usage );
			get_process();
		}
		else if( strcmp(command, HELP) == 0){
			//NOT_IMPLEMENTED(HELP);
			printf("\ncommand list:\n - terminate: terminate a process\n - kill: kill a process\n - suspend: force a process to sleep\n - resume: wake up a process\n - plot: plot statistics like cpu usage and memory usage\n - stop: terminate this programm\n");
		}
		else if( strcmp(command, STOP ) == 0){
			printf("-- terminated\n");
			finished = 1;
			break;
		}
		else printf("Command '%s' not found, insert {terminate, kill, suspend, resume, plot, stop, help}\n", command);
		
	}while( !finished );
	
}

