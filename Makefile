
#Si quieren llamar reglas adicionales, agregenlas como pre-requisitos a la regla all
#La regla logdb.so deben modificarla con su comando para generar dicho ejecutable.
#El archivo prueba.c esta vacio. NO deben llenarlo. Este se reemplazara con el codigo del profesor
#al probar su proyecto

all:  prueba logdb 

prueba: prueba.o logdb.so
	gcc obj/prueba.o -lhashtabprof -llogdb -Llib/ -o bin/prueba

prueba.o: src/prueba.c
	gcc -Wall -I include/ -c src/prueba.c -o obj/prueba.o

logdb.so: src/conectar_db.c src/crear_db.c src/abrir_db.c src/put_val.c src/get_val.c src/eliminar_.c src/cerrar_db.c src/compactar.c
	gcc -Wall -fPIC -shared -I include/ src/conectar_db.c src/crear_db.c src/abrir_db.c src/put_val.c src/get_val.c src/eliminar_.c src/cerrar_db.c src/compactar.c -o lib/liblogdb.so

logdb: put.o get.o eliminar.o compactardb.o creardb.o logdb.o
	gcc -Wall -g  obj/put.o obj/get.o obj/eliminar.o obj/compactardb.o obj/creardb.o obj/logdb.o -lhashtabprof -L./lib -Wl,-rpath,./lib  -o bin/logdb

put.o: src/put.c
	gcc -Wall -g -c src/put.c -I include/ -o obj/put.o

get.o: src/get.c
	gcc -Wall -g -c src/get.c -I include/ -o obj/get.o

eliminar.o: src/eliminar.c
	gcc -Wall -g -c src/eliminar.c -I include/ -o obj/eliminar.o

compactardb.o: src/compactardb.c
	gcc -Wall -g -c src/compactardb.c -I include/ -o obj/compactardb.o

creardb.o: src/creardb.c
	gcc -Wall -g -c src/creardb.c -I include/ -o obj/creardb.o

logdb.o: src/logdb.c
	gcc -Wall -g -c src/logdb.c -I include/ -o obj/logdb.o	
	
#testing.o: src/testing.c
#	gcc -Wall -g -c src/testing.c -I include/ -o obj/testing.o


.PHONY: clean
clean:
	rm bin/* obj/* lib/libhashtab.so

