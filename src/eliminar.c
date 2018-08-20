#include "hashtable.h"
#include "db.h"
#include <fcntl.h>
#include <unistd.h>
#include <error.h>
#include <stdio.h>
#include <string.h>

int eliminardb(char* nombredb,char* clave){
  hashtable* tabla=llenarHashTable(nombredb);
  put(tabla,clave,"!@");
  put_db(nombredb,clave,"!@");
  return 1;

}
