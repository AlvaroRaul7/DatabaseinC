#include <sys/types.h>          /* some systems still require this */
#include <sys/stat.h>
#include <stdio.h>              /* for convenience */
#include <stdlib.h>             /* for convenience */
#include <stddef.h>             /* for offsetof */
#include <string.h>             /* for convenience */
#include <unistd.h>
#include <error.h>             /* for convenience */
#include <signal.h>             /* for SIG_ERR */ 
#include <netdb.h> 
#include <errno.h> 
#include <syslog.h> 
#include <sys/socket.h> 
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "logdb.h"

void compactar(conexionlogdb *conexion){
	
	char buf[1000] =  { 0 };
	memset(buf,0,1000);

	if(conexion.nombredb==NULL){
		printf("No ha abierto la base de datos");
		return 0;
	}
	
	char *cadena;
	cadena=(char*)malloc(1000*(sizeof(char)));
	
	strcpy(cadena,"compactar");
	strcat(cadena,",");
	strcat(cadena,conexion.nombre_db);
	
	
	int n=send(conexion.sockdf,cadena,strlen(cadena),0);
	if(n<0){
		printf("Error de conexion con el servidor");
		return 0;
	}
	int m=recv(conexion.sockdf,buf,1000,0);
	if(m<0){
		printf("Error de conexion con el servidor");
		return 0;
	}
	
	free(cadena);	
	
	if(strcmp(buf,"exito")==0){
		printf("compactacion completada exitosamente");
		return 1;
	}
	else{
		printf("Error: no se pudo compactar la base de datos");
		return 0;
	}
}
	
	
