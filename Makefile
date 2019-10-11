CC=gcc
objects = index.o sha1.o
program.out : $(objects)
	${CC} $(objects) -o program.out -lssl -lcrypto
index.o : index.c header.h
	${CC} index.c -c
sha1.o : sha1.c
	${CC} sha1.c -c
