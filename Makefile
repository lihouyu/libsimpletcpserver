# You can modify PREFIX to change install location
PREFIX = /usr/local

all: libstcpsvr

install: all
	cp out/lib/libstcpsvr.so.0.0 $(PREFIX)/lib
	ln -sf $(PREFIX)/lib/libstcpsvr.so.0.0 $(PREFIX)/lib/libstcpsvr.so.0
	ln -sf $(PREFIX)/lib/libstcpsvr.so.0 $(PREFIX)/lib/libstcpsvr.so
	cp src/stcpsvrutil.h $(PREFIX)/include
	cp src/stcpsvr.h $(PREFIX)/include
	cp src/peersock.h $(PREFIX)/include

uninstall:
	rm -f $(PREFIX)/lib/libstcpsvr.so \
		$(PREFIX)/lib/libstcpsvr.so.0 \
		$(PREFIX)/lib/libstcpsvr.so.0.0
	rm -f $(PREFIX)/include/stcpsvrutil.h \
		$(PREFIX)/include/stcpsvr.h \
		$(PREFIX)/include/peersock.h

example: all
	ln -sf $(PWD)/out/lib/libstcpsvr.so.0.0 out/lib/libstcpsvr.so.0
	ln -sf $(PWD)/out/lib/libstcpsvr.so.0 out/lib/libstcpsvr.so
	gcc -Wall -g -I./src -c example/ex_st_svr.c -o example/ex_st_svr.o
	gcc -g -L./out/lib -lstcpsvr example/ex_st_svr.o -o example/ex_st_svr
	gcc -Wall -g -I./src -c example/ex_pt_svr.c -o example/ex_pt_svr.o
	gcc -g -L./out/lib -lstcpsvr example/ex_pt_svr.o -o example/ex_pt_svr

libstcpsvr: stcpsvrutil.o stcpsvr.o
	gcc -g -shared -Wl,-soname,libstcpsvr.so.0 \
		-I./src -lc -lpthread out/obj/stcpsvrutil.o out/obj/stcpsvr.o \
		-o out/lib/libstcpsvr.so.0.0

stcpsvrutil.o: src/stcpsvrutil.c src/stcpsvrutil.h
	gcc -fPIC -Wall -g -I./src -c src/stcpsvrutil.c -o out/obj/stcpsvrutil.o

stcpsvr.o: src/stcpsvr.c src/stcpsvr.h
	gcc -fPIC -Wall -g -I./src -c src/stcpsvr.c -o out/obj/stcpsvr.o

clean:
	rm -f out/lib/* out/obj/*

