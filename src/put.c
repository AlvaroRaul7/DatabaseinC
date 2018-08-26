#include "hashtable.h"
#include "db.h"
#include <fcntl.h>
#include <unistd.h>
#include <error.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



void escribirHashTableIndice(int fd,char* nombredb,char* clave, char* indice){
	int buckets=numBuckets(nombredb);
	hashtable *tablaindice=crearHashTable(buckets);
    int cantclave=0;
	int cantvalores=0;
	put(tablaindice,clave,indice);
	char** arrclaves=claves(tablaindice,&cantclave);
	char** arrvalores=(char** )valores(tablaindice,&cantvalores);
	int i=0;
	for(;i<cantclave;i++){
			char buf[100];
			strcpy(buf,arrclaves[i]);
  			strcat(buf, ":");
   			strcat(buf, arrvalores[i]);
			strcat(buf,"\n");
			int bytes=write(fd,buf,strlen(buf));
			 if(bytes<0){
      			  printf("No se pudo escribir en el indice");
    		}
		
	}
	
}



int put_db(char* nombredb, char *clave, char *valor){
    int fd = open(nombredb, O_RDWR|O_APPEND);
  	char buf[100];
	strcpy(buf,clave);
  	strcat(buf, ":");
   	strcat(buf, valor);
	strcat(buf,"\n");
	int bytes=write(fd,buf,strlen(buf));
	char bufnombre[100];
	strcpy(bufnombre,nombredb);
  	strcat(bufnombre, "indices");
	int descriptorindice=open(bufnombre, O_RDWR | O_CREAT, S_IWUSR | S_IRUSR);
	if(descriptorindice<0){
	}  
	//off_t position=lseek(fd,0,SEEK_CUR);
	//escribirHashTableIndice(descriptorindice,buf2,clave,"indice");
	char bufindice[100];
	strcpy(bufindice,clave);
	strcat(bufindice,":");
	//strcat(bufindice,"0");
	//int indice=write(descriptorindice,bufindice,100);
	//if(indice<0){
      //  printf("No se pudo escribir\n");
    //}
    if(bytes<0){
        return 0;
    }
    close(fd);
    return 1;
   

}