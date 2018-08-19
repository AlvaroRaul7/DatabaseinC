#include "hashtable.h"
#include <fcntl.h>
#include <unistd.h>
#include <error.h>
#include <stdio.h>
#include <string.h>
#include "db.h"
int put(conexionlogdb *conexion, char *clave, char *valor){
    int fd = open(conexion->nombredb, O_RDWR);
	lseek(fd,0,SEEK_END);
  	char buf[100];
	strcpy(buf,clave);
  	strcat(buf, ":");
   	strcat(buf, valor);
	strcat(buf,"\n");
  	int bytes=write(fd,buf,strlen(buf));

    if(bytes<0){
        return 0;
    }
    return 1;
  	close(fd);

}


