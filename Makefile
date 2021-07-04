SRC = \
	  main.c \
	  generic.c \
	  menu.c \
	  main_functions.c

OBJ = ${SRC:.c=.o}

INCS = -I. -I/usr/include

CFLAGS = -Wall ${INCS}
#LDFLAGS = -lpcre2-8

all: main

main: ${OBJ}
	cc -o $@ ${OBJ} ${LDFLAGS}

.c.o:
	${CC} -c ${CFLAGS} $<

clean:
	rm -f main ${OBJ}
