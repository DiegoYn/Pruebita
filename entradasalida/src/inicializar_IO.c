#include "IO_variables_globales.h"
#include "inicializar_IO.h"

void inicializa_IO(){
    inicializar_loggers_IO();
    inicializar_configs_IO();
}

void inicializar_loggers_IO(){
    IO_logger = log_create("IO.log","LOGGER",1,LOG_LEVEL_INFO);
	if(IO_logger == NULL){
		perror("No se pudo crear el logger");
		exit(EXIT_FAILURE);
	}
}

void inicializar_configs_IO(){

    IO_config = config_create("IO.config");
	if(IO_config == NULL){
		perror("Error al intentar cargar el config");
		exit(EXIT_FAILURE);
	}

    IP_MEMORIA = config_get_string_value(IO_config,"IP_MEMORIA");
    PUERTO_MEMORIA = config_get_string_value(IO_config,"PUERTO_MEMORIA");
    IP_KERNEL = config_get_string_value(IO_config,"IP_KERNEL");
    PUERTO_KERNEL = config_get_string_value(IO_config,"PUERTO_KERNEL");

}