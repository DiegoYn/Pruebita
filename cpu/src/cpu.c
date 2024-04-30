#include "cpu.h"
// void iterator(char* ,t_log* );
int main(int argc, char* argv[]) {
   inicializa_cpu();
   //Servidor cpu
   int servidor_cpu_dispatch = iniciar_servidor(PUERTO_CPU_DISPATCH, cpu_logger,"CPU_DISPATCH");
   int servidor_cpu_interrupt = iniciar_servidor(PUERTO_CPU_INTERRUPT, cpu_logger,"CPU_INTERRUPT");
   int conexion_memoria = crear_conexion(IP_MEMORIA,PUERTO_MEMORIA);
   // //Esperar kernel
   paquete(conexion_memoria);
   //int cliente_kernel = esperar_cliente(servidor_cpu_dispatch, cpu_logger,"KERNEL");

   // selector(cliente_kernel, cpu_logger, lista);
  
    //aquete(conexion_memoria);
   
   return 0;

}

