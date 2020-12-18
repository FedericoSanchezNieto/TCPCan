#include "EthInt.h"


EthInt::EthInt(std::string name, u_short port, bool Receive, int t){

  portnum = port; 
  htoname = name;

  timeout = t; 

  addr_in_size = sizeof(struct sockaddr_in);

  if( Receive ){
    from = (struct sockaddr_in *)malloc(addr_in_size);
    my_addr = (struct sockaddr_in *)malloc(addr_in_size);

    memset((char *)my_addr,(char)0,addr_in_size);
    my_addr->sin_family = AF_INET;
    my_addr->sin_addr.s_addr = htonl(INADDR_ANY);
    my_addr->sin_port = portnum;
    
    if((sockfd = socket (PF_INET, SOCK_DGRAM, 0)) < 0){
      fprintf(stderr,"Error %d in socket: %s\n",errno,strerror);
      exit(errno);
    };
    
    if(bind(sockfd, (struct sockaddr *)my_addr, addr_in_size) < 0){
      fprintf(stderr,"Error %d in bind: %s\n",errno,strerror);
      if(errno != EADDRINUSE) exit(errno);
    };
   
    struct timeval tv;
    tv.tv_sec = timeout;
    tv.tv_usec = 0;
    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv, sizeof tv)) {
      perror("setsockopt");    
    }

    fprintf(stdout,"Ready to receive\n");
  }
  else {
    to = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
    
    if((toinfo = gethostbyname(htoname.c_str())) == NULL){
      fprintf(stderr,"Error %d in gethostbyname: %s\n",errno,strerror);
      exit(errno);
    };
    toaddr = *(u_long *)toinfo->h_addr_list[0];
    
    addr_in_size = sizeof(struct sockaddr_in);
    memset((char *)to,(char)0,addr_in_size);
    
    to->sin_family = AF_INET;
    to->sin_addr.s_addr = toaddr;
    to->sin_port = /*(htons)*/portnum;
    
    if((sockfd = socket (PF_INET, SOCK_DGRAM, 0)) == -1){
      fprintf(stderr,"Error %d in socket: %s\n",errno,strerror);
      exit(errno);
    };
  }
}


int EthInt::Receive(char *msg){

  msg[0] = '\0';

  if( (cc = recvfrom (sockfd,msg,MSGSIZE,0,(struct sockaddr *)from, &addr_in_size)) == -1){
    if( errno == EAGAIN ) 
      return 1; 
    else 
      return 2;
  };
  
  return 0; 
}


void EthInt::Send(const char *message){
  
  if(sendto(sockfd,message,strlen(message),0,(struct sockaddr *)to, addr_in_size) == -1){
    fprintf(stderr,"Error %d in sendto: %s\n",errno,strerror);
    exit(errno);
  }
  
}
