#include "user/ustack.h"
#include <stdio.h>

int main()
{ // Test case 4: Allocate buffers until a new page is allocated
    printf("\nTest Case 4: Allocate buffers until a new page is allocated\n");
    const int buffer_size = 510; // Maximum buffer size of 500 bytes
    int num_buffers = 0;
    for (int i = 0; i < 10; i++)
    {
        void *buffer = ustack_malloc(buffer_size);
        if (buffer == (void *)-1)
        {
            printf("Allocation failed at buffer %d\n", num_buffers + 1);
            break;
        }
        printf("Buffer %d allocated: %p\n", num_buffers + 1, buffer);
        num_buffers++;
    }
    printf("Total buffers allocated: %d\n", num_buffers);
    int freed_size = 0;
    for (int i = 0; i < num_buffers; i++)
    {
        freed_size += ustack_free();
        printf("%d\n",freed_size);
    }
    printf("Total freed size: %d\n", freed_size);

    //return 0; /////remove to try next tests

    // Test ustack_malloc
    void *bbuffer1 = ustack_malloc(100);
    printf("Buffer1: %p\n", bbuffer1);

    void *bbuffer2 = ustack_malloc(200);
    printf("Buffer2: %p\n", bbuffer2);

    void *bbuffer3 = ustack_malloc(300);
    printf("Buffer3: %p\n", bbuffer3);

    void *bbuffer4 = ustack_malloc(400);
    printf("Buffer4: %p\n", bbuffer4);

    void *bbuffer5 = ustack_malloc(600); // Exceeds maximum allowed size
    printf("Buffer5: %p\n", bbuffer5);

    // Test ustack_free
    int ffreed_size;

    ffreed_size = ustack_free(); // Free buffer4
    printf("Freed size: %d\n", ffreed_size);
    ffreed_size = ustack_free(); // Free buffer3
    printf("Freed size: %d\n", ffreed_size);

    ffreed_size = ustack_free(); // Free buffer2
    printf("Freed size: %d\n", ffreed_size);

    ffreed_size = ustack_free(); // Free buffer1
    printf("Freed size: %d\n", ffreed_size);

    ffreed_size = ustack_free(); // Attempt to free when stack is empty
    printf("Freed size: %d\n", ffreed_size);

    // #include <stdio.h>
    // #include "user/ustack.h"

    // Test case 1: Allocate and free a single buffer
    printf("Test Case 1: Allocate and free a single buffer\n");
    void *buffer1 = ustack_malloc(100);
    if (buffer1 == (void *)-1)
    {
        printf("Allocation failed\n");
        return 1;
    }
    printf("Buffer 1 allocated: %p\n", buffer1);
    int freed_size1 = ustack_free();
    printf("Freed buffer 1, size: %d\n", freed_size1);

    // Test case 2: Allocate multiple buffers and free in reverse order
    printf("\nTest Case 2: Allocate multiple buffers and free in reverse order\n");
    void *buffer2 = ustack_malloc(50);
    void *buffer3 = ustack_malloc(80);
    void *buffer4 = ustack_malloc(120);
    if (buffer2 == (void *)-1 || buffer3 == (void *)-1 || buffer4 == (void *)-1)
    {
        printf("Allocation failed\n");
        return 1;
    }
    printf("Buffer 2 allocated: %p\n", buffer2);
    printf("Buffer 3 allocated: %p\n", buffer3);
    printf("Buffer 4 allocated: %p\n", buffer4);
    int freed_size4 = ustack_free();
    printf("Freed buffer 4, size: %d\n", freed_size4);
    int freed_size3 = ustack_free();
    printf("Freed buffer 3, size: %d\n", freed_size3);
    int freed_size2 = ustack_free();
    printf("Freed buffer 2, size: %d\n", freed_size2);

    // Test case 3: Allocate buffers exceeding the maximum allowed size
    printf("\nTest Case 3: Allocate buffers exceeding the maximum allowed size\n");
    void *buffer5 = ustack_malloc(600);
    void *buffer6 = ustack_malloc(1000);
    if (buffer5 == (void *)-1)
    {
        printf("Buffer 5 allocation failed as expected\n");
    }
    else
    {
        printf("Buffer 5 allocated: %p\n", buffer5);
    }
    if (buffer6 == (void *)-1)
    {
        printf("Buffer 6 allocation failed as expected\n");
    }
    else
    {
        printf("Buffer 6 allocated: %p\n", buffer6);
    }

    return 0;
}