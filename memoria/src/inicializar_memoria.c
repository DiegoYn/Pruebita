#include "m_variables_globales.h"
#include "inicializar_memoria.h"

void inicializa_memoria(){
    inicializar_loggers_memoria();
    inicializar_configs_memoria();
	// imprimirPrueba();
}

void inicializar_loggers_memoria(){
    memoria_logger = log_create("MEMORIA.log","LOGGER",1,LOG_LEVEL_INFO);
	if(memoria_logger == NULL){
		perror("No se pudo crear el logger");
		exit(EXIT_FAILURE);
	}
}

void inicializar_configs_memoria(){

    memoria_config = config_create("MEMORIA.config");
	if(memoria_config == NULL){
		perror("Error al intentar cargar el config");
		exit(EXIT_FAILURE);
	}

    PUERTO_ESCUCHA = config_get_string_value(memoria_config,"PUERTO_ESCUCHA");
    
}

// void imprimirPrueba(){
// 	log_info(memoria_logger,PUERTO_ESCUCHA);

// }

