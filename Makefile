all:
	gcc -g -o mread -Wall mread.c ringbuffer.c main.c

test:
	gcc -g -o testrb -Wall ringbuffer.c testringbuffer.c
