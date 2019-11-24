CFLAGS = -g -std=c99 -Wall -Werror -I ./include
CC = gcc

.PHONY: clean doc
.DEFAULT_GOAL := run

doc:
	doxygen conf/doxygen.conf
	firefox html/index.html

%.o: ./src/%.c
	$(CC) $(CFLAGS) -o $@ -c $^

read-file: read-file.o
	$(CC) $(CFLAGS) -o $@ $^

write-fact: write-fact.o
	$(CC) $(CFLAGS) -o $@ $^

conway-naive: conway-naive.o
	$(CC) $(CFLAGS) -o $@ $^

launch-conway-naive: conway-naive
	./conway-naive


generate-animation:
	convert -delay 10 -loop 0 out/*.ppm out/animation.gif

add-files-svn:
	svn add --force src/*.c include/*.h data/*.txt --auto-props --parents --depth infinity -q

clean:
	rm -f *.o read-file conway-naive write-fact



syntax-check: src/cell.c src/cell.c
	$(CC) $(CFLAGS) -c $^

syntax-check-app: src/app-cell.c src/app-cell.c
	$(CC) $(CFLAGS) -c $^

app-cell: src/cell.c src/app-cell.c
	$(CC) $(CFLAGS) -o $@ $^

run: app-cell
	./app-cell



syntax-check-load: src/load.c src/load.c
	$(CC) $(CFLAGS) -c $^

syntax-check-load-app: src/app-load.c src/app-load.c
	$(CC) $(CFLAGS) -c $^

load: src/load.c
	$(CC) $(CFLAGS) -o $@ $^

app-load: src/cell.c src/load.c src/app-load.c 
	$(CC) $(CFLAGS) -o $@ $^

run-load: app-load
	./app-load





syntax-check-image: src/generate-image.c src/generate-image.c
	$(CC) $(CFLAGS) -c $^
syntax-check-image-app: src/app-generate-image.c src/app-generate-image.c
	$(CC) $(CFLAGS) -c $^

image: src/generate-image.c
	$(CC) $(CFLAGS) -o $@ $^

app-image: src/cell.c src/load.c src/generate-image.c src/app-generate-image.c
	$(CC) $(CFLAGS) -o $@ $^

run-image: app-image
	./app-image



syntax-check-app-conway: src/app-conway.c src/app-conway.c
	$(CC) $(CFLAGS) -c $^

compile-all: src/cell.c src/load.c src/generate-image.c src/app-conway.c
	$(CC) $(CFLAGS) -o $@ $^

run-conway: compile-all
	./compile-all 
	make generate-animation





