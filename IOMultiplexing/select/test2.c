#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <fcntl.h>
 
#define CLIENT_COUNT 100
 
int clients[CLIENT_COUNT] = {0};
int remotes[CLIENT_COUNT] = {0};
 
static void remove_client(int i)
{
    shutdown(clients[i], SHUT_RD);
    close(clients[i]);
    shutdown(remotes[i], SHUT_RD);
    close(remotes[i]);
     
    clients[i] = remotes[i] = 0;
}
 
static int get_client()
{
    int i;
    for(i=0; i<CLIENT_COUNT; i++)
    {
        if(!clients[i])
            return i;
    }
     
    return 0;
}
 
 
int main(int argc, char* argv[])
{
    if(argc < 5)
    {
        printf("usage: %s local_ip local_port remote_ip remote_port.\n", basename(argv[0]));
        return 1;
    }
 
    char* local_ip = argv[1];
    int local_port = atoi(argv[2]);
    char* remote_ip = argv[3];
    int remote_port = atoi(argv[4]);
 
    struct sockaddr_in address;
    bzero(&address, sizeof(address));   
    address.sin_family = AF_INET;
    inet_pton(AF_INET, local_ip, &address.sin_addr);
    address.sin_port = htons(local_port);
 
    struct sockaddr_in remote_address;
    bzero(&remote_address, sizeof(remote_address));
    remote_address.sin_family = AF_INET;
    inet_pton(AF_INET, remote_ip, &remote_address.sin_addr);
    remote_address.sin_port = htons(remote_port);
     
    int listenfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(listenfd >= 0);
 
    int ret = bind(listenfd, (struct sockaddr*)&address, sizeof(address));
    assert(ret != -1);
 
    ret = listen(listenfd, 5);
    assert(ret != -1);
 
    printf("listen\n");
 
    fd_set fdreads,fdwrites;
    const int buf_size = 1024 * 32;
    char buf[buf_size];
     
    FD_ZERO(&fdreads);
 
    for(;;)
    {
        int i,j,k;
        FD_SET(listenfd, &fdreads);
 
        for(i=0; i<CLIENT_COUNT; i++)
        {
            if(clients[i])
            {
                FD_SET(clients[i], &fdreads);
                FD_SET(remotes[i], &fdreads);
            }
        }
         
        ret = select(CLIENT_COUNT * 2 + 1, &fdreads, NULL, NULL, NULL);
 
        printf("select ret=%d\n", ret);
 
        if(ret < 0)
        {
            printf("selecttion failure\n");
            break;
        }
 
        if(FD_ISSET(listenfd, &fdreads))
        {
            int j = get_client();
            printf("accept %d\n", j);
             
            struct sockaddr client_address;
            socklen_t client_addrlength = sizeof(client_address);   
             
            clients[j] = accept(listenfd, &client_address, &client_addrlength);
             
            remotes[j] = socket(PF_INET, SOCK_STREAM, 0);
 
            assert(remotes[j] >= 0);
         
            address.sin_port = 0;
            if(bind(remotes[j], (struct sockaddr*)&address, sizeof(address)) < 0)
            {
                printf("errno:%d\n", errno);
                break;
            }
 
            if(connect(remotes[j], (struct sockaddr*)&remote_address, sizeof(remote_address)) < 0)
            {
                printf("can not connect to remote host.\n");
                break;
            }
        }
         
        for(i=0; i<CLIENT_COUNT; i++)
        {
            if(!clients[i])
            {
                continue;
            }
     
            if(FD_ISSET(clients[i], &fdreads))
            {
                int ret = recv(clients[i], buf, buf_size -1, 0);
                printf("client_read_ret=%d\n", ret);
                if(ret > 0)
                {
                    send(remotes[i], buf, ret, 0);
                }
                if(ret <=0 )
                {   
                    printf("client disconnected or network error.\n");
                    remove_client(i);
                }
            }
            if(FD_ISSET(remotes[i], &fdreads))
            {
                int ret = recv(remotes[i], buf, buf_size, 0);
                printf("remote_read_ret=%d\n", ret);
                if(ret > 0)
                {
                    send(clients[i], buf, ret, 0);
                }
                else
                {
                    printf("remote host disconnected or network error occured.\n");
                    remove_client(i);
                }
            }
        }
    }
 
    close(listenfd); 
 
    return 0;
}
