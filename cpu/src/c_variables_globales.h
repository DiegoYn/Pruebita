#ifndef CPU_GESTOR_H_
#define CPU_GESTOR_H_

#include <stdlib.h>
#include <stdio.h>
#include <utils/conexiones.h>
#include <commons/txt.h>
#include <commons/log.h>
#include <commons/config.h>

//COPIA

//Variables globales
/* 
Variable extern para informar que existe una variable global, que alguien
del modulo la declaro y solo hay que usarla
Solo declaraciones NO inicializaciones
*/
extern t_log* cpu_logger;
extern t_config* cpu_config;

extern char* IP_MEMORIA;
extern char* PUERTO_MEMORIA;
extern char* PUERTO_CPU_DISPATCH;
extern char* PUERTO_CPU_INTERRUPT;

#endif