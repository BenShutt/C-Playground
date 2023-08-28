#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "socket.h"

#define PORT 666

int main()
{
    return socket_run(PORT);
}