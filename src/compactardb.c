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

	int d=creardb("compactado");
	if(d==1){
		printf("Archivo para compactar creado\n");
	}
	int i=0;
	for(;i<cantclave;i++){
			int valor=put_db("compactado",arrclaves[i],arrvalores[i]);
			valor=valor+0;
		
	}
	borrar(tablacompactada);
	
}


