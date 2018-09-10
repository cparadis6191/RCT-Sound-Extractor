TARGET = rctse
OBJS = ${TARGET}.o
CFLAGS = -g -Wall -Wextra -std=c99
.PHONY:clean

all: ${TARGET}.exe

# CXX is already defined and depends on the object being made
${TARGET}.exe: ${TARGET}.o
	${CC} -o ${TARGET} ${OBJS}

${TARGET}.o: ${TARGET}.h

# This rule must be called explicitly
clean:
	rm -f *.o ${TARGET} ${TARGET}.exe core*
