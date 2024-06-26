cmake_minimum_required (VERSION 3.12)
project(movepoint)

include(FindPkgConfig)
pkg_search_module(REDIS REQUIRED redis++)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.68 REQUIRED COMPONENTS date_time regex unit_test_framework coroutine system context url)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(movepoint
	engine.cpp
    comment.cpp
	index.cpp
	movepoint.cpp
	redis.cpp
	season.cpp
    login.cpp
    comments.cpp
    records.cpp
    record.cpp
	snippet.cpp
    handler.cpp
    sha1/sha1.c
    session_manager.cpp
    form_part.cpp
)

set_property(TARGET movepoint PROPERTY CXX_STANDARD 20)
target_include_directories(movepoint SYSTEM PUBLIC ${REDIS_INCLUDE_DIRS})
target_link_libraries(movepoint mimetic ${Boost_LIBRARIES} ${REDIS_LIBRARIES} Threads::Threads)
