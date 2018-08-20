#include "hashtable.h"
#include "db.h"
#include <fcntl.h>
#include <unistd.h>
#include <error.h>
#include <stdio.h>
#include <string.h>

int put_db(char* nombredb, char *clave, char *valor){
    int fd = open(nombredb, O_RDWR|O_APPEND);
	//lseek(fd,0,SEEK_END);
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


