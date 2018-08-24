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

int connect_retry( int domain, int type, int protocol, 	const struct sockaddr *addr, socklen_t alen){
	
	int numsec, fd;

	for (numsec = 1; numsec <= 64; numsec <<= 1) { 

		if (( fd = socket( domain, type, protocol)) < 0){
			return(-1); 

		if (connect( fd, addr, alen) == 0) {
			printf("conexion aceptada"); 
			return(fd); 
		} 
		close(fd); 				

		if (numsec <= 64/2)

			sleep( numsec); 
	} 
	return(-1); 
}



conexionlogdb *conectar_db(char *ip, int puerto){
	
	int fd;
	int numsec;
	int conec;

	struct sockaddr_in direccion_cliente;
	memset(&direccion_cliente, 0, sizeof(direccion_cliente));
	
	conexionlogdb conexion;
	memset(&conexion, 0, sizeof(conexion));	
	
	direccion_cliente.sin_family = AF_INET;		
	direccion_cliente.sin_port = htons(puerto);		
	direccion_cliente.sin_addr.s_addr = inet_addr(ip) ;	
	
	if (( sockfd = connect_retry( direccion_cliente.sin_family, SOCK_STREAM, 0, (struct sockaddr *)&direccion_cliente, sizeof(direccion_cliente))) < 0) { 
		printf("falló conexión\n"); 
		exit(-1);
	} 	
	
	conexion.ip=ip;
	conexion.puerto=puerto;
	conexion.sockdf=sockfd;
	conexion.id_sesion=rand()%1000;

	return conexion;
}
