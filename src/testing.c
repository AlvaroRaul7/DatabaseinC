#include "hashtable.h"
#include "logdb.h"



int main(int argc, char** argv){
	
    conexionlogdb conexion;
    conexion.ip="127.0.0.1";
    conexion.puerto=2540;
    conexion.sockdf=20;
    conexion.id_sesion=1;
    crear_db(&conexion,"db1");

}
