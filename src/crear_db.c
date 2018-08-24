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

int crear_db(conexionlogdb *conexion, char *nombre_db){
	
	char buf[1000] =  { 0 };
	memset(buf,0,1000);

	char *cadena;
	cadena=(char*)malloc(1000*(sizeof(char)));
	
	strcpy(cadena,"crear");
	strcat(cadena,",");
	strcat(cadena,nombre_db);
	
	send(conexion.sockdf,cadena,strlen(cadena),0);
	recv(conexion.sockdf,buf,1000,0);
	
	free(cadena);

	if(strcmp(buf,"exito")==0){
		printf("se creo la base con exito");
		return 1;
	}
	else{
		printf("no se pudo crear la base de datos");
		return 0;
	}
}
