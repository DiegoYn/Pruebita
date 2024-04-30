#include "k_variables_globales.h"
#include "inicializar_kernel.h"

void inicializa_kernel(){
    inicializar_loggers_kernel();
    inicializar_configs_kernel();
}

void inicializar_loggers_kernel(){
    kernel_logger = log_create("KERNEL.log","LOGGER",1,LOG_LEVEL_INFO);
	if(kernel_logger == NULL){
		perror("No se pudo crear el logger");
		exit(EXIT_FAILURE);
	}
}

void inicializar_configs_kernel(){

    kernel_config = config_create("KERNEL.config");
	if(kernel_config == NULL){
		perror("Error al intentar cargar el config");
		exit(EXIT_FAILURE);
	}
    
    PUERTO_ESCUCHA = config_get_string_value(kernel_config,"PUERTO_ESCUCHA");
    IP_MEMORIA = config_get_string_value(kernel_config,"IP_MEMORIA");
    PUERTO_MEMORIA = config_get_string_value(kernel_config,"PUERTO_MEMORIA");
    IP_CPU = config_get_string_value(kernel_config,"IP_CPU");
    PUERTO_CPU_DISPATCH = config_get_string_value(kernel_config,"PUERTO_CPU_DISPATCH");
    PUERTO_CPU_INTERRUPT = config_get_string_value(kernel_config,"PUERTO_CPU_INTERRUPT");
}
