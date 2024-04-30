#include "memoria.h"
#include <commons/collections/dictionary.h>
typedef struct {
	int codigo_operacion_tamanio;
	char* codigo_operacion;
	int parametro1_tamanio;
	int parametro2_tamanio;
	char* parametros[2];

}t_instruccion;

int main(int argc, char* argv[]) {
	//Inicializar memoria
    inicializa_memoria();
    //Iniciar servidor
    int servidor_memoria = iniciar_servidor(PUERTO_ESCUCHA,memoria_logger,"Memoria");
    escuchar_clientes(servidor_memoria);
    //Creacion de hilo para escucha
    // pthread_t t1;
    // pthread_create(&t1,NULL,escuchar_clientes,NULL);
    // pthread_join(t1,NULL);
    return 0;
}
void recibir_pseudocodigo(int cliente_cpu){
    t_dictionary * diccionario_pseudocodigo = dictionary_create();
    t_list * lista_instrucciones = list_create();
    //declarar variables para almacenar la direccion del path del archivo y el pid del proceso
    char* path_archivo;
    int pid;
    recibir_path_y_pid(cliente_cpu, &path_archivo, &pid);
    char* path = string_new();
    string_append(&path, lista_instrucciones);
    string_append(&path, path_archivo);
    if (string_contains(path, "./")){
        char *buffer = malloc(256*sizeof(char));
        getcwd(buffer, 256);
        path = string_replace(path,"./",buffer);
        //Liberar memoria
        free(buffer);
    }
    else if (string_contains(path, "~/")){
        path = string_replace (path, "~/" , "/home/utnso/");
    }

    //Abro el archivo y lo leo
    FILE* archivo = fopen(path, "r");

    if(archivo == NULL){
		log_error(memoria_logger, "Error en la apertura del archivo: %s", path);
		free(path);
		return;
	}
    //Declaro variables para almacenar la instruccion y la primera linea de pseudocódigo
    char *cadena;
    

    //mientra el archivo no sea null ejecuto lo de dentro del while
    while(!feof(archivo)){
        cadena = malloc(256*sizeof(char));
        fgets(cadena, 256, archivo);

        //separa los tokens delimitados por espacios
        if (cadena == NULL){
            log_error(memoria_logger, "Error en la lectura del archivo: %s", path);
            exit(EXIT_FAILURE);
        }
        if(string_contains(cadena, "\n")){
			char** array_de_cadenas = string_split(cadena, "\n");

			cadena = string_array_pop(array_de_cadenas);


			while(strcmp(cadena, "") == 0){
				cadena = string_array_pop(array_de_cadenas);
			}

			string_array_destroy(array_de_cadenas);
		}
    
        //creo una estructura de tipo instruccion (declarada al principio)
        t_instruccion *instruccion = malloc(sizeof(t_instruccion));

        //lleno la estructura con los datos de la instruccion

        //aux toma el valor de la instruccion ej (SET) AX 1
        char* aux = strtok(cadena, " ");
        //
        instruccion->codigo_operacion_tamanio = strlen(aux)+1;
        instruccion->codigo_operacion = aux;
        instruccion->parametros[0] = NULL;
        instruccion->parametros[1] = NULL;
        //aux toma el valor de la instruccion ej SET (AX) 1
        aux = strtok(NULL, " ");
        int n = 0;
        while (aux!=NULL)
        {
        instruccion->parametros[n] = aux;
        aux = strtok(NULL, " ");
        n++;
        }
        if (instruccion->parametros[0] != NULL){
            instruccion->parametro1_tamanio= strlen(instruccion->parametros[0])+1;
        }else{
            instruccion->parametro1_tamanio = 0;
        }

        if (instruccion->parametros[1] != NULL){
            instruccion->parametro2_tamanio= strlen(instruccion->parametros[1])+1;
        }else{
            instruccion->parametro2_tamanio = 0;
        }
        //finalizado el llenado de la estructura, la agrego a la lista de instrucciones
        list_add(lista_instrucciones,instruccion);
        

    }
    dictionary_put(diccionario_pseudocodigo, string_itoa(pid), lista_instrucciones);
    //ACA ENVIAR MENSAJE CON CÓDIGO DE OPERACIÓN 
    free(path);
    fclose(archivo);
}
void recibir_path_y_pid(int socket_cliente, char **path, int *pid)
{
	int size;
	int desplazamiento = 0;
	void * buffer;
	int tamanio;

	buffer = recibir_buffer(&size, socket_cliente);
	while(desplazamiento < size)
	{
		memcpy(&tamanio, buffer + desplazamiento, sizeof(int));
		desplazamiento+=sizeof(int);
		*path = malloc(tamanio);

		memcpy(*path, buffer+desplazamiento, tamanio);
		desplazamiento+=tamanio;

		memcpy(pid, buffer+desplazamiento, sizeof(int));
		desplazamiento+=sizeof(int);
	}
	free(buffer);
}