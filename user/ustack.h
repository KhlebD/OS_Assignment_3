#include "kernel/types.h"

#define MAX_SIZE  512   

struct header
{
    struct header *next;
    uint size;
};

typedef struct header Header;

void *ustack_malloc(uint len);
int ustack_free(void);
