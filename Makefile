INCS = -I. -I/usr/include

CFLAGS = -Wall ${INCS}
#LDFLAGS = -lpcre2-8

all: clean main

main.o:
	cc -o main.o -c main.c ${CFLAGS}

main: main.o
	cc -o main main.o ${LDFLAGS}

clean:
	rm -f main main.o
