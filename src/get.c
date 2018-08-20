#include "hashtable.h"
#include "db.h"
#include <fcntl.h>
#include <unistd.h>
#include <error.h>
#include <stdio.h>
#include <string.h>


hashtable *crearHashTable(int numeroBuckets);

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
hashtable* llenarHashTable(char *archivo){
	 hashtable *tabla=crearHashTable(100000);
	FILE *file = fopen(archivo, "r");
	char buf[300] = {0};
	if(file != NULL){
		while(fgets(buf, 300, file) != NULL){
			reemplazarCaracter(buf,'\n', 0);
			char *clave = strtok(buf,":");
			char *valor = strtok(NULL,":");
			put(tabla, strdup(clave), strdup(valor));
			//Despues de procesar la linea, borramos buffer
			memset(buf,0, 300);	
		}
		}
    return tabla;
}


char* get_db(char *nombredb,char* clave){
  hashtable *tabla=llenarHashTable(nombredb);
  char* valor=(char* ) get(tabla,clave);
  return valor;
}