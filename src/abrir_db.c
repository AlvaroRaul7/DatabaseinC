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

int abrir_db(conexionlogdb *conexion, char *nombre_db){

	char buf[1000] =  { 0 };
	memset(buf,0,1000);
	
	char *cadena;
	cadena=(char*)malloc(1000*(sizeof(char)));
	
	strcpy(cadena,"abrir");
	strcat(cadena,",");
	strcat(cadena,nombre_db);	
	
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

	if(strcmp(buf,"exito")==0){
		printf("se abrio la base de datos con èxito.\n");
		conexion->nombredb=nombre_db;
		return 1;
	}
	else{
		printf("no se pudo abrir la base de datos.\n");
		return 0;
	}
}
