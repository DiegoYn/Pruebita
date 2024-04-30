#include "m_variables_globales.h"
#include "inicializar_memoria.h"
#include <pthread.h>

void* esperar_kernel(void*);
void* esperar_cpu(void*);
void* esperar_io(void*);
void selector(int ,t_log* ,t_list* );
void iterator(char*);

t_log* memoria_logger;
t_config* memoria_config;
t_list* lista;


char* PUERTO_ESCUCHA;

void* escuchar_clientes(int servidor_memoria){
    log_info(memoria_logger,"Escuchando clientes...");
    
	//Esperar Cpu
	pthread_t EsperarCPU;
    pthread_create(&EsperarCPU, NULL, esperar_cpu, (void*)&servidor_memoria);
	//Esperar Kernel
    pthread_t EsperarKernel;
    pthread_create(&EsperarKernel, NULL, esperar_kernel, (void*)&servidor_memoria);
    //Esperar IO
    pthread_t EsperarIO;
    pthread_create(&EsperarIO, NULL, esperar_io, (void*)&servidor_memoria);

    pthread_join(EsperarCPU, NULL);
	pthread_join(EsperarKernel, NULL);
    pthread_join(EsperarIO, NULL);
    return EXIT_SUCCESS;
}

//HILOOS
void* esperar_kernel(void* servidor_memoria_ptr){
    int servidor_memoria = *((int*)servidor_memoria_ptr);
    //Esperar Kernel con hilos
    int cliente_kernel = esperar_cliente(servidor_memoria, memoria_logger, "KERNEL");
    selector(cliente_kernel, memoria_logger, lista);
    pthread_exit(NULL);
}

void* esperar_cpu(void* servidor_memoria_ptr){
    int servidor_memoria = *((int*)servidor_memoria_ptr);
    //Esperar CPU con hilos
    int cliente_cpu = esperar_cliente(servidor_memoria, memoria_logger, "CPU");
    selector(cliente_cpu, memoria_logger, lista);
    pthread_exit(NULL);
}

void* esperar_io(void* servidor_memoria_ptr){
    int servidor_memoria = *((int*)servidor_memoria_ptr);
    //Esperar IO con hilos
    int cliente_io = esperar_cliente(servidor_memoria, memoria_logger, "IO");
    selector(cliente_io, memoria_logger, lista);
    pthread_exit(NULL);
}

void selector(int cliente_fd,t_log* logger,t_list* lista){
    while (true) {
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
                return;
            default:
                log_warning(logger,"Operacion desconocida.");
                break;
        }
    }
}

void iterator(char* value) {
    log_info(memoria_logger,"%s", value);
}
