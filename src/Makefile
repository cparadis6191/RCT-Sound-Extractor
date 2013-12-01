TARGET = RCTSE
OBJS = ${TARGET}.o
CFLAGS = -g -Wall -Wextra -std=c99
.PHONY:clean

all: ../${TARGET}.exe

# CXX is already defined and depends on the object being made
../${TARGET}.exe: RCTSE.o
	${CC} -o ../${TARGET} ${OBJS}

RCTSE.o: RCTSE.h

# This rule must be called explicitly
clean:
	rm -f *.o ../${TARGET}.exe core*
