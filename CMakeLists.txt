cmake_minimum_required(VERSION 2.8.9)
SET (CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -Wall -pthread -lncurses")

add_executable(colled_server "src/server.c")
add_executable(colled_client "src/client.c")