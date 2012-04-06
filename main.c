#include "mread.h"

#include <stdio.h>
#include <unistd.h>

static void
test(struct mread_pool *m) {
	int id = mread_poll(m,0);
	if (id >= 0) {
		for (;;) {
			char * buffer = mread_pull(m, 4);
			if (buffer == NULL) {
				if (mread_closed(m)) {
					printf("%d: CLOSED\n",id);
				} 
				break;
			} else {
				printf("%d : %d %d %d %d\n",id, buffer[0],buffer[1],buffer[2],buffer[3]);
				mread_yield(m);
			}
		}
	}
}

int
main() {
	struct mread_pool * m = mread_create(2525 , 10, 0);
	if (m == NULL) {
		perror("error:");
		return 1;
	}
	for (;;) {
		test(m);
		sleep(1);
	}
	mread_close(m);
	return 0;
}
