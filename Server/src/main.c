#include <stdlib.h>
#include <stdbool.h>
#include <mongoose.h>

#include "check.h"
#include "request.h"

#define SERVER_URL "http://0.0.0.0:8000"
#define MG_LL MG_LL_ERROR

int main(int argc, char *argv[])
{
    // Check command line arguments
    check(argc == 2, "Please provide a directory as a command line argument.");
    const char *dir = argv[1];

    // Print max recv buffer size
    size_t max_recv_size = (size_t)MG_MAX_RECV_SIZE;
    printf("MG_MAX_RECV_SIZE is set to %lu.\n", max_recv_size);

    // Start Mongoose server
    struct mg_mgr mgr;
    mg_log_set(MG_LL);
    mg_mgr_init(&mgr);
    mg_http_listen(&mgr, SERVER_URL, on_http_event, (void *)dir);
    while(true) mg_mgr_poll(&mgr, 1000);
    mg_mgr_free(&mgr);
    return EXIT_SUCCESS;

error:
    return EXIT_FAILURE;
}
