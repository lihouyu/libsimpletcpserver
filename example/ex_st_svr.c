#include <stdio.h>
#include <unistd.h>

#include <sys/socket.h>

#include <stcpsvr.h>

void st_svr_proc(PEERSOCK * peer) __attribute__((cdecl));

int main(int argc, const char ** argv) {
    st_tcp_server(NULL, "50001", &st_svr_proc);
    return(0);
}

void st_svr_proc(PEERSOCK * peer) {
    copy_data(peer->ps_sock, 1);
    
    // You should explictly close sock after everything done
    close(peer->ps_sock);
}

