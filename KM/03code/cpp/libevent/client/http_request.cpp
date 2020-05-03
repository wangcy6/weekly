#include "event2/http.h"
#include "event2/http_struct.h"
#include "event2/event.h"
#include "event2/buffer.h"
#include "event2/dns.h"
#include "event2/thread.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <sys/queue.h>
#include <event.h>

void RemoteReadCallback(struct evhttp_request* remote_rsp, void* arg)
{
    event_base_loopexit((struct event_base*)arg, NULL);
} 

int ReadHeaderDoneCallback(struct evhttp_request* remote_rsp, void* arg)
{
    fprintf(stderr, "< HTTP/1.1 %d %s\n", evhttp_request_get_response_code(remote_rsp), evhttp_request_get_response_code_line(remote_rsp));
    struct evkeyvalq* headers = evhttp_request_get_input_headers(remote_rsp);
    struct evkeyval* header;
    TAILQ_FOREACH(header, headers, next)
    {
        fprintf(stderr, "< %s: %s\n", header->key, header->value);
    }
    fprintf(stderr, "< \n");
    return 0;
}
//http://www.wangafu.net/~nickm/libevent-2.1/doxygen/html/http_8h.html
void ReadChunkCallback(struct evhttp_request* remote_rsp, void* arg)
{
    char buf[4096];
    struct evbuffer* evbuf = evhttp_request_get_input_buffer(remote_rsp);
    int n = 0;
    while ((n = evbuffer_remove(evbuf, buf, 4096)) > 0)
    {
        fwrite(buf, n, 1, stdout);
    }
}

void RemoteRequestErrorCallback(enum evhttp_request_error error, void* arg)
{
    fprintf(stderr, "request failed\n");
    event_base_loopexit((struct event_base*)arg, NULL);
}

void RemoteConnectionCloseCallback(struct evhttp_connection* connection, void* arg)
{
    fprintf(stderr, "remote connection closed\n");
    event_base_loopexit((struct event_base*)arg, NULL);
}
// ./http_client http://www.qq.com 
int main(int argc, char** argv)
{
    if (argc != 2)
    {
        printf("usage:%s url", argv[1]);
        return 1;
    }
    char* url = argv[1];
    struct evhttp_uri* uri = evhttp_uri_parse(url);
    if (!uri)
    {
        fprintf(stderr, "parse url failed!\n");
        return 1;
    }

    struct event_base* base = event_base_new();
    if (!base)
    {
        fprintf(stderr, "create event base failed!\n");
        return 1;
    }

    struct evdns_base* dnsbase = evdns_base_new(base, 1);
    if (!dnsbase)
    {
        fprintf(stderr, "create dns base failed!\n");
    }
    assert(dnsbase);

    struct evhttp_request* request = evhttp_request_new(RemoteReadCallback, base);
    evhttp_request_set_header_cb(request, ReadHeaderDoneCallback);// 设置回调函数，在包头读取完成后回调
    evhttp_request_set_chunked_cb(request, ReadChunkCallback);// 设置回调函数，在body有数据返回后回调
    evhttp_request_set_error_cb(request, RemoteRequestErrorCallback);

    const char* host = evhttp_uri_get_host(uri);
    if (!host)
    {
        fprintf(stderr, "parse host failed!\n");
        return 1;
    }

    int port = evhttp_uri_get_port(uri);
    if (port < 0) port = 80;

    const char* request_url = url;
    const char* path = evhttp_uri_get_path(uri);
    if (path == NULL || strlen(path) == 0)
    {
        request_url = "/";
    }

    printf("url:%s host:%s port:%d path:%s request_url:%s\n", url, host, port, path, request_url);

    struct evhttp_connection* connection =  evhttp_connection_base_new(base, dnsbase, host, port);
    if (!connection)
    {
        fprintf(stderr, "create evhttp connection failed!\n");
        return 1;
    }

    evhttp_connection_set_closecb(connection, RemoteConnectionCloseCallback, base);

    evhttp_add_header(evhttp_request_get_output_headers(request), "Host", host);
    evhttp_make_request(connection, request, EVHTTP_REQ_GET, request_url);

    event_base_dispatch(base);

    return 0;
}