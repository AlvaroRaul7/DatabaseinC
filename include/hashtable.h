#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


//Estructuras 
typedef struct objetoTablaTDA{
    char *clave;                           //El id de este objeto
    void *valor;                       //el objeto
    struct objetoTablaTDA *siguiente;   //Puntero al siguiente objetoTablaTDA
} objeto;


typedef struct hashtableTDA{
    int id;                            //Id de la hashtable (numero aleatorio)
    int elementos;                     //Numero de elemento en la hashtable
    int numeroBuckets;                 //Numero de buckets
    objeto **buckets;           //Arreglo de buckets (arreglo de punteros a objetos)
} hashtable;


//Funciones
hashtable *crearHashTable(int numeroBuckets);

int numeroElementos(hashtable *tabla);

void put(hashtable *tabla, char *clave, void *valor);

void *get(hashtable *tabla, char *clave);               //Devuelve valor asociado a clave, sin sacarlo de la hashtable

void *remover(hashtable *tabla, char *clave);           //Remueve la clave/valor del la hashtable, y devuelve el valor asociado a la clave

void borrar(hashtable *tabla);                         //Borrar todos los elementos de la hashtable, sin devolverlos (liberando la memoria de cada objeto)

char **claves(hashtable *tabla, int *conteo);          //Devuelve un arreglo de strings con TODAS las claves que hay en la hashtable.
                                                       //El numero de elementos debe devolverse en la variable conteo

int contieneClave(hashtable *tabla, char *clave);       //Devuelve 1 si la clave existe en la hashtable, 0 si no.

void **valores(hashtable *tabla, int *conteo);          //Devuelve un arreglo de punteros con todos los valores dentro de la hash table
                                                        //El numero de elementos debe devolverse en la variable conteo
                                                        
unsigned long hash(unsigned char *str);                  //funcion de hashing
#endif
