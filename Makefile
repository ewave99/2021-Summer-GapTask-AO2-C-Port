INCS = -I. -I/usr/include

CFLAGS = -Wall ${INCS}
LDFLAGS = -lpcre2-8

all: main

main.o:
	cc -o main.o -c main.c ${CFLAGS}

main: main.o
	cc -o main main.o ${LDFLAGS}

clean:
	rm main main.o
