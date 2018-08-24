#include <sys/types.h>          /* some systems still require this */
#include <sys/stat.h>
#include <stdio.h>              /* for convenience */
#include <stdlib.h>             /* for convenience */
#include <stddef.h>             /* for offsetof */
#include <string.h>             /* for convenience */
#include <unistd.h>             /* for convenience */
#include <signal.h>             /* for SIG_ERR */ 
#include <netdb.h> 
#include <errno.h> 
#include <syslog.h> 
#include <sys/socket.h> 
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "db.h"

int initserver(int type, const struct sockaddr *addr, socklen_t alen, int qlen){

	int fd;
	int err = 0;
	
	if((fd = socket(addr->sa_family, type, 0)) < 0)
		return -1;
		
	if(bind(fd, addr, alen) < 0)
		goto errout;
		
	if(type == SOCK_STREAM || type == SOCK_SEQPACKET){
		
			if(listen(fd, qlen) < 0)
				goto errout;
	}
	return fd;
errout:
	err = errno;
	close(fd);
	errno = err;
	return (-1);
}

int main( int argc, char *argv[]) { 
	int sockfd;

	if(argc == 1){
		printf("Uso: ./servidor <numero de ip> <numero de puerto>\n");
		exit(-1);
	}

	if(argc < 3){

		printf( "por favor especificar un numero de ip o de puerto\n");
	}
	int puerto = atoi(argv[2]);
	char *ip=argv[1];
	printf("La ip es : %s\n",ip);
	printf("El socket a conectarse es: %d\n",puerto);
	struct sockaddr_in direccion_servidor;

	memset(&direccion_servidor, 0, sizeof(direccion_servidor));	//ponemos en 0 la estructura direccion_servidor

	//llenamos los campos
	direccion_servidor.sin_family = AF_INET;		//IPv4
	direccion_servidor.sin_port = htons(puerto);		//Convertimos el numero de puerto al endianness de la red
	direccion_servidor.sin_addr.s_addr = inet_addr(ip) ;	//Nos vinculamos a la interface localhost o podemos usar INADDR_ANY para ligarnos A TODAS las interfaces

	

	//inicalizamos servidor (AF_INET + SOCK_STREAM = TCP)
	if( (sockfd = initserver(SOCK_STREAM, (struct sockaddr *)&direccion_servidor, sizeof(direccion_servidor), 1000)) < 0){	//Hasta 1000 solicitudes en cola 
		printf("Error al inicializar el servidor\n");	
	}	
	int clfd=-1;
	char data[1000]={0};
	char *respuesta;
	respuesta=(char*)malloc(1000*(sizeof(char)));
	while(1){
		if(clfd==-1){
			int clfd = accept(sockfd, NULL, NULL);
		}

		int n=recv( clfd, data, 1000, 0);
		if(n==0){
			close(clfd);
			clfd=-1;
			continue;
		}
		else{
	

			char *string=strtok(data,",");

			if(strcmp(string[0],"crear")==0){
				int cod=creardb(string[1]);
				if(cod<1){
					strcpy(respuesta,"Error");
				}else{
					strcpy(respuesta,"exito");
				}					
			}
			else if(strcmp(string[0],"abrir")==0){
				int cod=1;
				//int cod=abrirdb(string[1]);
				if(cod<1){
					strcpy(respuesta,"Error");
				}else{
					strcpy(respuesta,"exito");
				}	
					
			}
			else if(strcmp(string[0],"put")==0){
				int cod=put_db(string[1],string[2],string[3]);
				if(cod<1){
					strcpy(respuesta,"Error");
				}else{
					strcpy(respuesta,"exito");
				}	
					
			}
			else if(strcmp(string[0],"get")==0){
				char* cod=get_db(string[1],string[2]);
				if(cod==NULL){
					strcpy(respuesta,"Error");
				}else{
					strcpy(respuesta,*cod);
				}	
							
			}
			else if(strcmp(string[0],"eliminar")==0){
				int cod=eliminardb(string[1],string[2]);

				if(cod<1){
					strcpy(respuesta,"Error");
				}else{
					strcpy(respuesta,"exito");
				}	
					
			}
			else if(strcmp(string[0],"compactar")==0){
				compactardb(string[1]);
				strcpy(respuesta,"exito");	
			}
			else{
				printf("Error: no ingresó a ninguna opcion");
				return 0;
			}
			send(clfd,respuesta, 1000, 0); 
		}
	}		
	
}


