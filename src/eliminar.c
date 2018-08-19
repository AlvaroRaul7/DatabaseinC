#include "hashtable.h"
#include "db.h"
#include <fcntl.h>
#include <unistd.h>
#include <error.h>
#include <stdio.h>
#include <string.h>


int eliminar(conexionlogdb* conexion,char* clave){
  hashtable *tabla=crearHashtable(10000);
  llenarTabla(tabla,conexion->nombredb);
  put(tabla,clave,"!@");
  return 1;

}
