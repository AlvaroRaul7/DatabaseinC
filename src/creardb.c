#include "db.h"
#include <fcntl.h>
#include <error.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>


int creardb(conexionlogdb *conexion, char *nombre_db){
    if(conexion==NULL){
        printf("Conexion no existente");
        return 0;
    }
    
    int archivodb=open(nombre_db,O_CREAT|O_RDWR);
    conexion->nombredb=nombre_db;
    if(archivodb<0){
        printf("Error de E/S");
        return 0;
    }
    close(archivodb);
    
    return 1;
    

}