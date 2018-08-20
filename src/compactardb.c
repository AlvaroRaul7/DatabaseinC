#include "hashtable.h"
#include "db.h"
#include <fcntl.h>
#include <unistd.h>
#include <error.h>
#include <stdio.h>
#include <string.h>


void compactardb(conexionlogdb *conexion){
	hashtable *tablacompactada=crearHashTable(1000000);
	llenarHashTable(tablacompactada,conexion->nombredb);
	int cantclave=0;

	int cantvalores=0;
	char** arrclave=claves(tablacompactada,&cantclave);
	char** arrvalores=(char** )valores(tablacompactada,&cantvalores);
	char bufnombre[100];
	strcat(bufnombre,conexion->nombredb);
	strcat(bufnombre,"compactado");
	int dbcompactado=open(bufnombre,O_CREAT|O_RDWR);
    if(dbcompactado<0){
        printf("Error de E/S al crear el archivo compactado");
        
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


