//#pragma once

#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#define handle_error(number,msg)	do{	if(number < 0 || number == NULL){ perror(msg); exit(EXIT_FAILURE); } } while(0)

#endif
