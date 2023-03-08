default: run

#run_g: movepoint_g
	#LD_LIBRARY_PATH=/lib:/usr/lib:/usr/local/lib ./movepoint_g 127.0.0.1 8080

run: movepoint
	LD_LIBRARY_PATH=/lib:/usr/lib:/usr/local/lib ./movepoint 127.0.0.1 8080 2>&1 | tee -a log

#movepoint_g: movepoint.cpp index.cpp redis.cpp index.h track.h redis.h Makefile
	#g++ -o $@ -std=c++17 -I/home/anek/www/boost `pkg-config --cflags --libs redis++` movepoint.cpp index.cpp redis.cpp -L/home/anek/www/boost/stage/lib -pthread -lboost_system -lboost_context -lboost_url

movepoint: movepoint.o index.o redis.o season1.o season2.o season3.o engine.o snippet.o
	g++ -o $@ `pkg-config --libs redis++` -L/home/anek/www/boost/stage/lib -lboost_system -lboost_context -lboost_url -lredis-cpp -lpthread $^

movepoint.o: movepoint.cpp index.h redis.h Makefile
	g++ -c -o $@ -I/home/anek/www/boost movepoint.cpp -pthread

redis.o: redis.cpp redis.h Makefile
	g++ -c -o $@ -std=c++17 `pkg-config --cflags redis++` redis.cpp -pthread

index.o: index.cpp index.h track.h redis.h Makefile
	g++ -c -o $@ index.cpp -pthread

engine.o: engine.cpp engine.h Makefile
	g++ -c -o $@ engine.cpp -pthread

season1.o: season1.cpp season1.h redis.h Makefile
	g++ -c -o $@ season1.cpp -pthread

season2.o: season2.cpp season2.h redis.h Makefile
	g++ -c -o $@ season2.cpp -pthread

season3.o: season3.cpp season3.h redis.h Makefile
	g++ -c -o $@ season3.cpp -pthread

snippet.o: snippet.cpp snippet.h Makefile
	g++ -c -o $@ snippet.cpp -pthread

movepoint.ru: movepoint.c++
	g++ -o $@ $<

install:
	cp movepoint.ru /usr/local/bin/

list:
	redis-cli lrange movepoint.ru:comments 0 -1

.PHONY: install list default run run_g
