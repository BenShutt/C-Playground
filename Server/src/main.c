#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "socket.h"

#define PORT 666

char *handle(char *message)
{
    static int num = 0;
    num += 1;

    printf("Received message %d) '%s'\n", num, message);
    return "Success";
}

int main()
{
    return socket_run(PORT, 1024, handle);
}