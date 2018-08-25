#include "hashtable.h"
#include "db.h"
#include <fcntl.h>
#include <error.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int abrirdb(char *nombre_db){
    int archivodb=open(nombre_db,O_RDWR | O_APPEND,S_IWUSR | S_IRUSR);
    if(archivodb<0){
        
        return 0;
    }
    return 1;
    

}
