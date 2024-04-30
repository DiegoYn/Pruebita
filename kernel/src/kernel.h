#ifndef KERNEL_H_
#define KERNEL_H_

#include "k_variables_globales.h"
#include "inicializar_kernel.h"


t_log* kernel_logger;
t_config* kernel_config;
t_list* lista;
void selector(int ,t_log* ,t_list* );
void iterator(char*);
typedef struct {
    int conexion;
    void (*funcion)(int);
} ThreadArgs;

char* PUERTO_ESCUCHA;
char* IP_MEMORIA;
char* PUERTO_MEMORIA;
char* IP_CPU;
char* PUERTO_CPU_DISPATCH;
char* PUERTO_CPU_INTERRUPT;

void* esperar_io(int servidor_memoria){
	//Esperar IO con hilos
	int cliente_io = esperar_cliente(servidor_memoria,kernel_logger,"IO");
	selector(cliente_io, kernel_logger, lista);
	pthread_exit(esperar_io);
}
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
	log_info(kernel_logger,"%s", value);
}

#endif