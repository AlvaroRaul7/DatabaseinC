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
#include "db.h"
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
int abrir_db(conexionlogdb *conexion, char *nombre_db){

	char buf[1000] =  { 0 };
	memset(buf,0,1000);
	
	char *cadena;
	cadena=(char*)malloc(1000*(sizeof(char)));
	
	strcpy(cadena,"abrir");
	strcat(cadena,",");
	strcat(cadena,nombre_db);	
	
	send(conexion.sockdf,cadena,strlen(cadena),0);
	recv(conexion.sockdf,buf,1000,0);
	
	free(cadena);

	if(strcmp(buf,"exito")==0){
		printf("se abrio la base de datos con èxito");
		conexion.nombredb=nombre_db;
		return 1;
	}
	else{
		printf("no se pudo abrir la base de datos");
		return 0;
	}
}
int put_val(conexionlogdb *conexion, char *clave, char *valor){

	char buf[1000] =  { 0 };
	memset(buf,0,1000);
	
	char *cadena;
	cadena=(char*)malloc(1000*(sizeof(char)));
	
	strcpy(cadena,"put");
	strcat(cadena,",");
	strcat(cadena,conexion.nombre_db);
	strcat(cadena,",");
	strcat(cadena,clave);
	strcat(cadena,",");
	strcat(cadena,valor);		
	
	if(conexion.nombredb==NULL){
		printf("No ha abierto ninguna base de datos");
		return 0;
	}
	
	send(conexion.sockdf,cadena,strlen(cadena),0);
	recv(conexion.sockdf,buf,1000,0);
	
	free(cadena);
	
	if(strcmp(buf,"exito")==0){
		printf("se ingreso la informacion exitosamente");
		return 1;
	}
	else{
		printf("Error: no se pudo ingresar los datos");
		return 0;
	}
}

char *get_val(conexionlogdb *conexion, char *clave){
	
	char buf[1000] =  { 0 };
	memset(buf,0,1000);
	
	if(conexion.nombredb==NULL){
		printf("No ha abierto ninguna base de datos");
		return NULL;
	}
	
	char *cadena;
	cadena=(char*)malloc(1000*(sizeof(char)));
	
	strcpy(cadena,"get");
	strcat(cadena,",");
	strcat(cadena,conexion.nombre_db);
	strcat(cadena,",");
	strcat(cadena,clave);	
	
	send(conexion.sockdf,cadena,strlen(cadena),0);
	recv(conexion.sockdf,buf,1000,0);
	
	free(cadena);	
	
	if(strcmp(buf,"error")==0){
		printf("no existe la clave");
		return NULL;
	}
	else{
		return &buf;
	}
}

int eliminar(conexionlogdb *conexion, char *clave){

	char buf[1000] =  { 0 };
	memset(buf,0,1000);

	if(conexion.nombredb==NULL){
		printf("No ha abierto ninguna base de datos");
		return 0;
	}
	
	char *cadena;
	cadena=(char*)malloc(1000*(sizeof(char)));
	
	strcpy(cadena,"eliminar");
	strcat(cadena,",");
	strcat(cadena,conexion.nombre_db);
	strcat(cadena,",");
	strcat(cadena,clave);	
	
	send(conexion.sockdf,cadena,strlen(cadena),0);
	recv(conexion.sockdf,buf,1000,0);
	
	free(cadena);	
	
	if(strcmp(buf,"exito")==0){
		printf("se elimino la informacion exitosamente");
		return 1;
	}
	else{
		printf("Error: no existe la clave");
		return 0;
	}

}

void cerrar_db(conexionlogdb *conexion){
	
	if(conexion.sockdf==NULL){
		printf("No ha abierto alguna conexion");
		return 0;
	}
	close(conexion.sockdf);
	free(conexion);
	printf("la conexion se ha cerrado")
	
	
}
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
	
	
	send(conexion.sockdf,cadena,strlen(cadena),0);
	recv(conexion.sockdf,buf,1000,0);
	
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
	
	








	


