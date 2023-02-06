default: run

run_g: movepoint_g
	LD_LIBRARY_PATH=/lib:/usr/lib:/usr/local/lib ./movepoint_g 127.0.0.1 8080

run: movepoint
	LD_LIBRARY_PATH=/lib:/usr/lib:/usr/local/lib ./movepoint 127.0.0.1 8080

movepoint_g: movepoint.cpp index.cpp index.h Makefile
	g++ -o $@ `pkg-config --cflags --libs hiredis` movepoint.cpp index.cpp -L/home/anek/www/boost/stage/lib -pthread -lboost_system -lboost_context

movepoint: movepoint.o index.o
	ld -o $@ `pkg-config --libs hiredis` movepoint.o index.o -L/home/anek/www/boost/stage/lib -lboost_system -lboost_context

movepoint.o: movepoint.cpp index.h Makefile
	g++ -c -o $@ `pkg-config --cflags hiredis` -I/home/anek/www/boost movepoint.cpp -pthread

index.o: index.cpp index.h Makefile
	g++ -c -o $@ `pkg-config --cflags hiredis` index.cpp -pthread

movepoint.ru: movepoint.c++
	g++ -o $@ $<

install:
	cp movepoint.ru /usr/local/bin/

.PHONY: install
