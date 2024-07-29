exec = csach.out
sources = $(wildcard src/*.c)
objects = $(sources:.c=.o)
flags = -g

$(exec): $(objects)
	gcc $(objects) $(flags) -o $(exec)

%.o: %.c include/%.h
	gcc -c $(flags) $< -o $@

install:
	make
	cp ./csach.out /usr/local/bin/csach

uninstall:
	rm /usr/local/bin/csach

clean:
	-rm *.out
	-rm *.objects
	-rm src/*.o