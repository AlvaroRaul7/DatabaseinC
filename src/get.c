#include "hashtable.h"
#include "db.h"
#include <fcntl.h>
#include <unistd.h>
#include <error.h>
#include <stdio.h>
#include <string.h>
#define LINE_SIZE 256
#define CONTROL_ARRAY_SIZE 2


void reemplazarCaracter(char *str, char viejo, char nuevo){
	//Funcion insegura...No usarla en la practica.
	while(*str != 0){
		if(*str == viejo){
			*str = nuevo;
			return;
		}
		str++;
	}
}
void llenarHashTable(hashtable *tabla, char *archivo){
	FILE *file = fopen(archivo, "r");
	int i = 0;
	int block_multiple = 2;
	char buf[LINE_SIZE] = {0};
	if(file != NULL){
		//printf("Empezamos a leer el archivo...\n");
		while(fgets(buf, LINE_SIZE, file) != NULL){
			if(i != 0 && i % CONTROL_ARRAY_SIZE == 0){
#ifdef DEBUG
				printf("Incrementando tamano de arreglo de control...\n");
#endif
				claves_arr = realloc(claves_arr, sizeof(char *) * CONTROL_ARRAY_SIZE * block_multiple);
				valores_arr = realloc(valores_arr, sizeof(char *) * CONTROL_ARRAY_SIZE * block_multiple);
				block_multiple++;
			}
			reemplazarCaracter(buf,'\n', 0);
			//split de 
			char *clave = strtok(buf,":");
			char *valor = strtok(NULL,":");
			//Llemanos la tabla
			put(tabla, strdup(clave), strdup(valor));
			//Despues de procesar la linea, borramos buffer
			memset(buf,0, LINE_SIZE);
			i++;
		}


		}
}


char* get_db(conexionlogdb* conexion,char* clave){
  hashtable *tabla=crearHashtable(10000);
  llenarHashTable(tabla,conexion->nombredb);
  char* valor=get(tabla,clave);
  if(valor!=NULL){
	  return valor;
  }
  return "La clave a buscar no existe";
}