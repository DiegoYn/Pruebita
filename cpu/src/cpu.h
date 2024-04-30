#ifndef CPU_H_
#define CPU_H_

#include "c_variables_globales.h"
#include "inicializar_cpu.h"
void selector(int ,t_log* ,t_list* );
void iterator(char*);
t_log* cpu_logger;
t_config* cpu_config;
t_list* lista;

char* IP_MEMORIA;
char* PUERTO_MEMORIA;
char* PUERTO_CPU_DISPATCH;
char* PUERTO_CPU_INTERRUPT;

void selector(int cliente_fd,t_log* logger,t_list* lista){
		while (1) {
		int cod_op = recibir_operacion(cliente_fd);
		switch (cod_op) {
		case MENSAJE:
			recibir_mensaje(cliente_fd,logger);
			break;
		case PAQUETE:
			log_info(logger, "Me llegaron los siguientes valores:\n");
			lista = recibir_paquete(cliente_fd);
			 list_iterate(lista, (void*)iterator);
			break;
		case -1:
			log_error(logger, "el cliente se desconecto. Terminando servidor");
			exit(EXIT_FAILURE);
		default:
			log_warning(logger,"Operacion desconocida.");
			break;
		}
	}
	return;
}
void iterator(char* value) {
	log_info(cpu_logger,"%s", value);
}
#endif