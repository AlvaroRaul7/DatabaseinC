#Escriba su makefiile en este archivo
#
# Integrante 1
# Integrante 2
#Escriba su makefiile en este archivo
#
# Integrante 1
# Integrante 2
#
#Si quieren llamar reglas adicionales, agregenlas como pre-requisitos a la regla all
#La regla logdb.so deben modificarla con su comando para generar dicho ejecutable.
#El archivo prueba.c esta vacio. NO deben llenarlo. Este se reemplazara con el codigo del profesor
#al probar su proyecto

all: prueba


prueba: testing.o logdb.so 
	gcc obj/testing.o -lhashtabprof -llogdb -Llib/ -o bin/prueba

prueba.o: src/prueba.c
	gcc -Wall -Iinclude/ -c src/prueba.c -o obj/prueba.o

testing.o: src/testing.c
	gcc -Wall -Iinclude/ -c src/testing.c -o obj/testing.o

logdb.so: src/creardb.c src/put.c
	gcc -Wall -fPIC -shared -Iinclude/ src/creardb.c src/put.c  -o lib/liblogdb.so


.PHONY: clean
clean:
	rm bin/* obj/* lib/libhashtab.so

