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
	abrir_db(conexion,"sandia");
	put_val(conexion,"fruta","sandia");
	put_val(conexion,"comida","ceviche");
	put_val(conexion,"Maria","Perez");
	get_val(conexion,"fruta");
	eliminar(conexion,"fruta");
	get_val(conexion,"fruta");
	put_val(conexion,"xd","hola");
	compactar(conexion);
	return 0;
}





