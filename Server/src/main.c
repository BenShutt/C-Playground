#include <stdlib.h>
#include <stdbool.h>
#include <mongoose.h>

#include "check.h"
#include "request.h"

#define SERVER_URL "http://0.0.0.0:8000"
#define LOGGING 0

int main(int argc, char *argv[])
{
    // Prepare command line arguments
    check(argc == 2, "Please provide a directory as a command line argument.");
    const char *dir = argv[1];

    // Set logging in enabled
    if(LOGGING) mg_log_set(MG_LL_DEBUG);

    // Start Mongoose server
    struct mg_mgr mgr;
    mg_mgr_init(&mgr);
    mg_http_listen(&mgr, SERVER_URL, on_http_event, (void *)dir);
    while(true) mg_mgr_poll(&mgr, 1000);
    mg_mgr_free(&mgr);
    return EXIT_SUCCESS;

error:
    return EXIT_FAILURE;
}
