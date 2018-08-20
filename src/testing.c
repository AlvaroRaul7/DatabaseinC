#include "hashtable.h"
#include "db.h"
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <error.h>
#include <stdio.h>
#include <string.h>


   

int main(int argc, char** argv){
   printf("PRUEBA #1: CREARDB\n");
   int valor=creardb("p");
   if(valor==1){
       printf("Se creo la base de datos\n");
   }
   printf("PRUEBA #2: PUT\n");
   int v=put_db("p","perro","xd");
   if(v==1){
       printf("Se inserto en la base de datos\n");
   }
   printf("PRUEBA #3: GET\n");
  
   char* clave=get_db("p","perro");
   if(clave!=NULL){
       printf("Se obtuvo la clave: %s\n",clave);
       
   }
   printf("PRUEBA #4: ELIMINARDB\n");
   int val=eliminardb("testfile","perro");
   if(val==1){
       printf("Se elimino en la base de datos\n");
   }

   printf("PRUEBA #5: COMPACTARDB\n");
    compactardb("testfile");
}
