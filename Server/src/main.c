#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "server.h"

#define PORT 666

int main()
{
    return run_server(PORT);
}