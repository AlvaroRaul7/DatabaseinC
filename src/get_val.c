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

char *get_val(conexionlogdb *conexion, char *clave){
	
	char *buf;
	buf=(char*)malloc(1000*(sizeof(char)));
	
	if(conexion->nombredb==NULL){
		printf("No ha abierto ninguna base de datos.\n");
		return NULL;
	}
	
	char *cadena;
	cadena=(char*)malloc(1000*(sizeof(char)));
	
	strcpy(cadena,"get");
	strcat(cadena,",");
	strcat(cadena,conexion->nombredb);
	strcat(cadena,",");
	strcat(cadena,clave);	
	
	int n=send(conexion->sockdf,cadena,strlen(cadena),0);
	if(n<0){
		printf("Error de conexion con el servidor.\n");
		return 0;
	}
	int m=recv(conexion->sockdf,buf,1000,0);
	if(m<0){
		printf("Error de conexion con el servidor.\n");
		return 0;
	}
	
	free(cadena);	
	
	if(strcmp(buf,"error")==0){
		printf("no existe la clave.\n");
		return NULL;
	}
	else{
		return (char *)buf;
	}
}

