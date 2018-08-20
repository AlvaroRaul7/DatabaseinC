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



int creardb(conexionlogdb *conexion, char *nombre_db);			//Recibe un objeto conexion, y crear la db con el nombre dado. Devuelve 1 en exito, 0 en error (por ejemplo,
													
int put_db(conexionlogdb *conexion, char *clave, char *valor);		//Inserta el elemento clave:valor en la db. Devuelve 1 en exito, 0 en  error.

char *get_db(conexionlogdb *conexion, char *clave); 				//devuelve el valor asociado a clave (si existe). Devuelve NULL si la clave no existe.

int eliminardb(conexionlogdb *conexion, char *clave);				//Elimina la clave. Devuelve 1 en exito, 0 en error.

void compactardb(conexionlogdb *conexion);				//Permite forzar la compactacion de la db.

void llenarHashTable(hashtable *tabla, char *archivo);   //Lee un archivo txt y crea una hashtable en memoria donde hacer solicitudes eficientemente

void reemplazarCaracter(char *str, char viejo, char nuevo); 
#endif