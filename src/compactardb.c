#include "hashtable.h"
#include "db.h"
#include <fcntl.h>
#include <unistd.h>
#include <error.h>
#include <stdio.h>
#include <string.h>


void compactardb(char* nombredb){
	hashtable *tablacompactada=llenarHashTable(nombredb);
	printf("%d\n",tablacompactada->elementos);
	int cantclave=0;
	int cantvalores=0;
	char** arrclaves=claves(tablacompactada,&cantclave);
	char** arrvalores=(char** )valores(tablacompactada,&cantvalores);
	char buf[100];
	char* compactado="compactado";
	strcpy(buf,nombredb);
  	strcat(buf, compactado);
	int fd = open(buf,O_RDWR | O_CREAT, S_IWUSR | S_IRUSR);
		if(fd < 0){
		perror("No se pudo crear el archivo\n");
		
	}
	int i=0;
	for(;i<cantclave;i++){
			int valor=put_db(buf,arrclaves[i],arrvalores[i]);
			valor=valor+0;
		
	}
	borrar(tablacompactada);
	close(fd);
}


