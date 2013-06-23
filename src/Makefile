TARGET = RCTSE
OBJS = RCTSE.o
CFLAGS = -g -Wall -std=c99
LDFLAGS = # Libaries to be linked
.PHONY:clean

# CXX is already defined and depends on the object being made
${TARGET}:${OBJS}
	${CC} -o ../${TARGET} ${OBJS} ${LDFLAGS}

RCTSE.o:RCTSE.h

# This rule must be called explicitly
clean:
	rm -f *.o ../${TARGET}.exe core*
