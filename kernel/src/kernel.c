#include "kernel.h"



int main(int argc, char* argv[]) {
    //Iniciar kernel
    inicializa_kernel();
    //Conexiones
    //int conexion_cpu_dispatch = crear_conexion(IP_CPU, PUERTO_CPU_DISPATCH);
    int servidor_kernel = iniciar_servidor(PUERTO_ESCUCHA,kernel_logger,"KERNEL");
    if (servidor_kernel == -1) {
        // Manejo de error si la inicialización del servidor falla
        return 1;
    }

    int conexion_memoria = crear_conexion(IP_MEMORIA,PUERTO_MEMORIA);
    if (conexion_memoria == -1) {
        // Manejo de error si la inicialización del servidor falla
        return 1;
    }
    int conexion_cpu_dispatch = crear_conexion(IP_CPU, PUERTO_CPU_DISPATCH);
    if (conexion_cpu_dispatch == -1) {
        // Manejo de error si la inicialización del servidor falla
        return 1;
    }
    int conexion_cpu_interrupt = crear_conexion(IP_CPU, PUERTO_CPU_INTERRUPT);
    if (conexion_cpu_interrupt == -1) {
        // Manejo de error si la inicialización del servidor falla
        return 1;
    }
    pthread_t enviar_mensaje;
    //argumentos para el hilo
    ThreadArgs args = {conexion_memoria, paquete};
    pthread_create(&enviar_mensaje,NULL,(void *(*)(void *))args.funcion, &args);
    pthread_join(enviar_mensaje,NULL);
    // pthread_t EsperarIO;
	// pthread_create(&EsperarIO,NULL,esperar_io,(void*)servidor_kernel);
    // pthread_join(EsperarIO,NULL);
    //paquete(conexion_cpu_interrupt);
    //paquete(conexion_cpu_dispatch);
    terminar_programa(conexion_memoria,kernel_logger,NULL);
    return 0;
}
