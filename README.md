# A lightweight epoll wrap for read multi-sockets

## api

```C
// create a pool , listen on port , set max connection and , buffer size (0 for default 1M bytes)
struct mread_pool * mread_create(int port , int max , int buffer);

// release the pool
void mread_close(struct mread_pool *m);

// poll the poll, timeout (in milliseconds) can be -1 for indefinitely.
// return id (which socket can read) , -1 for block
int mread_poll(struct mread_pool *m , int timeout);

// pull data from the id return by poll. 
// return size of buffer or NULL
void * mread_pull(struct mread_pool *m , int size);

// When you don't need use the data return by pull, you must call yield
// Otherwise, you will get them again after next poll
void mread_yield(struct mread_pool *m);

// When the id is closed, it returns 1
int mread_closed(struct mread_pool *m);

// Close id
void mread_close_client(struct mread_pool *m, int id);

// Get the socket fd bind with id , you can use it for sending.
int mread_socket(struct mread_pool *m , int id);

```
