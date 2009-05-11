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
#include <unistd.h>
#include <string.h>

#include "stcpsvrutil.h"

void freepeersock(PEERSOCK * peer) {
    free(peer->ps_addr);
    free(peer);
}

void die(const char * msg) {
    perror(msg);
    exit(1);
}

void copy_data(int from, int to) {
    char buff[BUFFLEN];
    int len;
    
    while ((len = read(from, buff, sizeof(buff))) > 0) {
        if (write(to, buff, len) != len) {
            die("Write error");
            return;
        }
    }
    
    if (len < 0) {
        die("Read error");
    }
}
