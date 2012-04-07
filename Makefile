all:
	gcc -g -o mread -Wall mread.c ringbuffer.c map.c main.c

test:
	gcc -g -o testmap -Wall map.c testmap.c
	gcc -g -o testrb -Wall ringbuffer.c testringbuffer.c
