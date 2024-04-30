#include "c_variables_globales.h"
#include "inicializar_cpu.h"

void inicializa_cpu(){
    inicializar_loggers_cpu();
    inicializar_configs_cpu();
}
// void saludame(){
//     log_info(cpu_logger,"Hola, soy una CPU");
// }

void inicializar_loggers_cpu(){
    cpu_logger = log_create("CPU.log","LOGGER",1,LOG_LEVEL_TRACE);
	if(cpu_logger == NULL){
		perror("No se pudo crear el logger");
		exit(EXIT_FAILURE);
	}
}

void inicializar_configs_cpu(){

    cpu_config = config_create("CPU.config");
	if(cpu_config == NULL){
		perror("Error al intentar cargar el config");
		exit(EXIT_FAILURE);
	}

    IP_MEMORIA = config_get_string_value(cpu_config,"IP_MEMORIA");
    PUERTO_MEMORIA = config_get_string_value(cpu_config,"PUERTO_MEMORIA");
    PUERTO_CPU_DISPATCH = config_get_string_value(cpu_config,"PUERTO_ESCUCHA_DISPATCH");
    PUERTO_CPU_INTERRUPT = config_get_string_value(cpu_config,"PUERTO_ESCUCHA_INTERRUPT");
}