#include "hashtable.h"
#include "db.h"
#include <fcntl.h>
#include <unistd.h>
#include <error.h>
#include <stdio.h>
#include <string.h>
hashtable *crearHashTable(int numeroBuckets);

int eliminardb(conexionlogdb* conexion,char* clave){
  hashtable *tabla=crearHashTable(1000000);
  llenarHashTable(tabla,conexion->nombredb);
  put(tabla,clave,"!@");
  return 1;

}
