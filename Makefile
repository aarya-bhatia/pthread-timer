COMPILERFLAGS = -std=c99 -g -Wall -Wextra -Wno-strict-prototypes -pedantic -O1
INCLUDE=-I/usr/local/include
LINKLIBS=-L/usr/local/lib -llog

.PHONY: all clean

all: obj test

test: obj/test.o obj/timer.o
	$(CC) $(COMPILERFLAGS) $^ -o $@ $(LINKLIBS)

clean :
	$(RM) obj/*.o test

obj/%.o: src/%.c
	$(CC) $(INCLUDE) $(COMPILERFLAGS) -c -o $@ $<
	
obj:
	mkdir -p obj
