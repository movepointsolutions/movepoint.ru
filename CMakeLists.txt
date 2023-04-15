cmake_minimum_required (VERSION 3.8)
project(movepoint)

include(FindPkgConfig)
pkg_search_module(REDIS REQUIRED redis++)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.68 REQUIRED COMPONENTS system context url)

add_executable(movepoint
	engine.cpp
	index.cpp
	movepoint.cpp
	redis.cpp
	season1.cpp
	season2.cpp
	season3.cpp
	snippet.cpp
)

target_include_directories(movepoint SYSTEM PUBLIC ${REDIS_INCLUDE_DIRS})
target_link_libraries(movepoint ${Boost_LIBRARIES} ${REDIS_LIBRARIES})
