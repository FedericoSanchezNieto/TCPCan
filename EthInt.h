#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <arpa/inet.h>
#include <string>
#include <stdlib.h>
#include <string.h>

#define MSGSIZE 500


class EthInt {

 private:
  int sockfd, cc;
  socklen_t addr_in_size;
  std::string htoname; 
  u_short portnum;
  struct sockaddr_in *my_addr, *from, *to;
  struct hostent *toinfo;
  u_long fromaddr;
  u_long toaddr;
  int timeout; 

 public:
  EthInt(std::string name, u_short port, bool Rec, int t = 1);
  int Receive(char *msg);
  void Send(const char *message);

}; 
