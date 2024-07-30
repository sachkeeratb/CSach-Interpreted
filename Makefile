exec = csach.out
sources = $(wildcard src/*.c)
objects = $(sources:.c=.o)
flags = -g
CC = $(shell command -v gcc >/dev/null 2>&1 && echo "gcc" || echo "clang")

$(exec): $(objects)
	$(CC) $(objects) $(flags) -o $(exec)

%.o: %.c include/%.h
	$(CC) -c $(flags) $< -o $@

install:
	make
	cp ./csach.out /usr/local/bin/csach

uninstall:
	rm /usr/local/bin/csach

clean:
	-rm *.out
	-rm *.objects
	-rm src/*.o