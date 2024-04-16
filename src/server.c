#include <libnet.h>
#include <netinet/in.h>
#include <stdint.h>
#include <string.h>
#define NBT_OWN_ZLIB <zlib.h>
#define NBT_IMPLEMENTATION
#include "server.h"
#include "libnbt.h"

#define BACKLOG 65536

Server serverInit(uint16_t port) {
  uint16_t actual_port = htons(port);
  Server serv = {0};
  serv.server_socket = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in serv_addr;
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = actual_port;
  
  int32_t err;
  if((err = bind(serv.server_socket, (struct sockaddr*) &serv_addr, sizeof(serv_addr))) < 0) {
    fprintf(stderr, "%s:%s: %s", __FILE_NAME__, __FUNCTION__, strerror(err)); 
  }  

  listen(serv.server_socket, BACKLOG);
  
  return serv;
}

void serverHandlePackets(Server serv) {
  accept
}
