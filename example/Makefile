all:
	ln -sf $(PWD)/../out/lib/libstcpsvr.so.0.0 ../out/lib/libstcpsvr.so.0
	ln -sf $(PWD)/../out/lib/libstcpsvr.so.0 ../out/lib/libstcpsvr.so
	gcc -Wall -g -I../src -c ex_st_svr.c
	gcc -g -L../out/lib -lstcpsvr ex_st_svr.o -o ex_st_svr
	gcc -Wall -g -I../src -c ex_pt_svr.c
	gcc -g -L../out/lib -lstcpsvr ex_pt_svr.o -o ex_pt_svr

clean:
	rm -f ex_st_svr.o ex_st_svr ex_pt_svr.o ex_pt_svr \
		$(PWD)/../out/lib/libstcpsvr.so.0 \
		$(PWD)/../out/lib/libstcpsvr.so

