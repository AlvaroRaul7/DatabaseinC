git remote remove origin

Then add your repository URL:

git remote add origin <URL of your repo>

Description:

In this base project have the following directories

- bin: location of the executable (logdb)
- include: header files
    a. Here is the declaration of structures and functions to implement.
       IF YOU NEED TO CREATE MORE HEADER FILES, YOU CAN DO IT.
    b. The following header files are included:
Yo. hashtable.h
ii. logdb.h
- src: all .c files will go here
Yo. The test.c file is empty. They should NOT fill it out. This will be replaced with the teacher's code
when testing your project
- obj: all object files should go here
- lib: libraries (liblogdb.so, libhashtab.so)
Yo. The libhashtabprof.so library is the professor's hashtable library. DO NOT USE IT. USE YOUR OWN IMPLEMENTATION (libhashtab.so)
- Makefile (Do not delete attached rules).

The objective of the project is to implement the database that implies:
1. The logdb program, which will handle client requests and database files.
2. The libhashtab.so library, which will be used for the index.
3. The liblogdb.so library, which will allow client programs to access the services offered by logdb.

YOU ARE NOT ALLOWED TO MODIFY THE FILES include/hashtable.h and include/logdb.h. These files may be updated by the teacher for the duration of the project.

