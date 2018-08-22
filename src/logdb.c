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
#include <db.h>


conexionlogdb *conectar_db(char *ip, int puerto){
	
	int fd;
	int numsec;
	int conec;
	int flag=1;
	conexionlogdb conexion;
	memset(&conexion, 0, sizeof(conexion));

	while(flag==1){ 

		if (( fd = socket(ip, SOCK_STREAM, 0)) < 0) 
			printf("Error al conectar\n");
			printf("reintentando conectar...");

		if ((conec=connect( fd, addr, alen)) == 0) { 
			printf("conexion establecida");
			conexion.sockdf=conec; 
			
		} 
		close(fd); 				
		
		
	} 	
	
	conexion.ip=ip;
	conexion.puerto=puerto;
	conexion.id_sesion=0;

	return conexion;
}
int crear_db(conexionlogdb *conexion, char *nombre_db){
	
	char buf[1000] =  { 0 };
	memset(buf,0,1000);
	send(conexion.sockdf,nombredb,strlen(nombre_db),0);
	recv(conexion.sockdf,buf,1000,0);
	
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
	send(conexion.sockdf,nombredb,strlen(nombre_db),0);
	recv(conexion.sockdf,buf,1000,0);
	
	if(strcmp(buf,"exito")==0){
		printf("se abrio la base de datos con èxito");
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

	if(conexion.nombredb==NULL){
		printf("No ha abierto ninguna base de datos");
		return 0;
	}
	
	send(conexion.sockdf,clave,strlen(clave),0);
	send(conexion.sockdf,valor,strlen(valor),0);
	recv(conexion.sockdf,buf,1000,0);
	
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
	send(conexion.sockdf,clave,strlen(clave),0);
	recv(conexion.sockdf,buf,1000,0);
	
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
	
	send(conexion.sockdf,clave,strlen(clave),0);
	recv(conexion.sockdf,buf,1000,0);
	
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
	
	char buf[1000] =  { 0 };
	memset(buf,0,1000);

	if(conexion.nombredb==NULL){
		printf("No ha abierto la base de datos");
		return 0;
	}
	
	send(conexion.sockdf,conexion.sockfd,sizeof(conexion.sockfd),0);
	recv(conexion.sockdf,buf,1000,0);
	
	if(strcmp(buf,"exito")==0){
		printf("se cerro la conexion con exito");
		return 1;
	}
	else{
		printf("Error: no se pudo cerrar la conexion");
		return 0;
	}

}
void compactar(conexionlogdb *conexion){
	
	char buf[1000] =  { 0 };
	memset(buf,0,1000);

	if(conexion.nombredb==NULL){
		printf("No ha abierto la base de datos");
		return 0;
	}
	
	send(conexion.sockdf,conexion.nombrebd,strlen(conexion.nombrebd),0);
	recv(conexion.sockdf,buf,1000,0);
	
	if(strcmp(buf,"exito")==0){
		printf("compactacion completada exitosamente");
		return 1;
	}
	else{
		printf("Error: no se pudo compactar la base de datos");
		return 0;
	}
}
	
	








	


