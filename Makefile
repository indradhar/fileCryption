CC=gcc
objects = index.o sha1.o mono_alphabetic_cipher.o new_encry.o
program.out : $(objects)
	${CC} $(objects) -o program.out -lssl -lcrypto
index.o : index.c header.h
	${CC} index.c -c
sha1.o : sha1.c
	${CC} sha1.c -c
mono_alphabetic_cipher.o : mono_alphabetic_cipher.c
	${CC} mono_alphabetic_cipher.c -c
new_encry.o : new_encry.c
	${CC} new_encry.c -c
