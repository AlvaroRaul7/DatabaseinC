#include "hashtable.h"
#include <fcntl.h>
#include <unistd.h>
#include <error.h>
#include <stdio.h>
#include <string.h>
#include "db.h"

void compactardb(conexionlogdb *conexion){
	hashtable* tablacompactada=crearHashtable(1000000);
	llenarHashTable(tabla,conexion->nombredb);
	int cantclave;
	int cantvalores;
	char** arrclave=claves(tabla,&cantclave);
	char** arrvalores=valores(tabla.&cantvalores);
	char *bufnombre[100];
	strcat(bufnombre,conexion->nombredb);
	strcat(bufnombre,"compactado");
	int dbcompactado=open(bufnombre,O_CREAT|O_RDWR);
    if(dbcompactado<0){
        printf("Error de E/S al crear el archivo compactado");
        return 0;
    }
	for(int i=0;i<cantclave;i++){
		for(int j=0;j<cantvalores;j++){
			char buf[100];
			lseek(dbcompactado,0,SEEK_END);
			strcat(buf,arrclave[i]);
			strcat(buf,":");
			strcat(buf,arrvalores[j]);
  			int bytes=write(dbcompactado,buf,strlen(buf));
			memset(buf,0,100);
   			 if(bytes<0){
       			 printf("No se pudo compactar la base de datos");
    			}

		}
	}
	close(dbcompactado);
}


