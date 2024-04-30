#ifndef IO_VARIABLES_GLOBALES_H_
#define IO_VARIABLES_GLOBALES_H_

#include <stdlib.h>
#include <stdio.h>
#include <utils/conexiones.h>
#include <commons/txt.h>
#include <commons/log.h>
#include <commons/config.h>
#include <pthread.h>
/* 
COPIA

Variables globales

Variable extern para informar que existe una variable global, que alguien
del modulo la declaro y solo hay que usarla
Solo declaraciones NO inicializaciones
*/
extern t_log* IO_logger;
extern t_config* IO_config;

extern char* IP_MEMORIA;
extern char* PUERTO_MEMORIA;
extern char* IP_KERNEL;
extern char* PUERTO_KERNEL;

#endif