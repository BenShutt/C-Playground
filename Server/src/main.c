#include <stdlib.h>
#include <stdbool.h>
#include <mongoose.h>

#define NL "\r\n"

static void fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data)
{
    if(ev != MG_EV_HTTP_MSG) return;

    struct mg_http_message *hm = (struct mg_http_message *)ev_data;
    if(!mg_http_match_uri(hm, "/api/hello")) // On /api/hello requests,
    {
        // Serve files from root_d for all other URIs
        struct mg_http_serve_opts opts = {.root_dir = "."}; 
        mg_http_serve_dir(c, hm, &opts);
        return;
    }

    // Send dynamic JSON response
    mg_http_reply(
        c, 
        200, 
        "Content-Type: application/json" NL, 
        "{%m:%d}\n",
        MG_ESC("status"), 
        0
    );
}

int main()
{
    struct mg_mgr mgr;
    mg_mgr_init(&mgr);
    mg_http_listen(&mgr, "http://0.0.0.0:8000", fn, NULL);
    while(true)
    {
        mg_mgr_poll(&mgr, 1000); // Infinite event loop
    }

    return EXIT_SUCCESS;
}
