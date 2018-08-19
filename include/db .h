#ifndef LOGDB_H
#define LOGDB_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


//Estructuras 
typedef struct conexionlogbTDA{
    char *ip;
    int puerto;              
    int sockdf;         //socket de la conexion a la base de datos.
    int id_sesion;		//Inicialmente en 0. Usado por el proceso logdb para saber que proceso esta usando cual db.
				//Al abrir la conexion, se llenar� este campo con un numero aleatorio (Este numero lo genera el proceso logdb, y lo devuelve a la lib).             
    char *nombredb;		//nombre de la db en uso. Inicialmente vacio hasta que se llame abrir_db(). Se llena SOLO si el proceso logdb pudo 
				//Abrir exitosamente los archivos de la DB (log e indice)
   
} conexionlogdb;

//Interfaz

conexionlogdb *conectar_db(char *ip, int puerto);			//Devuelve un objeto conexio, NULL si no se pudo abrir conexion.

int crear_db(conexionlogdb *conexion, char *nombre_db);			//Recibe un objeto conexion, y crear la db con el nombre dado. Devuelve 1 en exito, 0 en error (por ejemplo,
									//ya existe un base de datos con ese nombre, error de E/S, etc).

int abrir_db(conexionlogdb *conexion, char *nombre_db);			//Recibe un objeto conexion. Con esto se informa al proceso logdb que abra la base de datos nombre_db.
									//Retorna 1 si se pudo abrir, 0 en error (por ejemplo, si dicha db no existe).

int put_val(conexionlogdb *conexion, char *clave, char *valor);		//Inserta el elemento clave:valor en la db. Devuelve 1 en exito, 0 en  error.

char *get_val(conexionlogdb *conexion, char *clave); 				//devuelve el valor asociado a clave (si existe). Devuelve NULL si la clave no existe.

int eliminar(conexionlogdb *conexion, char *clave);				//Elimina la clave. Devuelve 1 en exito, 0 en error.

void cerrar_db(conexionlogdb *conexion);				//Cierra la conexion y libera la estructura conexion.

void compactar(conexionlogdb *conexion);				//Permite forzar la compactacion de la db.


#endif
