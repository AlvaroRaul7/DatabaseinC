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


prueba: prueba.o logdb.so
	gcc obj/prueba.o -lhashtabprof -llogdb -Llib/ -o bin/prueba

prueba.o: src/prueba.c
	gcc -Wall -Iinclude/ -c src/prueba.c -o obj/prueba.o

logdb.so: src/logdb.c
	gcc -Wall -fPIC -shared -Iinclude/ <archivos .c de libreria liblogdb.so> -o lib/liblogdb.so


.PHONY: clean
clean:
	rm bin/* obj/* lib/libhashtab.so

