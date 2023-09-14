#include "kernel/types.h"
#include "user/ustack.h"
#include "kernel/riscv.h"
#include "user.h"

static Header base;
static Header *top;

void *ustack_malloc(uint len)
{
    if (len > MAX_SIZE)
    {
        return (void *)-1;
    }

    uint nunits = (len + sizeof(Header) - 1) / sizeof(Header) + 1;

    if (top == 0)
    {
        base.size = 0;
        top = &base;
        top->next = 0;
    }

    // need to allocate a new page
    if (top->size < nunits)
    {
        Header *block;
        if ((block = (Header *)sbrk(PGSIZE)) == (Header *)-1)
        {
            return (void *)-1;
        }

        block->next = top;
        block->size = PGSIZE / sizeof(Header);
        top = block;
    }

    uint size = top->size;
    top->size = nunits;
    top = top + top->size;
    top->size = size - nunits;

    return (void *)(top + 1);
}

int ustack_free(void)
{
    if (top->size == 0)
        return -1;

    //iterate to prevent mermory holes
    uint size = top->size;
    Header *next = top + top->size - PGSIZE / sizeof(Header);
    Header *curr = next;
    uint next_size = next->size;

    while (curr->size != size)
    {
        curr += next->size;
        next_size = next->size;
        next = curr;
    }
    
    curr += next->size;
    next = next - next_size;

    uint nunits = next->size;
    next->size += size;
    top = next;

    if (top->size == PGSIZE / sizeof(Header))
    {
        top = top->next;
        sbrk(-PGSIZE);
    }

    return nunits * sizeof(Header);
}