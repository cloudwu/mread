#include "ringbuffer.h"
#include <stdio.h>

static void
init(struct ringbuffer_block * blk, int n) {
	char * ptr = (char *)(blk+1);
	int i;
	for (i=0;i<n;i++) {
		ptr[i] = i + 1;
	}
}

static void
dump(struct ringbuffer * rb, struct ringbuffer_block *blk, int size) {
	void * buffer;
	int sz = ringbuffer_data(rb, blk, size, 0, &buffer);
	char * data = buffer;
	if (data) {
		int i;
		for (i=0;i<sz;i++) {
			printf("%d ",data[i]);
		}
		printf("\n");
	} else {
		printf("size = %d\n",sz);
	}
}

static void
test(struct ringbuffer *rb) {
	struct ringbuffer_block * blk;
	blk = ringbuffer_alloc(rb,80);
	blk->id = 0;
	ringbuffer_free(rb,blk);
	blk = ringbuffer_alloc(rb,50);
	blk->id = 1;
	struct ringbuffer_block * next = ringbuffer_alloc(rb, 40);
	next->id = 1;
	ringbuffer_link(rb, blk, next);
	ringbuffer_dump(rb);
	blk = ringbuffer_alloc(rb,4);
	printf("%p\n",blk);
	int id = ringbuffer_collect(rb);
	printf("collect %d\n",id);

	blk = ringbuffer_alloc(rb,4);
	blk->id = 2;
	init(blk,4);

	next = ringbuffer_alloc(rb,5);
	init(next,5);
	ringbuffer_link(rb, blk, next);

	next = ringbuffer_alloc(rb,6);
	init(next,6);
	ringbuffer_link(rb, blk , next);


	dump(rb, blk , 3);
	dump(rb, blk , 6);
	dump(rb, blk , 16);

	blk = ringbuffer_yield(rb, blk, 5);

	next = ringbuffer_alloc(rb, 7);
	ringbuffer_copy(rb, blk, 1, next);
	dump(rb, next, 7);

	blk = ringbuffer_yield(rb, blk , 5);

	ringbuffer_dump(rb);
}

int
main() {
	struct ringbuffer * rb = ringbuffer_new(128);
	test(rb);
	ringbuffer_delete(rb);
	return 0;
}
