default: run

run_g: movepoint_g
	LD_LIBRARY_PATH=/lib:/usr/lib:/usr/local/lib ./movepoint_g 127.0.0.1 8080

run: movepoint
	LD_LIBRARY_PATH=/lib:/usr/lib:/usr/local/lib ./movepoint 127.0.0.1 8080

movepoint_g: movepoint.cpp index.cpp redis.cpp index.h redis.h Makefile
	g++ -v -o $@ `pkg-config --cflags --libs redis++` movepoint.cpp index.cpp redis.cpp -L/home/anek/www/boost/stage/lib -pthread -lboost_system -lboost_context -lboost_url

movepoint: movepoint.o index.o redis.o
	g++ -o $@ `pkg-config --libs redis++` -L/home/anek/www/boost/stage/lib -lboost_system -lboost_context -lboost_url -lredis-cpp -lpthread movepoint.o index.o redis.o

movepoint.o: movepoint.cpp index.h redis.h Makefile
	g++ -c -o $@ -I/home/anek/www/boost movepoint.cpp -pthread

redis.o: redis.cpp redis.h Makefile
	g++ -c -o $@ -std=c++17 `pkg-config --cflags redis++` redis.cpp -pthread

index.o: index.cpp index.h redis.h Makefile
	g++ -c -o $@ index.cpp -pthread

movepoint.ru: movepoint.c++
	g++ -o $@ $<

install:
	cp movepoint.ru /usr/local/bin/

list:
	redis-cli lrange movepoint.ru:comments 0 -1

.PHONY: install list default run run_g
