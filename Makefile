
#Si quieren llamar reglas adicionales, agregenlas como pre-requisitos a la regla all
#La regla logdb.so deben modificarla con su comando para generar dicho ejecutable.
#El archivo prueba.c esta vacio. NO deben llenarlo. Este se reemplazara con el codigo del profesor
#al probar su proyecto

all:  db

#prueba: testing.o 
#	gcc obj/testing.o -lhashtabprof -llogdb -Llib/ -o bin/prueba

#logdb.so: 
#	gcc -Wall -fPIC -shared -Iinclude/   -o lib/liblogdb.so

db: put.o get.o eliminar.o compactardb.o creardb.o testing.o
	gcc -Wall -g  obj/put.o obj/get.o obj/eliminar.o obj/compactardb.o obj/creardb.o obj/testing.o -lhashtab -L./lib -Wl,-rpath,./lib  -o bin/db

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

testing.o: src/testing.c
	gcc -Wall -g -c src/testing.c -I include/ -o obj/testing.o


.PHONY: clean
clean:
	rm bin/* obj/* lib/libhashtab.so

