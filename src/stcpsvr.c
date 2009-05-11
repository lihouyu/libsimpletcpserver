/**
 *
 * libsimpletcpserver
 *
 * A simple tcp socket library for easing tcp socket programing
 * 
 * Copyright (c) 2009 HouYu Li <karadog@gmail.com>
 * 
 * This file is a part of libsimpletcpserver
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "stcpsvr.h"

/**
 * The single threaded TCP server invoker
 * 
 * @param const char * hostname                 The IP address the server being binded to.
 *                                              Usually use NULL for listening on any interface.
 * @param const char * servicename              The service name or the port number.
 * @param void (* p_ss_callback)(PEERSOCK *)    The callback function for proccessing request 
 *                                                  when a new client request is accept()ed.
 */
int st_tcp_server(const char * hostname, const char * servicename, 
    void (* p_ss_callback)(PEERSOCK *)) {
    /**
     * The main socket descriptor
     */
    int sock_st_tcp_svr;
    
    /**
     * The client socket descriptor returned by accept()
     */
    int sock_peer;
    
    /**
     * The structure for holding client socket information 
     *   for passing to the callback function
     */
    PEERSOCK peer;
    
    /**
     * The address info used in socket creation
     */
    struct addrinfo hints, * addr;
    
    /**
     * The client socket address
     */
    struct sockaddr addr_peer;
    
    /**
     * Size of the sockaddr structure
     */
    unsigned int sz_addr_peer = sizeof(addr_peer);
    int ret, i;
    
    memset(&hints, 0, sizeof(hints));   // Clearing out the memory used by addrinfo
    
    hints.ai_socktype = SOCK_STREAM;    // The socket type will be a stream socket
    hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG;    // The socket is act as a server socket
    
    // Get address information
    if ((ret = getaddrinfo(hostname, servicename, &hints, &addr)) != 0) {
        die("Address info cannot be allocated");
    }
    
    // Create the main socket
    if ((sock_st_tcp_svr = socket(addr->ai_family, addr->ai_socktype, 
        addr->ai_protocol)) < 0) {
        freeaddrinfo(addr);
        die("Cannot create socket");
    }
    
    // Let kernel reuse the socket address 
    i = 1;
    setsockopt(sock_st_tcp_svr, SOL_SOCKET, SO_REUSEADDR, &i, sizeof(i));
    
    // Bind socket address
    if (bind(sock_st_tcp_svr, addr->ai_addr, addr->ai_addrlen)) {
        freeaddrinfo(addr);
        die("Cannot bind address");
    }
    
    freeaddrinfo(addr); // Now free the addrinfo struct
    
    // Start listening
    if (listen(sock_st_tcp_svr, 5)) {
        die("Unable to listen for connections");
    }
    
    // The always true loop
    while (1) {
        if ((sock_peer = accept(sock_st_tcp_svr, &addr_peer, &sz_addr_peer)) >= 0) {
            // Prepare client socket descriptor and address 
            peer.ps_sock = sock_peer;
            peer.ps_addr = &addr_peer;
            
            p_ss_callback(&peer);   // Run the callback with client socket information
        }
    }
    
    close(sock_st_tcp_svr); // Close main socket
    
    return 0;
}

/**
 * The multi thread TCP server invoker based on pThread
 * 
 * @param const char * hostname                 The IP address the server being binded to.
 *                                              Usually use NULL for listening on any interface.
 * @param const char * servicename              The service name or the port number.
 * @param void (* p_ss_callback)(PEERSOCK *)    The callback function for proccessing request 
 *                                                  when a new client request is accept()ed.
 */
int pt_tcp_server(const char * hostname, const char * servicename, 
    void (* p_ss_callback)(PEERSOCK *)) {
    /**
     * The main socket descriptor
     */
    int sock_pt_tcp_svr;
    
    /**
     * The client socket descriptor returned by accept()
     */
    int sock_peer;
    
    /**
     * The structure for holding client socket information 
     *   for passing to the callback function
     */
    PEERSOCK * peer;
    
    /**
     * The address info used in socket creation
     */
    struct addrinfo hints, * addr;
    
    /**
     * The client socket address
     */
    struct sockaddr * addr_peer;
    
    /**
     * Size of the sockaddr structure
     */
    unsigned int sz_addr_peer = sizeof(struct sockaddr);
    
    /**
     * pThread structure
     */
    pthread_t * pthread;
    int ret, i;
    
    memset(&hints, 0, sizeof(hints));   // Clearing out the memory used by addrinfo
    
    hints.ai_socktype = SOCK_STREAM;    // The socket type will be a stream socket
    hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG;    // The socket is act as a server socket
    
    // Get address information
    if ((ret = getaddrinfo(hostname, servicename, &hints, &addr)) != 0) {
        die("Address info cannot be allocated");
    }
    
    // Create the main socket
    if ((sock_pt_tcp_svr = socket(addr->ai_family, addr->ai_socktype, 
        addr->ai_protocol)) < 0) {
        freeaddrinfo(addr);
        die("Cannot create socket");
    }
    
    // Let kernel reuse the socket address 
    i = 1;
    setsockopt(sock_pt_tcp_svr, SOL_SOCKET, SO_REUSEADDR, &i, sizeof(i));
    
    // Bind socket address
    if (bind(sock_pt_tcp_svr, addr->ai_addr, addr->ai_addrlen)) {
        freeaddrinfo(addr);
        die("Cannot bind address");
    }
    
    freeaddrinfo(addr); // Now free the addrinfo struct
    
    // Start listening
    if (listen(sock_pt_tcp_svr, 5)) {
        die("Unable to listen for connections");
    }
    
    // The always true loop
    while (1) {
        addr_peer = (struct sockaddr *)malloc(sz_addr_peer);
        if ((sock_peer = accept(sock_pt_tcp_svr, addr_peer, &sz_addr_peer)) >= 0) {
            peer = (PEERSOCK *)malloc(sizeof(PEERSOCK));
            // Prepare client socket descriptor and address 
            peer->ps_sock = sock_peer;
            peer->ps_addr = addr_peer;
            
            pthread = (pthread_t *)malloc(sizeof(pthread_t));
            
            pthread_create(pthread, NULL, (void *)p_ss_callback, (void *)peer);
            //p_ss_callback(&peer);   // Run the callback with client socket information
        }
    }
    
    close(sock_pt_tcp_svr); // Close main socket
    
    return 0;
}
