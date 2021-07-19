SRC = \
	  main.c \
	  generic.c \
	  menu.c \
	  data_input.c \
	  data_output.c

OBJ = ${SRC:.c=.o}

#INCS = -I. -I/usr/include

CFLAGS = -Wall ${INCS}

all: main

main: ${OBJ}
	cc -o $@ ${OBJ} ${LIBS}

.c.o:
	${CC} -c ${CFLAGS} $<

clean:
	rm -f main ${OBJ}
