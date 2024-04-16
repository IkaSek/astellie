/// server.h
/// this file is a part of astellie

#pragma once

#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>

typedef int socket_fd_t;

typedef struct {
  socket_fd_t server_socket;
  socket_fd_t client_sockets[];
} Server;
