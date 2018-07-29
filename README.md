Descarguen este repositorio, y borren la URL de origin, y use la de su propio repositorio:

git remote remove origin

Luego, añadan la URL de su repositorio:

git remote add origin <URL de su repo>

Descripcion:

En este proyecto base tienen los siguientes directorios

- bin: ubicacion del ejecutable (logdb)
- include: archivos cabecera
    a. Aqui esta la declaracion de estructuras y funciones a implementar.
       SI NECESITAN CREAR MAS ARCHIVOS CABECERA, PUEDEN HACERLO.
    b. Se incluyen los siguientes archivos cabecera:
	 i. hashtable.h
	ii. logdb.h
- src: todos los archivo .c iran aqui
	i. El archivo prueba.c esta vacio. NO deben llenarlo. Este se reemplazara con el codigo del profesor 
	al probar su proyecto 
- obj: todos los archivos objetos deben ir a aqui
- lib: librerias (liblogdb.so, libhashtab.so)
	i. La libreria libhashtabprof.so es la libreria hashtable del profesor. NO LA USEN. USEN SU PROPIA IMPLEMENTACION (libhashtab.so)
- Makefile (No borrar las reglas adjuntas).

El objetivo del proyecto es implementar la base de datos que implica:
	1. El programa logdb, que manejara las solicitudes de los clientes y los archivos de la base de datos.
	2. La libreria libhashtab.so, que la usaran para el indice.
	3. La libreria liblogdb.so, que permitira a los programas clientes acceder a los servicios ofrecidos por logdb.

NO SE PERMITE MODIFICAR LOS ARCHIVOS include/hashtable.h ni include/logdb.h. Es posible que el profesor actualice estos archivos durante la duración del proyecto.


