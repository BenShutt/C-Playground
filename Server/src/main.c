#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "socket.h"
#include "request.h"

#define PORT 666

char *handle(char *message)
{
    static int num = 0;
    num += 1;
    printf("Handling message %d.\n", num);

    handle_request(message);
    return "Success";
}

int main()
{
    return socket_run(PORT, 1024, handle);
}