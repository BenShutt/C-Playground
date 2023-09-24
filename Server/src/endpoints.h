#ifndef __endpoints_h__
#define __endpoints_h__

#include <mongoose.h>
#include <stdbool.h>

#define ENDPOINT_STATUS "/api/status"
#define ENDPOINT_EXISTS "/api/exists"
#define ENDPOINT_UPLOAD "/api/upload"

int handle_status();
int handle_exists(struct mg_http_message *hm, const char *dir);
int handle_upload(struct mg_http_message *hm, struct mg_str data, const char *dir, bool is_end);

#endif