/**
 * Autor: Eduardo Murillo, M.Sc.
 * 
 **/
#include "hashtable.h"
#include "logdb.h"



int main(int argc, char** argv){
	char *ip="127.0.0.1";
	int puerto=4567;
	conexionlogdb *conexion = conectar_db(ip,puerto);
	crear_db(conexion,"sandia");
	return 0;
}





