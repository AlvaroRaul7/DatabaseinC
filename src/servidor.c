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

	conexionlogdb conexion;
	memset(&conexion, 0, sizeof(conexion));
	
	if((fd = socket(ip, SOCK_STREAM, 0)) < 0)
		printf("Error al inicializar el servidor\n");	

	if(bind(fd,conexion, sizeof(conexion)) < 0)
		goto errout;
			
	if(listen(fd, 1000) < 0)
		goto errout;
	}
	errout:
		err = errno;
		close(fd);
		errno = err;
		
	int clfd = accept(fd, NULL, NULL);
	conexion.ip=ip;
	conexion.puerto=puerto;
	conexion.sockdf=clfd;
	conexion.id_sesion=0;

	return conexion;
}
int crear_db(conexionlogdb *conexion, char *nombre_db){
	
	int arch = creardb(nombre_db);
	if(arch<0){
		return 0;
	}
	conexion.id_sesion=rand()%(100+1);
	return arch;
	
}
int abrir_db(conexionlogdb *conexion, char *nombre_db){

	int arch;
	arch = open(nombre_db, O_RDWR | O_APPEND);
	if(arch < 0){
		perror("Hubo error.");
		return 0;
	}
	conexion.nombredb=nombre_db;
	return 1;

}
int put_val(conexionlogdb *conexion, char *clave, char *valor){
	
	int put;
	if(conexion.nombredb==NULL){
		printf("No ha abierto ninguna base de datos");
		return 0;
	}
	put = put_db(conexion.nombredb,clave,valor);
	if{put==0){
		printf("error al ingresar la informacion");
		return 0;
	}
	else{
		printf("se ha ingresado la informacion con exito");
		return 1;
	}
}

char *get_val(conexionlogdb *conexion, char *clave){

	if(conexion.nombredb==NULL){
		printf("No ha abierto ninguna base de datos");
		return NULL;
	}
	char *valor=get_db(conexion.nombredb,clave);
	return valor;
}

int eliminar(conexionlogdb *conexion, char *clave){
	int elm=eliminardb(conexion.nombredb,clave);
	if(elm!=1){
		printf("no se pudo eliminar");
	}
	return 1;
}
void cerrar_db(conexionlogdb *conexion){


}
void compactar(conexionlogdb *conexion){
	
	compactardb(conexion.nombredb);
}
	
	








	


