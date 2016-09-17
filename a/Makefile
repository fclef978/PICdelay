# PICdelay alpha0.1 Makefile

PICdelay.exe: main.o func.o fileio.o
	gcc main.o func.o fileio.o -o PICdelay.exe -lm

main.o:main.c
	gcc -c main.c -W

func.o:func.c
	gcc -c func.c -W

fileio.o:fileio.c
	gcc -c fileio.c -W
