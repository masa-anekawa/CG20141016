#MAKEFILE

CC	= gcc
RM	= rm -f

CFLAGS	= -Wall
LDFLAGS	= -ljpeg -lglut -lGLU -lGL -lm

TARGET	= sample-image
OBJS	= sample-image.o readjpeg.o

.c.o:
	${CC} -c ${CFLAGS} $<

TARGET: ${OBJS}
	${CC} -o ${TARGET} ${OBJS} ${LDFLAGS}

clean:
	${RM} ${TARGET} *.o *~
