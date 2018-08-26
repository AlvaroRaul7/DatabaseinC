#include "hashtable.h"
#include "db.h"
#include <fcntl.h>
#include <unistd.h>
#include <error.h>
#include <stdio.h>
#include <string.h>

int eliminardb(char* nombredb,char* clave){
  hashtable* tabla=llenarHashTableIndice(nombredb);
 
  put(tabla,clave,"@T!");
  put_db(nombredb,clave,"@T!");
  return 1;

}
