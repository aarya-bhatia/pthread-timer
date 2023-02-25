COMPILERFLAGS = -std=c99 -g -Wall -Wextra -pedantic -O1

.PHONY: all clean

all: obj test

test: obj/test.o obj/timer.o
	$(CC) $(COMPILERFLAGS) $^ -o $@ $(LINKLIBS)

clean :
	$(RM) obj/*.o test

obj/%.o: src/%.c
	$(CC) $(COMPILERFLAGS) -c -o $@ $<
	
obj:
	mkdir -p obj
