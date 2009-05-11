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

#include <stcpsvrutil.h>

/**
 * The single threaded TCP server invoker
 * 
 * @param const char * hostname                 The IP address the server being binded to.
 *                                              Usually use NULL for listening on any interface.
 * @param const char * servicename              The service name or the port number.
 * @param void (* p_ss_callback)(PEERSOCK *)    The callback function for proccessing request 
 *                                                  when a new client request is accept()ed.
 */
int st_tcp_server(const char *, const char *, void (* p_ss_callback)(PEERSOCK *));

/**
 * The multi thread TCP server invoker based on pThread
 * 
 * @param const char * hostname                 The IP address the server being binded to.
 *                                              Usually use NULL for listening on any interface.
 * @param const char * servicename              The service name or the port number.
 * @param void (* p_ss_callback)(PEERSOCK *)    The callback function for proccessing request 
 *                                                  when a new client request is accept()ed.
 */
int pt_tcp_server(const char *, const char *, void (* p_ss_callback)(PEERSOCK *));
