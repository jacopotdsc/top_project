//#pragma once

#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#define handle_error(number,msg)	do{	if(number < 0 || number == NULL){ perror(msg); exit(EXIT_FAILURE); } } while(0)
#define handle_error_signal(number,msg)	do{	if(number == -1 ){ perror(msg); } } while(0)
#define handle_error_fclose(value, msg) do{	if(value == EOF ){ perror(msg); } } while(0)

#endif
