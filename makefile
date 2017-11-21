all: leaky.c
	gcc leaky.c
run: all
	./a.out
