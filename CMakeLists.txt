cmake_minimum_required(VERSION 2.8.9)
SET (CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -Wall -pthread -lncurses")

include_directories(inc)

add_executable(colled_server 
  src/server.c
  inc/server.h
  src/server_sockets.c
  inc/server_sockets.h
)

add_executable(colled_client 
  src/client.c
  inc/client.h
  src/client_sockets.c
  inc/client_sockets.h
)