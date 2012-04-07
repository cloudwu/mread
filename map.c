#include "map.h"

#include <stdlib.h>
#include <assert.h>

struct node {
	int fd;
	int id;
	int next;
};

struct map {
	int size;
	struct node * hash;
};

struct map * 
map_new(int max) {
	int sz = 1;
	max = max * 3 / 2;
	while (sz <= max) {
		sz *= 2;
	}
	struct map * m = malloc(sizeof(*m));
	m->size = sz;
	m->hash = malloc(sizeof(struct node) * sz);
	int i;
	for (i=0;i<sz;i++) {
		m->hash[i].fd = -1;
		m->hash[i].id = 0;
		m->hash[i].next = -1;
	}
	return m;
}

void 
map_delete(struct map * m) {
	free(m->hash);
	free(m);
}

int 
map_search(struct map * m, int fd) {
	int hash = fd & (m->size-1);
	struct node * n = &m->hash[hash];
	for(;;) {
		if (n->fd == fd)
			return n->id;
		if (n->next < 0)
			return -1;
		n = &m->hash[n->next];
	}
}

void 
map_insert(struct map * m, int fd, int id) {
	int hash = fd & (m->size-1);
	struct node * n = &m->hash[hash];
	for (;;) {
		if (n->fd < 0) {
			n->fd = fd;
			n->id = id;
			return;
		}
		if (n->next < 0 ) {
			break;
		}
		n = &m->hash[n->next];
	}
	int last = (n - m->hash) * 2;
	int i;
	for (i=0;i<m->size;i++) {
		int idx = (i + last + 1) & (m->size - 1);
		struct node * temp = &m->hash[idx];
		if (temp->fd < 0) {
			temp->fd = fd;
			temp->id = id;
			n->next = idx;
			return;
		}
	}
	assert(0);
}

void
map_erase(struct map *m , int fd) {
	int hash = fd & (m->size-1);
	struct node * n = &m->hash[hash];
	for(;;) {
		if (n->fd == fd) {
			n->fd = -1;
			return;
		}
		if (n->next < 0)
			return;
		n = &m->hash[n->next];
	}
}
