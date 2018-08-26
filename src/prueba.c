/**
 * Autor: Eduardo Murillo, M.Sc.
 * 
 **/
#include "hashtable.h"
#include "logdb.h"



int main(int argc, char** argv){
	char *ip="127.0.0.1";
	int puerto=4200;
	conexionlogdb *conexion = conectar_db(ip,puerto);
	crear_db(conexion,"sandia");
	crear_db(conexion,"db1");
	abrir_db(conexion,"sandia");
	printf("base de datos: %s\n",conexion->nombredb);
	put_val(conexion,"fruta","sandia");
	put_val(conexion,"comida","ceviche");
	put_val(conexion,"Maria","Perez");
	get_val(conexion,"fruta");
	eliminar(conexion,"fruta");
	get_val(conexion,"fruta");
	put_val(conexion,"xd","hola");
	abrir_db(conexion,"db1");
	printf("base de datos: %s\n",conexion->nombredb);
	put_val(conexion,"fruta","sandia");
	put_val(conexion,"comida","ceviche");
	put_val(conexion,"Maria","Perez");
	get_val(conexion,"fruta");
	eliminar(conexion,"fruta");
	get_val(conexion,"fruta");
	put_val(conexion,"xd","hola");
	put_val(conexion,"ls","xd");
	//compactar(conexion);
	abrir_db(conexion,"testfile_5000000");
	compactar(conexion);
	return 0;
}





