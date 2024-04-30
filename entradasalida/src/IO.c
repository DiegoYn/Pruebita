#include "IO.h"

void paquete(int );
int main(int argc, char* argv[]) {
    //Iniciar IO
    inicializa_IO();
    
    //Conexiones
    //int conexion_memoria = crear_conexion(IP_MEMORIA,PUERTO_MEMORIA);
    //paquete(conexion_memoria);
    int conexion_kernel = crear_conexion(IP_KERNEL,PUERTO_KERNEL);
    int conexion_memoria = crear_conexion(IP_MEMORIA,PUERTO_MEMORIA);
    paquete(conexion_memoria);
    return 0;
}