#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <pthread.h>
#include <sys/socket.h>

#include <stcpsvr.h>

void pt_svr_proc(PEERSOCK * peer) __attribute__((cdecl));

int main(int argc, const char ** argv) {
    pt_tcp_server(NULL, "50001", &pt_svr_proc);
    return(0);
}

void pt_svr_proc(PEERSOCK * peer) {
    copy_data(peer->ps_sock, 1);
    
    // You should explictly close sock after everything done
    close(peer->ps_sock);
    
    // Free resource
    freepeersock(peer);
    
    // Explicitly exit thread
    pthread_exit(NULL);
}

