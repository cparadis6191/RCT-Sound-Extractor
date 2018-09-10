TARGET = rctse
OBJS = src/${TARGET}.o
CFLAGS = -g -Wall -Wextra -std=c99
.PHONY:clean

all: ${TARGET}.exe

# CXX is already defined and depends on the object being made
${TARGET}.exe: src/${TARGET}.o
	${CC} -o src/${TARGET} ${OBJS}

src/${TARGET}.o: src/${TARGET}.h

# This rule must be called explicitly
clean:
	rm -f src/*.o ${TARGET} ${TARGET}.exe core*
