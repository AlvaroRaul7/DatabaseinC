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

void cerrar_db(conexionlogdb *conexion){
	char *cadena;
	cadena=(char*)malloc(1000*(sizeof(char)));
	
	strcpy(cadena,"cerrar");
	strcat(cadena,",");
	strcat(cadena,conexion->nombredb);

	if(conexion->sockdf==0){
		printf("No ha abierto alguna conexion");
		return;
	}
	int n=send(conexion->sockdf,cadena,strlen(cadena),0);
	if(n<0){
		printf("Error de conexion con el servidor");
		return;
	}
	free(cadena);
	int k=close(conexion->sockdf);
	if(k<0){
		printf("error al cerrar la conexion");
	}
	else{
		free(conexion);
		printf("la conexion se ha cerrado");
	}
	
}
