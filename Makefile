all:
	gcc -g -o mread -Wall mread.c ringbuffer.c map.c main.c
