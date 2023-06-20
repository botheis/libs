cc=gcc
exec=itman
opt=-O3 -Wall -g -o
libs=
cflags=
src=$(wildcard src/*.c) $(wildcard src/*/*.c) $(wildcard src/*/*/*.c)
obj=$(src:.c=.o)

$(exec): $(obj)
	$(cc) $(opt) $@ $^ $(libs) $(cflags)

valgrind: $(exec)
	valgrind ./$(exec)

%.o:%.c
	$(cc) $(opt) $@ -c $^ $(libs) $(cflags)

clean:
	rm -rf $(obj)

reset: clean
	rm -rf $(exec)