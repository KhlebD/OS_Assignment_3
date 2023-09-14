#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void test_malloc(int isMyMalloc)
{

    printf("-----------------TESTING %s-----------------\n", isMyMalloc ? "USTACK_MALLOC" : "MALLOC");

    // Allocate memory blocks of different sizes
    int* int_ptr = isMyMalloc ? (int *)ustack_malloc(sizeof(int)) : (int *)malloc(sizeof(int));
    char* char_ptr = isMyMalloc ? (char*)ustack_malloc(10 * sizeof(char)) : (char *)malloc(10 * sizeof(char));

    // Store data in the allocated memory blocks
    *int_ptr = 42;
    char_ptr[0] = 'H';
    char_ptr[1] = 'e';
    char_ptr[2] = 'l';
    char_ptr[3] = 'l';
    char_ptr[4] = 'o';
    char_ptr[5] = '\0';

    // Print the stored data
    printf("int: %d (supposed to be 42)\n", *int_ptr);
    printf("char: %s (supposed to be 'Hello')\n", char_ptr);

    // Free the allocated memory
    if (isMyMalloc)
        free(int_ptr);
    else
        ustack_free();
    if (isMyMalloc)
        free(char_ptr);
    else
        ustack_free();

    printf("-------------------------------------------------\n");
    
}

int
main(int argc, char *argv[])
{
    test_malloc(1);
    return 0;
}